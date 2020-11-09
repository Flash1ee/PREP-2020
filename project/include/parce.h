#ifndef PROJECT_INCLUDE_PARCE_H_
#define PROJECT_INCLUDE_PARCE_H_

#define END_OF_HEADER -2
#define NO -3
#define NOT_FOUND -3


#define FLAG 27
#define BUF_LEN 255

#define FROM "From"
#define TO "To"
#define DATE "Date"

#define CONT_TYPE "Content-Type"
#define CONT "Content"
#define MULTIPART "multipart/"
#define BOUNDARY "boundary"


typedef struct {
    char *sender;
    char *recipient;
    char *date;
    size_t count_part;
} letter_t;

void free_letter(letter_t *src);
void letter_print(letter_t *src);

char     *search_field(const char *str, const char *field);
int       parse_str(char *str, char *field, char **dst);
letter_t *parse_header(char *str);

int    get_content_type(char *str, size_t *value);
size_t get_boundary(char *content_type, const char *field);
size_t get_cnt_space(char *beg);


#endif  // PROJECT_INCLUDE_PARCE_H_
