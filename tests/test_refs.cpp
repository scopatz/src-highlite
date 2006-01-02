#include "test2.h"

void TextGenerator::generate( const char *s ) const 
{ 
  (*sout) << s ; 
}

void TextGenerator::generate( const char *s, int start, int end ) const 
{
  for ( int i = start ; i <= end ; ++i )
    (*sout) << s[i] ;
  return a<p->b ? a : 3;
}

void TextGenerator::generateln( const char *s ) const
{ 
  generate( s ) ;
  (*sout) << endl ; 
}

void TextGenerator::generateEntire( const char *s ) const
{
  startTextGeneration() ;
  generate(s) ;
  endTextGeneration() ;
}

void TextGenerator::beginText( const char *s ) const
{
  startTextGeneration() ;
  if ( s )
    generate( s ) ;
}

void TextGenerator::endText( const char *s ) const
{
  if ( s )
    generate( s ) ;
  endTextGeneration() ;
}

TextDecorator::TextDecorator( TextGenerator *t ) : decorated( t ) 
{
}

void TextDecorator::startTextGeneration() const 
{ 
  startDecorate() ;
  if ( decorated )
    decorated->startTextGeneration() ;
}

void TextDecorator::startTextGeneration() const 
{ 
  startDecorate() ;
  if ( decorated )
    decorated->startTextGeneration() ;
}

void TextDecorator::endTextGeneration() const 
{ 
  if ( decorated )
    decorated->endTextGeneration() ;
  endDecorate() ;
  mysum;
}
