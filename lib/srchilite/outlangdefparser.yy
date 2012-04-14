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
#include <string.h>
#include <iostream>
#include <string>

#include "parsestruct.h"
#include "outlangdefscanner.h"
#include "outlangdefparserfun.h"
#include "textstyles.h"
#include "parserexception.h"
#include "ioexception.h"

using std::cerr;
using std::string;

using namespace srchilite;

static void yyerror( const char *s ) ;
static void yyerror( const string &s ) ;

/// the buffer for storing errors
static string errorBuffer;

TextStylesPtr textstyles;
string start_doc, end_doc;
ColorMapPtr colorMap;
CharTranslatorPtr charTranslator;

const char *reference_vars[] = {"linenum", "infilename", "infile", "outfile", 0};
const char *anchor_vars[] = {"linenum", "infilename", "infile", 0};

/// used to record that the error is due to an included file not found
static bool includedFileNotFound = false;

%}

%union {
  int tok ; /* command */
  bool booloption ;
  const std::string * string ; /* string : id, ... */
  int flag ;
};

%token <tok> BEGIN_T END_T DOC_TEMPLATE_T NODOC_TEMPLATE_T STYLE_TEMPLATE_T STYLE_SEPARATOR_T
%token <tok> BOLD_T ITALICS_T UNDERLINE_T COLOR_T BG_COLOR_T FIXED_T NOTFIXED_T
%token <tok> COLORMAP_T DEFAULT_T ONESTYLE_T TRANSLATIONS_T EXTENSION_T ANCHOR_T
%token <tok> REFERENCE_T INLINE_REFERENCE_T POSTLINE_REFERENCE_T POSTDOC_REFERENCE_T
%token <string> KEY STRINGDEF REGEXDEF LINE_PREFIX_T LINENUM_T WRONG_INCLUDE_FILE


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
NODOC_TEMPLATE_T STRINGDEF STRINGDEF END_T
{
    textstyles->noDocTemplate = DocTemplate(*$2, *$3);
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
  LINENUM_T STRINGDEF
{
  textstyles->linenum = *$2;
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
| WRONG_INCLUDE_FILE {
            // this token is used by the scanner to signal an error
            // in opening an include file
            includedFileNotFound = true;
            yyerror("cannot open include file " + *$1);
            delete $1;
            YYERROR;
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
  errorBuffer = s;
}

void
yyerror( const string &s )
{
  yyerror(s.c_str());
}

namespace srchilite {

TextStylesPtr
parse_outlang_def()
{
  return parse_outlang_def("", "stdin");
}

TextStylesPtr
parse_outlang_def(const char *path, const char *name)
{
  includedFileNotFound = false;
  outlang_parsestruct = ParseStructPtr(new ParseStruct(path, name));
  textstyles = TextStylesPtr(new TextStyles);
  colorMap = ColorMapPtr(new ColorMap);
  charTranslator = CharTranslatorPtr(new CharTranslator);
  
  errorBuffer = "";
  int result = 1;
  bool fileNotFound = false;
  
  try {
  	if (strcmp(name, "stdin") != 0)
      open_outlang_file_to_scan(path, name);
  } catch (IOException &e) {
    errorBuffer = e.message;
    fileNotFound = true;
  }

  if (!fileNotFound)
     result = outlangdef_parse();
  
  if (result != 0 && ! fileNotFound) {
  	  // make sure the input file is closed
	  close_outlangdefinputfile();
	  // close it before clearing the scanner
  }
  
  // release scanner memory
  clear_outlangdefscanner ();
  
  if (result != 0 || errorBuffer.size()) {
  	if (fileNotFound || includedFileNotFound) {
	  throw ParserException(errorBuffer);
  	} else {
	  ParserException e(errorBuffer, outlang_parsestruct.get());
	  throw e;
	}
  }

  return textstyles;
}

}
