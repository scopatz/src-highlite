%{
/*
 * Copyright (C) 1999-2007 Lorenzo Bettini, http://www.lorenzobettini.it
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

#include <stdlib.h>

#include "stylekey.h"

#include "generatorfactory.h"
#include "styleparser.h"
#include "my_sstream.h"
#include "messages.h"
#include "parsestyles.h"

static std::ostringstream buff;

extern int line ;

//#define DEBUG_SCANNER
#ifdef DEBUG_SCANNER
#include <iostream> // for debug
#define DEB(s) std::cerr << s << std::endl;
#define DEB2(s,s2) std::cerr << s << ": " << s2 << std::endl;
#else
#define DEB(s)
#define DEB2(s,s2)
#endif


static void buffer(const char *s);
static const std::string *flush_buffer();

%}

%option prefix="stylesc_"
%option noyywrap

ws [ ]+
tabs [\t]+

nl \n
cr \r
IDE [a-zA-Z_]([a-zA-Z0-9_])*

STRING \"[^\"\n]*\"

%s COMMENT_STATE STRING_STATE

%%

{ws}|{tabs} {}

\r {}

<INITIAL>"//" { BEGIN(COMMENT_STATE); }
<COMMENT_STATE>[^\n] {}
<COMMENT_STATE>\n { ++line;  BEGIN(INITIAL); }

<INITIAL>"green"|"red"|"darkred"|"blue"|"brown"|"pink"|"yellow"|"cyan"|"purple"|"orange"|"brightorange"|"darkgreen"|"brightgreen"|"black"|"teal"|"gray"|"darkblue" { stylesc_lval.string = new std::string(yytext) ; return COLOR ; }

<INITIAL>\#[a-fA-F0-9]{6} {
  const std::string wrong = yytext ;
  parseStyleError("use of direct colors has changed", false);
  parseStyleError("use double quoted syntax: \"" +  wrong + "\" instead of " + wrong);
  exit(EXIT_FAILURE);
  return COLOR ;
}

<INITIAL>"bgcolor" { return BODY_BG_COLOR ; }

<INITIAL>"bg" { return BG_T ; }

<INITIAL>"b" { stylesc_lval.flag = ISBOLD ; return BOLD ; }
<INITIAL>"i" { stylesc_lval.flag = ISITALIC ; return ITALICS ; }
<INITIAL>"u" { stylesc_lval.flag = ISUNDERLINE ; return UNDERLINE ; }
<INITIAL>"f" { stylesc_lval.flag = ISFIXED; return FIXED; }
<INITIAL>"nf" { stylesc_lval.flag = ISNOTFIXED; return NOTFIXED; }
<INITIAL>"noref" { stylesc_lval.flag = ISNOREF; return NOREF; }

<INITIAL>"," { return ',' ; }
<INITIAL>";" { return ';' ; }
<INITIAL>":" { return ':' ; }

<INITIAL>{IDE} { stylesc_lval.string = new std::string(yytext) ; return KEY ; }

<INITIAL>\" { BEGIN(STRING_STATE); DEB("STRING_STATE"); buffer( yytext ) ; }
<STRING_STATE>\\\\ {  buffer( yytext ) ; }
<STRING_STATE>"\\\"" {  buffer( "\"" ) ; }
<STRING_STATE>\" { BEGIN(INITIAL) ; buffer( yytext ) ; DEB("END STRING_STATE"); stylesc_lval.string = flush_buffer() ; return STRINGDEF; }
<STRING_STATE>[^\n]|" " {  buffer( yytext ) ; }
<STRING_STATE>\n {  buffer( "\n" ) ; }

\n { ++line ; }

<INITIAL>.  { /* anything else will generate a parsing error */ return yytext[0] ; }

%%

void buffer(const char *s)
{
  DEB2("BUFFERING ", s);
  buff << s;
}

const std::string *flush_buffer()
{
  const std::string *ret = new std::string(buff.str());
  buff.str("");
  return ret;
}

