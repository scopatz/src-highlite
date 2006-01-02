/*
** Copyright (C) 1999, 2000, 2001 Lorenzo Bettini
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

// this file also contains the definition of mysum as a #define

// textgenerator.h : Text Generator class &&

#ifndef _TEXTGEN_H
#define _TEXTGEN_H

#define foo(x) (x + 1)

#define mysum myfunbody 

#include <iostream.h> // for cerr

#include "genfun.h" /* for generating functions */

class TextGenerator {
  public :
    virtual void generate( const char *s ) const { (*sout) << s ; }
    virtual void generate( const char *s, int start, int end ) const 
      {
        for ( int i = start ; i <= end ; ++i )
          (*sout) << s[i] ;
        return a<p->b ? a : 3;
      }
    virtual void generateln( const char *s ) const
	{ 
	    generate( s ) ;
	    (*sout) << endl ; 
	}
    virtual void generateEntire( const char *s ) const
	{
	    startTextGeneration() ;
	    generate(s) ;
	    endTextGeneration() ;
	}
    virtual void startTextGeneration() const {}
    virtual void endTextGeneration() const {}
    virtual void beginText( const char *s ) const
	{
	    startTextGeneration() ;
	    if ( s )
		generate( s ) ;
	}
    virtual void endText( const char *s ) const
	{
	    if ( s )
		generate( s ) ;
	    endTextGeneration() ;
	}
} ;

// Decorator
class TextDecorator : public TextGenerator {
  protected :
    TextGenerator *decorated ;
  
  public :
    TextDecorator( TextGenerator *t ) : decorated( t ) {}

    virtual void startTextGeneration() const 
    { 
	startDecorate() ;
	if ( decorated )
	    decorated->startTextGeneration() ;
    }
    virtual void endTextGeneration() const 
    { 
	if ( decorated )
	    decorated->endTextGeneration() ;
	endDecorate() ;
	mysum;
    }

    // pure virtual functions
    virtual void startDecorate() const = 0 ;
    virtual void endDecorate() const = 0 ;
} ;

#endif // _TEXTGEN_H
