/*
 * Copyright (C) 2000, 2001  Lorenzo Bettini <http://www.lorenzobettini.it>
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

#include <iostream>
#include <fstream>

#include "fileutil.h"
#include "messages.h" // for verbosity

using namespace std;

static void file_error(const string &error, const string &file);
static void internal_error(const string &error);

// global for the path to start to look for if no
// path was specified
// FIXME avoid using a global variable
std::string start_path;

char *
read_file(const string &fileName)
{
  char *buffer = 0;
  long int char_count;

  // we open it as binary otherwise we may experience problems under
  // Windows system: when we fread, the number of char read can be
  // less then char_count, and thus we'd get an error...
  ifstream file (fileName.c_str (), ios_base::binary);
  if (! file.is_open () )
    file_error ("Error operning", fileName);
  else
    {
      // let's go to the end of the file...
      file.seekg (0, ios::end);
      if (! file)
        file_error ("Error positioning", fileName);

      // ...to read the dimension
      char_count = file.tellg ();
      if (! file)
        file_error ("Error reading position", fileName);

      buffer = new char [char_count + 1];
      if (! buffer)
        internal_error ("Memory allocation failed");

      file.seekg (0, ios::beg);
      if (! file)
        file_error ("Error positioning to start", fileName);

      //copy file into memory
      file.read (buffer, char_count);
      buffer[char_count] = '\0';

      file.close ();
    }

  return buffer;
}

void
file_error(const string &error, const string &file)
{
  cerr << PACKAGE << ": " << error << ", file " << file << endl;
  exit (1);
}

void
internal_error(const string &error)
{
  cerr << PACKAGE << ": Internal error: " << error << endl;
  exit (1);
}

// output file name = <outputDir> + input file name + ext
string
createOutputFileName(const string &inputFileName, char *outputDir, const string &ext )
{
  string input_file_name;
  char path_separator = '/';

  if (! outputDir)
    input_file_name = inputFileName;
  else
    {
      string::size_type pos_of_sep;
      pos_of_sep = inputFileName.find_last_of('/');

      if (pos_of_sep == string::npos) // try with DOS separator
        {
  	  pos_of_sep = inputFileName.find_last_of ('\\');
          if (pos_of_sep != string::npos)
            path_separator = '\\';
        }


      if (pos_of_sep != string::npos)
        input_file_name = inputFileName.substr (pos_of_sep + 1);
      else
        input_file_name = inputFileName;
    }

  string outputFileName;

  if (outputDir)
    {
      outputFileName += outputDir;
      outputFileName += path_separator;
    }
  outputFileName += input_file_name;
  outputFileName += ext;

  return outputFileName;
}

unsigned int
get_line_count(const string &file_name)
{
  ifstream input (file_name.c_str ());

  if (! input)
    file_error ("Error opening", file_name);

  unsigned int count = get_line_count (input);

  input.close ();

  return count;
}

unsigned int
get_line_count(istream &input)
{
  unsigned int count = 0;
  string line;

  while (true)
    {
      getline (input, line);
      if (! input.eof ())
        ++count;
      else
        break;
    }

  return count;
}

string
get_file_extension(const string &s)
{
  string::size_type pos_of_sep;

  pos_of_sep = s.rfind(".");

  if (pos_of_sep == string::npos)
    return ""; // no extension

  return s.substr (pos_of_sep + 1);
}

void
reopen_stdin(const string &input_file_name)
{
  FILE *in = freopen (input_file_name.c_str(), "r", stdin);
  if (!in)
  {
    cerr << "Error in opening " << input_file_name
        << " for input" << endl ;
    exit(1) ;
  }
}

FILE *open_file_stream(const string &input_file_name)
{
  FILE *in = fopen (input_file_name.c_str(), "r");
  return in;
}

istream *open_file_istream(const string &input_file_name)
{
  ifstream *in = new ifstream (input_file_name.c_str());
  if (!in || !(*in))
  {
    if (!in)
      memory_exhausted();
    else
      delete in;
    return 0 ;
  }

  return in;
}

istream *open_file_istream_or_error(const string &input_file_name)
{
  istream *in = open_file_istream(input_file_name);

  if (!in)
    exitError("cannot open file " + input_file_name);

  return in;
}

istream *_open_data_file_istream(const string &path, const string &input_file_name)
{
  const string file = (path.size() ? path + "/" : "") + input_file_name;
  printMessage("opening " + file);
  return open_file_istream(file);
}

istream *open_data_file_istream(const string &path, const string &input_file_name,
                                const string &start)
{
  istream *in = 0;
  if (input_file_name.size() && contains_path(input_file_name)) {
    in = _open_data_file_istream("", input_file_name);
    if (!in) {
      exitError("file " + input_file_name + " not found");
    }
  } else if (path.size() && input_file_name.size()) {
    const string file = (path.size() ? path + "/" : "") + input_file_name;
    in = _open_data_file_istream(path, input_file_name);
    if (!in) {
      exitError("file " + file + " not found");
    }
  } else {
    string _path = path;
    string _file = input_file_name;
    bool has_path = contains_path(input_file_name);
    if (!path.size() && !has_path)
      _path = ".";

    in = _open_data_file_istream(_path, _file);
    if (! in && !path.size() && ! has_path)
      in = _open_data_file_istream(start, _file);
  }

  if (!in)
    exitError("cannot find language map file anywhere");

  return in;
}

// FIXME: duplicate for istream and FILE *, make it uniform!
FILE *_open_data_file_stream(const string &path, const string &input_file_name)
{
  const string file = (path.size() ? path + "/" : "") + input_file_name;
  printMessage("opening " + file);
  return open_file_stream(file);
}

FILE *open_data_file_stream(const string &path, const string &input_file_name,
                            const string &start)
{
  FILE *in = 0;
  if (input_file_name.size() && contains_path(input_file_name)) {
    in = _open_data_file_stream("", input_file_name);
    if (!in) {
      exitError("file " + input_file_name + " not found");
    }
  } else if (path.size() && input_file_name.size()) {
    const string file = (path.size() ? path + "/" : "") + input_file_name;
    in = _open_data_file_stream(path, input_file_name);
    if (!in) {
      exitError("file " + file + " not found");
    }
  } else {
    string _path = path;
    string _file = input_file_name;
    bool has_path = contains_path(input_file_name);
    if (!path.size() && !has_path)
      _path = ".";

    in = _open_data_file_stream(_path, _file);
    if (! in && !path.size() && ! has_path)
      in = _open_data_file_stream(start, _file);
  }

  if (!in)
    exitError("cannot find file " + input_file_name + " anywhere");

  return in;
}

bool read_line(istream *in, string &line)
{
  if (in->eof())
    return false;

  getline (*in, line);
  return true;
}

string
get_file_path(const string &s)
{
  string::size_type pos_of_sep;

  pos_of_sep = s.rfind("/");
  if (pos_of_sep == string::npos)
    pos_of_sep = s.rfind("\\"); // try also with DOS path sep

  if (pos_of_sep == string::npos)
    return ""; // no path

  return s.substr (0, pos_of_sep + 1);
}

bool
contains_path(const string &s)
{
  return (get_file_path(s).size() > 0);
}

string
strip_file_path(const string &s)
{
  string::size_type pos_of_sep;

  pos_of_sep = s.rfind("/");
  if (pos_of_sep == string::npos)
    pos_of_sep = s.rfind("\\"); // try also with DOS path sep

  if (pos_of_sep == string::npos)
    return s; // no path

  return s.substr (pos_of_sep + 1);
}

string
get_input_file_name(const string &file_name)
{
  if (! file_name.size())
    return "";

  return CHROOT_INPUT_DIR + file_name;
}
