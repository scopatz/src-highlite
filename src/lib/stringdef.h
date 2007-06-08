//
// C++ Interface: StringDef
//
// Description: a string definition that is used by all the language elements.
//
//
// Author: Lorenzo Bettini, 1999-2007 <http://www.lorenzobettini.it>
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
class StringDef {
private:
    /// the actual content
    std::string stringdef;
    /// the original representation (without any preprocessing)
    std::string orig;

public:
    /**
     * constructs a StringDef and store also the original representation
     * @param s the actual content
     * @param o the original representation
     */
    StringDef(const std::string &s, const std::string &o) :
        stringdef(s), orig(o) {
    }

    StringDef(const std::string &s) :
        stringdef(s) {
    }

    const std::string toString() const {
        return stringdef;
    }

    /**
     * return the original representation (this is useful for printing errors)
     * @return the original representation
     */
    const std::string toStringOriginal() const {
        return orig;
    }

    static StringDef *concat(const StringDef *s1, const StringDef *s2) {
        return new StringDef(s1->stringdef + s2->stringdef);
    }
};

typedef std::list<StringDef *> StringDefsBase;

class StringDefs : public StringDefsBase {
public:
    ~StringDefs() {
        for (StringDefsBase::iterator it = begin(); it != end(); ++it)
            delete *it;
    }
};

#endif
