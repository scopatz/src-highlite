#include <iostream>
#include <boost/regex.hpp>

#include "langdefparserfun.h"
#include "regexpreprocessor.h"

using namespace std;

int
main(int argc, const char **argv)
{
  LangElems *elems = 0;
  
  if (argc > 1)
    elems = parse_lang_def("", argv[1]);
  else
    elems = parse_lang_def();

  cout << "ORIGINAL:\n";
  cout << elems->toString() << endl;

  cout << "TRANSLATED:\n";
  cout << RegexPreProcessor::preprocess(elems->toString()) << endl;

  cout << "NONSENSITIVE:\n";
  cout << RegexPreProcessor::make_nonsensitive(elems->toString()) << endl;
  
  for (LangElems::const_iterator it = elems->begin(); it != elems->end(); ++it)
  {
    const string &ex_string = (*it)->toString();
      
    try {
      boost::regex ex(ex_string);
    } catch (boost::bad_expression &e) {
      cerr << "bad expression: " << ex_string << endl;
    }
  }

  return 0;
}
