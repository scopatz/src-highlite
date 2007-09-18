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
#include <string.h>
#include <iostream>
#include <string>

#include "messages.h"
#include "parsestruct.h"
#include "outlangdefscanner.h"
#include "outlangdefparserfun.h"
#include "textstyles.h"

using std::cerr;
using std::string;

static void yyerror( const char *s ) ;
//static void yyerror( const string &s ) ;

TextStylesPtr textstyles;
string start_doc, end_doc;
ColorMapPtr colorMap;
CharTranslatorPtr charTranslator;

const char *reference_vars[] = {"linenum", "infilename", "infile", "outfile", 0};
const char *anchor_vars[] = {"linenum", "infilename", "infile", 0};

%}

%union {
  int tok ; /* command */
  bool booloption ;
  const std::string * string ; /* string : id, ... */
  int flag ;
};

%token <tok> BEGIN_T END_T DOC_TEMPLATE_T STYLE_TEMPLATE_T STYLE_SEPARATOR_T
%token <tok> BOLD_T ITALICS_T UNDERLINE_T COLOR_T BG_COLOR_T FIXED_T NOTFIXED_T
%token <tok> COLORMAP_T DEFAULT_T ONESTYLE_T TRANSLATIONS_T EXTENSION_T ANCHOR_T
%token <tok> REFERENCE_T INLINE_REFERENCE_T POSTLINE_REFERENCE_T POSTDOC_REFERENCE_T
%token <string> KEY STRINGDEF REGEXDEF LINE_PREFIX_T


%%

outputlang : outputlangdefs
;

outputlangdefs : outputlangdefs outputlangdef
  | outputlangdef
;

outputlangdef : DOC_TEMPLATE_T STRINGDEF STRINGDEF END_T
{
    textstyles->docTemplate = DocTemplate(*$2, *$3);
    delete $2;
    delete $3;
}
|
  STYLE_TEMPLATE_T STRINGDEF
{
    textstyles->starting_template = *$2;
    delete $2;
}
|
  STYLE_SEPARATOR_T STRINGDEF
{
    textstyles->style_separator = *$2;
    delete $2;
}
|
  BOLD_T STRINGDEF
{
  textstyles->bold = *$2;
  delete $2;
}
|
  ITALICS_T STRINGDEF
{
  textstyles->italics = *$2;
  delete $2;
}
|
  UNDERLINE_T STRINGDEF
{
  textstyles->underline = *$2;
  delete $2;
}
|
  FIXED_T STRINGDEF
{
  textstyles->fixed = *$2;
  delete $2;
}
|
  NOTFIXED_T STRINGDEF
{
  textstyles->notfixed = *$2;
  delete $2;
}
|
  COLOR_T STRINGDEF
{
  textstyles->color = *$2;
  delete $2;
}
|
  BG_COLOR_T STRINGDEF
{
  textstyles->bg_color = *$2;
  delete $2;
}
|
  ONESTYLE_T STRINGDEF
{
  textstyles->onestyle = *$2;
  delete $2;
}
|
  EXTENSION_T STRINGDEF
{
  textstyles->file_extension = *$2;
  delete $2;
}
|
  ANCHOR_T STRINGDEF
{
  textstyles->refstyle.anchor = TextStyle(*$2, anchor_vars);
  delete $2;
}
|
  LINE_PREFIX_T STRINGDEF
{
  textstyles->line_prefix = *$2;
  delete $2;
}
|
  REFERENCE_T STRINGDEF
{
  if (textstyles->refstyle.inline_reference.empty())
    textstyles->refstyle.inline_reference = TextStyle(*$2, reference_vars);
  if (textstyles->refstyle.postline_reference.empty())
    textstyles->refstyle.postline_reference = TextStyle(*$2, reference_vars);
  if (textstyles->refstyle.postdoc_reference.empty())
    textstyles->refstyle.postdoc_reference = TextStyle(*$2, reference_vars);
  delete $2;
}
|
  INLINE_REFERENCE_T STRINGDEF
{
  textstyles->refstyle.inline_reference = TextStyle(*$2, reference_vars);
  delete $2;
}
|
  POSTLINE_REFERENCE_T STRINGDEF
{
  textstyles->refstyle.postline_reference = TextStyle(*$2, reference_vars);
  delete $2;
}
|
  POSTDOC_REFERENCE_T STRINGDEF
{
  textstyles->refstyle.postdoc_reference = TextStyle(*$2, reference_vars);
  delete $2;
}
|
  colormap
{
  textstyles->colorMap = colorMap;
}
|
  chartranslator
{
  textstyles->charTranslator = charTranslator;
}
;

colormap : COLORMAP_T colormapentries END_T
;

colormapentries : colormapentries colormapentry
|
colormapentry
;

colormapentry : STRINGDEF STRINGDEF
{
  (*colorMap)[*$1] = *$2;
  delete $1;
  delete $2;
}
|
  DEFAULT_T STRINGDEF
{
  colorMap->setDefault(*$2);
  delete $2;
}
;

chartranslator : TRANSLATIONS_T translations END_T
;

translations : translations translation
|
translation
;

translation : REGEXDEF REGEXDEF
{
  charTranslator->set_translation(*$1, *$2);
  delete $1;
  delete $2;
}

%%

extern int outlangdef_lex_destroy (void);

void
yyerror( const char *s )
{
  exitError(s, outlang_parsestruct);
}

TextStylesPtr
parse_outlang_def()
{
  outlang_parsestruct = new ParseStruct("", "stdin");
  textstyles = TextStylesPtr(new TextStyles);
  colorMap = ColorMapPtr(new ColorMap);
  charTranslator = CharTranslatorPtr(new CharTranslator);
  outlangdef_parse();
  delete outlang_parsestruct;
  outlang_parsestruct = 0;

  // release scanner memory
  outlangdef_lex_destroy ();

  return textstyles;
}

TextStylesPtr
parse_outlang_def(const char *path, const char *name)
{
  outlang_parsestruct = new ParseStruct(path, name);
  textstyles = TextStylesPtr(new TextStyles);
  colorMap = ColorMapPtr(new ColorMap);
  charTranslator = CharTranslatorPtr(new CharTranslator);
  open_outlang_file_to_scan(path, name);
  outlangdef_parse();
  delete outlang_parsestruct;
  outlang_parsestruct = 0;

  // release scanner memory
  outlangdef_lex_destroy ();

  return textstyles;
}

TextStylesPtr
parse_outlang_def_file(const char *path, const char *name)
{
  // the struct stores the path for further includes but...
  outlang_parsestruct = new ParseStruct(path, name);
  // when we open the first file the path is not used
  textstyles = TextStylesPtr(new TextStyles);
  colorMap = ColorMapPtr(new ColorMap);
  charTranslator = CharTranslatorPtr(new CharTranslator);
  open_outlang_file_to_scan("", name);
  outlangdef_parse();
  delete outlang_parsestruct;
  outlang_parsestruct = 0;

  // release scanner memory
  outlangdef_lex_destroy ();

  return textstyles;
}

