/*
 * Copyright (C) 1999, 2000, 2001, 2002  Lorenzo Bettini <http://www.lorenzobettini.it>
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

#include "styles.h"
#include "keys.h"
#include "textgenerator.h"
#include "textstyles.h"
#include "textstylebuilder.h"
#include "refgeneratormap.h"

// global
#include "maingeneratormap.h"

GeneratorFactory::GeneratorFactory(TextStylesPtr tstyles, Styles *sts,
    PreFormatter *pf,
    bool gen_ref,
    const string &_ctags_file, RefPosition position) :
  textStyles(tstyles), styles(sts), preformatter(pf),
  generate_references(gen_ref),
  ctags_file(_ctags_file), refposition(position)
{
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

void
GeneratorFactory::createGenerators()
{
  generatormap = createGeneratorMap();

  TextGenerator *text_gen;
  for (Styles::const_iterator it = styles->begin(); it != styles->end(); ++it)
    {
      text_gen = createGenerator(*it);
      generatormap->addGenerator((*it)->GetName(), text_gen);
    }

  // set the normal generator as the default generator
  TextGenerator *normal = createDefaultGenerator ();
  generatormap->setDefaultGenerator(normal);
}

TextGenerator *
GeneratorFactory::createDefaultGenerator()
{
  if (textStyles->onestyle.empty())
    return createGenerator (NORMAL);
  else
    return new TextGenerator(textStyles->onestyle);
}

TextGenerator *
GeneratorFactory::createGenerator( const string &key )
{
  const Style *tag = styles->GetStyle( key ) ;

  if ( ! tag ) // no options
    return new TextGenerator ;

  return createGenerator(tag);
}

TextGenerator *
GeneratorFactory::createGenerator( const Style *tag )
{
  if (! textStyles->onestyle.empty())
    return new TextGenerator(textStyles->onestyle.subst_style(tag->GetName()));

  TextStyleBuilder textStyleBuilder(textStyles->starting_template, textStyles->style_separator);

  textStyleBuilder.start();

  StyleConstantsPtr tagStyles = tag->getStyleConstants();
  if (tagStyles.get()) {
    for (StyleConstantsIterator it = tagStyles->begin(); it != tagStyles->end(); ++it) {
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
          generatormap->addNoReference(tag->GetName());
          break;
      }
    }
  }

  const string &color = tag->GetColor() ;
  if ( color.size () )
  {
    string c;
    if ( color[0] == '"' && color[color.size()-1] == '"')
      c = color.substr(1, color.size()-2);
    else
      c = textStyles->colorMap->getColor (color);

    textStyleBuilder.add(textStyles->color.subst_style(c));
  }

  TextStyle style = textStyleBuilder.end();

  return new TextGenerator(style);
}
