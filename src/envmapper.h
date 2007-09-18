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
 * src/envmapper.h -- prototypes and definitions for src/envmapper.c
 *
 * 19.04.2001 [SPX] * added ENV_REQUEST_METHOD
 *                  * added MAX_QUERY_STRING_LEN
 *                  * added REQUEST_METHOD_GET
 * 06.04.2001 [SPX] completed initial revision
 * 05.04.2001 [SPX] initial revision
 *
 * written by Robert Wetzel <rw8@mail.inf.tu-dresden.de>
 */

#ifndef _ENVMAPPER_H__
#define _ENVMAPPER_H__

#define ENV_REQUEST_METHOD    "REQUEST_METHOD"
#define ENV_QUERY_STRING      "QUERY_STRING"
#define REQUEST_METHOD_GET    "GET"
#define MAX_PARAM_AMOUNT      128
#define MAX_QUERY_STRING_LEN  512

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

char **map_environment(int *argc, char **argv);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _ENVMAPPER_H__ */
