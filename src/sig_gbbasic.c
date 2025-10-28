// This is free and unencumbered software released into the public domain.
// For more information, please refer to <https://unlicense.org>
// bbbbbr 2020

#include <stdint.h>
#include <stdbool.h>

#include "common.h"
#include "entries.h"
#include "gbtoolchainid.h"

#include "entry_names_gbbasic.h"

// Check for GB basic
bool check_gbbasic(void) {

    tool_entry entry;

    if (CHECK_PATTERN_AT_ADDR(sig_gbbasic_magic_key, sig_gbbasic_magic_key_at)) {
        if (CHECK_PATTERN_AT_ADDR(sig_gbbasic_magic_v13, sig_gbbasic_magic_version_at)) {
            entry = FORMAT_ENTRY(TYPE_ENGINE, "GBBasic", "v1.3");
        }
        else if (CHECK_PATTERN_AT_ADDR(sig_gbbasic_magic_v12, sig_gbbasic_magic_version_at)) {
            entry = FORMAT_ENTRY(TYPE_ENGINE, "GBBasic", "v1.2");            
        }
        else if (CHECK_PATTERN_AT_ADDR(sig_gbbasic_magic_v11, sig_gbbasic_magic_version_at)) {
            entry = FORMAT_ENTRY(TYPE_ENGINE, "GBBasic", "v1.1");            
        } else {
            // Default is un-versioned if unknown version is found
            // TODO: could read the bytes directly and convert the version
            entry = FORMAT_ENTRY(TYPE_ENGINE, "GBBasic", "");
        }

        entry_add(entry);
        return true;
    }
    else if (CHECK_PATTERN_AT_ADDR(sig_gbbasic_actor_init_alpha, sig_gbbasic_actor_init_alpha3_at)) {
        entry = FORMAT_ENTRY(TYPE_ENGINE, "GBBasic", "Alpha3");
        entry_add(entry);
        return true;
    }
    else if (CHECK_PATTERN_AT_ADDR(sig_gbbasic_actor_init_alpha, sig_gbbasic_actor_init_alpha4_at)) {
        entry = FORMAT_ENTRY(TYPE_ENGINE, "GBBasic", "Alpha4");
        entry_add(entry);
        return true;
    }


    return false;
}
