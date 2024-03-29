
#include <stdbool.h>
#include <stdint.h>

#include "common.h"

#ifndef _ENTRY_NAMES_ZGB_H
#define _ENTRY_NAMES_ZGB_H


    // ==== SHARED CODE WITH C STARTS HERE ====

    // ==== ZGB ====
    // All ZGB records can be at any location (depends on where the linker places them)
    DEF_PATTERN_BUF(sig_zgb_sound, AR_ARGS(0x05, 0x04, 0x05, 0x04, 0x03, 0x10, 0xFF, 0x16, 0xFF, 0x1A, 0xFF, 0x20, 0xFF, 0x24, 0xFF));
    DEF_PATTERN_BUF(sig_zgb_2017, AR_ARGS(0xF8, 0x02, 0x4E, 0x23, 0x46, 0xF8, 0x04, 0x11, 0x41, 0xFF, 0x1A, 0xE6, 0x02));
    DEF_PATTERN_BUF(sig_zgb_2020_0_pushbank, AR_ARGS(0x34, 0x4E, 0x23, 0x46, 0x02, 0x01, 0x00, 0x20, 0x02));
    DEF_PATTERN_BUF(sig_zgb_2020_0_popbank, AR_ARGS(0x35, 0x4E, 0x23, 0x46, 0x0A, 0x01, 0x00, 0x20, 0x02));
    DEF_PATTERN_BUF(sig_zgb_2020_1_plus_pushbank, AR_ARGS(0x34, 0x4E, 0x23, 0x46, 0xFA, 0x90, 0xFF, 0x02, 0xF8, 0x02, 0x7E, 0xEA, 0x90, 0xFF, 0xEA, 0x00, 0x20));
    DEF_PATTERN_BUF(sig_zgb_2020_1_plus_popbank, AR_ARGS(0x4E, 0x23, 0x46, 0x0A, 0xEA, 0x90, 0xFF, 0xEA, 0x00, 0x20, 0x2B, 0x35));

    // Present in 2020.1
    // https://github.com/Zal0/ZGB/compare/v2020.1...v2020.2#diff-807655bd4ab08ec4b981f43ea2fc0d095db3078ea2b7f1ab4a3d985aa8528e0fL60
    DEF_PATTERN_BUF(sig_zgb_2020_1_settile, AR_ARGS(0xF8 ,0x02 ,0x4E ,0x23 ,0x46 ,0xF8 ,0x04 ,0x11 , 0x41, 0xFF, 0x1A ,0xE6 ,0x02 ,0x20 ,0xF9 ,0x7E ,0x02 ,0xC9));
    // Present in 2020.2+
    // https://github.com/Zal0/ZGB/compare/v2020.1...v2020.2#diff-807655bd4ab08ec4b981f43ea2fc0d095db3078ea2b7f1ab4a3d985aa8528e0fR60
    DEF_PATTERN_BUF(sig_zgb_2020_2_plus_settile, AR_ARGS(0xF8 ,0x02 ,0x4E ,0x23 ,0x46 ,0xF8 ,0x04 ,0xFA ,0x41 ,0xFF ,0xE6 ,0x02 ,0x20 ,0xF9 ,0x7E ,0x02 ,0xC9));

    // Present until 2021.0, removed in 2021.1
    // https://github.com/Zal0/ZGB/compare/v2021.0...v2021.1#diff-931c0cc99a46f6a0f5a477d9ff63eb1e31108cb60e6e40bb50529fa6f2380d00L75
    DEF_PATTERN_BUF(sig_zgb_2021_0_flushoamsprite, AR_ARGS(0x2A, 0x02, 0x0c, 0x2A, 0x02, 0x0C, 0x2A, 0x02, 0x0C, 0x2A, 0x02, 0x0C));

    // Present in 2021.2+
    // https://github.com/Zal0/ZGB/commit/5d99766198c71da35d60c13992c80147ea47c001
    DEF_PATTERN_BUF(sig_zgb_2021_2_plus_update_attr, AR_ARGS(0xF8, 0x04, 0x3A, 0x57, 0x3A, 0xB7, 0xC8, 0x5F, 0x7E, 0x87, 0x87, 0xC6, 0x03, 0x6F));

    // ==== GBDK refs ====
    // For ZGB 2020.2 vs 2021.0
    DEF_PATTERN_BUF(sig_zgb_gbdk_bmp, AR_ARGS(0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80));
    DEF_PATTERN_ADDR(sig_zgb_gbdk_bmp_2x_to_2020_320_at, 0x0010);

    // ==== SHARED CODE WITH C ENDS HERE ====


#endif // _ENTRY_NAMES_ZGB_H
