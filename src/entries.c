
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "common.h"
#include "entries.h"


bool       types_found[TYPE_MAX + 1];
int        tool_entry_count = 0;
int        cur_entry = 0;
tool_entry tool_entries[TOOL_ENTRY_COUNT_MAX];


// Register an entry
void entry_add(tool_entry new_entry) {

    if (tool_entry_count < TOOL_ENTRY_COUNT_MAX) {

        tool_entries[tool_entry_count] = new_entry;

        if ((new_entry.type >= TYPE_MIN) && (new_entry.type <= TYPE_MAX))
            types_found[new_entry.type] = true;

        tool_entry_count++;
    } else
        fprintf(stdout, "Error: too many entries\n");
}


// Register an entry
void entry_add_with_version(tool_entry new_entry, char * version) {

    snprintf(new_entry.version, MAX_STR_LEN, "%s", version);
    entry_add(new_entry);
}


// Check if an entry of a given type has been found
bool entry_type_is_found(int tool_type) {
    if ((tool_type >= TYPE_MIN) && (tool_type <= TYPE_MAX))
        return types_found[tool_type];
    else
        return false;
}


// Get a tool entry by reference
tool_entry * entry_get(int index) {
     if ((index >= 0) && (index < tool_entry_count))
         return &(tool_entries[tool_entry_count]);
     else
         return NULL;
}


// Get the first entry of a given tool type
tool_entry * entry_get_first_of_type(int tool_type) {

     for (int c = 0; c < tool_entry_count; c++)
        if (tool_entries[c].type == tool_type) {
           cur_entry = c;
           return &(tool_entries[c]);
       }

    return NULL;
}


// Get the next entry of a given tool type
tool_entry * entry_get_next_of_type(int tool_type) {

     for (int c = cur_entry + 1; c < tool_entry_count; c++)
        if (tool_entries[c].type == tool_type) {
           cur_entry = c;
           return &(tool_entries[c]);
       }

    return NULL;
}



// Get max number of entries
int entry_get_count(int index) {
    return tool_entry_count;
}

