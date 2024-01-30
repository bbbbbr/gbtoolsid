// This is free and unencumbered software released into the public domain.
// For more information, please refer to <https://unlicense.org>
// bbbbbr 2020

#include <stdint.h>
#include <stdbool.h>

#include "common.h"
#include "entries.h"
#include "gbtoolchainid.h"

#include "entry_names_gbdk.h"
#include "entry_names_gbstudio.h"

// Check GBStudio engine
bool check_gbstudio(void) {

    tool_entry entry;

    // ==== SHARED CODE WITH C STARTS HERE ====

    entry = FORMAT_ENTRY(TYPE_ENGINE, "GBStudio", "");

    // GBStudio 1.0.0 - 1.2.1
    if (FIND_PATTERN_BUF(sig_gbs_fades_1_0_0_to_1_2_1)) {

        if (FIND_PATTERN_BUF(sig_gbs_uicolors_1_0_0)) {
            entry_add_with_version(entry, "1.0.0");
            return true;
        }
        // GBStudio 1.1.0 - 1.2.1
        else if (FIND_PATTERN_BUF(sig_gbs_uicolors_1_1_0_plus)) {
            entry_add_with_version(entry, "1.0.0 - 1.2.1");
            return true;
        }
    }
    // GBStudio 2.0.0 beta 1 (Should only be checked if previous test fails)
    else if (FIND_PATTERN_BUF(sig_gbs_fades_2_0_0_beta1)) {
        entry_add_with_version(entry, "2.0.0 Beta 1");
        return true;
    }

    // GBStudio 2.0.0 beta 2+
    if (FIND_PATTERN_BUF(sig_gbs_fades_2_0_0_beta2_plus)) {
        // GBStudio 2.0.0 beta 5+ (preliminary- not yet offically released)
        // Check Beta 5 first, then fall back since it has shared signatures
        if (FIND_PATTERN_BUF(sig_gbs_uicolors_2_0_0_beta5_plus)) {
            entry_add_with_version(entry, "2.0.0 beta 5+");
            return true;
        }
        // Otherwise GBStudio 2.0.0 beta 2 - 4
        else {
            entry_add_with_version(entry, "2.0.0 beta 2 - 4");
            return true;
        }
    }

    // GBStudio 3.0.0+
    if (FIND_PATTERN_BUF(sig_gbs_math_c_sinetable_3_0_0_alpha1_plus)) {

        if (FIND_PATTERN_BUF(sig_gbs_fade_manager_c_dmgfadetowhitestep_2_0_0_b5_to_3_1_0)) {
        // entry_check_match() Relies on GBDK tool check being run before ZGB is tested (it is)

            // ADDED:Apr 30, 2021 (v2.0.0-beta5) -> REMOVED:Feb 20, 2022 (3.0.3)
            if (FIND_PATTERN_BUF(sig_gbs_musicmanager_c_FX_ADDR_LO__2_0_0_b5_to_3_0_3)) {

                // GBStudio 3.0.0 alpha 1+ uses GBDK 4.0.4
                if (entry_check_match(TYPE_TOOLS, STR_GBDK, STR_GBDK_2020_4_0_4)) {
                    entry_add_with_version(entry, "3.0.0 alpha 1+");
                    return true;
                }
                // GBStudio 3.0.0 official - 3.1.0+ uses GBDK 4.0.5 & 4.0.6 (which cannot be differentiated
                else if (entry_check_match(TYPE_TOOLS, STR_GBDK, STR_GBDK_2020_4_0_5_to_4_0_6)) {
                    entry_add_with_version(entry, "3.0.0 - 3.0.3");
                    return true;
                }
            }
            else {
                entry_add_with_version(entry, "3.1.0+");
                return true;
            }
        }
        else if (FIND_PATTERN_BUF(sig_gbs_fade_manager_c_dmgfadetowhitestep_3_2_0_plus)) {

            // GBStudio 3.2.0 uses GBDK 4.2.0
            if (entry_check_match(TYPE_TOOLS, STR_GBDK, STR_GBDK_2020_4_2_0_plus)) {
                entry_add_with_version(entry, "3.2.0");
                return true;
            }
        }
    }

    return false;

    // ==== SHARED CODE WITH C ENDS HERE ====
}
