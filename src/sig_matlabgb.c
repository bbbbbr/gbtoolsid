// This is free and unencumbered software released into the public domain.
// For more information, please refer to <https://unlicense.org>
// bbbbbr 2020

#include <stdint.h>
#include <stdbool.h>

#include "common.h"
#include "entries.h"
#include "gbtoolchainid.h"

#include "entry_names_matlabgb.h"

#include <stdio.h>

// Check for Matlab GB Rom Creator
void check_matlabgb(void) {

    tool_entry entry;

    entry = FORMAT_ENTRY(TYPE_TOOLS, "Matlab GB", "");
    if (CHECK_PATTERN_AT_ADDR(sig_matlabgb_setup_gameboy_gfx, sig_matlabgb_setup_gameboy_gfx_at)) {
        entry_add(entry);
    }
    else if (CHECK_PATTERN_AT_ADDR(sig_matlabgb_update_audio_reg, sig_matlabgb_update_audio_reg_at)) {
        entry_add(entry);
    }
}
