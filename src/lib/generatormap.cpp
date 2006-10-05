//
// C++ Implementation: generatormap
//
// Description:
//
//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2004
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include "generatormap.h"
#include "textgenerator.h"
#include "preformatter.h"
#include "mainoutputbuffer.h"

using namespace std;

GeneratorMap::GeneratorMap(PreFormatter *pf) :
  default_generator (new TextGenerator),
  preformatter(pf), noOptimizations(false)
{
}

GeneratorMap::~GeneratorMap()
{
  for (MapType::const_iterator it = generatormap.begin(); it != generatormap.end(); ++it)
    delete it->second;
  delete default_generator;
}

void
GeneratorMap::setDefaultGenerator(TextGenerator *gen)
{
    if (default_generator)
        delete default_generator;
    default_generator = gen;
}

void
GeneratorMap::addGenerator(const std::string &elem, TextGenerator *gen)
{
  generatormap[elem] = gen;
}

TextGenerator *
GeneratorMap::getGenerator(const string &elem)
{
  MapType::const_iterator it = generatormap.find(elem);
  if (it == generatormap.end())
    {
      // create a copy of the prototype and substitute the style.
      TextGenerator *missing = new TextGenerator(*default_generator);
      missing->subst_style(elem);

      generatormap[elem] = missing;
      return missing;
    }

  return it->second;
}

void
GeneratorMap::addNoReference(const std::string &elem)
{
  noreferences.insert(elem);
}

bool
GeneratorMap::isNoReference(const std::string &elem) const
{
  return (noreferences.find(elem) != noreferences.end());
}

const string
GeneratorMap::generateString( const std::string &elem, const std::string &s ,
  const FileInfo *p )
{
  return getGenerator(elem)->generateEntire(preformatter->preformat(s));
}

void
GeneratorMap::generateEntire( const std::string &elem, const std::string &s,
  const FileInfo *p )
{
  if (noOptimizations) {
    // we generate the element right now, since during debugging
    // we want to be very responsive
    if (s.size())
      output(generateString(elem, s, p));

    return;
  }

  // otherwise we optmize output generation: delay formatting a specific
  // element until we deal with another element; this way strings that belong
  // to the same element are formatted using only one tag: e.g.,
  // <comment>/* mycomment */</comment>
  // instead of
  // <comment>/*</comment><comment>mycomment</comment><comment>*/</comment>
  if (elem == current_elem) {
    elem_buffer << s;
  } else {
    // first format the buffered string
    const string toformat = elem_buffer.str();
    if (toformat.size())
      output(generateString(current_elem, toformat, p));

    // then start a new buffer
    elem_buffer.str("");
    elem_buffer << s;
    current_elem = elem;
    current_file_info = p;
  }
}

void
GeneratorMap::generateNL( const std::string &text )
{
  // first format the buffered string
  flush();

  string preformat_text = preformatter->preformat(text);

  if (preformat_text == text)
    preformat_text = "\n";

  outputbuffer->output_ln(preformat_text);
}

void
GeneratorMap::flush()
{
  const string &remainder = elem_buffer.str();
  if (remainder.size()) {
    output(generateString(current_elem, remainder, current_file_info));
    elem_buffer.str("");
    current_elem = "";
    // each line is handled separately
  }
}

void
GeneratorMap::output(const string &s)
{
  outputbuffer->output(s);
}
