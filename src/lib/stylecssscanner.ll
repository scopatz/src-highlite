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
#include <string.h>

#include "generatorfactory.h"
#include "stylekey.h"

#include "stylecssparser.h"
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

%}

%option prefix="stylecsssc_"
%option noyywrap

ws [ ]+
tabs [\t]+

nl \n
cr \r
IDE [a-zA-Z_]([a-zA-Z0-9_])*

VALUE [^\n\r:;[:blank:]]+

STRING \"[^\"\n]*\"

%s COMMENT_STATE MULTI_COMMENT_STATE STRING_STATE CSS_SELECTOR CSS_PROPERTIES CSS_COLOR CSS_BG_COLOR CSS_FONT_WEIGHT CSS_FONT_STYLE CSS_FONT_FAMILY CSS_TEXT_DECORATION

%%

{ws}|{tabs} {}

\r {}

"/*" { BEGIN(MULTI_COMMENT_STATE); }
<MULTI_COMMENT_STATE>[^\n] {}
<MULTI_COMMENT_STATE>\n { ++line;  BEGIN(INITIAL); }


<CSS_SELECTOR>"," { return ',' ; }
<CSS_SELECTOR>{IDE} { stylecsssc_lval.string = new std::string(yytext) ; return KEY ; }

\n { ++line ; }

<INITIAL>\.  {
  BEGIN(CSS_SELECTOR) ;
  DEB("CSS SELECTOR");
}
<INITIAL>[bB][oO][dD][yY]  {
  BEGIN(CSS_SELECTOR) ;
  DEB("BODY CSS SELECTOR");
  stylecsssc_lval.string = new std::string(yytext) ;
  return KEY;
}

<CSS_SELECTOR>\.  {
  // in case of comma separated selectors
  DEB("CSS SELECTOR");
}
<CSS_SELECTOR>"{" {
  BEGIN(CSS_PROPERTIES);
  DEB("CSS PROPERTIES");
}
<CSS_PROPERTIES>"color" {
  BEGIN(CSS_COLOR);
  DEB("CSS COLOR");
}
<CSS_COLOR>"green"|"red"|"darkred"|"blue"|"brown"|"pink"|"yellow"|"cyan"|"purple"|"orange"|"brightorange"|"darkgreen"|"brightgreen"|"black"|"teal"|"gray"|"darkblue" {
  BEGIN(CSS_PROPERTIES);
  stylecsssc_lval.string = new std::string(yytext) ;
  DEB2("CSS COLOR", yytext);
  return COLOR ;
}
<CSS_COLOR>[#[:alnum:]]+ {
  BEGIN(CSS_PROPERTIES);
  DEB2("CSS COLOR", yytext);
  /*
    we need to add the " in order to make source-highlight realize
    that this is a direct color specification
  */
  stylecsssc_lval.string = new std::string("\"" + std::string(yytext) + "\"");
  return STRINGDEF;
}
<CSS_PROPERTIES>"background-color" {
  BEGIN(CSS_BG_COLOR);
  DEB("CSS BACKGROUND COLOR");
}
<CSS_BG_COLOR>"green"|"red"|"darkred"|"blue"|"brown"|"pink"|"yellow"|"cyan"|"purple"|"orange"|"brightorange"|"darkgreen"|"brightgreen"|"black"|"teal"|"gray"|"darkblue" {
  BEGIN(CSS_PROPERTIES);
  stylecsssc_lval.string = new std::string(yytext) ;
  DEB2("CSS BG COLOR", yytext);
  return BG_COLOR ;
}
<CSS_BG_COLOR>[#[:alnum:]]+ {
  BEGIN(CSS_PROPERTIES);
  DEB2("CSS BG COLOR", yytext);
  /*
    we need to add the " in order to make source-highlight realize
    that this is a direct color specification
  */
  stylecsssc_lval.string = new std::string("\"" + std::string(yytext) + "\"");
  return BG_STRINGDEF;
}
<CSS_PROPERTIES>"font-weight" {
  BEGIN(CSS_FONT_WEIGHT);
  DEB("CSS FONT WEIGHT");
}
<CSS_FONT_WEIGHT>{VALUE} {
  BEGIN(CSS_PROPERTIES);
  if (strcmp(yytext, "bold") == 0) {
    DEB("CSS BOLD");
    stylecsssc_lval.flag = ISBOLD ;
    return BOLD ;
  }
  DEB2("discarding not handled value", yytext);
}
<CSS_PROPERTIES>"font-style" {
  BEGIN(CSS_FONT_STYLE);
  DEB("CSS FONT STYLE");
}
<CSS_FONT_STYLE>{VALUE} {
  BEGIN(CSS_PROPERTIES);
  if (strcmp(yytext, "italic") == 0) {
    DEB("CSS ITALIC");
    stylecsssc_lval.flag = ISITALIC ;
    return ITALICS ;
  }
  DEB2("discarding not handled value", yytext);
}
<CSS_PROPERTIES>"font-family" {
  BEGIN(CSS_FONT_FAMILY);
  DEB("CSS FONT FAMILY");
}
<CSS_FONT_FAMILY>{VALUE} {
  BEGIN(CSS_PROPERTIES);
  if (strcmp(yytext, "monospace") == 0) {
    DEB("CSS FIXED");
    stylecsssc_lval.flag = ISFIXED ;
    return FIXED ;
  }
  DEB2("discarding not handled value", yytext);
}
<CSS_PROPERTIES>"text-decoration" {
  BEGIN(CSS_TEXT_DECORATION);
  DEB("CSS TEXT DECORATION");
}
<CSS_TEXT_DECORATION>{VALUE} {
  BEGIN(CSS_PROPERTIES);
  if (strcmp(yytext, "underline") == 0) {
    DEB("CSS UNDERLINE");
    stylecsssc_lval.flag = ISUNDERLINE ;
    return UNDERLINE ;
  }
  DEB2("discarding not handled value", yytext);
}
<CSS_PROPERTIES>"}" {
  BEGIN(INITIAL);
  DEB("CSS END PROPERTIES");
  /*
    we must return ; since this is the terminator of a style option
    so we simulate it in case of css files
  */
  return ';' ;
}
<CSS_COLOR,CSS_BG_COLOR,CSS_FONT_WEIGHT,CSS_FONT_STYLE,CSS_FONT_FAMILY,CSS_TEXT_DECORATION>":"|";"|[\t]|[[:blank:]] {
  /* discard other characters */
  DEB2("CSS discarding", yytext);
}
<CSS_PROPERTIES>. {
  /* discard other properties */
  DEB2("CSS PROPERTIES discarding", yytext);
}

<INITIAL>.  { return yytext[0] ; }

%%

