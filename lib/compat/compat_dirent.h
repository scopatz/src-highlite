/*
 * DIRENT.H (formerly DIRLIB.H)
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is a part of the mingw-runtime package.
 *
 * The mingw-runtime package and its code is distributed in the hope that it
 * will be useful but WITHOUT ANY WARRANTY.  ALL WARRANTIES, EXPRESSED OR
 * IMPLIED ARE HEREBY DISCLAIMED.  This includes but is not limited to
 * warranties of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * You are free to use this package and its code without limitation.
 */
#ifndef _DIRENT_H_
#define _DIRENT_H_
#include <io.h>
#include <stdio.h>

#define PATH_MAX 512

struct dirent
{
        long		d_ino;		/* Always zero. */
        unsigned short	d_reclen;	/* Always zero. */
        unsigned short	d_namlen;	/* Length of name in d_name. */
        char		d_name[FILENAME_MAX]; /* File name. */
};

/*
 * This is an internal data structure. Good programmers will not use it
 * except as an argument to one of the functions below.
 * dd_stat field is now int (was short in older versions).
 */
typedef struct
{
        /* disk transfer area for this dir */
        struct _finddata_t	dd_dta;

        /* dirent struct to return from dir (NOTE: this makes this thread
         * safe as long as only one thread uses a particular DIR struct at
         * a time) */
        struct dirent		dd_dir;

        /* _findnext handle */
        long			dd_handle;

        /*
         * Status of search:
         *   0 = not started yet (next entry to read is first entry)
         *  -1 = off the end
         *   positive = 0 based index of next entry
         */
        int			dd_stat;

        /* given path for dir with search pattern (struct is extended) */
        char			dd_name[PATH_MAX+3];
} DIR;

struct _wdirent
{
        long		d_ino;		/* Always zero. */
        unsigned short	d_reclen;	/* Always zero. */
        unsigned short	d_namlen;	/* Length of name in d_name. */
        wchar_t		d_name[FILENAME_MAX]; /* File name. */
};

/*
 * This is an internal data structure. Good programmers will not use it
 * except as an argument to one of the functions below.
 */
typedef struct
{
        /* disk transfer area for this dir */
        //struct _wfinddata_t	dd_dta;

        /* dirent struct to return from dir (NOTE: this makes this thread
         * safe as long as only one thread uses a particular DIR struct at
         * a time) */
        struct _wdirent		dd_dir;

        /* _findnext handle */
        long			dd_handle;

        /*
         * Status of search:
         *   0 = not started yet (next entry to read is first entry)
         *  -1 = off the end
         *   positive = 0 based index of next entry
         */
        int			dd_stat;

        /* given path for dir with search pattern (struct is extended) */
        wchar_t			dd_name[1];
} _WDIR;

DIR           *opendir(const char *);
int           closedir(DIR *);
struct dirent *readdir(DIR *);

#endif	/* Not _DIRENT_H_ */
