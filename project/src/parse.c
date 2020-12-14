#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "parse.h"

#define FROM "From"
#define TO "To"
#define DATE "Date"

#define CONT_TYPE "Content-Type"
#define CONT "Content"
#define MULTIPART "multipart/"
#define BOUNDARY "boundary"

char *search_field(const char *str, const char *field) {
    char data_field[255];
    snprintf(data_field, sizeof(data_field), "%s:", field);
    char *res = strcasestr(str, data_field);
    if (!res) {
        return NULL;
    }

    if (res == str) {
        res = res + get_cnt_space(res) + strlen(field) + 1;
        return res;
    }
    while (*(res - 1) != '\n') {
        char *tmp = res + 1;
        res = strcasestr(tmp, data_field);
    }

    return res + get_cnt_space(res) + strlen(field) + 1;
}

size_t get_cnt_space(char *beg) {
    size_t k = 0;
    while (isspace(*beg++)) {
        k++;
    }
    return k;
}

int parse_str(char *str, char *field, char **dst) {
    char *data = search_field(str, field);

    if (!data) {
        asprintf(dst, "%s", "");
        return EXIT_SUCCESS;
    }

    char *end = strchr(data, '\r');
    if (!end) {
        end = strchr(data, '\n');
    }
    while (true) {
        if (*end == '\n' && isspace(*(end + 1))) {
            end = strchr(end + 1, '\n');

        } else if (*end == '\r' && isspace(*(end + 1))) {
            end = strchr(end + 1, '\n');

        } else if (*end == '\r' && isspace(*(end + 2))) {
            end = strchr(end + 2, '\n');

        } else {
            data += get_cnt_space(data);
            asprintf(dst, "%.*s", (int)(end - data), data);

            end = *dst + strlen(*dst);
            for (char *cur = *dst; cur != end; cur++) {
                if (*cur == '\n' || *cur == '\r') {
                    *cur = FLAG;
                }
            }
            size_t len = strlen(*dst);

            for (size_t i = 0; i < len; i++) {
                if (*(*dst + i + 1) == FLAG) {
                    while (*(*dst + i + 1) == FLAG) {
                        for (size_t j = i + 1; j < len; j++) {
                            *(*dst + j) = *(*dst + j + 1);
                        }
                        len--;
                    }
                }
            }
            return EXIT_SUCCESS;
        }
    }
}

letter_t *parse_header(char *str) {
    letter_t *letter = calloc(sizeof(letter_t), 1);
    if (!letter) {
        return NULL;
    }
    if (parse_str(str, FROM, &(letter->sender))) {
        free_letter(letter);
        return NULL;
    }
    if (parse_str(str, TO, &(letter->recipient))) {
        free_letter(letter);
        return NULL;
    }
    if (parse_str(str, DATE, &(letter->date))) {
        free_letter(letter);
        return NULL;
    }
    get_content_type(str, &(letter->count_part));
    return letter;
}

void free_letter(letter_t *src) {
    free(src->date);
    free(src->recipient);
    free(src->sender);
    free(src);
}

int get_content_type(char *str, size_t *value) {
    char content_type[BUF_LEN];

    char *content_header = search_field(str, CONT_TYPE);
    if (!content_header) {
        *value = 1;
        return EXIT_SUCCESS;
    }
    snprintf(content_type, sizeof(content_type), "%s", content_header);

    char *multipart = strcasestr(content_type, MULTIPART);
    if (!multipart) {
        *value = 1;
        return EXIT_SUCCESS;
    }
    *value = get_boundary(str, BOUNDARY);

    return EXIT_SUCCESS;
}

size_t get_boundary(char *content_type, const char *field) {
    char *boundary = strcasestr(content_type, field);
    if (!boundary || isalpha(*(boundary - 1))) {
        return 1;
    }

    boundary += strlen(field);
    boundary = boundary + get_cnt_space(boundary) + 1;
    boundary += get_cnt_space(boundary);

    char res[BUF_LEN] = {'-', '-'};
    size_t boundary_cnt = 0;
    char *cur = boundary;
    size_t cnt = 0;

    if (*cur == '\"') {
        boundary++;
        cur++;
        while (*cur != '\"') {
            cur++;
        }
        cnt = cur - boundary;
    } else {
        while (*cur != '\r' && *cur != '\n') {
            cnt++;
            cur++;
        }
    }
    strncat(res, boundary, cnt);

    size_t cnt_wp_end = 0;

    for (size_t i = cnt + 1; i > 0; i--) {
        if (isspace(res[i])) {
            cnt_wp_end++;
        } else {
            break;
        }
    }
    res[cnt + 2 - cnt_wp_end] = '\0';

    char *tmp = strcasestr(content_type, res);
    char *data = NULL;

    while (tmp) {
        data = strcasestr(tmp, CONT);
        if (data) {
            boundary_cnt++;
        }
        tmp++;
        tmp = strcasestr(tmp, res);
    }
    return boundary_cnt;
}

void letter_print(letter_t *src) {
    printf("%s|%s|%s|%zu\n", src->sender, src->recipient, src->date, src->count_part);
}
