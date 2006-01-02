#include <iostream>
#include <string>

#include "langmap.h"
#include "messages.h"

using namespace std;

// "syntax: <filename> or <path> <filename>"

int
main(int argc, char **argv)
{
  DefaultMessages messages;
  setMessager(&messages);
    
  const char *path = (argc > 2 ? argv[1] : 0);
  const char *file = (argc > 2 ? argv[2] : (argc > 1 ? argv[1] : 0)); 
  
  string _path;
  string _file;
  if (path)
    _path = path;
  if (file)
    _file = file;
    
  LangMap langmap(_path, _file);
  langmap.print();

  return 0;
}
