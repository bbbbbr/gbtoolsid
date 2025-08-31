
#include <stdbool.h>
#include <stdint.h>

#include "common.h"

#ifndef _ENTRY_NAMES_LLVMGB_LIBGBXX_H
#define _ENTRY_NAMES_LLVMGB_LIBGBXX_H



    // Runtime.s startup (crt0 equivalent)
    //
    // https://github.com/DaveDuck321/gb-llvm/blob/f77225db5880eba01595adea5f2add14ce2f4f45/gameboy-tooling/runtime.S#L76
    //
    // Arguments for load and call instructions are masked out
    //
    DEF_PATTERN_BUF_MASKED(sig_llvmgb_libgbxx_runtime_startup, sig_llvmgb_libgbxx_runtime_startup_mask, \
        AR_ARGS(0xF3, 0xAF, 0xE0, 0xFF, 0x31, 0xFE, 0xDF, 0x21, 0x8C, 0xC2, 0x01, 0xC2, 0x44, 0x11, 0xDA, 0xC2, 0xCD, 0x1C, 0x16, 0x21, 0x80, 0xFF, 0x01, 0x50, 0x01, 0x11, 0x89, 0xFF, 0xCD, 0x1C, 0x16, 0xCD), \
        AR_ARGS(   1,    1,    1,    1,    1,    1,    1,    1,    0,    0,    1,    0,    0,    1,    0,    0,    1,    0,    0,    1,    0,    0,    1,    0,    0,    1,    0,    0,    1,    0,    0,    1));
        //                                               LD HL____________  LD BC___________ LD DE____________ CALL_____________ LD HL____________  LD BC___________ LD DE____________ CALL_____________ CALL_

        // Same as above, but full code all the way to calling main (in case more specificity is needed)
        //      0xF3, 0xAF, 0xE0, 0xFF, 0x31, 0xFE, 0xDF, 0x21, 0x8C, 0xC2, 0x01, 0xC2, 0x44, 0x11, 0xDA, 0xC2, 0xCD, 0x1C, 0x16, 0x21, 0x80, 0xFF, 0x01, 0x50, 0x01, 0x11, 0x89, 0xFF, 0xCD, 0x1C, 0x16, 0xCD, 0x28, 0x16, 0x01, 0x5A, 0x01, 0x11, 0x5C, 0x01, 0xCD, 0x3A, 0x16, 0x3E, 0x00, 0x21, 0x00, 0x00, 0xCD, 0x60, 0x01

        // .global _start
        // _start:
        //     di
        //     xor a
        //     ldh (0xff), a
        //     ld sp, 0xdffe

        //     ld hl, __gb_data_start
        //     ld bc, __gb_data_load_addr
        //     ld de, __gb_data_end
        //     call gb_init_section

        //     ld hl, __gb_hram_start
        //     ld bc, __gb_hram_load_addr
        //     ld de, __gb_hram_end
        //     call gb_init_section

        //     call gb_init_bss

        //     ld bc, __init_array_start
        //     ld de, __init_array_end
        //     call gb_call_fn_ptr_list

        //     ld a, 0
        //     ld hl, 0
        //     call main

#endif // _ENTRY_NAMES_LLVMGB_LIBGBXX_H
