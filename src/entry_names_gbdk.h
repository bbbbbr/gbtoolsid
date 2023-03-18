
#include <stdbool.h>
#include <stdint.h>

#include "common.h"

#ifndef _ENTRY_NAMES_GBDK_H
#define _ENTRY_NAMES_GBDK_H


    // ==== SHARED CODE WITH C STARTS HERE ====

    // These are also used by GBStudio and ZGB
    // Tool
    DEF_NAME_STR(STR_GBDK, "GBDK");
    // Versions
    DEF_NAME_STR(STR_GBDK_2_x_to_2020_3_2_0,       "2.x - 2020.3.2.0");
    DEF_NAME_STR(STR_GBDK_2020_4_0_0,              "2020.4.0.0");
    DEF_NAME_STR(STR_GBDK_2020_4_0_1_to_4_0_2,     "2020.4.0.1 - 2020.4.0.2");
    DEF_NAME_STR(STR_GBDK_2020_4_0_3,              "2020.4.0.3");
    DEF_NAME_STR(STR_GBDK_2020_4_0_4,              "2020.4.0.4");
    DEF_NAME_STR(STR_GBDK_2020_4_0_5_v0_zgb,       "2020.4.0.5.v0.zgb");
    DEF_NAME_STR(STR_GBDK_2020_4_0_5_v1_retracted, "2020.4.0.5.v1.retracted");
    DEF_NAME_STR(STR_GBDK_2020_4_0_5_to_4_0_6,     "2020.4.0.5 - 2020.4.0.6");
    DEF_NAME_STR(STR_GBDK_2020_4_1_0_to_4_1_1,     "2020.4.1.0 - 2020.4.1.1");
    DEF_NAME_STR(STR_GBDK_2020_4_2_0_plus,         "2020.4.2.0+");
    DEF_NAME_STR(STR_GBDK_2020_4_UNKNOWN,          "Unknown");


    // ==== GBDK ====
    //
    // These are almost all in crt0.s
    //
    // Bitmap defines
    DEF_PATTERN_BUF(sig_gbdk_bmp, AR_ARGS(0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80));
    DEF_PATTERN_ADDR(sig_gbdk_bmp_2x_to_2020_320_at, 0x0010);
    DEF_PATTERN_ADDR(sig_gbdk_bmp_2020_400_plus_at, 0x0070); // This entry may or MAY NOT be present for GBDK-2020 4.0.0+
    // 0x20
    DEF_PATTERN_ADDR(sig_gbdk_0x20_at, 0x0020);
    // First Entry is ambiguous, must be combined
    //DEF_PATTERN_BUF(sig_gbdk_0x20_GBDK_2x_to_2020_320, AR_ARGS(0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF));
    DEF_PATTERN_BUF(sig_gbdk_0x20_GBDK_2020_400_0x20, AR_ARGS(0xE9)); // {0xE9, 0xFF, 0xFF, 0xFF));
    DEF_PATTERN_BUF(sig_gbdk_0x20_GBDK_2020_401_plus_0x20, AR_ARGS(0xE9)); // {0xE9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x22, 0x0D, 0x20, 0xFC, 0xC9, 0xFF, 0xFF, 0xFF));
    // 0x28
    DEF_PATTERN_ADDR(sig_gbdk_0x28_at, 0x0028);
    DEF_PATTERN_BUF(sig_gbdk_0x20_GBDK_2020_401_plus_0x28, AR_ARGS(0x22, 0x0D, 0x20, 0xFC, 0xC9)); // {0xE9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x22, 0x0D, 0x20, 0xFC, 0xC9, 0xFF, 0xFF, 0xFF));

    // 0x30
    DEF_PATTERN_ADDR(sig_gbdk_0x30_at, 0x0030);
    // First Entry is ambiguous, must be combined
    // DEF_PATTERN_BUF(sig_gbdk_0x20_GBDK_2x_to_2020_400, AR_ARGS(0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
    //
    DEF_PATTERN_BUF(sig_gbdk_0x30_GBDK_2020_401_plus, AR_ARGS(0x1A, 0x22, 0x13, 0x0D, 0x20, 0xFA, 0xC9));
        // Had to shorten this for builds which have the crashhandler installed
        // Previously:
        // DEF_PATTERN_BUF(sig_gbdk_0x30_GBDK_2020_401_plus, AR_ARGS(0x1A, 0x22, 0x13, 0x0D, 0x20, 0xFA, 0xC9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF));
        // Or could also check for the crashhandler as an alternate
        // DEF_PATTERN_BUF(sig_gbdk_0x30_GBDK_2020_401_plus_with_crashhandler, AR_ARGS(0x1A, 0x22, 0x13, 0x0D, 0x20, 0xFA, 0xC9, 0xFF, 0xF3, 0xC3, 0x00, 0x02, 0xFF, 0xFF, 0xFF, 0xFF));
    // 0x80
    DEF_PATTERN_ADDR(sig_gbdk_0x80_at, 0x0080);
    DEF_PATTERN_BUF(sig_gbdk_0x80_GBDK_4_0_0, AR_ARGS(0xC5, 0xD5, 0x2A, 0xB6, 0x28, 0x09, 0xE5, 0x3A, 0x6E, 0x67, 0xE7, 0xE1, 0x23, 0x18, 0xF3, 0xD1, 0xC1, 0xE1, 0xF0, 0x41, 0xE6, 0x02, 0x20, 0xFA, 0xF1, 0xD9));

    // 0xCC
    // In 4.2.0 crt0.s vsync/wait_vbl_done moved from ~0x250 -> 0xCC
    DEF_PATTERN_ADDR(sig_gbdk_0xCC_at, 0x00CC);
    DEF_PATTERN_BUF(sig_gbdk_0xCC_GBDK_4_2_0_vsync, AR_ARGS(0xF0, 0x40, 0xE6, 0x80, 0xC8, 0xAF, 0xE0, 0x91, 0x76, 0x00, 0xF0, 0x91, 0xB7, 0x28, 0xF9, 0xC9));

    // 0x100
    DEF_PATTERN_ADDR(sig_gbdk_0x100_at, 0x0100);
    DEF_PATTERN_BUF(sig_gbdk_0x100_GBDK_4_0_4, AR_ARGS(0x18, 0x51));
    // ZGB uses a pre-release 4.0.5 where .code_start has been moved down, but is missing _refresh_OAM:: and .clear_WRAM
    DEF_PATTERN_BUF(sig_gbdk_0x100_GBDK_4_0_5_v0_zgb, AR_ARGS(0x18, 0x55));
    // 0x150
        // These should only be used when stacked on other entries
        DEF_PATTERN_BUF(sig_gbdk_0x150, AR_ARGS(0xF3, 0x57, 0xAF, 0x31));
            // This one is incorrect, 4.0.1 and 4.0.2 have an indistinguishable crt0.s
                // DEF_PATTERN_ADDR(sig_gbdk_0x150_GBDK_2x_to_2020_401_at, 0x0150);
        DEF_PATTERN_ADDR(sig_gbdk_0x150_GBDK_2020_401_to_402_at, 0x0153);
        // 0x0153
        DEF_PATTERN_BUF(sig_gbdk_0x153_GBDK_2020_403_plus, AR_ARGS(0xF3, 0x57, 0x31));
        DEF_PATTERN_ADDR(sig_gbdk_0x153_GBDK_2020_403_plus_at, 0x0153);
        // 0x0157
        DEF_PATTERN_BUF(sig_gbdk_0x157_GBDK_2020_405_plus, AR_ARGS(0xF3, 0x57, 0x58, 0x31));
        DEF_PATTERN_ADDR(sig_gbdk_0x157_GBDK_2020_405_plus_at, 0x0157);
        // _refresh_OAM:: crt0.s JP (HL) was replaced with // JP      .refresh_OAM + (.refresh_OAM_DMA - .start_refresh_OAM)
        DEF_PATTERN_BUF(sig_gbdk_0x157_GBDK_2020_405_v1, AR_ARGS(0xF3, 0x57, 0x58, 0x31));
        DEF_PATTERN_ADDR(sig_gbdk_0x157_GBDK_2020_405_v1_at, 0x0157);
    // .clear_WRAM:: Tail
            // Single instruction test is ok, but there is a slightly larger block shortly after:
            // DEF_PATTERN_BUF(sig_gbdk_0x00B7_GBDK_2020_410_plus, AR_ARGS(0xAF)); // "xor a".Was [0xD5, 0xAF] (push de, xor a)
            // DEF_PATTERN_ADDR(sig_gbdk_0x00B7_GBDK_2020_410_plus_at, 0x00B7);
        // 4.0.5-v1 crt0.s : had a "JP (HL)" after "_refresh_OAM::" ->  removed in 4.1.0 -> which shifted most of ".clear_WRAM:"
        DEF_PATTERN_BUF( sig_gbdk_clear_WRAM_tail_GBDK_2020_405_v1, AR_ARGS(0x67, 0xAF, 0x6F, 0x0E, 0xA0, 0xEF, 0xD1, 0xC9));
        DEF_PATTERN_ADDR(sig_gbdk_clear_WRAM_tail_GBDK_2020_405_v1_at, 0x00C7);
            // Optional extra test for 4.0.5.v1: 0x00B7: 0xE9 (jp hl) -> 4.0.5.v2 / 4.0.6  0x00B7: 0xD5  ("push de" got bumped upward to 0xB7)
        // 4.0.5-v2 / 4.0.5 crt0.s : had a "push de" after ".clear_WRAM:" which shifted everything one byte earlier in ROM
        DEF_PATTERN_BUF( sig_gbdk_clear_WRAM_tail_GBDK_2020_405_v2_to_406, AR_ARGS(0x67, 0xAF, 0x6F, 0x0E, 0xA0, 0xEF, 0xD1, 0xC9));
        DEF_PATTERN_ADDR(sig_gbdk_clear_WRAM_tail_GBDK_2020_405_v2_to_406_at, 0x00C6);
        // 4.1.0+
        DEF_PATTERN_BUF( sig_gbdk_clear_WRAM_tail_GBDK_2020_410_plus, AR_ARGS(0x67, 0xAF, 0x6F, 0x0E, 0xA0, 0xEF, 0xC9));
        DEF_PATTERN_ADDR(sig_gbdk_clear_WRAM_tail_GBDK_2020_410_plus_at, 0x00C5);

    // ==== SHARED CODE WITH C ENDS HERE ====


#endif // _ENTRY_NAMES_GBDK_H
