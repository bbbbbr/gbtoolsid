

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "gbtoolchainid.h"


static uint8_t * g_p_searchbuf = NULL;
static uint32_t g_searchbuf_len = 0;


// TODO: try to extract ROM name string


// Set the global search buffer
static void set_search_buf(uint8_t * p_rom_data, uint32_t rom_size) {
    g_p_searchbuf = p_rom_data;
    g_searchbuf_len = rom_size;
}


// TODO: add a max_position value to limit searches the possible range (don't search inapplicable areas)
// TODO: uint32_t -> size_t
// TODO: optimize: at least to rolling hash, or better
//                 https://en.wikipedia.org/wiki/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm
// Find pattern in a buffer, set p_index to starting location if found
static bool find_pattern(const uint8_t * p_pattern, uint32_t pattern_len, uint32_t * p_index) {
    
    if (pattern_len > g_searchbuf_len) {
        return false;
    }

    // Zero out index location
    *p_index = 0;

    // Try to locate first possible instance
    uint8_t * p_match = memchr(g_p_searchbuf, p_pattern[0], g_searchbuf_len);
    uint32_t remaining = g_searchbuf_len - (p_match - g_p_searchbuf);

    while (p_match != NULL) {       
        if (pattern_len <= remaining) {

            if (memcmp(p_match, p_pattern, pattern_len) == 0) {
                *p_index = (uint32_t)(p_match - g_p_searchbuf);
                return true;
            }
        } else
            break;

        p_match++;
        p_match = memchr(p_match, p_pattern[0], remaining);
        remaining = g_searchbuf_len - (p_match - g_p_searchbuf);        
    }
    return false;
}


// ==== ZGB ====
// All ZGB records can be at any location
    const uint8_t sig_zgb_sound[] = {0x05, 0x04, 0x05, 0x04, 0x03, 0x10, 0xFF, 0x16, 0xFF, 0x1A, 0xFF, 0x20, 0xFF, 0x24, 0xFF};
    const uint8_t sig_zgb_2017[] = {0xF8, 0x02, 0x4E, 0x23, 0x46, 0xF8, 0x04, 0x11, 0x41, 0xFF, 0x1A, 0xE6, 0x02};
    const uint8_t sig_zgb_2020_0_pushbank[] = {0x34, 0x4E, 0x23, 0x46, 0x02, 0x01, 0x00, 0x20, 0x02};
    const uint8_t sig_zgb_2020_0_popbank[]  = {0x35, 0x4E, 0x23, 0x46, 0x0A, 0x01, 0x00, 0x20, 0x02};
    const uint8_t sig_zgb_2020_1_to_2021_0_pushbank[] = {0x34, 0x4E, 0x23, 0x46, 0xFA, 0x90, 0xFF, 0x02, 0xF8, 0x02, 0x7E, 0xEA, 0x90, 0xFF, 0xEA, 0x00, 0x20};
    const uint8_t sig_zgb_2020_1_to_2021_0_popbank[]  = {0x4E, 0x23, 0x46, 0x0A, 0xEA, 0x90, 0xFF, 0xEA, 0x00, 0x20, 0x2B, 0x35};

// ==== GBDK ====
// Bitmap defines
    const uint8_t sig_gbdk_bmp[] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
    const uint32_t sig_gbdk_bmp_2x_to_2020_320_at = 0x0010;
    const uint32_t sig_gbdk_bmp_2020_400_plus_at = 0x0070; // This entry may or MAY NOT be present for GBDK-2020 4.0.0+
// 0x20
    const uint32_t sig_gbdk_0x20_at = 0x0020;
    // First Entry is ambiguous, must be combined
    //const uint8_t sig_gbdk_0x20_GBDK_2x_to_2020_320[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    const uint8_t sig_gbdk_0x20_GBDK_2020_400[]       = {0xE9, 0xFF, 0xFF, 0xFF};
    const uint8_t sig_gbdk_0x20_GBDK_2020_401_plus[]  = {0xE9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x22, 0x0D, 0x20, 0xFC, 0xC9, 0xFF, 0xFF, 0xFF};
// 0x30
    const uint32_t sig_gbdk_0x30_at = 0x0030;
    // First Entry is ambiguous, must be combined
    // const uint8_t sig_gbdk_0x20_GBDK_2x_to_2020_400[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
    const uint8_t sig_gbdk_0x30_GBDK_2020_401_plus[]  = {0x1A, 0x22, 0x13, 0x0D, 0x20, 0xFA, 0xC9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
// 0x80
    const uint32_t sig_gbdk_0x80_at = 0x0080;
    const uint8_t sig_gbdk_0x80_GBDK_4_0_0[]  = {0xC5, 0xD5, 0x2A, 0xB6, 0x28, 0x09, 0xE5, 0x3A, 0x6E, 0x67, 0xE7, 0xE1, 0x23, 0x18, 0xF3, 0xD1, 0xC1, 0xE1, 0xF0, 0x41, 0xE6, 0x02, 0x20, 0xFA, 0xF1, 0xD9};
// 0x150
    // These should only be used when stacked on other entries
    const uint8_t sig_gbdk_0x150[] = {0xF3, 0x57, 0xAF, 0x31};
    const uint32_t sig_gbdk_0x150_GBDK_2x_to_2020_401_at   = 0x0150;
    const uint32_t sig_gbdk_0x150_GBDK_2020_401_to_402_at  = 0x0153;
    // 0x153
    const uint8_t sig_gbdk_0x153[] = {0xF3, 0x57, 0x31};
    const uint32_t sig_gbdk_0x153_GBDK_2020_403_plus_at = 0x0153;
    

// ====GB STUDIO
    // TODO: FADES AND UI_b.c don't appear to cover GBStudio BETAS??? (check: maxoakland / wink, 2bityou)
// Fades
    const uint8_t sig_gbs_fades_1_0_0_to_1_2_1[] = {0x0, 0x1, 0x3, 0x7, 0xF, 0x1F, 0x3F, 0x00, 0x00, 0x42, 0x82, 0xD2, 0xD2, 0x00, 0x00, 0x40, 0x90, 0xA4, 0xE4};
    // Similar to above, but lacks lead in bytes
    const uint8_t sig_gbs_fades_2_0_0_beta1[] =      {0x00, 0x00, 0x42, 0x82, 0xD2, 0xD2, 0x00, 0x00, 0x40, 0x90, 0xA4, 0xE4};
    const uint8_t sig_gbs_fades_2_0_0_beta2_plus[] = {0x00, 0x00, 0x40, 0x80, 0x90, 0xD0, 0xD0, 0x00, 0x00, 0x40, 0x90, 0xA4, 0xE4, 0xE4, 0xFF, 0xFF, 0xF8, 0xE4, 0xD4, 0xD0, 0xD0, 0xFF, 0xFF, 0xFE, 0xE9, 0xE5, 0xE4, 0xE4};
// UI_b.c uicolors
    const uint8_t sig_gbs_uicolors_1_0_0[]      = {0xD0, 0xd6, 0xd2, 0xd8, 0xd1, 0xd7, 0xd3, 0xd5, 0xd4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    const uint8_t sig_gbs_uicolors_1_1_0_plus[] = {0xC0, 0xC6, 0xC2, 0xC8, 0xC1, 0xC7, 0xC3, 0xC5, 0xC4, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    // Preliminary (11/20/2020)
    const uint8_t sig_gbs_uicolors_2_0_0_beta5_plus[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x01, 0x03, 0x07, 0x0F, 0x1F};



// Check GBStudio engine
static bool check_gbstudio() {

    uint32_t p_match_idx;

    // GBStudio 1.0.0 - 1.2.1
    if (find_pattern(sig_gbs_fades_1_0_0_to_1_2_1, sizeof(sig_gbs_fades_1_0_0_to_1_2_1), &p_match_idx)) {        
         // fprintf(stdout, "  - Found: 0x%08x - %s\n", p_match_idx, "sig_gbs_fades_1_0_0_to_1_2_1");
        
        if (find_pattern(sig_gbs_uicolors_1_0_0, sizeof(sig_gbs_uicolors_1_0_0), &p_match_idx)) {
            fprintf(stdout, "  - Engine: GBStudio 1.0.0\n");
            return true;
            // fprintf(stdout, "  - Found: 0x%08x - %s\n", p_match_idx, "sig_gbs_uicolors_1_0_0");
        }
        // GBStudio 1.1.0 - 1.2.1
        else
        if (find_pattern(sig_gbs_uicolors_1_1_0_plus, sizeof(sig_gbs_uicolors_1_1_0_plus), &p_match_idx)) {
            fprintf(stdout, "  - Engine: GBStudio 1.0.0 - 1.2.1\n");
            return true;
            fprintf(stdout, "  - Found: 0x%08x - %s\n", p_match_idx, "sig_gbs_uicolors_1_1_0_plus");
        }
    }
    // GBStudio 2.0.0 beta 1
    // Should only be checked if previous fails
    else if (find_pattern(sig_gbs_fades_2_0_0_beta1, sizeof(sig_gbs_fades_2_0_0_beta1), &p_match_idx)) {        
        fprintf(stdout, "  - Engine: GBStudio 2.0.0 beta 1\n");
        return true;
        // fprintf(stdout, "  - Found: 0x%08x - %s\n", p_match_idx, "sig_gbs_fades_2_0_0_beta1");
    }
    // GBStudio 2.0.0 beta 2+
    if (find_pattern(sig_gbs_fades_2_0_0_beta2_plus, sizeof(sig_gbs_fades_2_0_0_beta2_plus), &p_match_idx)) {        
         // fprintf(stdout, "  - Found: 0x%08x - %s\n", p_match_idx, "sig_gbs_fades_2_0_0_beta2_plus");

        // GBStudio 2.0.0 beta 5+ (preliminary- not yet offically released)
        if (find_pattern(sig_gbs_uicolors_2_0_0_beta5_plus, sizeof(sig_gbs_uicolors_2_0_0_beta5_plus), &p_match_idx)) {
            fprintf(stdout, "  - Engine: GBStudio 2.0.0 beta 5+\n");
            return true;
            // fprintf(stdout, "  - Found: 0x%08x - %s\n", p_match_idx, "sig_gbs_uicolors_2_0_0_beta5_plus");
        }
        // Otherwise GBStudio 2.0.0 beta 2 - 4
        else {
            fprintf(stdout, "  - Engine: GBStudio 2.0.0 beta 2 - 4\n");
            return true;
        }

    }
    return false;
}


// Check for GBDK 2.x - GBDK-2020
static bool check_gbdk() {

    uint32_t p_match_idx;

    // GBDK 2.x - GBDK-2020 3.2.0
    if (find_pattern(sig_gbdk_bmp, sizeof(sig_gbdk_bmp), &p_match_idx)) {
        if (p_match_idx == sig_gbdk_bmp_2x_to_2020_320_at) {


            // Otherwise: GBDK 2.x - GBDK-2020 3.2.0
            fprintf(stdout, "  - Tools: GBDK 2.x - GBDK-2020 3.2.0\n");
            return true;
            // fprintf(stdout, "  - Found: 0x%08x - %s\n", p_match_idx, "sig_gbdk_bmp_2x_to_2020_320_at");
        }
    }

    // GBDK-2020 4.0.0
    if (find_pattern(sig_gbdk_0x80_GBDK_4_0_0, sizeof(sig_gbdk_0x80_GBDK_4_0_0), &p_match_idx)) {
        if (p_match_idx == sig_gbdk_0x80_at) {
            // fprintf(stdout, "  - Found: 0x%08x - %s\n", p_match_idx, "sig_gbdk_0x80_GBDK_4_0_0");

            // A second test
            // GBDK-2020 4.0.0
            if (find_pattern(sig_gbdk_0x20_GBDK_2020_400, sizeof(sig_gbdk_0x20_GBDK_2020_400), &p_match_idx)) {
                if (p_match_idx == sig_gbdk_0x20_at) {

                    fprintf(stdout, "  - Tools: GBDK-2020.4.0.0\n");
                    return true;
                    // fprintf(stdout, "  - Found: 0x%08x - %s\n", p_match_idx, "sig_gbdk_0x20_GBDK_2020_400");
                }
            }
        }
    }

    // GBDK-2020 4.0.1 and later
    if (find_pattern(sig_gbdk_0x20_GBDK_2020_401_plus, sizeof(sig_gbdk_0x20_GBDK_2020_401_plus), &p_match_idx)) {
        if (p_match_idx == sig_gbdk_0x20_at) {
            // fprintf(stdout, "  - Tools: GBDK-2020.4.0.1+\n");

            // An additional check
            // GBDK Part 3 (0x30) GBDK-2020 4.0.1 and later
            if (find_pattern(sig_gbdk_0x30_GBDK_2020_401_plus, sizeof(sig_gbdk_0x30_GBDK_2020_401_plus), &p_match_idx)) {
                if (p_match_idx == sig_gbdk_0x30_at) {

                    // fprintf(stdout, "  - Tools: GBDK-2020.4.0.1+\n");
                    // fprintf(stdout, "  - Found: 0x%08x - %s\n", p_match_idx, "sig_gbdk_0x30_GBDK_2020_401_plus");

                    // GBDK Part 4 (0x150) GBDK-2020 4.0.1
                    if (find_pattern(sig_gbdk_0x150, sizeof(sig_gbdk_0x150), &p_match_idx)) {

                        if (p_match_idx == sig_gbdk_0x150_GBDK_2x_to_2020_401_at) {
                            fprintf(stdout, "  - Tools: GBDK 2020.4.0.1\n");
                            return true;
                            // fprintf(stdout, "  - Found: 0x%08x - %s\n", p_match_idx, "sig_gbdk_0x150_GBDK_2x_to_2020_401_at");
                        }

                        //  GBDK-2020 4.0.2
                        if (p_match_idx == sig_gbdk_0x150_GBDK_2020_401_to_402_at) {
                            fprintf(stdout, "  - Tools: GBDK 2020.4.0.2\n");
                            return true;
                            // fprintf(stdout, "  - Found: 0x%08x - %s\n", p_match_idx, "sig_gbdk_0x150_GBDK_2020_401_to_402_at");
                        }
                    }

                    // GBDK-2020 4.0.3 and later
                    if (find_pattern(sig_gbdk_0x153, sizeof(sig_gbdk_0x153), &p_match_idx)) {
                        if (p_match_idx == sig_gbdk_0x153_GBDK_2020_403_plus_at) {
                            fprintf(stdout, "  - Tools: GBDK 2020.4.0.3+\n");
                            return true;
                            // fprintf(stdout, "  - Found: 0x%08x - %s\n", p_match_idx, "sig_gbdk_0x153_GBDK_2020_403_plus_at");
                        }
                    }
                }
            }
        }
    }

    return false;
}



// TODO: early ZGB titles (2016 - 2017) aren't reliably detected. Consider dropping the sound table requirement.
// Check ZGB engine
static bool check_zgb() {

    uint32_t p_match_idx;

    // Require sound const pattern, as starting filter
    if (find_pattern(sig_zgb_sound, sizeof(sig_zgb_sound), &p_match_idx)) {        
        // fprintf(stdout, "  - Found: 0x%08x - %s\n", p_match_idx, "sig_zgb_sound");
        
        if (find_pattern(sig_zgb_2017, sizeof(sig_zgb_2017), &p_match_idx)) {
            fprintf(stdout, "  - Engine: ZGB 2016-2017\n");
            return true;
            // fprintf(stdout, "  - Found: 0x%08x - %s\n", p_match_idx, "sig_zgb_2017");
        }

        // ZGB 2020.0
        if ((find_pattern(sig_zgb_2020_0_pushbank, sizeof(sig_zgb_2020_0_pushbank), &p_match_idx)) &&
            (find_pattern(sig_zgb_2020_0_popbank,  sizeof(sig_zgb_2020_0_popbank), &p_match_idx))) {

            fprintf(stdout, "  - Engine: ZGB 2020.0\n");
            return true;
            // fprintf(stdout, "  - Found: 0x%08x - %s\n", p_match_idx, "sig_zgb_2020_0_pushbank");
            // fprintf(stdout, "  - Found: 0x%08x - %s\n", p_match_idx, "sig_zgb_2020_0_popbank");
        }

        // ZGB 2020.1        
        if ((find_pattern(sig_zgb_2020_1_to_2021_0_pushbank, sizeof(sig_zgb_2020_1_to_2021_0_pushbank), &p_match_idx)) &&
            (find_pattern(sig_zgb_2020_1_to_2021_0_popbank, sizeof(sig_zgb_2020_1_to_2021_0_popbank), &p_match_idx))) {
            fprintf(stdout, "  - Engine: ZGB 2020.1 - 2021.0\n");
            return true;
            // fprintf(stdout, "  - Found: 0x%08x - %s\n", p_match_idx, "sig_zgb_2020_1_to_2021_0_pushbank");
            // fprintf(stdout, "  - Found: 0x%08x - %s\n", p_match_idx, "sig_zgb_2020_1_to_2021_0_popbank");
        }
    }

    return false;
}




bool gbtools_detect(uint8_t * p_rom_data, uint32_t rom_size) {

    set_search_buf(p_rom_data, rom_size);

    check_gbdk();
    // if (check_gbdk()) {
    check_zgb();
    check_gbstudio();

 

    return true;
//    return false;
}

