// test the readtags library

#include "readtags.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static int extensionFields;

static void printTag (const tagEntry *entry)
{
    int i;
    int first = 1;
    const char* separator = ";\"";
    const char* const empty = "";
/* "sep" returns a value only the first time it is evaluated */
#define sep (first ? (first = 0, separator) : empty)
    printf ("%s\t%s\t%s",
	entry->name, entry->file, entry->address.pattern);
    if (extensionFields)
    {
	if (entry->kind != NULL  &&  entry->kind [0] != '\0')
	    printf ("%s\tkind:%s", sep, entry->kind);
	if (entry->fileScope)
	    printf ("%s\tfile:", sep);
	for (i = 0  ;  i < entry->fields.count  ;  ++i)
	    printf ("%s\t%s:%s", sep, entry->fields.list [i].key,
		entry->fields.list [i].value);
    }
    putchar ('\n');
#undef sep
}

static void listTags (const char *TagFileName)
{
    tagFileInfo info;
    tagEntry entry;
    tagFile *const file = tagsOpen (TagFileName, &info);
    if (file == NULL)
    {
	fprintf (stderr, "%s: cannot open tag file: %s: %s\n",
		"test_readtags", strerror (info.status.error_number), TagFileName);
	exit (1);
    }
    else
    {
	while (tagsNext (file, &entry) == TagSuccess)
	    printTag (&entry);
	tagsClose (file);
    }
}

int
main()
{
  listTags("mytags");

  return 0;
}

