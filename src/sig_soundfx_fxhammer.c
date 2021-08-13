// This is free and unencumbered software released into the public domain.
// For more information, please refer to <https://unlicense.org>
// bbbbbr 2020

#include <stdint.h>
#include <stdbool.h>

#include "common.h"
#include "entries.h"
#include "gbtoolchainid.h"


// ==== FX Hammer Player
// Records can be at any location

    // From "Sliced" 32KB SRAM File (*.sav) into two files (or ROM banks for assembler)
    // Slices a 32KB SRAM File (*.sav) into two files (or ROM banks for assembler):
        // 1) 16KB music player code and music data (*.bin)
        // "@FX HAMMER Version 1.0 (c)2000 Aleksi Eeben (email:aleksi@cncd.fi)";
        const uint8_t sig_fxhammer_info_1_0[] = {0x40, 0x46, 0x58, 0x20, 0x48, 0x41, 0x4D, 0x4D, 0x45, 0x52, 0x20, 0x56, 0x65, 0x72, 0x73, 0x69, 0x6F, 0x6E, 0x20, 0x31, 0x2E, 0x30, 0x20, 0x28, 0x63, 0x29, 0x32, 0x30, 0x30, 0x30, 0x20, 0x41, 0x6C, 0x65, 0x6B, 0x73, 0x69, 0x20, 0x45, 0x65, 0x62, 0x65, 0x6E, 0x20, 0x28, 0x65, 0x6D, 0x61, 0x69, 0x6C, 0x3A, 0x61, 0x6C, 0x65, 0x6B, 0x73, 0x69, 0x40, 0x63, 0x6E, 0x63, 0x64, 0x2E, 0x66, 0x69, 0x29, };


// Check for FX Hammer sound and sample driver
bool check_soundfx_fxhammer(void) {

    tool_entry entry = {.type = TYPE_SOUNDFX, .name = "FX Hammer", .version = "1.0"};

    // FXHammer music 1.0
    if (find_pattern(sig_fxhammer_info_1_0, sizeof(sig_fxhammer_info_1_0))) {
        entry_add(entry);
        return true;
    }

    return false;
}
