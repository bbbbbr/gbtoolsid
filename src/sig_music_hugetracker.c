// This is free and unencumbered software released into the public domain.
// For more information, please refer to <https://unlicense.org>
// bbbbbr 2020

#include <stdint.h>
#include <stdbool.h>

#include "common.h"
#include "gbtoolchainid.h"


// ==== hUGETracker
// Records can be at any locations

    // _load_note_data -> lookup_note
    // https://github.com/untoxa/hUGEBuild/blame/master/hUGEDriver.asm#L332
    const uint8_t sig_hugetracker_load_note_data[] = {0x67, 0x84, 0x84, 0xC6, 0x02, 0x26, 0x00, 0x6F, 0x09, 0x3A, 0x4F, 0x3A, 0x47, 0x7E, 0xC9, };


// Check for hUGETracker sound driver
//
// If match is found: calls set_music() and returns true
//
bool check_music_hugetracker(void) {

    const char str_hugetracker[] = "hUGETracker";

    // hugetracker (all versions)
    if (find_pattern(sig_hugetracker_load_note_data, sizeof(sig_hugetracker_load_note_data))) {
        set_music(str_hugetracker, "");
        return true;
    }

    return false;
}
