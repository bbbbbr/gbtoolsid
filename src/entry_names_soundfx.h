
#include <stdbool.h>
#include <stdint.h>

#include "common.h"

#ifndef _ENTRY_NAMES_SOUNDFX_H
#define _ENTRY_NAMES_SOUNDFX_H


    // ==== FX Hammer Player
    // Records can be at any location

        // From "Sliced" 32KB SRAM File (*.sav) into two files (or ROM banks for assembler)
        // Slices a 32KB SRAM File (*.sav) into two files (or ROM banks for assembler):
            // 1) 16KB music player code and music data (*.bin)
            // "@FX HAMMER Version 1.0 (c)2000 Aleksi Eeben (email:aleksi@cncd.fi)";
            // FX@HAMMER@V1:0@@@ ... @<2000@ALEKSI@EEBEN@
            DEF_PATTERN_STR(sig_fxhammer_info_1, "FX HAMMER");
            DEF_PATTERN_STR(sig_fxhammer_info_2, "FX@HAMMER");

    // ==== CBT-FX
    // Records can be at any location
        // constant : https://github.com/datguywitha3ds/CBT-FX/tree/main
        DEF_PATTERN_STR(sig_cbtfx_info, "CBT-FX BY COFFEEBAT 2021");

    // ==== VAL-FX
    // Records can be at any location
        // constant: https://github.com/ISSOtm/val-fx/blob/master/val-fx.asm#L49
        DEF_PATTERN_STR(sig_valfx_info, "VAL-FX BY CVB");

    // ==== VGM2GBSFX
    // Records can be at any location
        // This may also ID GBStudio 3.1.0+
        // asm : https://github.com/untoxa/VGM2GBSFX/blob/main/src/gbz80/sfxplayer.c#L61
        DEF_PATTERN_BUF(sig_vgm2gbsfx_aud3waveram_load, AR_ARGS(0x2A, 0x47, 0xE6, 0x07, 0xFE, 0x05, 0x38, 0x5A, 0xFE, 0x07, 0x28, 0x50, 0xAF, 0xEA, 0x1A, 0xFF, 0x0E, 0x30, 0x2A, 0xE2, 0x0C, 0x2A, 0xE2, 0x0C));
        // Full version, but prob not needed // {0x2A, 0x47, 0xE6, 0x07, 0xFE, 0x05, 0x38, 0x5A, 0xFE, 0x07, 0x28, 0x50, 0xAF, 0xEA, 0x1A, 0xFF, 0x0E, 0x30, 0x2A, 0xE2, 0x0C, 0x2A, 0xE2, 0x0C, 0x2A, 0xE2, 0x0C, 0x2A, 0xE2, 0x0C, 0x2A, 0xE2, 0x0C, 0x2A, 0xE2, 0x0C, 0x2A, 0xE2, 0x0C, 0x2A, 0xE2, 0x0C, 0x2A, 0xE2, 0x0C, 0x2A, 0xE2, 0x0C, 0x2A, 0xE2, 0x0C, 0x2A, 0xE2, 0x0C, 0x2A, 0xE2, 0x0C, 0x2A, 0xE2, 0x0C, 0x2A, 0xE2, 0x0C, 0x2A, 0xE2, 0x0C};
        // Updated version:
        // 2023/02/19+
        // https://github.com/untoxa/VGM2GBSFX/blob/62108bca3afd282ebb6177902d21fb2bebe6f5e6/src/sm83/sfxplayer.c#L60C1-L79C39
        DEF_PATTERN_BUF(sig_vgm2gbsfx_aud3waveram_load_v2, AR_ARGS(0x2A, 0x47, 0xE6, 0x07, 0xFE, 0x05, 0x38,  0x62, 0xFE, 0x07, 0x28, 0x58, 0xF0, 0x25, 0x4F, 0xE6, 0xBB, 0xE0, 0x25, 0xAF, 0xEA, 0x1A, 0xFF, 0x2A, 0xE0, 0x30, 0x2A, 0xE0, 0x31, 0x2A,));

    // ==== DevSFX
        // https://github.com/DevEd2/potion-panic/blob/ccf7a8283aa05e16c29db0a9d6996c7e134f7628/Audio/DevSFX.asm#L393
        DEF_PATTERN_STR(sig_str_DevSFX, "DevSFX sound effect engine by DevEd");


#endif // _ENTRY_NAMES_SOUNDFX_H
