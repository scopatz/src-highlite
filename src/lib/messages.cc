/*
** Copyright (C) 1999-2007, Lorenzo Bettini <http://www.lorenzobettini.it>
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 3 of the License, or
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
#include "parserinfo.h"
#include "parsestruct.h"

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

void printError( const std::string &s, const ParserInfo *pinfo, ostream &stream ) {
  printError(pinfo->filename, pinfo->line, s, stream);
}

void printError(const std::string &filename, unsigned int line, const std::string &error, ostream & stream)
{
  stream << filename << ":";
  if (line)
      stream << line << ": ";
  stream << error << endl;
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

void exitError(const std::string &error, const ParserInfo *pinfo)
{
  exitError(pinfo->filename, pinfo->line, error);
}

void exitError(const std::string &error, const ParseStruct *pinfo)
{
  exitError((pinfo->path.size() ? pinfo->path + "/" : "") + pinfo->file_name, pinfo->line, error);
}

void exitError(const std::string &filename, unsigned int line, const std::string &error)
{
  cerr << PACKAGE << ": ";
  printError(filename, line, error);
  exit(EXIT_FAILURE);
}

void foundBug(const std::string &error, const std::string &file, int line)
{
  cerr << PACKAGE << ": " << error;
  if (file.size())
      cerr << ", " << file << ":" << line;
  cerr << endl;
  cerr << PACKAGE << ": " << "it looks like you found a bug of this program" << endl;
  cerr << PACKAGE << ": " << "could you please send this output and the input file" << endl;
  cerr << PACKAGE << ": " << "to the author of this program?" << endl;
  exit(EXIT_FAILURE);
}

bool shouldPrint()
{
  return (_messager && !_messager->dontPrint);
}
