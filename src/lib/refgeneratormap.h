//
// C++ Interface: refgeneratormap
//
// Description:
//
//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2005
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef REFGENERATORMAP_H
#define REFGENERATORMAP_H

#include <generatormap.h>

#include "my_sstream.h"
#include "readtags.h"
#include "textstyles.h"

typedef enum {INLINE=1, POSTLINE, POSTDOC} RefPosition;

/**
A specialized GeneratorMap that also generates anchors and references, by using ctags information

@author Lorenzo Bettini
*/
class RefGeneratorMap : public GeneratorMap
{
private:
  const std::string ctags_file_name;
  TextStyles::RefTextStyle refstyle;
  RefPosition refposition;
  tagFile *ctags_file;
  tagFileInfo info;
  std::ostringstream buffer;

public:
    RefGeneratorMap(PreFormatter *pf, const std::string &_ctags_file_name,
                    const TextStyles::RefTextStyle &r, RefPosition pos);

    ~RefGeneratorMap();

protected:
    virtual const std::string generateString(const std::string& elem, const std::string& s, const FileInfo* arg1);
    const std::string _generateString(const std::string& elem, const std::string& s, const FileInfo* arg1);
};

#endif
