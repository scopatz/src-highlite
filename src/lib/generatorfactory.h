/*
** Copyright (C) 1999, 2000, 2002 Lorenzo Bettini <http://www.lorenzobettini.it>
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
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
#include "textstyles.h"
#include "refgeneratormap.h"

using std::string;

class Style;
class Styles;
class TextGenerator;
class PreFormatter;

class GeneratorFactory
{
 protected:
  TextStylesPtr textStyles; // contains all the styles for formatting
  Styles *styles;
  PreFormatter *preformatter; // to preformat text
  bool generate_references; // whether to generate references using ctags
  string ctags_file;
  RefPosition refposition;

  TextGenerator *createGenerator(const string &key);
  TextGenerator *createGenerator(const Style *style);
  TextGenerator *createDefaultGenerator();

  GeneratorMap *createGeneratorMap();

 public:
  GeneratorFactory(TextStylesPtr tstyles, Styles *sts, PreFormatter *pf,
                   bool gen_references,
                   const string &ctags_file, RefPosition position);
  ~GeneratorFactory();
  void createGenerators();
};

#endif // GENERATORFACTORY_H
