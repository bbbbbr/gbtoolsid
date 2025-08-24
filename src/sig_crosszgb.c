// This is free and unencumbered software released into the public domain.
// For more information, please refer to <https://unlicense.org>
// bbbbbr 2020

#include <stdint.h>
#include <stdbool.h>

#include "common.h"
#include "entries.h"
#include "gbtoolchainid.h"

#include "entry_names_gbdk.h"
#include "entry_names_crosszgb.h"


// Check Cross ZGB engine
bool check_crosszgb(void) {

    tool_entry entry;

    entry = FORMAT_ENTRY(TYPE_ENGINE, "Cross ZGB", "");

    // Cross ZGB 2024.0 - 2024.2 not currently detected
    // They may not have any inline asm or constants that
    // are guaranteed to link (vs optional soundfx, printing recode table, etc)

    // ZGB 2025.0
    if (FIND_PATTERN_BUF(sig_crosszgb_buffer_exchange_v2025_0)) {

        entry_add_with_version(entry, "2025.0");
        return true;
    }

    return false;
}
