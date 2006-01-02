//
// C++ Interface: %{MODULE}
//
// Description: 
//
//
// Author: %{AUTHOR} <%{EMAIL}>, (C) %{YEAR}
//
// Copyright: See COPYING file that comes with this distribution
//
//

#ifndef TOSTRINGCOLLECTION_H
#define TOSTRINGCOLLECTION_H

#include <string>
#include "my_sstream.h"

template <class T>
const std::string toStringCollection(const T *collection, char sep = ' ')
{
  std::ostringstream buf;
  
  for (typename T::const_iterator it = collection->begin();
       it != collection->end(); )
  {
    buf << (*it)->toString();
    if (++it != collection->end())
      buf << sep;
  }
  
  return buf.str();
}

#endif // TOSTRINGCOLLECTION_H
