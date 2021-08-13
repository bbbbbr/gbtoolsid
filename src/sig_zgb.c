// This is free and unencumbered software released into the public domain.
// For more information, please refer to <https://unlicense.org>
// bbbbbr 2020

#include <stdint.h>
#include <stdbool.h>

#include "common.h"
#include "entries.h"
#include "gbtoolchainid.h"


// ==== ZGB ====
// All ZGB records can be at any location (depends on where the linker places them)
    const uint8_t sig_zgb_sound[] = {0x05, 0x04, 0x05, 0x04, 0x03, 0x10, 0xFF, 0x16, 0xFF, 0x1A, 0xFF, 0x20, 0xFF, 0x24, 0xFF};
    const uint8_t sig_zgb_2017[] = {0xF8, 0x02, 0x4E, 0x23, 0x46, 0xF8, 0x04, 0x11, 0x41, 0xFF, 0x1A, 0xE6, 0x02};
    const uint8_t sig_zgb_2020_0_pushbank[] = {0x34, 0x4E, 0x23, 0x46, 0x02, 0x01, 0x00, 0x20, 0x02};
    const uint8_t sig_zgb_2020_0_popbank[]  = {0x35, 0x4E, 0x23, 0x46, 0x0A, 0x01, 0x00, 0x20, 0x02};
    const uint8_t sig_zgb_2020_1_to_2021_0_pushbank[] = {0x34, 0x4E, 0x23, 0x46, 0xFA, 0x90, 0xFF, 0x02, 0xF8, 0x02, 0x7E, 0xEA, 0x90, 0xFF, 0xEA, 0x00, 0x20};
    const uint8_t sig_zgb_2020_1_to_2021_0_popbank[]  = {0x4E, 0x23, 0x46, 0x0A, 0xEA, 0x90, 0xFF, 0xEA, 0x00, 0x20, 0x2B, 0x35};   


// TODO: early ZGB titles (2016 - 2017) aren't reliably detected. Consider dropping the sound table requirement.

// Check ZGB engine
bool check_zgb(void) {

    tool_entry entry = {.type = TYPE_ENGINE, .name = "ZGB", .version = ""};

    // Require sound const pattern, as starting filter
    if (find_pattern(sig_zgb_sound, sizeof(sig_zgb_sound))) {

        if (find_pattern(sig_zgb_2017, sizeof(sig_zgb_2017))) {
            entry_add_with_version(entry, "2016-2017");
            return true;
        }

        // ZGB 2020.0
        if ((find_pattern(sig_zgb_2020_0_pushbank, sizeof(sig_zgb_2020_0_pushbank))) &&
            (find_pattern(sig_zgb_2020_0_popbank,  sizeof(sig_zgb_2020_0_popbank)))) {

            entry_add_with_version(entry, "2020.0");
            return true;
        }

        // ZGB 2020.1
        if ((find_pattern(sig_zgb_2020_1_to_2021_0_pushbank, sizeof(sig_zgb_2020_1_to_2021_0_pushbank))) &&
            (find_pattern(sig_zgb_2020_1_to_2021_0_popbank, sizeof(sig_zgb_2020_1_to_2021_0_popbank)))) {
            entry_add_with_version(entry, "2020.1 - 2021.0");
            return true;
        }
    }

    return false;
}
