//
// C++ Interface: stopwatch
//
// Description:
//
//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <time.h>

/**
Records elapsed time

	@author Lorenzo Bettini <http://www.lorenzobettini.it>
*/
class StopWatch{
  clock_t start;
public:
  /**
   * constructs a StopWatch object by storing the current time
   * (uses clock())
   */
  StopWatch() : start(clock()) {}

  /**
   * Upon destruction, prints the elapsed time in seconds,
   * since the construction of this StopWatch
   */
  ~StopWatch();

};

#endif
