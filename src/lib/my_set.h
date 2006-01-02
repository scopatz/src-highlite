// deal with namespace problems

#ifndef _MY_SET_H
#define _MY_SET_H

#include <set>

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef HAVE_NAMESPACES 
using std::set;
#endif

#endif // _MY_SET_H
