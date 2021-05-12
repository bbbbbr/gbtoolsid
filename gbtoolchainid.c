

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "common.h"
#include "sig_gbdk.h"
#include "sig_zgb.h"
#include "sig_gbstudio.h"


static uint8_t * g_p_searchbuf = NULL;
static uint32_t g_searchbuf_len = 0;

char g_tools_name[MAX_STR_LEN] = "";
char g_tools_version[MAX_STR_LEN] = "";
bool g_tools_found = false;

char g_engine_name[MAX_STR_LEN] = "";
char g_engine_version[MAX_STR_LEN] = "";
bool g_engine_found = false;


static void set_search_buf(uint8_t *, uint32_t);


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


// Set the global search buffer
static void set_search_buf(uint8_t * p_rom_data, uint32_t rom_size) {
    g_p_searchbuf = p_rom_data;
    g_searchbuf_len = rom_size;
}


// Test for a pattern at a specific address
//
bool check_pattern_addr(const uint8_t * p_pattern, uint32_t pattern_len, uint32_t match_index) {

    uint8_t * p_match = g_p_searchbuf;

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
bool find_pattern(const uint8_t * p_pattern, uint32_t pattern_len) {

    uint32_t cur_addr = 0;

    if (pattern_len > g_searchbuf_len) {
        return false;
    }

    // Try to locate first possible instance
    uint8_t * p_match = memchr(g_p_searchbuf, p_pattern[0], g_searchbuf_len);
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
        p_match = memchr(p_match, p_pattern[0], remaining);
        remaining = g_searchbuf_len - (p_match - g_p_searchbuf);
    }
    return false;
}


bool gbtools_detect(uint8_t * p_rom_data, uint32_t rom_size) {

    set_search_buf(p_rom_data, rom_size);

    check_gbdk();
    // TODO: probably better to only test ZGB and GBStudio if GBDK has a positive match
    // if (check_gbdk()) {
    check_zgb();
    check_gbstudio();

    if (g_tools_found)
        printf("Tools: %s, Version: %s\n", g_tools_name, g_tools_version);
    else
        printf("Tools: <unknown>\n");

    if (g_engine_found)
        printf("Engine: %s, Version: %s\n", g_engine_name, g_engine_version);

    return true;
//    return false;
}

