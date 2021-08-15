// This is free and unencumbered software released into the public domain.
// For more information, please refer to <https://unlicense.org>
// bbbbbr 2020

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "common.h"
#include "entries.h"


static void render_entry_json(const char * name_field, const char * version_field, int tool_type, bool comma);
static void render_entry_csv(const char * name_field, const char * version_field, int tool_type, bool comma);
static void render_entry_csv_bare(int tool_type, bool comma);
static void render_entry_default(const char * name_field, int tool_type);


static void render_entry_json(const char * name_field, const char * version_field, int tool_type, bool comma) {

    tool_entry * p_entry = entry_get_first_of_type(tool_type);

    if (p_entry)
        fprintf(stdout,"\"%s\": \"%s\", \"%s\": \"%s\"", name_field, p_entry->name, version_field, p_entry->version);
    else
        fprintf(stdout,"\"%s\": null, \"%s\": null", name_field, version_field);

    if (comma) fprintf(stdout,",");
    fprintf(stdout,"\n");
}


static void render_entry_csv(const char * name_field, const char * version_field, int tool_type, bool comma) {

    tool_entry * p_entry = entry_get_first_of_type(tool_type);

    if (p_entry)
        fprintf(stdout,"\"%s\",\"%s\",\"%s\",\"%s\"", name_field, p_entry->name, version_field, p_entry->version);
    else
        fprintf(stdout,"\"%s\",\"\",\"%s\",\"\"", name_field, version_field);

    if (comma) fprintf(stdout,",");
}


static void render_entry_csv_bare(int tool_type, bool comma) {

    tool_entry * p_entry = entry_get_first_of_type(tool_type);

    if (p_entry)
        fprintf(stdout,"\"%s\",\"%s\"", p_entry->name, p_entry->version);
    else
        fprintf(stdout,"\"\",\"\"");

    if (comma) fprintf(stdout,",");
}



static void render_entry_default(const char * name_field, int tool_type) {

    tool_entry * p_entry = entry_get_first_of_type(tool_type);

    if (p_entry) {
        // This mode shows multiple entries for a given tool type if present
        while (p_entry) {
            fprintf(stdout,"%s: %s", name_field, p_entry->name);

            // Don't print empty versions
            if (strlen(p_entry->version) > 0)
                fprintf(stdout,", Version: %s", p_entry->version);

            fprintf(stdout,"\n");
            p_entry = entry_get_next_of_type(tool_type);
        };
    }
    else
        if (tool_type == TYPE_TOOLS) // Only display unknown value for main tools type
            fprintf(stdout,"%s: <unknown>\n", name_field);
}




void display_output(int output_style, const char * filename) {


    if (output_style == OUTPUT_JSON) {

        fprintf(stdout,"{\n");
        fprintf(stdout, "\"file\": \"%s\",\n", filename);
            render_entry_json("toolsName",   "toolsVersion",   TYPE_TOOLS,   true);
            render_entry_json("engineName",  "engineVersion",  TYPE_ENGINE,  true);
            render_entry_json("musicName",   "musicVersion",   TYPE_MUSIC,   true);
            render_entry_json("soundfxName", "soundfxVersion", TYPE_SOUNDFX, false);
        fprintf(stdout,"}\n");
    }
    else if (output_style == OUTPUT_CSV) {

        fprintf(stdout,"\"File\",\"%s\",", filename);
            render_entry_csv("Tools Name",   "Tools Version",   TYPE_TOOLS,   true);
            render_entry_csv("Engine Name",  "Engine Version",  TYPE_ENGINE,  true);
            render_entry_csv("Music Name",   "Music Version",   TYPE_MUSIC,   true);
            render_entry_csv("SoundFX Name", "SoundFX Version", TYPE_SOUNDFX, false);
        fprintf(stdout,"\n");
    }
    else if (output_style == OUTPUT_CSV_BARE) {

        fprintf(stdout,"\"%s\",", filename);
            render_entry_csv_bare(TYPE_TOOLS,   true);
            render_entry_csv_bare(TYPE_ENGINE,  true);
            render_entry_csv_bare(TYPE_MUSIC,   true);
            render_entry_csv_bare(TYPE_SOUNDFX, false);
        fprintf(stdout,"\n");
    }
    else { // OUTPUT_DEFAULT

        fprintf(stdout, "File: %s\n", filename);
            render_entry_default("Tools", TYPE_TOOLS);
            render_entry_default("Engine", TYPE_ENGINE);
            render_entry_default("Music", TYPE_MUSIC);
            render_entry_default("SoundFX", TYPE_SOUNDFX);
        fprintf(stdout,"\n");
    }
}