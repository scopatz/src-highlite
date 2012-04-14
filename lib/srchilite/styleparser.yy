%{
/*
 * Copyright (C) 1999-2007 Lorenzo Bettini <http://www.lorenzobettini.it>
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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

#include "formatterfactory.h"
#include "colors.h"
#include "keys.h"
#include "parsestyles.h"
#include "fileutil.h"
#include "stylekey.h"
#include "parserexception.h"
#include "settings.h"

using std::cerr;
using std::string;

using namespace srchilite;

static int yyparse() ;
static void yyerror( const char *s ) ;
static void yyerror( const string &s ) ;

int line = 1 ;

extern int stylesc_lex() ;
extern FILE *stylesc_in ;
extern int stylesc_lex_destroy  (void);

static string bodyBgColor;

static void updateBgColor(const std::string *);

// to generate the formatter for each language element
static FormatterFactory *formatterFactory;

/// where we store possible errors
static string errorBuffer;

%}

%union {
  int tok ; /* command */
  const std::string * string ; /* string : id, ... */
  srchilite::StyleConstant flag ;
  srchilite::StyleConstants *styleconstants;
  srchilite::KeyList *keylist;
} ;

%token <flag> BOLD ITALICS UNDERLINE FIXED NOTFIXED NOREF
%token <string> KEY COLOR BG_COLOR STRINGDEF
%token <tok> BG_T BODY_BG_COLOR

%type <flag> value
%type <styleconstants> stylevalues values
%type <string> color bgcolor
%type <keylist> keylist

%destructor {
	if ($$)
	  delete $$;
} keylist KEY COLOR BG_COLOR STRINGDEF color bgcolor

%%

stylefile : { /* allow empty files */ }
    | statements
    ;

statements : statements statement
    | statement
    ;

statement : option
    | bodybgcolor
    ;

option : keylist color bgcolor
             {
                 //printSequence( $1 ) ;
                 //printMessage_noln( ": " ) ;
                 //printMessage_noln( ($2 ? *$2 : "") ) ;
                 //printMessage_noln( " bg: " ) ;
                 //printMessage_noln( ($3 ? *$3 : "") ) ;
             }
         stylevalues ';'
             {
               KeyType key;
               KeyList *keylist = $1;
               StyleConstantsPtr stylevalues = StyleConstantsPtr($5);
               for (KeyList::const_iterator it = keylist->begin(); it != keylist->end(); ++it) {
                key = *it;
                if (!formatterFactory->createFormatter(key, ($2 ? *$2 : ""), ($3 ? *$3 : ""), stylevalues)) {
                  errorBuffer = "already defined " + *it;
                  //yyerror(alreadydef);

                  delete keylist;
                  if ($2)
                   delete $2;
                  if ($3)
                   delete $3;

                  YYERROR;
                }
               }
               delete keylist;
               if ($2)
                delete $2;
               if ($3)
                delete $3;
             }
       ;

keylist : keylist ',' KEY
            {
              $1->push_back(*$3);
              $$ = $1;
              delete $3;
            }
        | KEY
            {
              $$ = new KeyList;
              $$->push_back(*$1);
              delete $1;
            }
  ;

color : { $$ = 0; }
      | COLOR { $$ = $1;}
      | STRINGDEF { $$ = $1; }
      ;

bgcolor : { $$ = 0; }
      | BG_T ':' COLOR { $$ = $3;}
      | BG_T ':' STRINGDEF { $$ = $3; }
      ;

bodybgcolor : BODY_BG_COLOR COLOR ';' { updateBgColor($2); }
      | BODY_BG_COLOR STRINGDEF ';' { updateBgColor($2); }
      ;

stylevalues : { $$ = 0 ; }
            | values { $$ = $1; }
            ;

values : values ',' value { $$ = $1; $$->push_back($3) ; }
       | value { $$ = new StyleConstants; $$->push_back($1); }
       ;

value : BOLD { $$ = ISBOLD ; }
      | ITALICS { $$ = ISITALIC ; }
      | UNDERLINE { $$ = ISUNDERLINE ; }
      | FIXED { $$ = ISFIXED ; }
      | NOTFIXED { $$ = ISNOTFIXED ; }
      | NOREF { $$ = ISNOREF ; }
      ;

%%

string current_file;

namespace srchilite {

void
parseStyles(const string &name, FormatterFactory *genFactory,
           string &bodyBgColor_) {
  parseStyles(Settings::retrieveDataDir(), name, genFactory, bodyBgColor_);
}

void
parseStyles(const string &path, const string &name, FormatterFactory *genFactory,
           string &bodyBgColor_)
{
  formatterFactory = genFactory;
  errorBuffer = "";
  int result = 1;
  line = 1;

  // opens the file for yylex
  stylesc_in = open_data_file_stream(path, name);

  if (contains_path(name))
    current_file = name;
  else
    current_file = (path.size() ? path + "/" : "") + name;

  bodyBgColor = "";

  result = yyparse() ;

  bodyBgColor_ = bodyBgColor;

  fclose(stylesc_in);

  // free scanner memory
  stylesc_lex_destroy();
  
  if (result != 0 || errorBuffer.size()) {
  	throw ParserException(errorBuffer, current_file, line);
  }
}

}

void
yyerror( const char *s )
{
  errorBuffer = s;
}

void yyerror(const string &s) {
  yyerror(s.c_str());
}

void parseStyleError(const std::string &error)
{
	yyerror(error);
}

void updateBgColor(const std::string *c)
{
  if (bodyBgColor != "")
    yyerror("bgcolor already defined");
  else
    bodyBgColor = *c;

  // we don't need it anymore
  delete c;
}
