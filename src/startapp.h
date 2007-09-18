/*
 * Copyright (C) 1999, 2000, 2001  Lorenzo Bettini <http://www.lorenzobettini.it>
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

#ifndef _STARTAPP_H
#define _STARTAPP_H

#include "langmap.h"
#include "textstyles.h"

class PreFormatter;
class DocGenerator;
class GeneratorFactory;

class StartApp
{
 protected:
  char *inputFileName, *outputFileName; /* what we're reading  */
  DocGenerator *docgenerator;
  PreFormatter *preformatter;
  LangMapPtr langmap;
  LangMapPtr outlangmap;
  TextStylesPtr textstyles;
  GeneratorFactory *generator_factory;

  int entire_doc; // we want a real html doc
  short verbose;
  char *cssUrl;
  int use_css; // Use CSS instead of font styles
  int is_cgi;   // set if in CGI mode (and therefore has to add CGI-header)
  bool gen_version;
  bool generate_line_num;
  bool generate_ref;

  std::string data_dir;
  std::string lang_file;
  std::string source_language;

  virtual void print_copyright();
  virtual void print_reportbugs();
  virtual void print_version();

  int processFile(const std::string &inputFileName, const std::string &outputFileName,
    const std::string &file_extension = "") ;

  /**
   * Try to infer the input language by inspecting the file
   * @ref LanguageInfer
   * @param inputFileName The name of the file to inspect
   * @return the inferred language or an empty string upon failure
   */
  std::string inferLang(const std::string &inputFileName);

 public:
  StartApp();
  virtual ~StartApp();

  virtual int start(int argc, char * argv[]);
} ;

#endif /* _STARTAPP_H */
