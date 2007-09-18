/*
 * Copyright (C) 1999, 2000, 2001, 2002, 2003  Lorenzo Bettini, http://www.lorenzobettini.it
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

#ifndef COLORMAP_H
#define COLORMAP_H

#include <map>
#include <string>
#include <boost/shared_ptr.hpp>
#include "my_sstream.h"

using std::map;
using std::string;
using std::ostringstream;

class ColorMap : public map<string, string>
{
 protected:
  string default_color;

 public:
  void setDefault(const string &d) { default_color = d; }
  const string getColor(const string &key)
  {
    const_iterator it = find (key);
    if (it == end ())
      return default_color;
    else
      return it->second;
  }
  const string toString() const
  {
    ostringstream s;
    for (const_iterator it = begin(); it != end(); ++it)
      s << "[" << it->first << "]=" << it->second << "\n";
    s << "default=" << default_color;
    return s.str();
  }
};

typedef boost::shared_ptr<ColorMap> ColorMapPtr;

#endif // COLORMAP_H
