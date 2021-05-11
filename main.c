
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "gbtoolchainid.h"
#include "files.h"
#include "path_ops.h"

#define MAX_STR_LEN     4096

char filename_in[MAX_STR_LEN] = {'\0'};

uint8_t * p_buf_in  = NULL;

bool opt_mode_compress = true;
bool opt_verbose       = false;


static void display_help(void);
static int handle_args(int argc, char * argv[]);
void cleanup(void);


static void display_help(void) {
    fprintf(stdout,
       "gbtoolchainid [options] infile.gb[c]\n"
       "Use: Try to identify what toolchain was used to build a Game Boy game,\n"
       "     the result is printed to stdout.\n"
       "\n"
       "Options\n"
       "-h : Show this help screen\n"
       "-v : Verbose output\n"
       "Example: \"gbtoolchainid petris.gbc\"\n"
       );
}


int handle_args(int argc, char * argv[]) {

    int i = 1; // start at first arg

    if( argc < 2 ) {
        display_help();
        return false;
    }

    // Start at first optional argument
    // Last argument *must* be input files
    for (i = 1; i < (argc - 1); i++ ) {

        if (argv[i][0] == '-') {
            if (strstr(argv[i], "-h")) {
                display_help();
                return false;  // Don't parse input when -h is used
            } else
                printf("gbtoolchainid: Warning: Ignoring unknown option %s\n", argv[i]);
        }
    }

    // Copy input filename from last argument if not preceded with option dash
    if (argv[i][0] != '-') {
        snprintf(filename_in, sizeof(filename_in), "%s", argv[i++]);
        return true;
    }

    return false;
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

    fprintf(stdout, "File: %s\n", get_filename_from_path(filename_in));
    p_buf_in =  file_read_into_buffer(filename_in, &buf_size_in);

    if (p_buf_in)
        return gbtools_detect(p_buf_in, buf_size_in);
    else
        fprintf(stdout, "ERROR:  -->Failed to open %s\n", filename_in);

    return false;    
}


int main( int argc, char *argv[] )  {

    // Exit with failure by default
    int ret = EXIT_FAILURE;

    // Register cleanup with exit handler
    atexit(cleanup);

    if (handle_args(argc, argv)) {
        if (process_file())
            ret = EXIT_SUCCESS;

        fprintf(stdout, "\n");        
    }
    cleanup();

    ret = EXIT_SUCCESS;
    return ret; // Exit with failure by default
}
