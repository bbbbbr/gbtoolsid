// This is free and unencumbered software released into the public domain.
// For more information, please refer to <https://unlicense.org>
// bbbbbr 2020

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "common.h"
#include "entries.h"
#include "gbtoolchainid.h"

#include "entry_names_gbbasic.h"

// Check for GB basic
bool check_gbbasic(void) {

    tool_entry entry;

    if (CHECK_PATTERN_AT_ADDR(sig_gbbasic_magic_key, sig_gbbasic_magic_key_at)) {

        char str_ver[MAX_FILE_STR];
        uint8_t ver_major, ver_minor;

        // Read version bytes and format them into a string for the entry
        if (read_byte_addr(sig_gbbasic_magic_version_major_at, &ver_major) &&
            read_byte_addr(sig_gbbasic_magic_version_minor_at, &ver_minor)) {

            snprintf(str_ver, MAX_STR_LEN, "v%u.%u", (unsigned int)ver_major, (unsigned int)ver_minor);
            entry = FORMAT_ENTRY(TYPE_ENGINE, "GBBasic", str_ver);
        } else {
            // If the read failed for some reason then default is un-versioned
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
