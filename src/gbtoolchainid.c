// This is free and unencumbered software released into the public domain.
// For more information, please refer to <https://unlicense.org>
// bbbbbr 2020

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "common.h"
#include "sig_gbdk.h"
#include "sig_zgb.h"
#include "sig_gbstudio.h"

#include "sig_music_gbtplayer.h"
#include "sig_music_hugetracker.h"
#include "sig_music_carillon.h"
#include "sig_music_paragon5.h"
#include "sig_music_lemon.h"
#include "sig_music_tbengine.h"

#include "sig_soundfx_fxhammer.h"

static uint8_t * g_p_searchbuf = NULL;
static uint32_t g_searchbuf_len = 0;

char g_tools_name[MAX_STR_LEN] = "";
char g_tools_version[MAX_STR_LEN] = "";
bool g_tools_found = false;

char g_engine_name[MAX_STR_LEN] = "";
char g_engine_version[MAX_STR_LEN] = "";
bool g_engine_found = false;

char g_music_name[MAX_STR_LEN] = "";
char g_music_version[MAX_STR_LEN] = "";
bool g_music_found = false;

char g_soundfx_name[MAX_STR_LEN] = "";
char g_soundfx_version[MAX_STR_LEN] = "";
bool g_soundfx_found = false;


static void set_search_buf(uint8_t *, uint32_t);


// TODO: switch to just registering type / name / version entries

void set_tools(const char * tools_name, const char * tools_version) {
    snprintf(g_tools_name,    MAX_STR_LEN, "%s", tools_name);
    snprintf(g_tools_version, MAX_STR_LEN, "%s", tools_version);
    g_tools_found = true;
}


void set_engine(const char * engine_name, const char * engine_version) {
    snprintf(g_engine_name,    MAX_STR_LEN, "%s", engine_name);
    snprintf(g_engine_version, MAX_STR_LEN, "%s", engine_version);
    g_engine_found = true;
}


void set_music(const char * music_name, const char * music_version) {
    snprintf(g_music_name,    MAX_STR_LEN, "%s", music_name);
    snprintf(g_music_version, MAX_STR_LEN, "%s", music_version);
    g_music_found = true;
}

void set_soundfx(const char * soundfx_name, const char * soundfx_version) {
    snprintf(g_soundfx_name,    MAX_STR_LEN, "%s", soundfx_name);
    snprintf(g_soundfx_version, MAX_STR_LEN, "%s", soundfx_version);
    g_soundfx_found = true;
}


// Set the global search buffer
static void set_search_buf(uint8_t * p_rom_data, uint32_t rom_size) {
    g_p_searchbuf = p_rom_data;
    g_searchbuf_len = rom_size;
}


// Test for a pattern at a specific address
//
bool check_pattern_addr(const uint8_t * p_pattern, uint32_t pattern_len, uint32_t match_index) {

    uint8_t * p_match = g_p_searchbuf;

    if ((g_p_searchbuf == NULL) || (p_pattern == NULL) ||
        (g_searchbuf_len == 0)  || (pattern_len == 0))
        return false;

    // Don't try to search if requested match address or
    // pattern length would be past end of [zero indexed] search buffer
    if ((match_index + pattern_len - 1) > (g_searchbuf_len - 1))
        return false;

    if (memcmp(&p_match[match_index], p_pattern, pattern_len) == 0)
        return true;
    else
        return false;
}


// Try to find a pattern in a buffer
//
// No memmem on MinGW, so use the same for both instead of:
// return (memmem(g_p_searchbuf, g_searchbuf_len, p_pattern, pattern_len) != NULL);
//
bool find_pattern(const uint8_t * p_pattern, uint32_t pattern_len) {

    uint32_t cur_addr = 0;

    if ((g_p_searchbuf == NULL) || (p_pattern == NULL) ||
        (g_searchbuf_len == 0)  || (pattern_len == 0)  ||
        (pattern_len > g_searchbuf_len))
        return false;

    // Try to locate first possible instance
    uint8_t * p_match = (uint8_t *)memchr(g_p_searchbuf, p_pattern[0], g_searchbuf_len);
    uint32_t remaining = g_searchbuf_len - (p_match - g_p_searchbuf);

    while (p_match != NULL) {
        if (pattern_len <= remaining) {

            if (memcmp(p_match, p_pattern, pattern_len) == 0) {
                cur_addr = (uint32_t)(p_match - g_p_searchbuf);

                return true;
            }
        } else
            break;

        p_match++;
        p_match = (uint8_t *)memchr(p_match, p_pattern[0], remaining);
        remaining = g_searchbuf_len - (p_match - g_p_searchbuf);
    }

    return false;
}


void gbtools_detect(uint8_t * p_rom_data, uint32_t rom_size, bool strict_mode) {

    bool result_gbdk     = false;
    bool result_zgb      = false;
    bool result_gbstudio = false;

    bool result_music_gbtplayer   = false;
    bool result_music_hugetracker = false;
    bool result_music_carillon    = false;
    bool result_music_paragon5    = false;
    bool result_music_lemon       = false;
    bool result_music_tbengine    = false;

    bool result_soundfx_fxhammer  = false;

    set_search_buf(p_rom_data, rom_size);

    result_gbdk = check_gbdk();

    // If strict mode is turned on, only test
    // for ZGB and GBStudio when GBDK is present
    if ((strict_mode == false) || (result_gbdk == true)) {
        result_zgb      = check_zgb();
        result_gbstudio = check_gbstudio();
    }
    // Check for music drivers
    // TODO: Should only one driver per ROM be supported? 2+ is unlikely, but...
    result_music_gbtplayer =   check_music_gbtplayer();
    result_music_hugetracker = check_music_hugetracker();
    result_music_carillon =    check_music_carillon();
    result_music_paragon5 =    check_music_paragon5();
    result_music_lemon =       check_music_lemon();
    result_music_tbengine =    check_music_tbengine();

    // Check for sound fx drivers
    result_soundfx_fxhammer = check_soundfx_fxhammer();
}


void display_output(int output_style, const char * filename) {

    if (output_style == OUTPUT_JSON) {
        fprintf(stdout,"{\n");

        fprintf(stdout, "\"file\": \"%s\",\n", filename);

        if (g_tools_found)
            fprintf(stdout,"\"toolsName\": \"%s\", \"toolsVersion\": \"%s\",\n", g_tools_name, g_tools_version);
        else
            fprintf(stdout,"\"toolsName\": null,   \"toolsVersion\": null,\n");

        if (g_engine_found)
            fprintf(stdout,"\"engineName\": \"%s\", \"engineVersion\": \"%s\",\n", g_engine_name, g_engine_version);
        else
            fprintf(stdout,"\"engineName\": null, \"engineVersion\": null\n");

        fprintf(stdout,"}\n");
    }
    else if (output_style == OUTPUT_CSV) {

        fprintf(stdout,"\"File\",\"%s\",", filename);
        fprintf(stdout,"\"Tools Name \",\"%s\",\"Tools Version\",\"%s\",", g_tools_name, g_tools_version);
        fprintf(stdout,"\"Engine Name\",\"%s\",\"Engine Version\",\"%s\"\n", g_engine_name, g_engine_version);
    }
    else if (output_style == OUTPUT_CSV_BARE) {

        fprintf(stdout,"\"%s\",", filename);
        fprintf(stdout,"\"%s\",\"%s\",", g_tools_name, g_tools_version);
        fprintf(stdout,"\"%s\",\"%s\"\n", g_engine_name, g_engine_version);
    }
    else { // OUTPUT_DEFAULT

        fprintf(stdout, "File: %s\n", filename);

        if (g_tools_found)
            fprintf(stdout,"Tools: %s, Version: %s\n", g_tools_name, g_tools_version);
        else
            fprintf(stdout,"Tools: <unknown>\n");

        if (g_engine_found)
            fprintf(stdout,"Engine: %s, Version: %s\n", g_engine_name, g_engine_version);

        if (g_music_found)
            fprintf(stdout,"Music: %s, Version: %s\n", g_music_name, g_music_version);

        if (g_soundfx_found)
            fprintf(stdout,"SoundFX: %s, Version: %s\n", g_soundfx_name, g_soundfx_version);

        fprintf(stdout,"\n");
    }
}