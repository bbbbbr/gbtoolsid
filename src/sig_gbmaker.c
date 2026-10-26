// This is free and unencumbered software released into the public domain.
// For more information, please refer to <https://unlicense.org>
// bbbbbr 2020

#include <stdint.h>
#include <stdbool.h>

#include "common.h"
#include "entries.h"
#include "gbtoolchainid.h"


// ==== GB Maker, lua based

    // Initial startup at 0x0300
    //
    // - @ 0x300 -> 315
    //         di
    //         ld   sp, $DFFF
    //         ldh  a, [rLCDC]
    //         bit  7, a
    //         jr   z, _LABEL_313_
    // _LABEL_30A_:    
    //         ldh  a, [rLY]
    //         cp   $90
    //         jr   c, _LABEL_30A_
    //         xor  a
    //         ldh  [rLCDC], a
    // _LABEL_313_:    
    //         ld   hl, $0001
    DEF_PATTERN_ADDR(sig_gbmaker_startup_at, 0x300);
    DEF_PATTERN_BUF(sig_gbmaker_startup, AR_ARGS(0xF3, 0x31, 0xFF, 0xDF, 0xF0, 0x40, 0xCB, 0x7F, 0x28, 0x09, 0xF0, 0x44, 0xFE, 0x90, 0x38, 0xFA, 0xAF, 0xE0, 0x40, 0x21, 0x01, 0x00));

    // Other possible fallbacks, unsure if they'd be more reliable:
    // - Various addresses and sometimes joined
    //   - "9:;<=>?@ABCDEFGHIJKLMNO"
    //   - "PQRSTUVWXYZ[\]^_`abcdefghij"
    // - 0x36DE, 0x39BF: GBMLINK2
    // - 0x25E3, 0x25E3: GBMSz



// Check for GB Maker
void check_gbmaker(void) {

    tool_entry entry;

    entry = FORMAT_ENTRY(TYPE_ENGINE, "GB Maker", "");
    if (FIND_PATTERN_STR_NOTERM(sig_gbmaker_startup))
        entry_add(entry);
}
