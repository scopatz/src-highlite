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
#include "utils.h"
#include "parserexception.h"

using std::cerr;

using namespace srchilite;

extern int line;

static int yyparse() ;
static void yyerror( const char *s ) ;

// line is defined in styleparser

// to generate the formatter for each language element
static FormatterFactory *formatterFactory;

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
%token <string> KEY COLOR BG_COLOR STRINGDEF BG_STRINGDEF

%type <keylist> keylist

%destructor {
	if ($$)
	  delete $$;
} keylist KEY COLOR BG_COLOR STRINGDEF

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
               //printSequence( $1 ) ;
               //printMessage_noln( ": " ) ;
               currentStyleConstants = StyleConstantsPtr(new StyleConstants);
               currentColor = "";
               currentBGColor = "";
             }
         optionspecs ';'
             {
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
                    if (!formatterFactory->createFormatter(NORMAL, currentColor, "", currentStyleConstants)) {
                      errorBuffer = "already defined " NORMAL;
                      delete keylist;
                      YYERROR;
                    }
                  }
                } else {
                  if (!formatterFactory->createFormatter(key, currentColor, currentBGColor, currentStyleConstants)) {
                      errorBuffer = "already defined " + key;
                      delete keylist;
                      YYERROR;
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

styleconstant : BOLD { currentStyleConstants->push_back(ISBOLD); }
      | ITALICS { currentStyleConstants->push_back(ISITALIC); }
      | UNDERLINE { currentStyleConstants->push_back(ISUNDERLINE); }
      | FIXED { currentStyleConstants->push_back(ISFIXED); }
      | NOTFIXED { currentStyleConstants->push_back(ISNOTFIXED); }
      | NOREF { currentStyleConstants->push_back(ISNOREF); }
      ;

%%

// string current_file; defined in styleparser

extern string current_file;

void
yyerror( const char *s )
{
  errorBuffer = s;
}

void updateBgColor(const std::string &c)
{
  if (bodyBgColor != "")
    yyerror("bgcolor already defined");
  else
    bodyBgColor = c;
}

namespace srchilite {

void parseCssStyles(const string &path, const string &name, FormatterFactory *genFactory,
                   string &bodyBgColor_)
{
  formatterFactory = genFactory;
  errorBuffer = "";
  int result = 1;
  line = 1;

  // opens the file for yylex
  stylecsssc_in = open_data_file_stream(path, name);

  if (contains_path(name))
    current_file = name;
  else
    current_file = (path.size() ? path + "/" : "") + name;

  bodyBgColor = "";

  result = yyparse() ;

  bodyBgColor_ = bodyBgColor;

  fclose(stylecsssc_in);

  // release scanner memory
  stylecsssc_lex_destroy();
  
  if (result != 0 || errorBuffer.size()) {
  	throw ParserException(errorBuffer, current_file, line);
  }
}

}
