%{
/*
 * Copyright (C) 1999, 2000, Lorenzo Bettini, http://www.lorenzobettini.it
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

#include <stdlib.h>

#include "styles.h"

#include "optparser.h"
#include "my_sstream.h"
#include "messages.h"
#include "parsestyles.h"

static std::ostringstream buff;

extern int line ;

#define PUSH(s) yy_push_state(s);
#define POP() yy_pop_state();

static void buffer(const char *s);
static const std::string *flush_buffer();

%}

%option prefix="opsc_"
%option noyywrap

ws [ ]+
tabs [\t]+

nl \n
cr \r
IDE [a-zA-Z_]([a-zA-Z0-9_])*

STRING \"[^\"\n]*\"

%option stack

%s COMMENT_STATE STRING_STATE

%%

{ws}|{tabs} {}

\r {}

<INITIAL>"//" { PUSH(COMMENT_STATE); }
<COMMENT_STATE>[^\n] {}
<COMMENT_STATE>\n { ++line;  POP(); }

<INITIAL>"green" |
"red" |
"darkred" |
"blue" |
"brown" |
"pink" |
"yellow" |
"cyan" |
"purple" |
"orange" |
"brightorange" |
"darkgreen" |
"brightgreen" |
"black" |
"teal" |
"gray" |
"darkblue" { opsc_lval.string = new std::string(yytext) ; return COLOR ; }

<INITIAL>\#[a-fA-F0-9]{6} {
  const std::string wrong = yytext ;
  parseStyleError("use of direct colors has changed");
  parseStyleError("use double quoted syntax: \"" +  wrong + "\" instead of " + wrong);
  exit(EXIT_FAILURE);
  return COLOR ;
}

<INITIAL>"b" { opsc_lval.flag = ISBOLD ; return BOLD ; }
<INITIAL>"i" { opsc_lval.flag = ISITALIC ; return ITALICS ; }
<INITIAL>"u" { opsc_lval.flag = ISUNDERLINE ; return UNDERLINE ; }
<INITIAL>"f" { opsc_lval.flag = ISFIXED; return FIXED; }
<INITIAL>"nf" { opsc_lval.flag = ISNOTFIXED; return NOTFIXED; }
<INITIAL>"noref" { opsc_lval.flag = ISNOREF; return NOREF; }

<INITIAL>"," { return ',' ; }
<INITIAL>";" { return ';' ; }

<INITIAL>{IDE} { opsc_lval.string = new std::string(yytext) ; return KEY ; }

<INITIAL>\" { BEGIN(STRING_STATE); buffer( yytext ) ; }
<STRING_STATE>\\\\ {  buffer( yytext ) ; }
<STRING_STATE>"\\\"" {  buffer( "\"" ) ; }
<STRING_STATE>\" { BEGIN(INITIAL) ; buffer( yytext ) ; opsc_lval.string = flush_buffer() ; return STRINGDEF; }
<STRING_STATE>[^\n]|" " {  buffer( yytext ) ; }
<STRING_STATE>\n {  buffer( "\n" ) ; }

\n { ++line ; }

<INITIAL>.  { return yytext[0] ; }

%%

void buffer(const char *s)
{
  buff << s;
}

const std::string *flush_buffer()
{
  const std::string *ret = new std::string(buff.str());
  buff.str("");
  return ret;
}

