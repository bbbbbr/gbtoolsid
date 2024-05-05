// This is free and unencumbered software released into the public domain.
// For more information, please refer to <https://unlicense.org>
// bbbbbr 2020

#include <stdint.h>
#include <stdbool.h>

#include "common.h"
#include "entries.h"
#include "gbtoolchainid.h"

#include "entry_names_gbdk.h"
#include "entry_names_zgb.h"


// TODO: early ZGB titles (2016 - 2017) aren't reliably detected. Consider dropping the sound table requirement.

// Check ZGB engine
bool check_zgb(void) {

    tool_entry entry;

    // ==== SHARED CODE WITH C STARTS HERE ====

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
            // DEF_PATTERN_BUF(sig_gbdk_0x150, AR_ARGS(0xF3, 0x57, 0xAF, 0x31));
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
                    // 2022.0 uses GBDK 4.1.0
                    if (entry_check_match(TYPE_TOOLS, STR_GBDK, STR_GBDK_2020_4_1_0_to_4_1_1)) {
                        entry_add_with_version(entry, "2022.0+");
                        return true;
                    }
                    // 2023.0 uses GBDK 4.2.0
                    if (entry_check_match(TYPE_TOOLS, STR_GBDK, STR_GBDK_2020_4_2_0)) {
                        entry_add_with_version(entry, "2023.0+");
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

   // ==== SHARED CODE WITH C ENDS HERE ====
}
