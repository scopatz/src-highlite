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
#include "utils.h"

using std::cerr;

static int yyparse() ;
static void yyerror( char *s ) ;

// line is defined in styleparser

// to generate the generator for each language element
static GeneratorFactory *generatorFactory;

static void updateBgColor(const std::string &c);

// for the background color of the entire output
static string bodyBgColor;

extern int stylecsssc_lex() ;
extern FILE *stylecsssc_in ;
extern int stylecsssc_lex_destroy  (void);

/// the global pointer to style constant for a specific element
static StyleConstantsPtr currentStyleConstants;
/// the global pointer to the current color
static string currentColor;
/// the global pointer to the current bg color
static string currentBGColor;

%}

%union {
  int tok ; /* command */
  const std::string * string ; /* string : id, ... */
  StyleConstant flag ;
  StyleConstants *styleconstants;
  KeyList *keylist;
} ;

%token <flag> BOLD ITALICS UNDERLINE FIXED NOTFIXED NOREF
%token <string> KEY COLOR BG_COLOR STRINGDEF BG_STRINGDEF

%type <keylist> keylist

%%

stylefile : { /* allow empty files */ }
    | statements
    ;

statements : statements statement
    | statement
    ;

statement : option
    ;

option : keylist
             {
               printSequence( $1 ) ;
               printMessage_noln( ": " ) ;
               currentStyleConstants = StyleConstantsPtr(new StyleConstants);
               currentColor = "";
               currentBGColor = "";
             }
         optionspecs ';'
             {
               printMessage_noln(" color: " + currentColor + " ") ;
               if (currentBGColor != "")
                  printMessage_noln(" bg color: " + currentBGColor + " ") ;
               printMessage("");

               KeyType key;
               KeyList *keylist = $1;
               for (KeyList::const_iterator it = keylist->begin(); it != keylist->end(); ++it) {
                key = *it;
                // check whether it's the body specification
                if (Utils::tolower(key) == "body") {
                  updateBgColor(currentBGColor);

                  // notice that for text style specification for the body, the background
                  // is assumed for the entire document and not for the normal text
                  // following the semantics of css

                  // avoid adding an empty style definition for normal
                  if (currentColor != "" || currentStyleConstants->size()) {
                    if (!generatorFactory->createGenerator(NORMAL, currentColor, "", currentStyleConstants)) {
                      parseStyleError(key);
                      yyerror("already defined");
                    }
                  }
                } else {
                      if (!generatorFactory->createGenerator(key, currentColor, currentBGColor, currentStyleConstants)) {
                      parseStyleError(key);
                      yyerror("already defined");
                  }
                }
               }
               delete keylist;
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

optionspecs : {}
      | optionspecs optionspec
      ;

optionspec : color
      | bgcolor
      | styleconstant
      ;

color : COLOR
        {
          currentColor = *$1;
          delete $1;
        }
      | STRINGDEF
        {
          currentColor = *$1;
          delete $1;
        }
      ;

bgcolor : BG_COLOR
        {
          currentBGColor = *$1;
          delete $1;
        }
      | BG_STRINGDEF
        {
          currentBGColor = *$1;
          delete $1;
        }
      ;

styleconstant : BOLD { printMessage_noln( " bold" ) ; currentStyleConstants->push_back(ISBOLD); }
      | ITALICS { printMessage_noln( " italics" ) ; currentStyleConstants->push_back(ISITALIC); }
      | UNDERLINE { printMessage_noln( " underline" ) ; currentStyleConstants->push_back(ISUNDERLINE); }
      | FIXED { printMessage_noln( " fixed" ) ; currentStyleConstants->push_back(ISFIXED); }
      | NOTFIXED { printMessage_noln( " notfixed" ) ; currentStyleConstants->push_back(ISNOTFIXED); }
      | NOREF { printMessage_noln( " noref" ) ; currentStyleConstants->push_back(ISNOREF); }
      ;

%%

// string current_file; defined in styleparser

extern string current_file;

void parseCssStyles(const string &path, const string &name, GeneratorFactory *genFactory,
                   string &bodyBgColor_)
{
  generatorFactory = genFactory;
  // opens the file for yylex
  stylecsssc_in = open_data_file_stream(path, name);

  current_file = (path.size() ? path + "/" : "") + name;

  printMessage_noln( "Parsing ", cerr ) ;
  printMessage_noln (current_file, cerr);
  printMessage( " file ...", cerr ) ;

  bodyBgColor = "";

  yyparse() ;

  bodyBgColor_ = bodyBgColor;

  printMessage( "Parsing done!", cerr ) ;
  fclose(stylecsssc_in);

  // release scanner memory
  stylecsssc_lex_destroy();
}

void
yyerror( char *s )
{
  parseStyleError(s);
}

void updateBgColor(const std::string &c)
{
  if (bodyBgColor != "")
    yyerror("bgcolor already defined");
  else
    bodyBgColor = c;
}
