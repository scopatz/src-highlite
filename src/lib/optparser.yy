%{
/*
 * Copyright (C) 1999, 2000, 2001 Lorenzo Bettini <http://www.lorenzobettini.it>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
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

#include "my_sstream.h"

#include "styles.h"
#include "colors.h"
#include "keys.h"
#include "messages.h"
#include "parsestyles.h"
#include "fileutil.h"

using std::cerr;

static int yyparse() ;
static void yyerror( char *s ) ;

int line = 1 ;

static void add_style(Styles *styles, Style *t);
static Styles *parsed_styles = 0;

extern int opsc_lex() ;
extern FILE *opsc_in ;

%}

%union {
  int tok ; /* command */
  const std::string * string ; /* string : id, ... */
  StyleConstant flag ;
  Style *style ;
  Styles *styles ;
  StyleConstants *styleconstants;
} ;

%token <flag> BOLD ITALICS UNDERLINE FIXED NOTFIXED NOREF
%token <string> KEY COLOR STRINGDEF

%type <style> option
%type <styles> options
%type <flag> value
%type <styleconstants> stylevalues values
%type <string> color

%%

globalstyles : options { parsed_styles = $1; }
;

options : options option { add_style( $1, $2 ) ; }
        | option { $$ = new Styles() ; $$->AddStyle( $1 ) ;  }
        ;

option : KEY color
             {
                 printMessage_noln( *$1 ) ;
                 printMessage_noln( ": " ) ;
                 printMessage_noln( ($2 ? *$2 : "") ) ;
             }
         stylevalues ';'
             {
               if ($2)
                  $$ = new Style( *$1, *$2 ) ;
               else
                  $$ = new Style( *$1 ) ;
               $$->setStyles(StyleConstantsPtr($4)) ;
               delete $1;
               if ($2)
                delete $2;
             }
       ;

color : { $$ = 0; }
      | COLOR { $$ = $1;}
      | STRINGDEF { $$ = $1; }
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

Styles *
parseStyles(const string &path, const string &name)
{
  // opens the file for yylex
  opsc_in = open_data_file_stream(path, name);

  current_file = (path.size() ? path + "/" : "") + name;

  printMessage_noln( "Parsing ", cerr ) ;
  printMessage_noln (current_file, cerr);
  printMessage( " file ...", cerr ) ;
  parsed_styles = 0;
  yyparse() ;
  printMessage( "Parsing done!", cerr ) ;
  fclose(opsc_in);
  return parsed_styles;
}

void
yyerror( char *s )
{
  parseStyleError(s);
  exit(EXIT_FAILURE);
}

void parseStyleError(const std::string &error)
{
  ostringstream str ;
  str << current_file << ":" << line << ": " << error;
  printError( str.str(), cerr ) ;
}

void
add_style(Styles *styles, Style *t)
{
  if (! styles->AddStyle(t))
  {
    yyerror("already defined");
  }
}
