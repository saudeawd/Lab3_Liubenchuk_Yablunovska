// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "mystring.hpp"
#include "mystring_c.h"

struct str_t {
    my_str_t* obj;
};

str_t* str_new_repeat(const size_t size, const char initial) {
    return new str_t{new my_str_t{size, initial}};
}

str_t* str_new(const size_t size) {
    return new str_t{new my_str_t{size}};
}

str_t* str_new_from_buf(const size_t size, const char* buf) {
    return new str_t{new my_str_t{size, buf}};
}

str_t* str_new_from_cstr(const char* str) {
    return new str_t{new my_str_t{str}};
}

str_t* str_copy(const str_t* str) {
    return new str_t{new my_str_t{*str->obj}};
}

char str_get(const str_t* str, const size_t idx) {
    return (*str->obj)[idx];
}

void str_set(const str_t* str, const size_t idx, const char value) {
    (*str->obj)[idx] = value;
}

void str_reserve(const str_t* str, const size_t new_capacity) {
    str->obj->reserve(new_capacity);
}

void str_shrink_to_fit(const str_t* str) {
    str->obj->shrink_to_fit();
}

void str_resize(const str_t* str, const size_t new_size, const char new_char) {
    str->obj->resize(new_size, new_char);
}

void str_clear(const str_t* str) {
    str->obj->clear();
}

void str_insert_char(const str_t* str, const size_t idx, const char value) {
    str->obj->insert(idx, value);
}

void str_insert_str(const str_t* str, const size_t idx, const str_t* str2) {
    str->obj->insert(idx, *str2->obj);
}

void str_insert_cstr(const str_t* str, size_t idx, const char* str2) {
    str->obj->insert(idx, str2);
}

void str_append_char(const str_t* str, char value) {
    str->obj->append(value);
}

void str_append_str(const str_t* str, const str_t* str2) {
    str->obj->append(*str2->obj);
}

void str_append_cstr(const str_t* str, const char* str2) {
    str->obj->append(str2);
}

void str_erase(const str_t* str, const size_t begin, const size_t size) {
    str->obj->erase(begin, size);
}

size_t str_size(const str_t* str) {
    return str->obj->size();
}

size_t str_capacity(const str_t* str) {
    return str->obj->capacity();
}

const char* str_cstr(const str_t* str) {
    return str->obj->c_str();
}

size_t str_find_char(const str_t* str, const char c, const size_t idx) {
    return str->obj->find(c, idx);
}

size_t str_find_cstr(const str_t* str, const char* str2, size_t idx) {
    return str->obj->find(str2, idx);
}

str_t* str_substr(const str_t* str, const size_t begin, const size_t size) {
    return new str_t{new my_str_t{str->obj->substr(begin, size)}};
}

int str_cmp(const str_t* str1, const str_t* str2) {
    const std::strong_ordering order = (*str1->obj) <=> (*str2->obj);
    if (order == std::strong_ordering::less) {
        return -1;
    }

    if (order == std::strong_ordering::greater) {
        return 1;
    }

    return 0;
}

int str_cmp_cstr(const str_t* str1, const char* str2) {
    const std::strong_ordering order = (*str1->obj) <=> str2;

    if (order == std::strong_ordering::less) {
        return -1;
    }

    if (order == std::strong_ordering::greater) {
        return 1;
    }

    return 0;
}

void str_free(const str_t* str) {
    delete str->obj;
    delete str;
}

str_t* str_repeat(const str_t* str, const size_t times) {
    return new str_t{
        new my_str_t{(*str->obj) * times}
    };
}

str_t* str_concat(const str_t* str1, const str_t* str2) {
    return new str_t{
        new my_str_t{(*str1->obj) + (*str2->obj)}
    };
}

void str_repeat_inplace(const str_t* str, const size_t times) {
    *str->obj *= times;
}

void str_concat_inplace(const str_t* str, const str_t* str2) {
    *str->obj += *str2->obj;
}
