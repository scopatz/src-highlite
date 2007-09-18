/*
** Copyright (C) 1999-2007 Lorenzo Bettini <http://www.lorenzobettini.it>
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

// docgenerator.h : Document generator class

// for preable, header, footer, etc.

#ifndef DOCGENERATOR_H
#define DOCGENERATOR_H

#include <string>
#include "doctemplate.h"

using std::string;

class DocGenerator
{
 protected:
  string title;
  bool gen_source_highlight_version;
  string input_file_name;
  string doc_header;
  string doc_footer;
  string css_url;
  string doc_background;
  bool entire_doc;

  DocTemplate docTemplate;

 public:
  DocGenerator(const string &s, const string &i,
               const string &h, const string &f, const string &c,
               const string &back,
               bool entire,
               const string &start_tmpl, const string &end_tmpl) : title (s),
    gen_source_highlight_version (true), input_file_name (i), doc_header (h),
    doc_footer (f), css_url (c), doc_background(back), entire_doc (entire),
    docTemplate(DocTemplate(start_tmpl, end_tmpl)) {}
  DocGenerator() {}
  ~DocGenerator() {}

  void generate_start_doc();
  void generate_end_doc();

  void generate(const string &);
  void generateln(const string &);

  void set_gen_version(bool b) { gen_source_highlight_version = b; }
};

#endif // DOCGENERATOR_H
