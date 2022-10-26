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
        // constant : https://github.com/datguywitha3ds/CBT-FX/tree/main
        const uint8_t sig_cbtfx_info[] = "CBT-FX BY COFFEEBAT 2021";

    // ==== VAL-FX
    // Records can be at any location
        // constant: https://github.com/ISSOtm/val-fx/blob/master/val-fx.asm#L49
        const uint8_t sig_valfx_info[] = "VAL-FX BY CVB";

    // ==== VGM2GBSFX
    // Records can be at any location
        // This may also ID GBStudio 3.1.0+
        // asm : https://github.com/untoxa/VGM2GBSFX/blob/main/src/gbz80/sfxplayer.c#L61
        const uint8_t sig_vgm2gbsfx_aud3waveram_load[] = {0x2A, 0x47, 0xE6, 0x07, 0xFE, 0x05, 0x38, 0x5A, 0xFE, 0x07, 0x28, 0x50, 0xAF, 0xEA, 0x1A, 0xFF, 0x0E, 0x30, 0x2A, 0xE2, 0x0C, 0x2A, 0xE2, 0x0C};
        // Full version, but prob not needed // {0x2A, 0x47, 0xE6, 0x07, 0xFE, 0x05, 0x38, 0x5A, 0xFE, 0x07, 0x28, 0x50, 0xAF, 0xEA, 0x1A, 0xFF, 0x0E, 0x30, 0x2A, 0xE2, 0x0C, 0x2A, 0xE2, 0x0C, 0x2A, 0xE2, 0x0C, 0x2A, 0xE2, 0x0C, 0x2A, 0xE2, 0x0C, 0x2A, 0xE2, 0x0C, 0x2A, 0xE2, 0x0C, 0x2A, 0xE2, 0x0C, 0x2A, 0xE2, 0x0C, 0x2A, 0xE2, 0x0C, 0x2A, 0xE2, 0x0C, 0x2A, 0xE2, 0x0C, 0x2A, 0xE2, 0x0C, 0x2A, 0xE2, 0x0C, 0x2A, 0xE2, 0x0C, 0x2A, 0xE2, 0x0C};


// Check for Sound FX drivers
void check_soundfx(void) {

    tool_entry entry;

    entry = FORMAT_ENTRY(TYPE_SOUNDFX,"FX Hammer", "");
    if (FIND_PATTERN_STR_NOTERM(sig_fxhammer_info_1) ||
        FIND_PATTERN_STR_NOTERM(sig_fxhammer_info_2) )
        entry_add(entry);

    entry = FORMAT_ENTRY(TYPE_SOUNDFX,"CBT-FX", "");
    if (FIND_PATTERN_STR_NOTERM(sig_cbtfx_info))
        entry_add(entry);

    entry = FORMAT_ENTRY(TYPE_SOUNDFX,"VAL-FX", "");
    if (FIND_PATTERN_STR_NOTERM(sig_valfx_info))
        entry_add(entry);

    entry = FORMAT_ENTRY(TYPE_SOUNDFX,"VGM2GBSFX", "");
    if (FIND_PATTERN_BUF(sig_vgm2gbsfx_aud3waveram_load))
        entry_add(entry);
}
