// This is free and unencumbered software released into the public domain.
// For more information, please refer to <https://unlicense.org>
// bbbbbr 2020

#include <stdint.h>
#include <stdbool.h>

#include "common.h"
#include "entries.h"
#include "gbtoolchainid.h"


// ==== RetroGBFull Toolkit, GBDK based engine

    const uint8_t sig_retrorgbfull_signature[] = "RGBFULL!";

// Check for RetroGBFull Toolkit
void check_retrorgbfull(void) {

    tool_entry entry;

    entry = FORMAT_ENTRY(TYPE_ENGINE, "RetroGBFull Toolkit", "");
    if (FIND_PATTERN_STR_NOTERM(sig_retrorgbfull_signature))
        entry_add(entry);
}
