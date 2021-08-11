// This is free and unencumbered software released into the public domain.
// For more information, please refer to <https://unlicense.org>
// bbbbbr 2020

#include <stdint.h>
#include <stdbool.h>

#include "common.h"
#include "gbtoolchainid.h"


// ==== GBDK ====
//
// These are almost all in crt0.s
//
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
// 0x100
    const uint32_t sig_gbdk_0x100_at = 0x0100;
    const uint8_t sig_gbdk_0x100_GBDK_4_0_4[]  = {0x18, 0x51};
// 0x150
    // These should only be used when stacked on other entries
    const uint8_t sig_gbdk_0x150[] = {0xF3, 0x57, 0xAF, 0x31};
    const uint32_t sig_gbdk_0x150_GBDK_2x_to_2020_401_at   = 0x0150;
    const uint32_t sig_gbdk_0x150_GBDK_2020_401_to_402_at  = 0x0153;
    // 0x153
    const uint8_t sig_gbdk_0x153[] = {0xF3, 0x57, 0x31};
    const uint32_t sig_gbdk_0x153_GBDK_2020_403_plus_at = 0x0153;


// Check for GBDK 2.x - GBDK-2020
//
// If match is found: calls set_tools() and returns true
//
bool check_gbdk(void) {

        const char str_gbdk[] = "GBDK";

    // GBDK-2020 4.0.0
    if (check_pattern_addr(sig_gbdk_0x80_GBDK_4_0_0, sizeof(sig_gbdk_0x80_GBDK_4_0_0), sig_gbdk_0x80_at)) {
        // GBDK-2020 4.0.0 (Additional test to strengthen match)
        if (check_pattern_addr(sig_gbdk_0x20_GBDK_2020_400, sizeof(sig_gbdk_0x20_GBDK_2020_400), sig_gbdk_0x20_at)) {
            set_tools(str_gbdk, "2020.4.0.0");
            return true;
        }
    }

    // GBDK 2.x - GBDK-2020 3.2.0
    if (check_pattern_addr(sig_gbdk_bmp, sizeof(sig_gbdk_bmp), sig_gbdk_bmp_2x_to_2020_320_at)) {
        set_tools(str_gbdk, "2.x - 2020-3.2.0");
        return true;
    }


    // GBDK-2020 4.0.1 and later
    if (check_pattern_addr(sig_gbdk_0x20_GBDK_2020_401_plus, sizeof(sig_gbdk_0x20_GBDK_2020_401_plus), sig_gbdk_0x20_at)) {
        // GBDK-2020 4.0.1 and later (Additional test to strengthen match)
        if (check_pattern_addr(sig_gbdk_0x30_GBDK_2020_401_plus, sizeof(sig_gbdk_0x30_GBDK_2020_401_plus), sig_gbdk_0x30_at)) {

            // GBDK Part 4 (0x150) GBDK-2020 4.0.1
            if (check_pattern_addr(sig_gbdk_0x150, sizeof(sig_gbdk_0x150), sig_gbdk_0x150_GBDK_2x_to_2020_401_at)) {
                set_tools(str_gbdk, "2020.4.0.1");
                return true;
            }

            //  GBDK-2020 4.0.2
            if (check_pattern_addr(sig_gbdk_0x150, sizeof(sig_gbdk_0x150), sig_gbdk_0x150_GBDK_2020_401_to_402_at)) {
                set_tools(str_gbdk, "2020.4.0.2");
                return true;
            }

            // GBDK-2020 4.0.3 and later
            if (check_pattern_addr(sig_gbdk_0x153, sizeof(sig_gbdk_0x153), sig_gbdk_0x153_GBDK_2020_403_plus_at)) {
                set_tools(str_gbdk, "2020.4.0.3");

                // GBDK-2020 4.0.4 and later
                if (check_pattern_addr(sig_gbdk_0x100_GBDK_4_0_4, sizeof(sig_gbdk_0x100_GBDK_4_0_4), sig_gbdk_0x100_at)) {
                    set_tools(str_gbdk, "2020.4.0.4+");
                    return true;
                }

                return true;
            }
        }
    }

    return false;
}
