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

class StringDefs;

/**
 represent a string for a language element

 @author Lorenzo Bettini
 */
class StringDef {
private:
    /// @brief the actual content
    std::string stringdef;
    /// @brief the original representation (without any preprocessing)
    std::string orig;
    /// @brief whether the string was specified with double quotes
    bool doubleQuotedString;
    /// @brief whether this is only a back reference to a matched subexpression
    bool isbackref;

public:
    /**
     * constructs a StringDef and store also the original representation
     * @param s the actual content
     * @param o the original representation
     */
    StringDef(const std::string &s, const std::string &o) :
        stringdef(s), orig(o), doubleQuotedString(false), isbackref(false) {
    }

    /**
     * constructs a StringDef and record whether it comes from a double quoted
     * string.
     * @param s the actual content
     * @param doubleQuotes
     */
    StringDef(const std::string &s, bool doubleQuotes = false) :
        stringdef(s), doubleQuotedString(doubleQuotes), isbackref(false) {
    }

    const std::string toString() const;

    /**
     * return the original representation (this is useful for printing errors)
     * @return the original representation
     */
    const std::string toStringOriginal() const {
        return orig;
    }

    /**
     * whether this comes from a double quoted string
     * @return whether this comes from a double quoted string
     */
    bool isDoubleQuoted() const {
        return doubleQuotedString;
    }

    /**
     * @return whether this is only a back reference
     */
    int isBackRef() const {
        return isbackref;
    }
    
    /**
     * @param b
     */
    void setBackRef(bool b) {
        isbackref = b;
    }
    
    /**
     * Given two StringDef produces a new StringDef (keeping properties such as
     * isbackref)
     * @param s1
     * @param s2
     * @return the new StringDef
     */
    static StringDef *concat(const StringDef *s1, const StringDef *s2);
    
};

typedef std::list<StringDef *> StringDefsBase;

/**
 * A collection (list) of StringDef's.  This collection is the owner
 * of its elements, so it will delete them when the collection is deleted
 */
class StringDefs : public StringDefsBase {
public:
    ~StringDefs() {
        for (StringDefsBase::iterator it = begin(); it != end(); ++it)
            delete *it;
    }
};

#endif
