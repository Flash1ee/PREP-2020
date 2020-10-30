#ifndef _PARSE_H_
#define _PARSE_H_
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define END_OF_HEADER -2
#define NO -3
#define NOT_FOUND -3

typedef struct {
    char *sender;
    char *recipient;
    char *date;
    size_t count_part;
} letter_t;


char *search_field(const char *str, const char *field);
int parse_str(char *str, char *field, char **dst);
letter_t *parse_header(char *str);
void free_letter(letter_t *src);
void letter_print(letter_t *src);
int get_content_type(char *str, size_t *value);
size_t get_boundary(char *content_type, const char *field);
size_t get_cnt_space(char *beg);


#endif  // _PARSE_H_