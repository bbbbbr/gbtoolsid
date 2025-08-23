// This is free and unencumbered software released into the public domain.
// For more information, please refer to <https://unlicense.org>
// bbbbbr 2020

#include <stdint.h>
#include <stdbool.h>

#include "common.h"
#include "entries.h"
#include "gbtoolchainid.h"

#include "entry_names_music.h"

// Check for misc sound drivers
void check_music(void) {

    tool_entry entry;



    entry = FORMAT_ENTRY(TYPE_MUSIC,"GHX", "");
    if (FIND_PATTERN_STR_NOTERM(sig_str_ghx_audio) ||
        FIND_PATTERN_STR_NOTERM(sig_str_ghx_sound))
        entry_add(entry);

    if (FIND_PATTERN_STR_NOTERM(sig_str_devsound_classic)) {
        entry = FORMAT_ENTRY(TYPE_MUSIC,"DevSound","Classic");
        entry_add(entry);
    }
    else if (FIND_PATTERN_STR_NOTERM(sig_str_devsound_lite)) {
        entry = FORMAT_ENTRY(TYPE_MUSIC,"DevSound","Lite");
        entry_add(entry);
    }
    else if (FIND_PATTERN_STR_NOTERM(sig_str_devsound_x)) {
        entry = FORMAT_ENTRY(TYPE_MUSIC,"DevSound","X");
        entry_add(entry);
    }

    if (FIND_PATTERN_STR_NOTERM(sig_str_gbmusicplayer_audio)) {
        entry = FORMAT_ENTRY(TYPE_MUSIC,"Visual Impact", "");
        entry_add(entry);
    }

    if (FIND_PATTERN_STR_NOTERM(sig_str_MusyX_1) ||
        FIND_PATTERN_STR_NOTERM(sig_str_MusyX_2) ||
        FIND_PATTERN_STR_NOTERM(sig_str_MusyX_3)) {

        entry = FORMAT_ENTRY(TYPE_MUSIC,"MusyX", "");
        entry_add(entry);
    }

    if (FIND_PATTERN_STR_NOTERM(sig_str_freaq_1) ||
        FIND_PATTERN_STR_NOTERM(sig_str_freaq_2)) {
        entry = FORMAT_ENTRY(TYPE_MUSIC,"Freaq", "");
        entry_add(entry);
    }

    entry = FORMAT_ENTRY(TYPE_MUSIC,"LSDJ", "");
    if (FIND_PATTERN_STR_NOTERM(sig_str_lsdj_1) ||
        FIND_PATTERN_STR_NOTERM(sig_str_lsdj_2))
        entry_add(entry);
    else if (CHECK_PATTERN_AT_ADDR(sig_lsdpack_header_title, sig_lsdpack_header_title_at_0x134))
        entry_add(entry);

    // hUGETracker and variants
    entry = FORMAT_ENTRY(TYPE_MUSIC,"hUGETracker","SuperDisk");
    if (FIND_PATTERN_BUF(sig_hugetracker_fx_vol_slide_base_v1))
        entry_add(entry);
    else if (FIND_PATTERN_BUF(sig_hugetracker_fx_vol_slide_base_v2))
        entry_add(entry);
    else if (FIND_PATTERN_BUF(sig_hugetracker_fortissimo_fx_vol_slide)) {
        entry = FORMAT_ENTRY(TYPE_MUSIC,"hUGETracker","fortISSimO");
        entry_add(entry);
    } else if (FIND_PATTERN_BUF(sig_hugetracker_fx_get_note_poly)) {

        if (FIND_PATTERN_BUF(sig_hugetracker_fx_coffeebat_get_shift_ch3)) {
            entry = FORMAT_ENTRY(TYPE_MUSIC,"hUGETracker","Coffee Bat");
            entry_add(entry);
        } else
            entry_add(entry); // Fallback, default HT entry
    }

    if (FIND_PATTERN_STR_NOTERM(sig_tbengine_noisetable)) {
        entry = FORMAT_ENTRY(TYPE_MUSIC,"Trackerboy engine", "");
        entry_add(entry);
    }

    if (FIND_PATTERN_BUF(sig_blackboxplayer_1) &&
        FIND_PATTERN_BUF(sig_blackboxplayer_2)) {
        entry = FORMAT_ENTRY(TYPE_MUSIC,"Black Box Music Box", "");
        entry_add(entry);
    }

    if (FIND_PATTERN_BUF(sig_lemon_wave_default)) {
        entry = FORMAT_ENTRY(TYPE_MUSIC,"Lemon", "");
        entry_add(entry);
    }

    if (FIND_PATTERN_BUF(sig_gbtplayer_gbt_wave)) {
        entry = FORMAT_ENTRY(TYPE_MUSIC,"GBT Player", "");
        entry_add(entry);
    }

    entry = FORMAT_ENTRY(TYPE_MUSIC,"Carillon Player", "Standard");
    if (FIND_PATTERN_STR_NOTERM(sig_carillon_player_1) ||
        FIND_PATTERN_STR_NOTERM(sig_carillon_player_2))
        entry_add(entry);
    else if (FIND_PATTERN_BUF(sig_carillon_player_3)) {
        if (FIND_PATTERN_BUF(sig_makrillon_1)) {
            entry = FORMAT_ENTRY(TYPE_MUSIC,"Carillon Player", "Makrillon");
            entry_add(entry);
        } else {
            entry_add(entry);
        }
    }

    entry = FORMAT_ENTRY(TYPE_MUSIC,"MPlay", "");
    if (FIND_PATTERN_BUF(sig_mplay2))
        entry_add_with_version(entry, "2");
    else if (FIND_PATTERN_BUF(sig_mplay1))
        entry_add_with_version(entry, "1");

    // GBSoundSystem (Paragon5) and variants
    entry = FORMAT_ENTRY(TYPE_MUSIC,"GBSoundSystem","Modern");
    if (FIND_PATTERN_BUF(sig_bin_gbsoundsystem_modern_SSFP_multi_sfx)) {
        entry_add(entry);
    }
    else {
        entry = FORMAT_ENTRY(TYPE_MUSIC,"GBSoundSystem","Classic");
        if (FIND_PATTERN_STR_NOTERM(sig_str_gbsoundsystem_1) &&
            FIND_PATTERN_STR_NOTERM(sig_str_gbsoundsystem_2))
            entry_add(entry);
        else if (FIND_PATTERN_BUF(sig_bin_gbsoundsystem_MultiSFXLoop))
            entry_add(entry);
    }

    // MMLGB and variants
    if ((FIND_PATTERN_BUF(sig_mmlgb1)) || (FIND_PATTERN_BUF(sig_mmlgb2))) {
        entry = FORMAT_ENTRY(TYPE_MUSIC,"MMLGB", "");

        if (FIND_PATTERN_BUF(sig_mmlgb_v2))
            entry_add_with_version(entry, "Retro-Hax");
        else
            entry_add(entry);
    }

    // GBMC (Game Boy Music Compiler)
    if (FIND_PATTERN_BUF(sig_gbmc_snd_exec_modv)) {
        entry = FORMAT_ENTRY(TYPE_MUSIC,"GBMC", "");
        entry_add(entry);
    }

    // QuickThunder (Audio Arts)
    if (FIND_PATTERN_STR_NOTERM(sig_quickthunder_audio_arts_ch2)) {
        entry = FORMAT_ENTRY(TYPE_MUSIC,"QuickThunder", "");
        entry_add(entry);
    }

    if (FIND_PATTERN_BUF(sig_imedgboy)) {
        entry = FORMAT_ENTRY(TYPE_MUSIC,"IMEDGBoy", "");
        entry_add(entry);
    }

    if (FIND_PATTERN_BUF(sig_cosmigo3)) {
        entry = FORMAT_ENTRY(TYPE_MUSIC,"Cosmigo", "");
        entry_add(entry);
    }

    if (CHECK_PATTERN_AT_ADDR(sig_deflemask_romstart, sig_deflemask_at_0x0001)) {
        entry = FORMAT_ENTRY(TYPE_MUSIC,"DefleMask", "");
        entry_add(entry);
    }

    if (FIND_PATTERN_STR_NOTERM(sig_tonicfur)) {
        entry = FORMAT_ENTRY(TYPE_MUSIC,"TonicFur Audio Engine", "");
        entry_add(entry);
    }


}