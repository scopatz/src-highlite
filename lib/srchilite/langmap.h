//
// C++ Interface: langmap
//
// Description:
//
//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2004
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef LANGMAP_H
#define LANGMAP_H

#include <string>
#include <map>

/**
 * A map stored in a file with the format
 * key = elem
 * 
 * Comment line start with a #
 * 
 * This is used for lang.map, outlang.map and style.defaults
 * 
 * @author Lorenzo Bettini
 */
class LangMap {
    typedef std::map<std::string, std::string> Map;

    Map langmap;
    
    /// whether the corresponding file is opened
    bool isOpen;
    
    const std::string path, filename;

public:
    LangMap() : isOpen(false) {
    }
    LangMap(const std::string &path, const std::string &filename);

    ~LangMap();

    typedef Map::const_iterator const_iterator;
    const_iterator begin() {
        return langmap.begin();
    }
    const_iterator end() {
        return langmap.end();
    }

    void print();
    
    /**
     * Open the corresponding file (if it is not already opened) and read
     * and parse its contents.
     */
    void open();
    
    const std::string &get_file(const std::string &lang) {
        return langmap[lang];
    }
};

#endif
