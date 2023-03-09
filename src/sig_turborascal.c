// This is free and unencumbered software released into the public domain.
// For more information, please refer to <https://unlicense.org>
// bbbbbr 2020

#include <stdint.h>
#include <stdbool.h>

#include "common.h"
#include "entries.h"
#include "gbtoolchainid.h"


// ==== Turbo Rascal Syntax Error

// 0x0134
    // May get added to the header as a post-processing step
    const uint32_t sig_turborascal_header_at = 0x0134;
    const uint8_t sig_turborascal_header[] = "TRSE GB";

// Check for Turbo Rascal Syntax Error
void check_turborascal(void) {

    tool_entry entry;

    entry = FORMAT_ENTRY(TYPE_TOOLS, "Turbo Rascal Syntax Error", "");
    if (CHECK_PATTERN_AT_ADDR(sig_turborascal_header, sig_turborascal_header_at))
        entry_add(entry);
}
