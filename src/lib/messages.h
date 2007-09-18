// messages.h: for messages printing

#ifndef _MESSAGES_H
#define _MESSAGES_H

#include <iostream>
#include <string>
#include <iterator>

using std::ostream;
using std::cerr;
using std::endl;

class ParserInfo;
class ParseStruct;

class Messages {
 public:
  /// whether to print anything
  bool dontPrint;

  virtual void printMessage( const char *s, ostream & stream = cerr ) = 0 ;
  virtual void printMessage( const std::string &s, ostream & stream = cerr ) = 0 ;

  virtual void printMessage_noln( const char *s,
                                  ostream & stream = cerr ) = 0 ;
  virtual void printMessage_noln( const std::string &s,
                                  ostream & stream = cerr ) = 0 ;
  virtual void printWarning( const char *s, ostream & stream = cerr ) = 0 ;
  virtual void printError( const char *s, ostream & stream = cerr ) = 0 ;
  
  Messages(bool dontPrint_ = true) : dontPrint(dontPrint_) {}
  virtual ~Messages() {}
} ;

class DefaultMessages : public Messages {
 protected:
  virtual void _print( const char *s, ostream &stream )
    { stream << s << endl ; }
  virtual void _print( const std::string &s, ostream &stream )
    { stream << s << endl ; }
  virtual void _print_noln( const char *s, ostream &stream )
    { stream << s ; }
  virtual void _print_noln( const std::string &s, ostream &stream )
    { stream << s ; }

 public:
  virtual void printMessage( const char *s, ostream &stream )
    { _print(s,stream); }
  virtual void printMessage( const std::string &s, ostream &stream )
    { _print(s,stream); }
  virtual void printMessage_noln( const char *s, ostream &stream )
    { _print_noln(s,stream); }
  virtual void printMessage_noln( const std::string &s, ostream &stream )
    { _print_noln(s,stream); }
  virtual void printWarning( const char *s, ostream &stream )
    { _print(s,stream); }
  virtual void printError( const char *s, ostream &stream )
    { _print(s,stream); }
    
  DefaultMessages() : Messages(false) {}
} ;

// prefer functions? ;-)
void printMessage( const char *s, ostream &stream = cerr ) ;
void printMessage( const std::string &s, ostream &stream = cerr ) ;
void printMessage_noln( const char *s, ostream &stream = cerr ) ;
void printMessage_noln( const std::string &s, ostream &stream = cerr ) ;
void printWarning( const char *s, ostream &stream = cerr ) ;
void printError( const char *s, ostream &stream = cerr ) ;
void printError( const std::string &s, ostream &stream = cerr ) ;
void printError( const std::string &s, const ParserInfo *pinfo, ostream &stream = cerr ) ;
void printError(const std::string &filename, unsigned int line, const std::string &error, ostream & stream = cerr );
void memory_exhausted();
void exitError(const std::string &error);
void exitError(const std::string &error, const ParserInfo *pinfo);
void exitError(const std::string &error, const ParseStruct *pinfo);
void exitError(const std::string &filename, unsigned int line, const std::string &error);
void foundBug(const std::string &error, const std::string &file = "", int line = -1);
bool shouldPrint();

void setMessager( Messages *m ) ;

template <class T>
void printSequence( const T *seq, ostream & stream = cerr )
{
  if (shouldPrint() && seq) {
    std::copy(seq->begin(), seq->end(), 
      std::ostream_iterator<typename T::value_type>(stream, " "));
  }
}


#endif // _MESSAGES_H
