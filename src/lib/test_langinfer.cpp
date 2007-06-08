/**
 * Tests for language inference, class LanguageInfer
 */

#include "languageinfer.h"
#include "my_sstream.h"
#include "asserttest.h"
#include "utils.h"

using namespace std;

LanguageInfer inf;
int result = 0;

void testInfer(const string &input, const string &expected)
{
  stringstream buf;

  buf << input << "\nother lines\nother lines" << endl;

  string res = inf.infer(buf);

  cout << "inferred language: " << res << endl;
  result += assertEquals(expected, res);
}

int
main()
{
  testInfer("#!/bin/sh", "sh");
  testInfer("# !/bin/bash", "bash");
  testInfer("#! /usr/local/bin/python", "python");
  testInfer("#! mypython  ", "mypython");
  testInfer("#! usr/local/bin/perl", "perl");
  testInfer("#! ../usr/local/bin/perl", "perl");
  testInfer("#! ../usr/../local/bin/sh", "sh");

  // now test emacs specifications
  testInfer("# -*- perl -*-", "perl");
  testInfer("# -*- perl, as specified in Emacs -*-", "perl");
  testInfer("# -*- Perl, as specified in Emacs -*-", "Perl");
  testInfer("# -*- php3, as specified in Emacs -*-", "php3");

  testInfer("#!/bin/sh\n# -*- tcl, as specified in Emacs -*-", "tcl");

  // try with the env specification
  testInfer("#! /usr/bin/env python", "python");
  testInfer("#! /bin/env perl", "perl");
  
  // just a small check for tolower
  string s = "Lisp";
  Utils::toLower(s);
  cout << "lowered string: " << s << endl;
  result += assertEquals("lisp", s);

  cout << "lowered string: " << Utils::tolower("Php3") << endl;
  result += assertEquals("php3", Utils::tolower("Php3"));

  return result;
}
