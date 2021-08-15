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
        // FX@HAMMER@V1:0@@@ ... @<2000@ALEKSI@EEBEN@
        const uint8_t sig_fxhammer_info_1[] = "FX HAMMER";
        const uint8_t sig_fxhammer_info_2[] = "FX@HAMMER";

// Check for Sound FX drivers
void check_soundfx(void) {

    tool_entry entry = {.type = TYPE_SOUNDFX, .name = "FX Hammer", .version = ""};

    // FXHammer music 1.0
    if (find_pattern(sig_fxhammer_info_1, sizeof_str_noterm(sig_fxhammer_info_1)) ||
        find_pattern(sig_fxhammer_info_2, sizeof_str_noterm(sig_fxhammer_info_2))
        )
        entry_add(entry);
}
