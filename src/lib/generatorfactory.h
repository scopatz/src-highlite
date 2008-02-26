/*
** Copyright (C) 1999-2007 Lorenzo Bettini <http://www.lorenzobettini.it>
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
**
*/

// abstract factory for generators

#ifndef GENERATORFACTORY_H
#define GENERATORFACTORY_H

#include <string>
#include <list>
#include <boost/shared_ptr.hpp>

#include "textstyles.h"
#include "refposition.h"

typedef enum { ISBOLD=1, ISITALIC, ISUNDERLINE, ISFIXED, ISNOTFIXED, ISNOREF } StyleConstant;
typedef std::list<StyleConstant> StyleConstants;
typedef boost::shared_ptr<StyleConstants> StyleConstantsPtr;
typedef StyleConstants::const_iterator StyleConstantsIterator;

using std::string;

class TextGenerator;
class PreFormatter;
class TextFormatter;
class OutputBuffer;

class GeneratorFactory
{
 protected:
  /// contains all the styles for formatting
  TextStylesPtr textStyles;
  /// to preformat text
  PreFormatter *preformatter;
  /// whether to generate references using ctags
  bool generate_references;
  string ctags_file;
  RefPosition refposition;
  /// whether to turn off optimizations for generating output (default false)
  bool noOptimizations;
  /// the main text formatter
  TextFormatter *textformatter;
  OutputBuffer *outputbuffer;

  TextFormatter *createTextFormatter();

 public:
  GeneratorFactory(TextStylesPtr tstyles, PreFormatter *pf, OutputBuffer *b,
                   bool gen_references,
                   const string &ctags_file, RefPosition position,
                   bool optimizations);
  
  ~GeneratorFactory();

  /**
   * Creates a generator for the specific language element (identifed by
   * key) with the passed style parameters
   * 
   * @param key 
   * @param color 
   * @param bgcolor 
   * @param styleconstants 
   * @return false if a generator for the specific key is already present
   */
  bool createGenerator(const string &key, const string &color,
    const string &bgcolor, StyleConstantsPtr styleconstants);
  
  /**
   * Creates a generator for key1, if not already present, that has the same
   * style as the generator for key2
   * 
   * @return false if the generator for key1 is already present, or there's
   * no generator for key2
   */
  bool createMissingGenerator(const string &key1, const string &key2);
  
  /**
   * Adds the generator for the normal style if not already present.
   * 
   * This must be called after all the generators for the language elements
   */
  void addDefaultGenerator();

  /**
   * Check whether the color must be translated with the color map or
   * left as it is (in that case, remove the ")
   * @param color
   * @return
     */
  string preprocessColor(const string &color);
  
  TextFormatter *getTextFormatter() { return textformatter; }
};

#endif // GENERATORFACTORY_H
