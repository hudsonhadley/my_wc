/**
 * @file main.c
 * @author Hudson Hadley
 * @date 2025-02-09
 * @brief A tool akin to wc
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

extern int errno;


int main(int argc, char* argv[]) {
    // Check we have sufficient info
    if (argc < 2) {
        printf("Usage: ./my_wc <filename>\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    FILE* file = fopen(argv[1], "r+");
    
    if (errno == EISDIR) {
        printf("my_wc: %s: Is a directory\n", argv[1]);
        return EXIT_FAILURE;
    } else if (errno != 0 || file == NULL) {
        printf("my_wc: %s: No such file or directory\n", argv[1]);
        return EXIT_FAILURE;
    }

    


    return EXIT_SUCCESS;
}