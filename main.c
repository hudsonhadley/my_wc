/**
 * @file main.c
 * @author Hudson Hadley
 * @date 2025-02-09
 * @brief A tool akin to wc
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>

extern int errno;

long count_bytes(FILE* file);

int main(int argc, char* argv[]) {
    char* file_name;
    bool bytes = false;
    bool chars = false;
    bool lines = false;

    // If a flag was attempted
    if (argc == 3) {
        char* flag = argv[1];
        file_name = argv[2];

        if (flag[0] != '-') { // Invalid flag
            printf(".my_wc: %s: invalid flag\n", flag);
            return EXIT_FAILURE;
        } else if (flag[1] == 'c') {
            bytes = true;
        } else if (flag[1] == 'm') {
            chars = true;
        } else if (flag[1] == 'l') {
            lines = true;
        } else { // Invalid flag
            printf(".my_wc: %s: invalid flag\n", flag);
            return EXIT_FAILURE;
        }
    } else if (argc == 2) {
        file_name = argv[1];

        bytes = true;
        chars = true;
        lines = true;
    } else {
        printf("Usage: ./my_wc [OPTION] <filename>\n");
        return EXIT_FAILURE;
    }

    

    errno = 0;
    FILE* file = fopen(file_name, "r+");
    
    if (errno == EISDIR) {
        printf("my_wc: %s: Is a directory\n", file_name);
        return EXIT_FAILURE;
    } else if (errno != 0 || file == NULL) {
        printf("my_wc: %s: No such file or directory\n", file_name);
        return EXIT_FAILURE;
    }



    if (bytes) {
        int byte_count = count_bytes(file);
        printf(" %d", byte_count);
    }

    printf(" %s\n", file_name);

    return EXIT_SUCCESS;
}


/**
 * @brief Counts the number of bytes in a file
 * 
 * @param file The file we want to read
 * @return The number of bytes in the file, or -1 if the file is null
 */
long count_bytes(FILE* file) {
    if (file == NULL) {
        return -1;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fclose(file);

    return file_size;
}