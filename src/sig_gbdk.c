// This is free and unencumbered software released into the public domain.
// For more information, please refer to <https://unlicense.org>
// bbbbbr 2020

#include <stdint.h>
#include <stdbool.h>

#include "common.h"
#include "entries.h"
#include "gbtoolchainid.h"

#include "entry_names_gbdk.h"

// Check for GBDK 2.x - GBDK-2020
bool check_gbdk(void) {

    tool_entry entry;

    entry = FORMAT_ENTRY(TYPE_TOOLS, STR_GBDK, "");

    // GBDK-2020 4.0.0
    if (CHECK_PATTERN_AT_ADDR(sig_gbdk_0x80_GBDK_4_0_0, sig_gbdk_0x80_at)) {
        // GBDK-2020 4.0.0 (Additional test to strengthen match)
        if (CHECK_PATTERN_AT_ADDR(sig_gbdk_0x20_GBDK_2020_400_0x20, sig_gbdk_0x20_at)) {
            entry_add_with_version(entry, STR_GBDK_2020_4_0_0);
            return true;
        }
    }

    // GBDK 2.x - GBDK-2020 3.2.0
    if (CHECK_PATTERN_AT_ADDR(sig_gbdk_bmp, sig_gbdk_bmp_2x_to_2020_320_at)) {
        // GBDK-2020 3.2.0
        if (CHECK_PATTERN_AT_ADDR(sig_gbdk_0x164_GBDK_320, sig_gbdk_0x164_GBDK_320_at)) {
            entry_add_with_version(entry, STR_GBDK_2020_3_2_0);
            return true;
        }

        // GBDK 2.9.0 - GBDK-2020 3.1.0
        if (CHECK_PATTERN_AT_ADDR(sig_gbdk_0x1c2_GBDK_29x, sig_gbdk_0x1c2_GBDK_29x_at)) {
            // GBDK 2.9.5 - GBDK-2020 3.1.0
            if (CHECK_PATTERN_AT_ADDR(sig_gbdk_0x1ca_GBDK_295, sig_gbdk_0x1ca_GBDK_295_at)) {
                entry_add_with_version(entry, STR_GBDK_2_9_5_to_2020_3_1_0);
                return true;
            }

            // GBDK 2.9.0 - GBDK 2.9.4
            entry_add_with_version(entry, STR_GBDK_2_9_0_to_2_9_4);
            return true;
        }

        // GBDK 2.0.18 - GBDK 2.0.15
        if (CHECK_PATTERN_AT_ADDR(sig_gbdk_0x1c2_GBDK_2018_to_215, sig_gbdk_0x1c2_GBDK_2018_to_215_at)) {
            entry_add_with_version(entry, STR_GBDK_2_0_18_to_2_1_5);
            return true;
        }

        // GBDK 2.0.x - GBDK 2.0.17
        if (CHECK_PATTERN_AT_ADDR(sig_gbdk_0x1c2_GBDK_20x_to_2017, sig_gbdk_0x1c2_GBDK_20x_to_2017_at)) {
            entry_add_with_version(entry, STR_GBDK_2_0_x_to_2_0_17);
            return true;
        }

        // GBDK 2.x, cannot narrow down further
        // (for example, Demotronic uses a modified crt0 which fails the above checks)
        entry_add_with_version(entry, STR_GBDK_2_x);
        return true;
    }


    // GBDK-2020 4.0.1 and later
    if ((CHECK_PATTERN_AT_ADDR(sig_gbdk_0x20_GBDK_2020_401_plus_0x20, sig_gbdk_0x20_at)) &&
        (CHECK_PATTERN_AT_ADDR(sig_gbdk_0x20_GBDK_2020_401_plus_0x28, sig_gbdk_0x28_at))) {

        // GBDK-2020 4.0.1 and later (Additional test to strengthen match)
        if (CHECK_PATTERN_AT_ADDR(sig_gbdk_0x30_GBDK_2020_401_plus, sig_gbdk_0x30_at)) {

            //  GBDK-2020 4.0.1 - 4.0.2
            if (CHECK_PATTERN_AT_ADDR(sig_gbdk_0x150, sig_gbdk_0x150_GBDK_2020_401_to_402_at)) {
                entry_add_with_version(entry, STR_GBDK_2020_4_0_1_to_4_0_2);
                return true;
            }

            // GBDK-2020 4.0.3 - 4.0.4
            if (CHECK_PATTERN_AT_ADDR(sig_gbdk_0x153_GBDK_2020_403_plus, sig_gbdk_0x153_GBDK_2020_403_plus_at)) {

                // GBDK-2020 4.0.4 and later
                if (CHECK_PATTERN_AT_ADDR(sig_gbdk_0x100_GBDK_4_0_4, sig_gbdk_0x100_at)) {
                    entry_add_with_version(entry, STR_GBDK_2020_4_0_4);
                    return true;
                }

                entry_add_with_version(entry, STR_GBDK_2020_4_0_3);
                return true;
            }

            // 4.0.5+
            if (CHECK_PATTERN_AT_ADDR(sig_gbdk_0x157_GBDK_2020_405_plus, sig_gbdk_0x157_GBDK_2020_405_plus_at)) {

                // 4.0.5.v1 was retracted and binaries replaced after 2 months. Maybe only available in ZGB 2021.2?
                if (CHECK_PATTERN_AT_ADDR(sig_gbdk_clear_WRAM_tail_GBDK_2020_405_v1, sig_gbdk_clear_WRAM_tail_GBDK_2020_405_v1_at)) {
                    entry_add_with_version(entry, STR_GBDK_2020_4_0_5_v1_retracted);
                    return true;
                }
                // Standard 4.0.5 (non-retracted 4.0.5.v1) cannot be distinguished from 4.0.6 based on the contents of crt0.s
                else if (CHECK_PATTERN_AT_ADDR(sig_gbdk_clear_WRAM_tail_GBDK_2020_405_v2_to_406, sig_gbdk_clear_WRAM_tail_GBDK_2020_405_v2_to_406_at)) {
                    entry_add_with_version(entry, STR_GBDK_2020_4_0_5_to_4_0_6);
                    return true;
                }
                // 4.1.0+
                else if (CHECK_PATTERN_AT_ADDR(sig_gbdk_clear_WRAM_tail_GBDK_2020_410_plus, sig_gbdk_clear_WRAM_tail_GBDK_2020_410_plus_at)) {

                    if (CHECK_PATTERN_AT_ADDR(sig_gbdk_0xCC_GBDK_4_2_0_vsync, sig_gbdk_0xCC_at))
                        entry_add_with_version(entry, STR_GBDK_2020_4_2_0_interim);
                    else
                        entry_add_with_version(entry, STR_GBDK_2020_4_1_0_to_4_1_1);

                    return true;
                }
                // 4.2.0+
                else if (CHECK_PATTERN_AT_ADDR(sig_gbdk_clear_WRAM_tail_GBDK_2020_420, sig_gbdk_clear_WRAM_tail_GBDK_2020_420_at)) {

                    // 4.3.0+
                    if (CHECK_PATTERN_AT_ADDR(sig_gbdk_clear_WRAM_tail_GBDK_2020_430_plus, sig_gbdk_clear_WRAM_tail_GBDK_2020_430_plus_at)) {

                        entry_add_with_version(entry, STR_GBDK_2020_4_3_0_plus);
                        return true;
                    }

                    entry_add_with_version(entry, STR_GBDK_2020_4_2_0);
                    return true;
                }
                // Some ZGB versions uses a GBDK version somewhere between 4.0.4 and 4.0.5.v1
                else if (CHECK_PATTERN_AT_ADDR(sig_gbdk_0x100_GBDK_4_0_5_v0_zgb, sig_gbdk_0x100_at)) {

                    entry_add_with_version(entry, STR_GBDK_2020_4_0_5_v0_zgb);
                    return true;
                }
            }

            // Optional broader detection
            // It's GBDK 4.x but unclear what version
            entry_add_with_version(entry, STR_GBDK_2020_4_UNKNOWN);

        } // end GBDK-2020 4.0.1 and later extra match
    } // end GBDK-2020 4.0.1 and later

    // GBDK 1.x - 2.0.x
    if ((CHECK_PATTERN_AT_ADDR(sig_gbdk_0x150_GBDK_1_x, sig_gbdk_0x150_GBDK_1_x_at)) &&
        (CHECK_PATTERN_AT_ADDR(sig_gbdk_0x158_GBDK_1_x, sig_gbdk_0x158_GBDK_1_x_at))) {
        entry_add_with_version(entry, STR_GBDK_1_x_to_2_0_x);
        return true;
    }

    return false;
}
