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
#include "sig_turborascal.h"
#include "sig_gbforth.h"
#include "sig_gbbasic.h"
#include "sig_gbnim.h"

#include "sig_music.h"

#include "sig_soundfx.h"

static uint8_t * g_p_searchbuf = NULL;
static uint32_t g_searchbuf_len = 0;
static uint32_t addr_last_match = 0;


static void set_search_buf(uint8_t *, uint32_t);

// Set the global search buffer
static void set_search_buf(uint8_t * p_rom_data, uint32_t rom_size) {
    // Reset from any previous searches (only matters with web/emscripten runtime)
    addr_last_match = 0;

    g_p_searchbuf = p_rom_data;
    g_searchbuf_len = rom_size;
}

uint32_t get_addr_last_match(void) {
    return addr_last_match;
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

    if (memcmp(&p_match[match_index], p_pattern, pattern_len) == 0) {
            #ifdef DEBUG_LOG_MATCHES
                printf("At: 0x%08x\n", match_index);
                for (int c=0; c < pattern_len; c++)
                    printf("0x%02x, ", p_pattern[c]);
                printf("\n\n");
            #endif
        addr_last_match = match_index;
        return true;
    }
    else
        return false;
}


// Try to find a pattern in a buffer
//
// No memmem on MinGW, so use the same for both instead of:
// return (memmem(g_p_searchbuf, g_searchbuf_len, p_pattern, pattern_len) != NULL);
//
bool find_pattern(const uint8_t * p_pattern, uint32_t pattern_len) {

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
                addr_last_match = (uint32_t)(p_match - g_p_searchbuf);
                #ifdef DEBUG_LOG_MATCHES
                    printf("At: 0x%08x\n", addr_last_match);
                    for (int c=0; c < pattern_len; c++)
                        printf("0x%02x, ", p_pattern[c]);
                    printf("\n\n");
                #endif
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

    bool result_gbdk = false;

    set_search_buf(p_rom_data, rom_size);

    // Note: GBStudio entry_check_match() relies on GBDK tool check being run here before ZGB is tested
    result_gbdk = check_gbdk();

    // If strict mode is turned on, only test
    // for ZGB, GBStudio, GBBasic when GBDK is present
    if ((strict_mode == false) || (result_gbdk == true)) {
        check_zgb();
        check_gbstudio();
        check_gbbasic();
    }

    // Various other toolchains
    check_turborascal();
    check_gbforth();
    check_gbnim();

    // Check for music drivers
    // May report multiple drivers (if found) in default output mode
    check_music();

    // Check for sound fx drivers
    check_soundfx();
}

