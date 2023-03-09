
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
    // For passing in designated inits that work on both linux gcc & mingw builds
    const char * c_name;
    const char * c_version;
    // Final rendered name/version
    char         version[MAX_STR_LEN];
    char         name[MAX_STR_LEN];
} tool_entry;


// Tool
#define STR_GBDK "GBDK"
// Versions
#define STR_GBDK_2_x_to_2020_3_2_0       "2.x - 2020.3.2.0"
#define STR_GBDK_2020_4_0_0              "2020.4.0.0"
#define STR_GBDK_2020_4_0_1_to_4_0_2     "2020.4.0.1 - 2020.4.0.2"
#define STR_GBDK_2020_4_0_3              "2020.4.0.3"
#define STR_GBDK_2020_4_0_4              "2020.4.0.4"
#define STR_GBDK_2020_4_0_5_v0_zgb       "2020.4.0.5.v0.zgb"
#define STR_GBDK_2020_4_0_5_v1_retracted "2020.4.0.5.v1.retracted"
#define STR_GBDK_2020_4_0_5_to_4_0_6     "2020.4.0.5 - 2020.4.0.6"
#define STR_GBDK_2020_4_1_0_to_4_1_1     "2020.4.1.0 - 2020.4.1.1"
#define STR_GBDK_2020_4_2_0_plus         "2020.4.2.0+"
#define STR_GBDK_2020_4_UNKNOWN          "Unknown"



void entry_add(tool_entry);
void entry_add_with_version(tool_entry, const char *);

int entry_get_count(int);
bool entry_type_is_found(int);
tool_entry * entry_get(int);
tool_entry * entry_get_first_of_type(int tool_type);
tool_entry * entry_get_next_of_type(int tool_type);
bool entry_check_match(int tool_type, char * str_match_name, char * str_match_version);



#endif // _ENTRIES_H
