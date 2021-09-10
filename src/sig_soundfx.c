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

// ==== CBT-FX
// Records can be at any location
        const uint8_t sig_cbtfx_info[] = "CBT-FX BY COFFEEBAT 2021";

// Check for Sound FX drivers
void check_soundfx(void) {

    tool_entry entry;

    // FXHammer music 1.0
    entry = (tool_entry){.type = TYPE_SOUNDFX, .c_name = "FX Hammer", .c_version = ""};
    if (find_pattern(sig_fxhammer_info_1, sizeof_str_noterm(sig_fxhammer_info_1)) ||
        find_pattern(sig_fxhammer_info_2, sizeof_str_noterm(sig_fxhammer_info_2)) )
        entry_add(entry);

    // CBT-FX : https://github.com/datguywitha3ds/CBT-FX/tree/main
    entry = (tool_entry){.type = TYPE_SOUNDFX, .c_name = "CBT-FX", .c_version = ""};
    if (find_pattern(sig_cbtfx_info, sizeof_str_noterm(sig_cbtfx_info)))
        entry_add(entry);
}
