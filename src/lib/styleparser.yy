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

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

#include "generatorfactory.h"
#include "colors.h"
#include "keys.h"
#include "messages.h"
#include "parsestyles.h"
#include "fileutil.h"
#include "stylekey.h"

using std::cerr;

static int yyparse() ;
static void yyerror( char *s ) ;

int line = 1 ;

extern int stylesc_lex() ;
extern FILE *stylesc_in ;
extern int stylesc_lex_destroy  (void);

static string bodyBgColor;

static void updateBgColor(const std::string *);

// to generate the generator for each language element
static GeneratorFactory *generatorFactory;

%}

%union {
  int tok ; /* command */
  const std::string * string ; /* string : id, ... */
  StyleConstant flag ;
  StyleConstants *styleconstants;
  KeyList *keylist;
} ;

%token <flag> BOLD ITALICS UNDERLINE FIXED NOTFIXED NOREF
%token <string> KEY COLOR BG_COLOR STRINGDEF BODY_BG_COLOR
%token <tok> BG_T

%type <flag> value
%type <styleconstants> stylevalues values
%type <string> color bgcolor bodybgcolor
%type <keylist> keylist

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
                 printSequence( $1 ) ;
                 printMessage_noln( ": " ) ;
                 printMessage_noln( ($2 ? *$2 : "") ) ;
                 printMessage_noln( " bg: " ) ;
                 printMessage_noln( ($3 ? *$3 : "") ) ;
             }
         stylevalues ';'
             {
               KeyType key;
               KeyList *keylist = $1;
               StyleConstantsPtr stylevalues = StyleConstantsPtr($5);
               for (KeyList::const_iterator it = keylist->begin(); it != keylist->end(); ++it) {
                key = *it;
                if (!generatorFactory->createGenerator(key, ($2 ? *$2 : ""), ($3 ? *$3 : ""), stylevalues)) {
                  parseStyleError(key);
                  yyerror("already defined");
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

stylevalues : { $$ = 0 ; printMessage( " (no options) " ) ; }
            | values { $$ = $1; printMessage(""); }
            ;

values : values ',' value { $$ = $1; $$->push_back($3) ; }
       | value { $$ = new StyleConstants; $$->push_back($1); }
       ;

value : BOLD { printMessage_noln( " - bold" ) ; $$ = ISBOLD ; }
      | ITALICS { printMessage_noln( " - italics" ) ; $$ = ISITALIC ; }
      | UNDERLINE { printMessage_noln( " - underline" ) ; $$ = ISUNDERLINE ; }
      | FIXED { printMessage_noln( " - fixed" ) ; $$ = ISFIXED ; }
      | NOTFIXED { printMessage_noln( " - notfixed" ) ; $$ = ISNOTFIXED ; }
      | NOREF { printMessage_noln( " - noref" ) ; $$ = ISNOREF ; }
      ;

%%

string current_file;

void
parseStyles(const string &path, const string &name, GeneratorFactory *genFactory,
           string &bodyBgColor_)
{
  generatorFactory = genFactory;

  // opens the file for yylex
  stylesc_in = open_data_file_stream(path, name);

  current_file = (path.size() ? path + "/" : "") + name;

  printMessage_noln( "Parsing ", cerr ) ;
  printMessage_noln (current_file, cerr);
  printMessage( " file ...", cerr ) ;

  bodyBgColor = "";

  yyparse() ;

  bodyBgColor_ = bodyBgColor;

  printMessage( "Parsing done!", cerr ) ;
  fclose(stylesc_in);

  // free scanner memory
  stylesc_lex_destroy();
}

void
yyerror( char *s )
{
  parseStyleError(s);
}

void parseStyleError(const std::string &error, bool exit)
{
	if (exit)
  		exitError(current_file, line, error);
  	else {
  		printError(current_file, line, error);
  	}
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

