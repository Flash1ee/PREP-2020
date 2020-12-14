#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include "parse.h"


int main(int argc, const char **argv) {
    if (argc != 2) {
        return -1;
    }

    const char *path_to_eml = argv[1];
    int file = open(path_to_eml, O_RDONLY);
    if (file < 0) {
        return -1;
    }

    char *ptr_to_data = NULL;
    struct stat file_buf = { };

    if (fstat(file, &file_buf) < 0) {
        return -1;
    }
    ptr_to_data = (char *)mmap(0, file_buf.st_size, PROT_READ, MAP_SHARED, file, 0);
    if (ptr_to_data == MAP_FAILED) {
        return -1;
    }

    letter_t *letter = parse_header(ptr_to_data);
    if (!letter) {
        puts("E-mail parse error...");
    }

    letter_print(letter);
    free_letter(letter);

    close(file);

    return 0;
}
