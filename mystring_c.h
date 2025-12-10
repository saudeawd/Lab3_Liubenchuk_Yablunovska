#ifndef LAB1_STRINGS_MYSTRING_C_H_
#define LAB1_STRINGS_MYSTRING_C_H_


#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

typedef struct str_t str_t;

str_t* str_new_repeat(size_t size, char initial);
str_t* str_new(size_t size);
str_t* str_new_from_buf(size_t size, const char* buf);
str_t* str_new_from_cstr(const char* str);

str_t* str_copy(const str_t* str);
char str_get(const str_t* str, size_t idx);
void str_set(const str_t* str, size_t idx, char value);

void str_reserve(const str_t* str, size_t new_capacity);
void str_shrink_to_fit(const str_t* str);
void str_resize(const str_t* str, size_t new_size, char new_char);
void str_clear(const str_t* str);

void str_insert_char(const str_t* str, size_t idx, char value);
void str_insert_str(const str_t* str, size_t idx, const str_t* str2);
void str_insert_cstr(const str_t* str, size_t idx, const char* str2);

void str_append_char(const str_t* str, char value);
void str_append_str(const str_t* str, const str_t* str2);
void str_append_cstr(const str_t* str, const char* str2);

void str_erase(const str_t* str, size_t begin, size_t size);

size_t str_size(const str_t* str);
size_t str_capacity(const str_t* str);

const char* str_cstr(const str_t* str);

size_t str_find_char(const str_t*, char c, size_t idx);
size_t str_find_cstr(const str_t*, const char* cstr, size_t idx);

str_t* str_substr(const str_t* str, size_t begin, size_t size);

int str_cmp(const str_t* str1, const str_t* str2);
int str_cmp_cstr(const str_t* str1, const char* str2);

void str_free(const str_t* str);

str_t* str_repeat(const str_t* str, size_t times);
str_t* str_concat(const str_t* str1, const str_t* str2);

void str_repeat_inplace(const str_t* str, size_t times);
void str_concat_inplace(const str_t* str, const str_t* str2);

#ifdef __cplusplus
}
#endif

#endif
