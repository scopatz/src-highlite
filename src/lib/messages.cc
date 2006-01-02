/*
** Copyright (C) 1999, 2000, Lorenzo Bettini <http://www.lorenzobettini.it>
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
**
*/


// messages.cc

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdlib.h>

#include "messages.h"

static Messages *_messager = 0 ;

void printMessage( const char *s, ostream &stream ) {
  if ( _messager )
    _messager->printMessage(s,stream) ;
}

void printMessage( const std::string &s, ostream &stream ) {
  if ( _messager )
    _messager->printMessage(s,stream) ;
}

void
printMessage_noln( const char *s, ostream &stream ) {
  if ( _messager )
    _messager->printMessage_noln(s,stream) ;
}

void
printMessage_noln( const std::string &s, ostream &stream ) {
  if ( _messager )
    _messager->printMessage_noln(s,stream) ;
}

void printWarning( const char *s, ostream &stream ) {
  if ( _messager )
    _messager->printWarning(s,stream) ;
}

void printError( const char *s, ostream &stream ) {
  stream << s << endl;
}

void printError( const std::string &s, ostream &stream ) {
  stream << s << endl;
}

void printError(const std::string &filename, unsigned int line, const std::string &error, ostream & stream)
{
  stream << filename << ":" << line << ": " << error << endl;
}

void setMessager( Messages *m ) {
  if ( m )
    _messager = m ;
}

void memory_exhausted()
{
  cerr << "no more free memory" << endl;
}

void exitError(const std::string &error)
{
  cerr << PACKAGE << ": " << error << endl;
  exit(EXIT_FAILURE);
}

void foundBug(const std::string &error, const std::string &file, int line)
{
  cerr << PACKAGE << ": " << error << ", " << file << ":" << line << endl;
  exit(EXIT_FAILURE);
}
