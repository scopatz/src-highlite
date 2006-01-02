#ifndef _FILEUTIL_H
#define _FILEUTIL_H

#include <iostream>
#include <string>

using std::istream;
using std::string;

extern std::string start_path;

char *read_file(const string &fileName);
string createOutputFileName(const string &inputFileName, char *outputDir, const string &ext );
unsigned int get_line_count(const string &file_name);
unsigned int get_line_count(istream &input);
string get_file_extension(const string &filename);
void reopen_stdin(const string &input_file_name);
FILE * open_file_stream(const string &input_file_name);
istream * open_file_istream(const string &filename);
istream * open_file_istream_or_error(const string &filename);
istream * open_data_file_istream(const string &path, const string &filename,
                                 const string &start = start_path);
FILE * open_data_file_stream(const string &path, const string &filename,
                             const string &start = start_path);
bool read_line(istream *in, string &line);
string get_file_path(const string &s);
bool contains_path(const string &);
string strip_file_path(const string &);
string get_input_file_name(const string &file_name);

#endif //_FILEUTIL_H
