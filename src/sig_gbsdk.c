// This is free and unencumbered software released into the public domain.
// For more information, please refer to <https://unlicense.org>
// bbbbbr 2020

#include <stdint.h>
#include <stdbool.h>

#include "common.h"
#include "entries.h"
#include "gbtoolchainid.h"

#include "entry_names_gbsdk.h"

#include <stdio.h>

// Check for GB Nim
void check_gbsdk(void) {

    tool_entry entry;

    // ==== SHARED CODE WITH C STARTS HERE ====
    entry = FORMAT_ENTRY(TYPE_TOOLS, "gbsdk", "");
    if (FIND_PATTERN_BUF(sig_gbsdk_joypad)) {
        entry_add(entry);
    }

    // ==== SHARED CODE WITH C ENDS HERE ====
}
