/**
 * Tests for language inference, class LanguageInfer
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "srchilite/languageinfer.h"
#include <sstream>
#include "asserttestexit.h"
#include "srchilite/utils.h"

using namespace std;
using namespace srchilite;

LanguageInfer inf;

static void testInfer(const string &input, const string &expected);

void testInfer(const string &input, const string &expected) {
    stringstream buf;

    buf << input << "\nother lines\nother lines" << endl;

    string res = inf.infer(buf);

    cout << "inferred language: " << res << endl;
    assertEquals(expected, res);
}

int main() {
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
    assertEquals("lisp", s);

    cout << "lowered string: " << Utils::tolower("Php3") << endl;
    assertEquals("php3", Utils::tolower("Php3"));

    // try with scripts starting with <?
    testInfer("<?php", "php");
    testInfer("<?xml", "xml");

    // try xml like
    testInfer("<!DOCTYPE kpartgui ", "xml");

    cout << "test_langinfer: SUCCESS" << endl;

    return 0;
}
