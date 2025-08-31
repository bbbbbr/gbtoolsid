// This is free and unencumbered software released into the public domain.
// For more information, please refer to <https://unlicense.org>
// bbbbbr 2020

#include <stdint.h>
#include <stdbool.h>

#include "common.h"
#include "entries.h"
#include "gbtoolchainid.h"

#include "entry_names_llvmgb_libgbxx.h"

#include <stdio.h>

// Check for LibGB++ built with LLVM-GB
void check_llvmgb_libgbxx(void) {

    tool_entry entry;

    entry = FORMAT_ENTRY(TYPE_TOOLS, "libgb++", "");
    if (FIND_PATTERN_BUF_MASKED(sig_llvmgb_libgbxx_runtime_startup, sig_llvmgb_libgbxx_runtime_startup_mask)) {
        entry_add(entry);
    }

}
