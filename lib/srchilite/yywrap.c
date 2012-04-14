/*
  yywrap.c

  this is a kind of work around to make java2html work even if who compiles
  it doesn't have lex installed on his/her system (I don't know itf this
  works).  This way, even if he/she can't link to any lex library
  he/she shouldn't get any error...  This should work with flex,
  I don't know about lex; anyway this should worry only who implements.
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

int
yywrap()
{
  return 1 ;
}
