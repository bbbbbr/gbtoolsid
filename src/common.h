
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

// For code copy & paste compat between C version and JS version
#define FIND_PATTERN_BUF(ptr_to_buf) (find_pattern(ptr_to_buf, sizeof(ptr_to_buf)))
#define FIND_PATTERN_STR_NOTERM(ptr_to_buf) (find_pattern(ptr_to_buf, sizeof_str_noterm(ptr_to_buf)))
#define FORMAT_ENTRY(e_type, e_name, e_version) ((tool_entry){.type = e_type, .c_name = e_name, .c_version = e_version})

#endif // _COMMON_H
