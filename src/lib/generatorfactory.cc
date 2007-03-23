/*
 * Copyright (C) 1999-2007  Lorenzo Bettini <http://www.lorenzobettini.it>
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

// generatorfactory.cc

#include "generatorfactory.h"

#include "keys.h"
#include "textgenerator.h"
#include "textstyles.h"
#include "textstylebuilder.h"
#include "refgeneratormap.h"

// global
#include "maingeneratormap.h"

GeneratorFactory::GeneratorFactory(TextStylesPtr tstyles,
                                   PreFormatter *pf,
                                   bool gen_ref,
    const string &_ctags_file, RefPosition position,
    bool optimizations) :
    textStyles(tstyles), preformatter(pf),
  generate_references(gen_ref),
  ctags_file(_ctags_file), refposition(position),
  noOptimizations(optimizations)
{
  generatormap = createGeneratorMap();
  generatormap->setNoOptimizations(noOptimizations);
}

GeneratorFactory::~ GeneratorFactory()
{
  if (generatormap)
    delete generatormap;
}

GeneratorMap *
GeneratorFactory::createGeneratorMap()
{
  if (generate_references)
    return new RefGeneratorMap(preformatter, ctags_file,
      textStyles->refstyle, refposition);

  return new GeneratorMap(preformatter);
}

string GeneratorFactory::preprocessColor(const string &color)
{
  if ( color[0] == '"' && color[color.size()-1] == '"')
    return color.substr(1, color.size()-2);
  else
    return textStyles->colorMap->getColor (color);
}

bool GeneratorFactory::createGenerator(const string &key, const string &color,
    const string &bgcolor, StyleConstantsPtr styleconstants)
{
  if (generatormap->hasGenerator(key))
    return false;
  
  if (! textStyles->onestyle.empty()) {
    generatormap->addGenerator (key, new TextGenerator(textStyles->onestyle.subst_style(key)));
    return true;
  }

  TextStyleBuilder textStyleBuilder(textStyles->starting_template, textStyles->style_separator);

  textStyleBuilder.start();

  if (styleconstants.get()) {
    for (StyleConstantsIterator it = styleconstants->begin(); it != styleconstants->end(); ++it) {
      switch( *it ){
        case ISBOLD:
          textStyleBuilder.add(textStyles->bold);
          break;
        case ISITALIC:
          textStyleBuilder.add(textStyles->italics);
          break;
        case ISUNDERLINE:
          textStyleBuilder.add(textStyles->underline);
          break;
        case ISFIXED:
          textStyleBuilder.add(textStyles->fixed);
          break;
        case ISNOTFIXED:
          textStyleBuilder.add(textStyles->notfixed);
          break;
        case ISNOREF:
          generatormap->addNoReference(key);
          break;
      }
    }
  }

  if ( color.size () ) {
    textStyleBuilder.add(textStyles->color.subst_style(preprocessColor(color)));
  }

  if ( bgcolor.size () ) {
    textStyleBuilder.add(textStyles->bg_color.subst_style(preprocessColor(bgcolor)));
  }

  TextStyle style = textStyleBuilder.end();

  generatormap->addGenerator(key, new TextGenerator(style));
  return true;
}

void GeneratorFactory::addDefaultGenerator()
{
  TextGenerator *defaultGenerator = generatormap->hasGenerator(NORMAL);
  
  if (!defaultGenerator) {
  
    if (textStyles->onestyle.empty())
      defaultGenerator = new TextGenerator();
    else
      defaultGenerator = new TextGenerator(textStyles->onestyle.subst_style(NORMAL));
    
    generatormap->addGenerator (NORMAL, defaultGenerator);
  }
  
  generatormap->setDefaultGenerator(defaultGenerator);
}

