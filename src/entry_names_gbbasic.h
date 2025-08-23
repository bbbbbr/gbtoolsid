
#include <stdbool.h>
#include <stdint.h>

#include "common.h"

#ifndef _ENTRY_NAMES_GBBASIC_H
#define _ENTRY_NAMES_GBBASIC_H


    // ==== GBBasic ====
    //
    DEF_PATTERN_BUF(sig_gbbasic_actor_init, AR_ARGS(0x00, 0x19, 0xE5, 0x7D, 0xF8, 0x04, 0x77, 0xE1, 0x7C, 0xF8, 0x03, 0x32, 0x2A, 0x66, 0x6F, 0xAF, 0x22, 0x77, 0xE1, 0xE5, 0xAF, 0x22, 0x77, 0xF8, 0x02, 0x2A, 0x5F, 0x56));
    DEF_PATTERN_ADDR(sig_gbbasic_actor_init_alpha3_at, 0x861A); // Bank 2: 0x461A
    DEF_PATTERN_ADDR(sig_gbbasic_actor_init_alpha4_at, 0x83C3); // Bank 2: 0x43C3

    // ==== GBBASIC
    // https://github.com/gbbasic/prototype
    //

    // Bank 2: 0x461A - 0x4634, partway through actor_init
    //
    // add  hl, de
    // push hl
    // ld   a, l
    // ld   hl, sp+4
    // ld   [hl], a
    // pop  hl
    // ld   a, h
    // ld   hl, sp+3
    // ldd  [hl], a
    // ldi  a, [hl]
    // ld   h, [hl]
    // ld   l, a
    // xor  a
    // ldi  [hl], a
    // ld   [hl], a
    // pop  hl
    // push hl
    // xor  a
    // ldi  [hl], a
    // ld   [hl], a
    // ld   hl, sp+2
    // ldi  a, [hl]
    // ld   e, a
    // ld   d, [hl]


#endif // _ENTRY_NAMES_GBBASIC_H
