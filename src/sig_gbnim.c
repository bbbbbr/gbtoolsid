// This is free and unencumbered software released into the public domain.
// For more information, please refer to <https://unlicense.org>
// bbbbbr 2020

#include <stdint.h>
#include <stdbool.h>

#include "common.h"
#include "entries.h"
#include "gbtoolchainid.h"

#include "entry_names_gbnim.h"

#include <stdio.h>

// Check for GB Nim
void check_gbnim(void) {

    tool_entry entry;

    // ==== SHARED CODE WITH C STARTS HERE ====
    entry = FORMAT_ENTRY(TYPE_TOOLS, "gbnim", "");
    if (CHECK_PATTERN_AT_ADDR(sig_gbnim_startup_1, sig_gbnim_startup_1_at)) {
        if (CHECK_PATTERN_AT_ADDR(sig_gbnim_startup_2, sig_gbnim_startup_2_at)) {
            entry_add(entry);
        }
    }
    else if (FIND_PATTERN_STR_NOTERM(sig_gbnim_exception_handle_string)) {
            entry_add(entry);
    }

    // ==== SHARED CODE WITH C ENDS HERE ====
}
