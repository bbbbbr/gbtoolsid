
#include <stdbool.h>

#include "common.h"

#ifndef _ENTRIES_H
#define _ENTRIES_H


#define TYPE_TOOLS    0
#define TYPE_ENGINE   1
#define TYPE_MUSIC    2
#define TYPE_SOUNDFX  3

#define TYPE_MIN      TYPE_TOOLS
#define TYPE_MAX      TYPE_SOUNDFX

#define TOOL_ENTRY_COUNT_MAX 50 // Shouldn't ever need this many

typedef struct tool_entry {
    int  type;
    char name[MAX_STR_LEN];
    char version[MAX_STR_LEN];
} tool_entry;


void entry_add(tool_entry);
void entry_add_with_version(tool_entry, char *);

bool entry_type_is_found(int);
tool_entry * entry_get(int);
tool_entry * entry_get_first_of_type(int tool_type);
int entry_get_count(int);



#endif // _ENTRIES_H
