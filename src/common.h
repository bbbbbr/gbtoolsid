
#ifndef _COMMON_H
#define _COMMON_H

#define MAX_FILE_STR 4096
#define MAX_STR_LEN  2048

#define OUTPUT_DEFAULT  0
#define OUTPUT_JSON     1
#define OUTPUT_CSV      2
#define OUTPUT_CSV_BARE 3

#define PATH_STYLE_FILEONLY 0
#define PATH_STYLE_FULL     1
#define PATH_STYLE_DEFAULT  PATH_STYLE_FILEONLY

// Get string length without trailing terminator
#define sizeof_str_noterm(instr) (sizeof(instr) - 1)

// Debug option
// #define DEBUG_LOG_MATCHES

#define GET_ADDR_LAST_MATCH() (get_addr_last_match())

// For code copy & paste compat between C version and JS version
#define FIND_PATTERN_BUF(ptr_to_buf) (find_pattern(ptr_to_buf, sizeof(ptr_to_buf)))
#define FIND_PATTERN_STR_NOTERM(ptr_to_buf) (find_pattern(ptr_to_buf, sizeof_str_noterm(ptr_to_buf)))
#define CHECK_PATTERN_AT_ADDR(ptr_to_buf, check_addr) (check_pattern_addr(ptr_to_buf, sizeof(ptr_to_buf), check_addr))
#define FORMAT_ENTRY(e_type, e_name, e_version) ((tool_entry){.type = e_type, .c_name = e_name, .c_version = e_version})

// Reference example: Formerly: #define STR_GBDK_2_x_to_2020_3_2_0       "2.x - 2020.3.2.0"
#define DEF_NAME_STR(varname, str_content) static const char varname[] = str_content

// Reference example: const uint8_t sig_str_devsound_lite[] = "DevSound Lite";
#define DEF_PATTERN_STR(varname, str_content) static const uint8_t varname[] = str_content


// Reference example: const uint32_t sig_zgb_gbdk_bmp_2x_to_2020_320_at = 0x0010;
#define DEF_PATTERN_ADDR(varname, addr) static const uint32_t varname = addr

// Reference example: const uint8_t sig_gbsoundsystem_MultiSFXLoop[] = {0x2A, 0x4E, 0x06, 0x00, 0x87, 0xCB, 0x10, 0x87, 0xCB, 0x10, 0x87, 0xCB, 0x10};
// Need an additional macro wrapper AR_ARGS() to pass and expand a set of values to the array declaration
#define AR_ARGS(...) __VA_ARGS__
#define DEF_PATTERN_BUF(varname, buf_content) static const uint8_t varname[] = {buf_content}

#endif // _COMMON_H
