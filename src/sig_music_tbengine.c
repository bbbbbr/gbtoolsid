// This is free and unencumbered software released into the public domain.
// For more information, please refer to <https://unlicense.org>
// bbbbbr 2020

#include <stdint.h>
#include <stdbool.h>

#include "common.h"
#include "gbtoolchainid.h"


// ==== tbengine
// No known use at the time of adding this, but why not :)
//
// Records can be at any location

    // tables.asm, tbe_dNoiseTable:
    const uint8_t sig_tbengine_noisetable[] = {
            0xD7, 0xD6, 0xD5, 0xD4, 0xC7, 0xC6, 0xC5, 0xC4, 0xB7, 0xB6, 0xB5, 0xB4,
            0xA7, 0xA6, 0xA5, 0xA4, 0x97, 0x96, 0x95, 0x94, 0x87, 0x86, 0x85, 0x84,
            0x77, 0x76, 0x75, 0x74, 0x67, 0x66, 0x65, 0x64, 0x57, 0x56, 0x55, 0x54};
            // Continues below, but above is probably sufficient
            // 0x47, 0x46, 0x45, 0x44, 0x37, 0x36, 0x35, 0x34, 0x27, 0x26, 0x25, 0x24,
            // 0x17, 0x16, 0x15, 0x14, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 0x00};


// Check for tbengine sound driver
//
// If match is found: calls set_music() and returns true
//
bool check_music_tbengine(void) {

    const char str_tbengine[] = "Trackerboy engine";

    // tbengine (all versions)
    if (find_pattern(sig_tbengine_noisetable, sizeof(sig_tbengine_noisetable))) {
        set_music(str_tbengine, "");
        return true;
    }

    return false;
}
