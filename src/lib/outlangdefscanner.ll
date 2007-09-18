%{
/*
 * Copyright (C) 1999-2005, Lorenzo Bettini, http://www.lorenzobettini.it
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
#include "outlangdefparser.h"
#include "outlangdefscanner.h"
#include "fileutil.h"

#include <stack>
#include <stdlib.h>

//#define DEBUG_SCANNER
#ifdef DEBUG_SCANNER
#include <iostream> // for debug
#define DEB(s) std::cerr << s << std::endl;
#define DEB2(s,s2) std::cerr << s << ": " << s2 << std::endl;
#else
#define DEB(s)
#define DEB2(s,s2)
#endif

#define PUSH(s) yy_push_state(s);
#define POP() yy_pop_state();

static std::ostringstream buff;

static void buffer(const char *s);
static void buffer(const char c);
static void buffer_escape(const char *c);
static const std::string *flush_buffer();
static void open_include_file(const char *file);
static void close_include_file();

ParseStruct *outlang_parsestruct = 0;

typedef std::stack<ParseStruct *> ParseStructStack;
static ParseStructStack parsestructstack;

%}

%option prefix="outlangdef_"
%option noyywrap

ws [ ]+
tabs [\t]+

nl \n
cr \r
IDE [a-zA-Z_]([a-zA-Z0-9_])*

STRING \"[^\n"]+\"

%option stack

%s COMMENT_STATE STRING_STATE INCLUDE_STATE TRANSLATION_STATE REGEX_STATE LITERAL_STATE TRANSLATED_STATE

%%

<INITIAL,TRANSLATION_STATE,TRANSLATED_STATE>[ \t] {}

\r {}

<INITIAL,TRANSLATION_STATE>"#" { PUSH(COMMENT_STATE); }
<COMMENT_STATE>[^\n] {}
<COMMENT_STATE>\n { ++(outlang_parsestruct->line);  POP(); }

<INITIAL>"doctemplate" { return DOC_TEMPLATE_T ; }
<INITIAL>"styletemplate" { return STYLE_TEMPLATE_T ; }
<INITIAL>"styleseparator" { return STYLE_SEPARATOR_T ; }
<INITIAL>"bold" { return BOLD_T ; }
<INITIAL>"italics" { return ITALICS_T ; }
<INITIAL>"underline" { return UNDERLINE_T ; }
<INITIAL>"notfixed" { return NOTFIXED_T ; }
<INITIAL>"fixed" { return FIXED_T ; }
<INITIAL>"colormap" { return COLORMAP_T ; }
<INITIAL>"bgcolor" { return BG_COLOR_T ; }
<INITIAL>"color" { return COLOR_T ; }
<INITIAL>"default" { return DEFAULT_T ; }
<INITIAL>"onestyle" { return ONESTYLE_T ; }
<INITIAL>"extension" { return EXTENSION_T ; }
<INITIAL>"anchor" { return ANCHOR_T ; }
<INITIAL>"inline_reference" { return INLINE_REFERENCE_T ; }
<INITIAL>"postline_reference" { return POSTLINE_REFERENCE_T ; }
<INITIAL>"postdoc_reference" { return POSTDOC_REFERENCE_T ; }
<INITIAL>"reference" { return REFERENCE_T ; }
<INITIAL>"lineprefix" { return LINE_PREFIX_T; }
<INITIAL>"translations" { BEGIN(TRANSLATION_STATE); return TRANSLATIONS_T ; }
<INITIAL>"begin" { return BEGIN_T ; }
<INITIAL,TRANSLATION_STATE>"end" { BEGIN(INITIAL); return END_T ; }

<INITIAL>"include"[ \t] { BEGIN(INCLUDE_STATE); }
<INCLUDE_STATE>{STRING} {
  char *file_name = &yytext[1];
  file_name[strlen(file_name)-1] = '\0';

  open_include_file(file_name);

  yypush_buffer_state(yy_create_buffer( outlangdef_in, YY_BUF_SIZE));

  BEGIN(INITIAL);
}

<<EOF>> {
  fclose(outlangdef_in);
  yypop_buffer_state();

  if ( !YY_CURRENT_BUFFER )
    {
      yyterminate();
    }
  else
    close_include_file();
}

<INITIAL>{IDE} { DEB2("KEY",yytext); outlangdef_lval.string = new std::string(yytext) ; return KEY ; }
<INITIAL>"=" { return '=' ; }
<INITIAL>"," { return ',' ; }
<INITIAL>"+" { return '+' ; }

<INITIAL>\" { BEGIN(STRING_STATE) ; }
<STRING_STATE>"\\x"[0-9a-zA-Z][0-9a-zA-Z] {
  string s = &yytext[1];
  s = "0" + s;
  int i = strtol(s.c_str(), (char **)NULL, 0);
  buffer( (char)i ) ;
}
<STRING_STATE>\\\\ {  buffer( yytext ) ; }
<STRING_STATE>"\\\"" {  buffer( "\"" ) ; }
<STRING_STATE>\" { BEGIN(INITIAL) ; outlangdef_lval.string = flush_buffer() ; DEB2("STRINGDEF",outlangdef_lval.string); return STRINGDEF; }
<STRING_STATE>[^\n]|" " {  buffer( yytext ) ; }
<STRING_STATE>\n {  buffer( "\n" ) ; }

<TRANSLATION_STATE,TRANSLATED_STATE>\" { BEGIN(LITERAL_STATE) ; }
<LITERAL_STATE>("*"|"."|"?"|"+"|"("|")"|"{"|"}"|"["|"]"|"^"|"$"|"|") {  buffer_escape( yytext ) ; }
<LITERAL_STATE>\\\\ {  buffer( yytext ) ; }
<LITERAL_STATE>"\\\"" {  buffer( yytext ) ; }
<LITERAL_STATE>\" { BEGIN(TRANSLATION_STATE) ; outlangdef_lval.string = flush_buffer() ; DEB2("STRINGDEF",loutlangdef_lval.string); return REGEXDEF; }
<LITERAL_STATE>[^\n]|" " {  buffer( yytext ) ; }

<TRANSLATION_STATE>\' { BEGIN(REGEX_STATE) ; }
<REGEX_STATE>\\\\ {  buffer( yytext ) ; }
<REGEX_STATE>"\\'" {  buffer( "'" ) ; }
<REGEX_STATE>\' {
    BEGIN(TRANSLATED_STATE) ;
    // entering TRANSLATED_STATE makes sure that 'regex' is used only
    // for specifying the sequence to be translated, and not the translated sequence
    outlangdef_lval.string = flush_buffer() ;
    DEB2("STRINGDEF",outlangdef_lval.string); return REGEXDEF;
}
<REGEX_STATE>[^\n] {  buffer( yytext ) ; }

<INITIAL,TRANSLATION_STATE>{nl} { DEB("NEWLINE"); ++(outlang_parsestruct->line) ; }

<INITIAL>.  { return yytext[0] ; }

%%

void buffer(const char *s)
{
  buff << s;
}

void buffer(const char s)
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

void open_outlang_file_to_scan(const string &path, const string &name)
{
  outlangdef_in = open_data_file_stream(path, name);
}

void open_include_file(const char *name)
{
  string file_name = name;
  string path = outlang_parsestruct->path;

  if (! contains_path(name) &&
      contains_path(outlang_parsestruct->file_name))
    path = get_file_path(outlang_parsestruct->file_name);

  parsestructstack.push(outlang_parsestruct);
  outlang_parsestruct = new ParseStruct(outlang_parsestruct->path, file_name);
  open_outlang_file_to_scan(path.c_str(), file_name.c_str());
}

void close_include_file()
{
  delete outlang_parsestruct;
  outlang_parsestruct = parsestructstack.top();
  parsestructstack.pop();
}
