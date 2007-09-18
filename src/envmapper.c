/*
 * Copyright (C) 1999, 2000, 2001  Lorenzo Bettini <http://www.lorenzobettini.it>
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

/*
 * src/envmapper.c -- maps QUERY_STRING environment to argv
 *
 * 19.04.2001 [SPX] * added __convert_string() and __convert_char() to
 *                    interpret '%XX' 'characters' of 'QUERY_STRING'
 *                  * checks for CGI by scanning REQUEST_METHOD
 *                  * 'QUERY_STRING' is determined by REQUEST_METHOD
 * 06.04.2001 [SPX] completed initial revision
 * 05.04.2001 [SPX] initial revision
 *
 * written by Robert Wetzel <rw8@mail.inf.tu-dresden.de>
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "envmapper.h"


int
__convert_char(char *hexstr, int *source)
{
  int i, ch, temp_ch;

  for (ch = i = 0; i < 2; i++) {
    temp_ch = hexstr[(*source)++];
    if (!isxdigit(temp_ch))
      return temp_ch;
    temp_ch -= '0';
    if (temp_ch > 9)
      temp_ch -= 'A' - '9' - 1;
    ch = (ch << 4) + temp_ch;
  }
  return ch;
}

char *
__convert_string(char *hexstr)
{
  int source, dest, ch, len;

  source = dest = 0;
  len = strlen(hexstr);
  while (source < len) {
    if ((ch=hexstr[source++]) == '%')
      hexstr[dest++] = __convert_char(hexstr, &source);
    else
      hexstr[dest++] = ch;
  }
  hexstr[dest] = '\0';
  return hexstr;
}

char *
__get_option_string(char *token)
{
  char *new_token;

  new_token = (char*)calloc(strlen(token)+3, 1);
  sprintf(new_token, "--%s", token);
  return new_token;
}

char **
map_environment(int *argc, char **argv)
{
  char *query_string, *request_method, *token;
  char **new_argv;

  /* check first, if CGI environment exists */
  request_method = getenv(ENV_REQUEST_METHOD);
  if (!request_method)
    return argv;
  /* Ok. There is a request method. Lets check how the 'arguments'
     are given by determining the request method... */
  if (!strcasecmp(request_method, REQUEST_METHOD_GET))
    query_string = getenv(ENV_QUERY_STRING);
  else {
    query_string = (char*)calloc(MAX_QUERY_STRING_LEN, sizeof(char));
    query_string = fgets(query_string, MAX_QUERY_STRING_LEN - 2, stdin);
    if (query_string)
      query_string[strlen(query_string)-2] = '\0';
  }
  if (!query_string)
    /* print error page! Currently this looks like a security hole as
       it switches back to command line mode. */
    return argv;
  query_string = __convert_string(query_string);
  /* allocate memory for the new argv which may hold up to
     MAX_PARAM_AMOUNT options */
  new_argv = (char**)calloc(MAX_PARAM_AMOUNT, sizeof argv);
  /* 'copy' parameter strings */
  memcpy(new_argv, argv, *argc * sizeof argv);
  token = strtok(query_string, "&");
  do {
    new_argv[(*argc)++] = __get_option_string(token);
  }
  while ((token = strtok(NULL, "&")));
  return new_argv;
}
