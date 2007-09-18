/*
 * Copyright (C) 1999, 2000, 2002, 2003  Lorenzo Bettini <http://www.lorenzobettini.it>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "docgenerator.h"

#include "globalostream.h"

using std::endl;

void
DocGenerator::generate(const string &s)
{
  *sout << s ;
}

void
DocGenerator::generateln(const string &s)
{
  *sout << s << endl;
}

void
DocGenerator::generate_start_doc()
{
    bool docTitle = (title.size () > 0);
    bool inputFileName = (input_file_name.size () > 0);

    generate(
        docTemplate.output_begin(
            ( docTitle ? title :
                  ( inputFileName ? input_file_name : "source file" ) ),
            css_url,
            "GNU " PACKAGE " " + string((gen_source_highlight_version ? VERSION : "")) +
            "\nby Lorenzo Bettini\nhttp://www.lorenzobettini.it\nhttp://www.gnu.org/software/src-highlite",
            doc_header,
            doc_footer,
            doc_background
        )
    );
}

void
DocGenerator::generate_end_doc()
{
    generate(
        docTemplate.output_end(
            "",
            css_url,
            "\nby Lorenzo Bettini\nhttp://www.lorenzobettini.it\nhttp://www.gnu.org/software/src-highlite",
            doc_header,
            doc_footer,
            doc_background
        )
    );
}
