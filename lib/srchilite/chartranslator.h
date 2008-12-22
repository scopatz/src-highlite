/*
 * Copyright (C) 1999, 2000, 2001  Lorenzo Bettini, http://www.lorenzobettini.it
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

// base class for char translators

#ifndef _CHARTRANSLATOR_H
#define _CHARTRANSLATOR_H

#define NUM_OF_CHARS 256

#include <string>
#include <boost/regex.hpp>

#include "preformatter.h"

class CharTranslator : public PreFormatter
{
 protected:
   unsigned int counter;
   std::string translation_exp; // what to translate
   std::string translation_format; // translate into
   boost::regex *reg_exp;
   bool bol; // whether we are at the beginning of a new line

   virtual const std::string doPreformat(const std::string &text);

 public:
  CharTranslator(PreFormatterPtr f = PreFormatterPtr());
  virtual ~CharTranslator();

  void set_translation(const std::string &s1, const std::string &s2);

  const std::string toString() const
  {
    return translation_exp + " -> " + translation_format;
  }
} ;

typedef boost::shared_ptr<CharTranslator> CharTranslatorPtr;

#endif // _CHARTRANSLATOR_H
