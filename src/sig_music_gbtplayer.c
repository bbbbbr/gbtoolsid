// This is free and unencumbered software released into the public domain.
// For more information, please refer to <https://unlicense.org>
// bbbbbr 2020

#include <stdint.h>
#include <stdbool.h>

#include "common.h"
#include "entries.h"
#include "gbtoolchainid.h"


// ==== gbt_player
// Records can be at any location (appears to be the same between GBDK and RGBDS versions)
//
// gbt_wave: ; 8 sounds
    const uint8_t sig_gbtplayer_gbt_wave[] = {
        0xA5, 0xD7, 0xC9, 0xE1, 0xBC, 0x9A, 0x76, 0x31, 0x0C, 0xBA, 0xDE, 0x60, 0x1B, 0xCA, 0x03, 0x93,
        0xF0, 0xE1, 0xD2, 0xC3, 0xB4, 0xA5, 0x96, 0x87, 0x78, 0x69, 0x5A, 0x4B, 0x3C, 0x2D, 0x1E, 0x0F,
        0xFD, 0xEC, 0xDB, 0xCA, 0xB9, 0xA8, 0x97, 0x86, 0x79, 0x68, 0x57, 0x46, 0x35, 0x24, 0x13, 0x02};

// Check for gbt_player sound driver
bool check_music_gbtplayer(void) {

    tool_entry entry = {.type = TYPE_MUSIC, .name = "GBT Player", .version = ""};

    // gbtplayer (all versions)
    if (find_pattern(sig_gbtplayer_gbt_wave, sizeof(sig_gbtplayer_gbt_wave))) {
        entry_add(entry);
        return true;
    }

    return false;
}
