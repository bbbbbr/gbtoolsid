// This is free and unencumbered software released into the public domain.
// For more information, please refer to <https://unlicense.org>
// bbbbbr 2020

#include <stdint.h>
#include <stdbool.h>

#include "common.h"
#include "entries.h"
#include "gbtoolchainid.h"

#include "entry_names_soundfx.h"

// Check for Sound FX drivers
void check_soundfx(void) {

    tool_entry entry;

    entry = FORMAT_ENTRY(TYPE_SOUNDFX,"FX Hammer", "");
    if (FIND_PATTERN_STR_NOTERM(sig_fxhammer_info_1) ||
        FIND_PATTERN_STR_NOTERM(sig_fxhammer_info_2) )
        entry_add(entry);

    entry = FORMAT_ENTRY(TYPE_SOUNDFX,"CBT-FX", "");
    if (FIND_PATTERN_STR_NOTERM(sig_cbtfx_info))
        entry_add(entry);

    entry = FORMAT_ENTRY(TYPE_SOUNDFX,"VAL-FX", "");
    if (FIND_PATTERN_STR_NOTERM(sig_valfx_info))
        entry_add(entry);

    entry = FORMAT_ENTRY(TYPE_SOUNDFX,"VGM2GBSFX", "");
    if (FIND_PATTERN_BUF(sig_vgm2gbsfx_aud3waveram_load) ||
        FIND_PATTERN_BUF(sig_vgm2gbsfx_aud3waveram_load_v2))
        entry_add(entry);
}
