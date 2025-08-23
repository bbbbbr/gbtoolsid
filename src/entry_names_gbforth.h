
#include <stdbool.h>
#include <stdint.h>

#include "common.h"

#ifndef _ENTRY_NAMES_GBFORTH_H
#define _ENTRY_NAMES_GBFORTH_H


    // ==== GBForth ====
    //
    DEF_PATTERN_BUF(sig_gbforth_startup_1, AR_ARGS(0x0E, 0xFE, 0x31, 0xFF, 0xCF, 0x3E));
    // ... one byte gap for variable value ... (TODO: bitmask for search patterns to make this easier)
    DEF_PATTERN_ADDR(sig_gbforth_startup_1_next_at, (6 + 1));
    DEF_PATTERN_BUF(sig_gbforth_startup_2, AR_ARGS(0xEA, 0x00, 0xC0, 0x3E));
    // ... one byte gap for variable value ...
    DEF_PATTERN_ADDR(sig_gbforth_startup_2_next_at, (4 + 1));
    DEF_PATTERN_BUF(sig_gbforth_startup_3, AR_ARGS(0xEA, 0x01, 0xC0, 0xCD));

    // ==== GBForth
    // https://gbforth.org/
    // https://github.com/ams-hackers/gbforth
    //
    // ram.fs
    // https://github.com/ams-hackers/gbforth/blob/e131cc807b884b69f4512d1be6b223cfefd3a8ae/src/ram.fs#L16
    // : cp-init,
    //   ram-offset dup
    //   lower-byte # A ld, A DP ]* ld,
    //   higher-byte # A ld, A DP 1 + ]* ld, ;
    //
    // runtime.fs
    // https://github.com/ams-hackers/gbforth/blob/e131cc807b884b69f4512d1be6b223cfefd3a8ae/src/runtime.fs#L7C1-L20C13
    //
    // : preserve-cgb-flag,
    //   A DP0 ]* ld, ;
    //
    // : sp-init,
    //   SP0 $FF00 - # C ld, ;
    //
    // : rp-init,
    //   RP0 # SP ld, ;
    //
    // : runtime-init,
    //   preserve-cgb-flag,
    //   sp-init,
    //   rp-init,
    //   cp-init, ;
    //
    // Generates this, often at the end of ROM0
    //
    // _LABEL_runtime-init_:
    //         ld   c, $FE     ; sp-init (stack pointer)
    //         ld   sp, $CFFF  ; rp-init (return stack pointer)
    //         ld   a, ...N...     ; cp-init <- Value loaded varies by program
    //         ld   [_RAM_C000_], a
    //         ld   a, ...N...     ;  <- Value loaded varies by program
    //         ld   [_RAM_C001_], a
    //         call ..


#endif // _ENTRY_NAMES_GBFORTH_H
