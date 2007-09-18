%{
/*
 * Copyright (C) 1999-2007, Lorenzo Bettini, http://www.lorenzobettini.it
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

#include "my_sstream.h"
#include "langdefparser.h"
#include "langdefscanner.h"
#include "fileutil.h"
#include "regexpreprocessor.h"
#include "stringdef.h"
#include "messages.h"

#include <stack>

//#define DEBUG_SCANNER
#ifdef DEBUG_SCANNER
#include <iostream> // for debug
#define DEB(s) std::cerr << s << std::endl;
#define DEB2(s,s2) std::cerr << s << ": " << s2 << std::endl;
#else
#define DEB(s)
#define DEB2(s,s2)
#endif

static std::ostringstream buff;

static void buffer(const char *s);
static void buffer_escape(const char *c);
static const std::string *flush_buffer();
static StringDef *flush_buffer_preproc();
static void open_include_file(const char *file);
static void close_include_file();

ParseStruct *parsestruct = 0;

typedef std::stack<ParseStruct *> ParseStructStack;
static ParseStructStack parsestructstack;

void
updateTokenInfo()
{
  langdef_lloc.first_line = parsestruct->line ;
}


%}

%option prefix="langdef_"
%option noyywrap

ws [ ]+
tabs [\t]+

nl \n
cr \r
IDE [a-zA-Z_]([a-zA-Z0-9_])*

STRING \"[^\n"]+\"

%s COMMENT_STATE STRING_STATE REGEXP_STATE REGEXP_NOPREPROC_STATE INCLUDE_STATE

%%

<INITIAL,COMMENT_STATE,INCLUDE_STATE>[ \t] {}

\r {}

<INITIAL>"#" { BEGIN(COMMENT_STATE); }
<COMMENT_STATE>[^\n] {}
<COMMENT_STATE>\n { ++(parsestruct->line);  BEGIN(INITIAL); }

<INITIAL>"begin" { return BEGIN_T ; }
<INITIAL>"end" { return END_T ; }
<INITIAL>"environment" { return ENVIRONMENT_T; }
<INITIAL>"state" { return STATE_T; }
<INITIAL>"multiline" { return MULTILINE_T; }
<INITIAL>"delim" { return DELIM_T; }
<INITIAL>"start" { return START_T; }
<INITIAL>"escape" { return ESCAPE_T; }
<INITIAL>"nested" { return NESTED_T; }
<INITIAL>"exitall" { return EXIT_ALL; }
<INITIAL>"exit" { return EXIT_T; }
<INITIAL>"vardef" { return VARDEF_T; }
<INITIAL>"redef" { return REDEF_T; }
<INITIAL>"subst" { return SUBST_T; }
<INITIAL>"nonsensitive" { return NONSENSITIVE_T; }

<INITIAL>"include" { BEGIN(INCLUDE_STATE); }
<INCLUDE_STATE>{STRING} {
  DEB2("inclusion of ", yytext);
  
  char *file_name = &yytext[1];
  file_name[strlen(file_name)-1] = '\0';

  open_include_file(file_name);

  yypush_buffer_state(yy_create_buffer( langdef_in, YY_BUF_SIZE));

  BEGIN(INITIAL);
}

<<EOF>> {
  DEB("END OF FILE");
  
  fclose(langdef_in);
  yypop_buffer_state();

  if ( !YY_CURRENT_BUFFER )
    {
      yyterminate();
    }
  else
    close_include_file();
}

<INITIAL>"$"{IDE} { DEB2("VAR",yytext); langdef_lval.string = new std::string(&yytext[1]) ; return VARUSE ; }
<INITIAL>"@{"[[:digit:]]"}" { 
	DEB2("BACKREFVAR",yytext);
	langdef_lval.string = new std::string(yytext); 
	return BACKREFVAR ; 
}
<INITIAL>{IDE} { DEB2("KEY",yytext); langdef_lval.string = new std::string(yytext) ; updateTokenInfo(); return KEY ; }
<INITIAL>"=" { return '=' ; }
<INITIAL>"," { return ',' ; }
<INITIAL>"+" { return '+' ; }
<INITIAL>"(" { updateTokenInfo(); return '(' ; }
<INITIAL>")" { return ')' ; }

<INITIAL>\" { BEGIN(STRING_STATE) ; }
<STRING_STATE>("*"|"."|"?"|"+"|"("|")"|"{"|"}"|"["|"]"|"^"|"$"|"@") {  buffer_escape( yytext ) ; }
<STRING_STATE>\\\| {  buffer( yytext ) ; }
<STRING_STATE>\\\\ {  buffer( yytext ) ; }
<STRING_STATE>\\[[:digit:]] {  
	printError(parsestruct->file_name, parsestruct->line, "backreferences are not allowed") ;
	exitError(parsestruct->file_name, parsestruct->line, "use backreferences only inside ` `") ; 
	}
<STRING_STATE>"\\\"" {  buffer( yytext ) ; }
<STRING_STATE>\" { BEGIN(INITIAL) ; langdef_lval.string = flush_buffer() ; DEB2("STRINGDEF",langdef_lval.string); return STRINGDEF; }
<STRING_STATE>[^\n] {  buffer( yytext ) ; }

<INITIAL>\' { BEGIN(REGEXP_STATE) ; }
<REGEXP_STATE>"@" {  buffer_escape( yytext ) ; }
<REGEXP_STATE>\\\\ {  buffer( yytext ) ; }
<REGEXP_STATE>\\[[:digit:]] {  
	printError(parsestruct->file_name, parsestruct->line, "backreferences are not allowed") ;
	exitError(parsestruct->file_name, parsestruct->line, "use backreferences only inside ` `") ; 
	}
<REGEXP_STATE>"\\'" {  buffer( "'" ) ; }
<REGEXP_STATE>\' { BEGIN(INITIAL) ; langdef_lval.stringdef = flush_buffer_preproc() ; DEB2("REGEXPDEF",langdef_lval.string); return REGEXPDEF; }
<REGEXP_STATE>[^\n] {  buffer( yytext ) ; }

<INITIAL>` { BEGIN(REGEXP_NOPREPROC_STATE) ; }
<REGEXP_NOPREPROC_STATE>"@" {  buffer_escape( yytext ) ; }
<REGEXP_NOPREPROC_STATE>\\\\ {  buffer( yytext ) ; }
<REGEXP_NOPREPROC_STATE>"\\`" {  buffer( "'" ) ; }
<REGEXP_NOPREPROC_STATE>` { BEGIN(INITIAL) ; langdef_lval.string = flush_buffer() ; DEB2("REGEXPNOPREPROCDEF",langdef_lval.string); return REGEXPNOPREPROC; }
<REGEXP_NOPREPROC_STATE>[^\n] {  buffer( yytext ) ; }


<INITIAL>{nl} { DEB("NEWLINE"); ++(parsestruct->line) ; }

<INITIAL>.  { return yytext[0] ; }

%%

void buffer(const char *s)
{
  buff << s;
}

void buffer_escape(const char *s)
{
  buff << "\\" << s;
}

const std::string *flush_buffer()
{
  const std::string *ret = new std::string(buff.str());
  buff.str("");
  return ret;
}

StringDef *flush_buffer_preproc()
{
  StringDef *sd = new StringDef(RegexPreProcessor::preprocess(buff.str()), buff.str());
  buff.str("");
  return sd;
}

void _open_file_to_scan(const string &path, const string &name)
{
  langdef_in = open_data_file_stream(path, name);
}

void open_file_to_scan(const string &path, const string &name)
{
  _open_file_to_scan(path, name);
  langdef_restart(langdef_in);
}

void open_include_file(const char *name)
{
  string file_name = name;
  string path = parsestruct->path;

  if (! contains_path(name) &&
      contains_path(parsestruct->file_name))
    path = get_file_path(parsestruct->file_name);

  parsestructstack.push(parsestruct);
  parsestruct = new ParseStruct(parsestruct->path, file_name);
  _open_file_to_scan(path.c_str(), file_name.c_str());
}

void close_include_file()
{
  delete parsestruct;
  parsestruct = parsestructstack.top();
  parsestructstack.pop();
}
