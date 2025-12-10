// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "mystring_c.h"
#include <stdio.h>
#include <string.h>


int main() {
    const str_t* name = str_new_from_cstr("Assistant");
    printf("Hello %s!\n", str_cstr(name));

    str_repeat_inplace(name, 2);
    printf("Double hello %s!\n", str_cstr(name));

    const str_t* name2 = str_repeat(name, 2);
    printf("Double hello %s! (2)\n", str_cstr(name));
    str_free(name2);

    str_append_cstr(name, " :)");
    printf("Glad to see ya, %s!\n", str_cstr(name));

    const str_t* message2 = str_new_from_cstr("i love python");
    printf("Found: %zu, expected: 2", str_find_cstr(message2, "love", 0));

    const str_t* python = str_new_from_buf(strlen("python"), "python");
    str_erase(message2, str_find_cstr(message2, "python", 0), str_size(python));

    str_append_cstr(message2, "c++");
    printf("%s\n", str_cstr(message2));

    str_insert_cstr(message2, 2, "<3 ");
    printf("%s\n", str_cstr(message2));

    str_resize(message2, str_size(message2) + 3, '!');
    printf("%s\n", str_cstr(message2));

    str_clear(message2);
    if (str_size(message2) != 0)
        printf("Bad clear\n");

    str_free(message2);
    str_free(python);

    const str_t* c1 = str_new(0);
    str_append_char(c1, 'c');
    str_append_char(c1, 'c');
    str_append_char(c1, 'c');

    const str_t* c2 = str_new_repeat(3, 'c');
    printf("Comparison result: %d", str_cmp(c1, c2));

    str_free(c1);
    str_free(c2);

    const str_t* hello = str_new_from_buf(3, "hello");
    printf("%s\n", str_cstr(hello));
    printf("Comparison result: %d\n", strcmp(str_cstr(hello), "hel"));

    const str_t* hello_copy = str_copy(hello);
    const str_t* lo = str_new_from_cstr("lo");
    str_concat_inplace(hello_copy, lo);
    printf("%s\n", str_cstr(hello));
    printf("%s\n", str_cstr(hello_copy));

    str_free(hello);
    str_free(hello_copy);

    hello = str_new_from_cstr("hello");
    str_append_char(hello, '!');

    printf("%c\n", str_get(hello, str_size(hello) - 1));
    printf("%c\n", str_get(hello, 0));
    str_set(hello, 0, 'H');
    printf("%s\n", str_cstr(hello));
    str_set(hello, 0, 'h');
    printf("%s\n", str_cstr(hello));

    printf("Capacity: %zu\n", str_capacity(hello));
    str_shrink_to_fit(hello);
    printf("Capacity (after shrink): %zu\n", str_capacity(hello));
    str_reserve(hello, 20);
    printf("Capacity (after reserve): %zu\n", str_capacity(hello));

    str_free(hello);

    const str_t* message3 = str_new_from_cstr("Goodbye, !");
    str_insert_str(message3, 9, name);
    printf("%zu %s\n", str_find_char(message3, 'G', 0), str_cstr(message3));

    str_free(message3);

    const str_t* message4 = str_new_from_cstr("test");
    str_insert_char(message4, 1, 't');
    printf("%s\n", str_cstr(message4));

    str_free(message4);

    const str_t* message5 = str_new_from_cstr("msg");
    const str_t* substr = str_substr(message5, 1, 2);
    printf("%s\n", str_cstr(substr));
    str_free(substr);

    str_append_char(message5, ' ');
    str_append_str(message5, name);
    str_append_cstr(message5, "!!!");
    printf("%s\n", str_cstr(message5));

    printf("Comparison result: %d\n", str_cmp_cstr(message5, "msg"));

    str_free(message5);

    const str_t* message6 = str_new_from_cstr("hello ");
    const str_t* message7 = str_concat(message6, name);
    printf("%s\n", str_cstr(message7));

    str_free(message7);
    str_free(message6);

    str_free(name);
}
