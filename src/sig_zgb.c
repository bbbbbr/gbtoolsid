// This is free and unencumbered software released into the public domain.
// For more information, please refer to <https://unlicense.org>
// bbbbbr 2020

#include <stdint.h>
#include <stdbool.h>

#include "common.h"
#include "entries.h"
#include "gbtoolchainid.h"


// ==== ZGB ====
// All ZGB records can be at any location (depends on where the linker places them)
    const uint8_t sig_zgb_sound[] = {0x05, 0x04, 0x05, 0x04, 0x03, 0x10, 0xFF, 0x16, 0xFF, 0x1A, 0xFF, 0x20, 0xFF, 0x24, 0xFF};
    const uint8_t sig_zgb_2017[] = {0xF8, 0x02, 0x4E, 0x23, 0x46, 0xF8, 0x04, 0x11, 0x41, 0xFF, 0x1A, 0xE6, 0x02};
    const uint8_t sig_zgb_2020_0_pushbank[] = {0x34, 0x4E, 0x23, 0x46, 0x02, 0x01, 0x00, 0x20, 0x02};
    const uint8_t sig_zgb_2020_0_popbank[]  = {0x35, 0x4E, 0x23, 0x46, 0x0A, 0x01, 0x00, 0x20, 0x02};
    const uint8_t sig_zgb_2020_1_plus_pushbank[] = {0x34, 0x4E, 0x23, 0x46, 0xFA, 0x90, 0xFF, 0x02, 0xF8, 0x02, 0x7E, 0xEA, 0x90, 0xFF, 0xEA, 0x00, 0x20};
    const uint8_t sig_zgb_2020_1_plus_popbank[]  = {0x4E, 0x23, 0x46, 0x0A, 0xEA, 0x90, 0xFF, 0xEA, 0x00, 0x20, 0x2B, 0x35};

    // Present in 2020.1
    // https://github.com/Zal0/ZGB/compare/v2020.1...v2020.2#diff-807655bd4ab08ec4b981f43ea2fc0d095db3078ea2b7f1ab4a3d985aa8528e0fL60
    const uint8_t sig_zgb_2020_1_settile[] = {0xF8 ,0x02 ,0x4E ,0x23 ,0x46 ,0xF8 ,0x04 ,0x11 , 0x41, 0xFF, 0x1A ,0xE6 ,0x02 ,0x20 ,0xF9 ,0x7E ,0x02 ,0xC9};
    // Present in 2020.2+
    // https://github.com/Zal0/ZGB/compare/v2020.1...v2020.2#diff-807655bd4ab08ec4b981f43ea2fc0d095db3078ea2b7f1ab4a3d985aa8528e0fR60
    const uint8_t sig_zgb_2020_2_plus_settile[] = {0xF8 ,0x02 ,0x4E ,0x23 ,0x46 ,0xF8 ,0x04 ,0xFA ,0x41 ,0xFF ,0xE6 ,0x02 ,0x20 ,0xF9 ,0x7E ,0x02 ,0xC9};

    // Present until 2021.0, removed in 2021.1
    // https://github.com/Zal0/ZGB/compare/v2021.0...v2021.1#diff-931c0cc99a46f6a0f5a477d9ff63eb1e31108cb60e6e40bb50529fa6f2380d00L75
    const uint8_t sig_zgb_2021_0_flushoamsprite[] = {0x2A, 0x02, 0x0c, 0x2A, 0x02, 0x0C, 0x2A, 0x02, 0x0C, 0x2A, 0x02, 0x0C};

    // Present in 2021.2+
    // https://github.com/Zal0/ZGB/commit/5d99766198c71da35d60c13992c80147ea47c001
    const uint8_t sig_zgb_2021_2_plus_update_attr[] = {0xF8, 0x04, 0x3A, 0x57, 0x3A, 0xB7, 0xC8, 0x5F, 0x7E, 0x87, 0x87, 0xC6, 0x03, 0x6F};

// ==== GBDK refs ====
    // For ZGB 2020.2 vs 2021.0
    const uint8_t sig_zgb_gbdk_bmp[] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
    const uint32_t sig_zgb_gbdk_bmp_2x_to_2020_320_at = 0x0010;



// TODO: early ZGB titles (2016 - 2017) aren't reliably detected. Consider dropping the sound table requirement.

// Check ZGB engine
bool check_zgb(void) {

    tool_entry entry;

    // ================== Copy & Paste can start below here ==================

    entry = FORMAT_ENTRY(TYPE_ENGINE, "ZGB", "");

    // Exception to the rule: The Squire fails this due to removing ZGB default sound consts
    // https://freshdeus.itch.io/the-squire-gameboy
    // So the requirement is relaxed for versions after 2020.0 which have additional tests
    //
    // Require sound const pattern, as starting filter
    if (FIND_PATTERN_BUF(sig_zgb_sound)) {

        if (FIND_PATTERN_BUF(sig_zgb_2017)) {
            entry_add_with_version(entry, "2016-2017");
            return true;
        }

        // ZGB 2020.0
        if ((FIND_PATTERN_BUF(sig_zgb_2020_0_pushbank)) &&
            (FIND_PATTERN_BUF(sig_zgb_2020_0_popbank))) {

            entry_add_with_version(entry, "2020.0");
            return true;
        }
    }

    // ZGB 2020.1
    if ((FIND_PATTERN_BUF(sig_zgb_2020_1_plus_pushbank)) &&
        (FIND_PATTERN_BUF(sig_zgb_2020_1_plus_popbank))) {

        if (FIND_PATTERN_BUF(sig_zgb_2020_1_settile)) {
            entry_add_with_version(entry, "2020.1");
            return true;
        }
        else if (FIND_PATTERN_BUF(sig_zgb_2020_2_plus_settile)) {

            // v2020.2 - gbdk 2020 v3.1.1 - Jun 5, 2020
            // Use sig for: GBDK 2.x - GBDK-2020 3.2.0
            if (CHECK_PATTERN_AT_ADDR(sig_zgb_gbdk_bmp,sig_zgb_gbdk_bmp_2x_to_2020_320_at)) {
                entry_add_with_version(entry, "2020.2");
                return true;
            }

            // 2021.0 -  gbdk 2020 v4.0.2 - Jan 22, 2021
            // Could also check via GBDK version
            // const uint8_t sig_gbdk_0x150[] = {0xF3, 0x57, 0xAF, 0x31};
            // const uint32_t sig_gbdk_0x150_GBDK_2020_401_to_402_at  = 0x0153;
            //
            if (FIND_PATTERN_BUF(sig_zgb_2021_0_flushoamsprite)) {
                entry_add_with_version(entry, "2021.0");
                return true;
            }
            else {
                // 2021.1+ - ZGB        2021.1: Removed FlushOAMSprite inline asm


                // 2021.2+
                if (FIND_PATTERN_BUF(sig_zgb_2021_2_plus_update_attr)) {
                    // entry_check_match() Relies on GBDK tool check being run before ZGB is tested (it is)

                    // Not sure whether there is a discernable 2021.2 and 2021.3 division
                    // The crt0 in the zip file is the same between the two releases (4.0.5.v1),
                    // yet some games (MHz Athletic World Demo) have the old 4.0.5.zgb + asm update_attr
                    if (entry_check_match(TYPE_TOOLS, STR_GBDK, STR_GBDK_2020_4_0_5_v0_zgb) ||
                        entry_check_match(TYPE_TOOLS, STR_GBDK, STR_GBDK_2020_4_0_5_v1_retracted)) {
                        entry_add_with_version(entry, "2021.2 - 2021.3");
                        return true;
                    }
                    // 2022.2 uses GBDK 4.1.0
                    if (entry_check_match(TYPE_TOOLS, STR_GBDK, STR_GBDK_2020_4_1_0_plus)) {
                        entry_add_with_version(entry, "2022.0+");
                        return true;
                    }
                }
                // 2021.1
                // Since it's not 2021.2+, can test for 2021.1 using the version shared with 2021.2
                else if (entry_check_match(TYPE_TOOLS, STR_GBDK, STR_GBDK_2020_4_0_5_v0_zgb)) {
                    entry_add_with_version(entry, "2021.1");
                    return true;
                }

                // It's ZGB 2020.2+ something, but unclear what version
                entry_add_with_version(entry, "Unknown");
                return true;
            }
        }
    }

    return false;
}
