
#include <stdbool.h>
#include <stdint.h>

#include "common.h"

#ifndef _ENTRY_NAMES_GBBASIC_H
#define _ENTRY_NAMES_GBBASIC_H


    // ==== GBBasic ====
    //
    DEF_PATTERN_BUF(sig_gbbasic_actor_init_alpha, AR_ARGS(0x00, 0x19, 0xE5, 0x7D, 0xF8, 0x04, 0x77, 0xE1, 0x7C, 0xF8, 0x03, 0x32, 0x2A, 0x66, 0x6F, 0xAF, 0x22, 0x77, 0xE1, 0xE5, 0xAF, 0x22, 0x77, 0xF8, 0x02, 0x2A, 0x5F, 0x56));
    DEF_PATTERN_ADDR(sig_gbbasic_actor_init_alpha3_at, 0x861A); // Bank 2: 0x461A
    DEF_PATTERN_ADDR(sig_gbbasic_actor_init_alpha4_at, 0x83C3); // Bank 2: 0x43C3

    // TODO: Add support for masked patterns at address (accept start addr and len/-1)
    DEF_PATTERN_BUF(sig_gbbasic_magic_v11, AR_ARGS(0x01, 0x01, 0x00, 0x00, 0x9B, 0x0B, 0xA5, 0x1C));
    //                                             .MAJ, .MIN, .REV......, .MAGIC................ 
    DEF_PATTERN_ADDR(sig_gbbasic_magic_v11_at, 0x20000); // Start of Fixed Bank 8: 0x20000
    
    // TODO: Add support for masked patterns at address (accept start addr and len/-1)
    DEF_PATTERN_BUF(sig_gbbasic_magic_v12, AR_ARGS(0x01, 0x02, 0x00, 0x00, 0x9B, 0x0B, 0xA5, 0x1C));
    //                                             .MAJ, .MIN, .REV......, .MAGIC................ 
    DEF_PATTERN_ADDR(sig_gbbasic_magic_v12_at, 0x20000); // Start of Fixed Bank 8: 0x20000


    // Found by checking symbols in "kernel" which is a pre-compiled gb rom
    // bundled with the application. It's a region of stable (pre-compiled)
    // C code with no variables, etc in `void actor_init(void) BANKED` (vm_actor.c)

    // Alpha 3 & 4
    //
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


    // V1.1 and maybe later
    //
    // src/data/builtin.c
    // 
    // #pragma bank 8
    //
    // ...
    //
    // const unsigned char VERSION_MAJOR = GBBVM_VER_MAJOR; // Major ahead.
    // const unsigned char VERSION_MINOR = GBBVM_VER_MINOR;
    // const unsigned int VERSION_REVISION = GBBVM_VER_REVISION;
    //
    // // Head.
    //
    // const unsigned char MAGIC[] = {
    //     0x9B, 0x0B, 0xA5, 0x1C
    // };

    // V1.2
    //
    // gbb/src/vm/data/builtin.c
    // https://github.com/paladin-t/gbb/blob/e11a57696f09b022c1678ca07e50b8d858672fd6/src/vm/data/builtin.c#L26


#endif // _ENTRY_NAMES_GBBASIC_H
