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
void check_gbbasic(void) {

    tool_entry entry;

    // ==== SHARED CODE WITH C STARTS HERE ====

    entry = FORMAT_ENTRY(TYPE_ENGINE, "GBBasic", "Alpha3");
    if (CHECK_PATTERN_AT_ADDR(sig_gbbasic_actor_init_alpha3, sig_gbbasic_actor_init_alpha3_at)) {
        entry_add(entry);
    }

    // ==== SHARED CODE WITH C ENDS HERE ====
}
