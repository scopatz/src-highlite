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
#ifndef STRINGDEF_H
#define STRINGDEF_H

#include <string>
#include <list>

/**
represent a string for a language element

@author Lorenzo Bettini
*/
class StringDef
{
  private:
    std::string stringdef;
    
  public:
    StringDef(const char *s);
    StringDef(const std::string &s);

    ~StringDef();
    
    const std::string toString() const { return stringdef; }
    static StringDef *concat(const StringDef *s1, const StringDef *s2)
    { return new StringDef(s1->stringdef + s2->stringdef); }
};

typedef std::list<StringDef *> StringDefsBase;

class StringDefs : public StringDefsBase
{
  public:
    ~StringDefs() {
      for (StringDefsBase::iterator it = begin(); it != end(); ++it)
        delete *it;
    }
};

#endif
