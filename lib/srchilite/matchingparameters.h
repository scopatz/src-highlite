//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2004-2008
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef MATCHINGPARAMETERS_H_
#define MATCHINGPARAMETERS_H_

/**
 * Structure for passing parameters to the matching algorithm
 * (e.g., "not beginning of line", etc.)
 */
struct MatchingParameters {
    bool beginningOfLine;

    MatchingParameters() :
        beginningOfLine(true) {

    }
};

#endif /*MATCHINGPARAMETERS_H_*/
