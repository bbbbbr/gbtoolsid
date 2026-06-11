// This is free and unencumbered software released into the public domain.
// For more information, please refer to <https://unlicense.org>
// bbbbbr 2020

#include <stdint.h>
#include <stdbool.h>

#include "common.h"
#include "entries.h"
#include "gbtoolchainid.h"


// ==== Not yet named GBDK based engine

    const uint8_t sig_unnamed_engine_signature[] = "RGBFULL!";

// Check for [Unnamed Engine]
void check_unnamed_engine(void) {

    tool_entry entry;

    entry = FORMAT_ENTRY(TYPE_TOOLS, "Unnamed Engine", "");
    if (FIND_PATTERN_STR_NOTERM(sig_unnamed_engine_signature))
        entry_add(entry);
}
