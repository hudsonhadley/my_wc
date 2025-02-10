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

bool is_whitespace(char c);

int main(int argc, char* argv[]) {
    char* file_name;
    bool bytes = false;
    bool chars = false;
    bool lines = false;
    bool words = false;

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
        } else if (flag[1] == 'w') {
            words = true;
        } else { // Invalid flag
            printf(".my_wc: %s: invalid flag\n", flag);
            return EXIT_FAILURE;
        }
    } else if (argc == 2) {
        file_name = argv[1];

        bytes = true;
        lines = true;
        words = true;
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

    long char_count = 0;
    long line_count = 0;
    long byte_count = 0;
    long word_count = 0;
    bool in_word = false; // Keeps track if we are in a word or not
    while (true) {
        int c_int = fgetc(file);
        if (c_int == EOF) {
            break;
        }

        char c = (char) c_int;
        char_count++;

        if (c == '\n') {
            line_count++;
        }

        // If it isn't whitespace, and we haven't seen a word yet
        if (is_whitespace(c) && in_word) { // Count words at the start
            word_count++;
            in_word = false;
        } else if (!is_whitespace(c) && !in_word) {
            in_word = true;
        }

        byte_count += sizeof(c);
    }

    // If we end with a word, it counts as a word
    if (in_word) {
        word_count++;
    }

    if (bytes) {
        printf("%ld ", byte_count);
    }
    if (lines) {
        printf("%ld ", line_count);
    }
    if (words) {
        printf("%ld ", word_count);
    }
    if (chars) {
        printf("%ld ", char_count);
    }

    printf("%s\n", file_name);

    return EXIT_SUCCESS;
}


bool is_whitespace(char c) {
    char whitespace[] = {' ', '\n', '\t', '\r'};
    size_t const SIZE = 4;

    for (int i = 0; i < SIZE; i++) {
        if (c == whitespace[i]) {
            return true;
        }
    }

    return false;
}