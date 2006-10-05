//
// C++ Interface: languageinfer
//
// Description:
//
//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef LANGUAGEINFER_H
#define LANGUAGEINFER_H

#include <string>
#include <iostream>

/**
Tries to infer the language by inspecting the input file

	@author Lorenzo Bettini <http://www.lorenzobettini.it>
*/
class LanguageInfer{
public:
    LanguageInfer();

    ~LanguageInfer();

    /**
     * Tries to infer the language of the specified inputfile.
     * @param filename The file to inspect
     * @return The inferred language, or "" if inference failed
     */
    const std::string infer(const std::string &filename);

    /**
     * Tries to infer the language of the specified input stream.
     * @param stream The stream to inspect
     * @return The inferred language, or "" if inference failed
     */
    const std::string infer(std::istream &stream = std::cin);
};

#endif
