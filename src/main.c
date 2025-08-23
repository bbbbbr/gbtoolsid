// This is free and unencumbered software released into the public domain.
// For more information, please refer to <https://unlicense.org>
// bbbbbr 2020

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "common.h"

#include "files.h"
#include "entries.h"
#include "path_ops.h"
#include "gbtoolchainid.h"
#include "display.h"

char filename_in[MAX_STR_LEN] = {'\0'};
uint8_t * p_buf_in  = NULL;

#define VERSION "1.5.3"

int opt_output_style = OUTPUT_DEFAULT;
int opt_path_output_style = PATH_STYLE_DEFAULT;
bool opt_strict_checks = false;


static void display_help(void);
static int handle_args(int argc, char * argv[]);
void init(void);
void cleanup(void);


static void display_help(void) {
    fprintf(stdout,
       "gbtoolsid [options] infile.gb[c]\n"
       "Version: "VERSION"\n"
       "Use: Try to identify the toolchain used to build a\n"
       "     Game Boy game the result is printed to stdout.\n"
       "\n"
       "Options\n"
       "-h   : Show this help screen\n"
       "-oj  : json style output\n"
       "-oc  : csv style output\n"
       "-oC  : Bare csv style output (no field names)\n"
       "-s   : Strict mode: require GBDK match before testing ZGB or GBStudio\n"
       "-pF  : Show full path to file in output (default: filename only)\n"
       "\n"
       "Example: \"gbtoolchainid petris.gbc\"\n"
       );
}


int handle_args(int argc, char * argv[]) {

    int i;
    bool filename_present = false;

    if( argc < 2 ) {
        display_help();
        return false;
    }

    // Start at first optional argument ([0] is executable)
    for (i = 1; i < argc; i++ ) {

        if (strstr(argv[i], "-h") == argv[i]) {
            display_help();
            return false;  // Don't parse input when -h is used
        }
        else if (strstr(argv[i], "-oj") == argv[i]) {
            opt_output_style = OUTPUT_JSON;
        }
        else if (strstr(argv[i], "-oc") == argv[i]) {
            opt_output_style = OUTPUT_CSV;
        }
        else if (strstr(argv[i], "-oC") == argv[i]) {
            opt_output_style = OUTPUT_CSV_BARE;
        }
        else if (strstr(argv[i], "-pF") == argv[i]) {
            opt_path_output_style = PATH_STYLE_FULL;
        }
        else if (strstr(argv[i], "-s") == argv[i]) {
            opt_strict_checks = true;

        } else if (argv[i][0] == '-') {
            printf("gbtoolchainid: Warning: Ignoring unknown option %s\n", argv[i]);
            return false;
        }

        // Copy input filename (if not preceded with option dash)
        else if (argv[i][0] != '-') {
            snprintf(filename_in, sizeof(filename_in), "%s", argv[i]);
            filename_present = true;
        }
    }

    if (filename_present) {
        return true;
    } else {
        display_help();
        return false;
    }
}


void init(void) {
    entry_init();
}

// Called by atexit() (or earlier) to free resources
void cleanup(void) {
    if (p_buf_in != NULL) {
        free(p_buf_in);
        p_buf_in = NULL;
    }
}


static int process_file() {

    uint32_t  buf_size_in = 0;

    p_buf_in = file_read_into_buffer(filename_in, &buf_size_in);

    if ((p_buf_in) && (buf_size_in > 0)) {
        gbtools_detect(p_buf_in, buf_size_in, opt_strict_checks);
        return true;
    }

    return false;
}


int main( int argc, char *argv[] )  {

    init();

    // Exit with failure by default
    int ret = EXIT_FAILURE;

    // Register cleanup with exit handler
    atexit(cleanup);

    if (handle_args(argc, argv)) {
        if (process_file()) {
            if (opt_path_output_style == PATH_STYLE_FULL)
                display_output(opt_output_style, filename_in);
            else
                display_output(opt_output_style, get_filename_from_path(filename_in));
            ret = EXIT_SUCCESS;
        }
    }
    cleanup();

    return ret; // Exit with failure by default
}
