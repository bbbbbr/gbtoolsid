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
    // - 0x36DE, 0x39BF: GBMLINK2  <-- not at same address, but also applies for GBC Maker
    // - 0x25E3, 0x25E3: GBMSz     <-- not at same address, but also applies for GBC Maker


// ==== GBC Maker, lua based

    // Initial startup at 0x0150
    // @ 150
    //         di
    //         cp   $11
    //         ld   a, $00
    //         jr   nz, _LABEL_158_
    //         inc  a
    // _LABEL_158_:    
    //         ld   [_RAM_FFBA_], a
    //         xor  a
    //         ld   [_RAM_FFBC_], a
    //         ld   sp, $DFFF
    //         ldh  a, [rLCDC]
    //         bit  7, a
    //         jr   z, _LABEL_171_
    // _LABEL_168_:    
    //         ldh  a, [rLY]
    DEF_PATTERN_ADDR(sig_gbcmaker_startup_at, 0x150);
    DEF_PATTERN_BUF_MASKED(sig_gbcmaker_startup, sig_gbcmaker_startup_mask, \
        AR_ARGS(0xF3, 0xFE, 0x11, 0x3E, 0x00, 0x20, 0x01, 0x3C, 0xEA, 0xBA, 0xFF, 0xAF, 0xEA, 0xBC, 0xFF, 0x31, 0xFF, 0xDF, 0xF0, 0x40, 0xCB, 0x7F, 0x28, 0x09, 0xF0, 0x44), \
        AR_ARGS(   1,    1,    1,    1,    1,    1,    1,    1,    1,    0,    0,    1,    1,    0,    0,    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,    1));


// Check for GB Maker
void check_gbmaker(void) {

    tool_entry entry_gb, entry_gbc;

    entry_gb  = FORMAT_ENTRY(TYPE_TOOLS, "GB Maker", "");
    entry_gbc = FORMAT_ENTRY(TYPE_TOOLS, "GBC Maker", "");
    if (FIND_PATTERN_STR_NOTERM(sig_gbmaker_startup)) {
        entry_add(entry_gb);
    } else if (CHECK_PATTERN_MASKED_AT_ADDR(sig_gbcmaker_startup,
                                          sig_gbcmaker_startup_mask,
                                          sig_gbcmaker_startup_at)) {
        entry_add(entry_gbc);
    }
}
