
#include <stdbool.h>
#include <stdint.h>

#include "common.h"

#ifndef _ENTRY_NAMES_MATLABGB_H
#define _ENTRY_NAMES_MATLABGB_H


    // ==== gbnim ====
    //
    // https://github.com/LyesDemri/Matlab_GB_ROM_Creator/blob/cad1a48ee4ae7983811e2a214366b493b6ec8668/setup_gameboy.m#L10
    // gfx and sound init at 0x150
    DEF_PATTERN_ADDR(sig_matlabgb_setup_gameboy_gfx_at, 0x0150);
    DEF_PATTERN_BUF(sig_matlabgb_setup_gameboy_gfx, AR_ARGS(0x21, 0x47, 0xFF, 0x36, 0xE4, 0x21, 0x48, 0xFF, 0x36, 0xE4, 0x21, 0x49, 0xFF, 0x36, 0xE4, 0x21, 0x26, 0xFF, 0x36, 0x80, 0x21, 0x25, 0xFF, 0x36, 0xFF, 0x21, 0x24, 0xFF, 0x36, 0x77));

    // There is a sound only init, but no roms seem to use it so far
    // https://github.com/LyesDemri/Matlab_GB_ROM_Creator/blob/cad1a48ee4ae7983811e2a214366b493b6ec8668/setup_gameboy_no_graphics.m#L10

    // Matches audio roms that don't have gfx or other standard init.
    //
    // https://github.com/LyesDemri/Matlab_GB_ROM_Creator/blob/main/update_audio_registers_script.m
    // update audio registers, fixed at 0x1000
    // -> skipping past an address load to start at 0x1007 (but could start earlier with a masked pattern)
    DEF_PATTERN_ADDR(sig_matlabgb_update_audio_reg_at, 0x1007);
    DEF_PATTERN_BUF(sig_matlabgb_update_audio_reg, AR_ARGS(0x0A, 0x67, 0x03, 0x0A, 0x6F, 0x46, 0x23, 0x4E, 0x3E, 0xFF));

#endif // _ENTRY_NAMES_MATLABGB_H
