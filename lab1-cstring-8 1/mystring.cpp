// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "mystring.hpp"

#include <cstring>

#include <string>
#include <iostream>
#include <stdexcept>

inline size_t min(const size_t a, const size_t b) {
    return (a > b) ? b : a;
}

//! Choose capacity s.t. cap > size
//! and cap % 16 = 15
inline size_t evaluate_capacity(const size_t size) {
    return ((size + 0x10) & (~0xf)) - 1;
}

inline size_t expand(const size_t old_capacity, const size_t required_size) {
    size_t new_capacity;
    if (old_capacity > 1024) {
        new_capacity = old_capacity + 1024;
    }
    else {
        new_capacity = old_capacity * 2;
    }

    if (required_size > new_capacity) {
        return evaluate_capacity(required_size);
    }

    return evaluate_capacity(new_capacity);
}

inline size_t get_cstr_size(const char* str) {
    if (str == nullptr) {
        throw std::invalid_argument("nullptr for cstr");
    }

    size_t size = 0;
    while (str[size] != '\0')
        size++;

    return size;
}

my_str_t::my_str_t(const size_t size, const char* str) : size_m{size}, capacity_m{evaluate_capacity(size)},
                                                         data_m{new char[capacity_m + 1]} {
    memcpy(data_m, str, size_m);
    data_m[size_m] = '\0';
}

my_str_t::my_str_t(const size_t size, const char initial) : size_m{size}, capacity_m(evaluate_capacity(size)),
                                                            data_m{new char[capacity_m + 1]} {
    // Fill the string
    for (size_t i = 0; i < size_m; i++)
        data_m[i] = initial;

    data_m[size_m] = '\0';
}

my_str_t::my_str_t(const char* cstr) : size_m{get_cstr_size(cstr)}, capacity_m{evaluate_capacity(size_m)},
                                       data_m{new char[capacity_m + 1]} {
    memcpy(data_m, cstr, size_m + 1);
}

my_str_t::my_str_t(const size_t size) : size_m{size}, capacity_m{evaluate_capacity(size)},
                                        data_m{new char[capacity_m + 1]} {
    data_m[size_m] = '\0';
}

my_str_t::my_str_t(const std::string& str) : size_m{str.length()}, capacity_m{evaluate_capacity(size_m)},
                                             data_m{new char[capacity_m + 1]} {
    memcpy(data_m, str.c_str(), size_m + 1);
}

my_str_t::my_str_t(const my_str_t& str) : size_m{str.size_m}, capacity_m{str.capacity_m},
                                          data_m{new char[capacity_m + 1]} {
    memcpy(data_m, str.data_m, size_m + 1);
}

my_str_t& my_str_t::operator=(const my_str_t& str) {
    my_str_t temp{str};
    swap(temp);
    return *this;
}

my_str_t::my_str_t(my_str_t&& str) noexcept {
    swap(str);
}

my_str_t& my_str_t::operator=(my_str_t&& str) noexcept {
    swap(str);

    return *this;
}

void my_str_t::swap(my_str_t& other) noexcept {
    std::swap(data_m, other.data_m);
    std::swap(capacity_m, other.capacity_m);
    std::swap(size_m, other.size_m);
}


char& my_str_t::operator[](const size_t idx) {
    return data_m[idx];
}

const char& my_str_t::operator[](const size_t idx) const {
    return data_m[idx];
}

char& my_str_t::at(const size_t idx) {
    if (idx >= size_m)
        throw std::out_of_range("string_t::at");

    return data_m[idx];
}

const char& my_str_t::at(const size_t idx) const {
    if (idx >= size_m)
        throw std::out_of_range("string_t::at");

    return data_m[idx];
}

void my_str_t::reserve(const size_t new_capacity) {
    // new_capacity = evaluate_capacity(new_capacity);
    // Disabled alignment because tests fail
    if (new_capacity <= capacity_m)
        return;

    // Copy data from old array to new
    char* new_data = new char[new_capacity + 1];
    if (data_m != nullptr) {
        memcpy(new_data, data_m, size_m + 1);
        delete[] data_m;
    }

    capacity_m = new_capacity;
    data_m = new_data;
}

void my_str_t::shrink_to_fit() {
    // const size_t new_capacity = evaluate_capacity(size_m);
    const size_t new_capacity = size_m; // Disabled alignment because tests fail
    if (new_capacity == capacity_m)
        return;

    // Copy data from old array to new
    char* new_data = new char[new_capacity + 1];
    memcpy(new_data, data_m, size_m + 1);
    delete[] data_m;

    capacity_m = new_capacity;
    data_m = new_data;
}

void my_str_t::resize(const size_t new_size, const char new_char) {
    // If we are shrinking, then there is no need to work with capacity
    if (new_size <= size_m) {
        size_m = new_size;
        return;
    }

    // We need to expand string
    if (new_size > capacity_m) {
        reserve(expand(capacity_m, new_size));
    }

    // Fill with new_char
    for (size_t i = size_m; i < new_size; i++)
        data_m[i] = new_char;

    size_m = new_size;
}

void my_str_t::clear() {
    size_m = 0;
}

void my_str_t::insert(const size_t idx, const char c) {
    if (idx > size_m)
        throw std::out_of_range("string_t::insert");

    if (idx == size_m)
        return append(c);

    if (size_m + 1 > capacity_m)
        reserve(expand(capacity_m, size_m + 1));

    memmove(data_m + idx + 1, data_m + idx, size_m - idx + 1);
    data_m[idx] = c;
    size_m++;
}

void my_str_t::insert(const size_t idx, const my_str_t& str) {
    if (idx > size_m)
        throw std::out_of_range("string_t::insert");

    if (idx == size_m)
        return append(str);

    if (size_m + str.size_m > capacity_m)
        reserve(expand(capacity_m, size_m + str.size_m));

    memmove(
        data_m + idx + str.size_m,
        data_m + idx,
        size_m - idx + 1
    );
    memcpy(data_m + idx, str.data_m, str.size_m);
    size_m += str.size_m;
}

void my_str_t::insert(const size_t idx, const char* cstr) {
    if (idx > size_m)
        throw std::out_of_range("string_t::insert");

    if (idx == size_m)
        return append(cstr);

    const size_t size = get_cstr_size(cstr);
    if (size_m + size > capacity_m)
        reserve(expand(capacity_m, size_m + size));

    memmove(
        data_m + idx + size,
        data_m + idx,
        size_m - idx + 1
    );

    memcpy(data_m + idx, cstr, size);
    size_m += size;
}

void my_str_t::append(const char c) {
    if (size_m + 1 > capacity_m)
        reserve(expand(capacity_m, size_m + 1));

    data_m[size_m] = c;
    size_m++;
    data_m[size_m] = '\0';
}

void my_str_t::append(const my_str_t& str) {
    if (str.size_m == 0)
        return;
    if (size_m + str.size_m > capacity_m)
        reserve(expand(capacity_m, size_m + str.size_m));

    memcpy(data_m + size_m, str.data_m, str.size_m);
    size_m += str.size_m;
    data_m[size_m] = '\0';
}

void my_str_t::append(const char* cstr) {
    const size_t size = get_cstr_size(cstr);
    if (size == 0)
        return;
    if (size_m + size > capacity_m)
        reserve(expand(capacity_m, size_m + size));

    memcpy(data_m + size_m, cstr, size);
    size_m += size;
    data_m[size_m] = '\0';
}

void my_str_t::erase(const size_t begin, const size_t size) {
    if (begin > size_m)
        throw std::out_of_range("string_t::erase");

    if (begin + size >= size_m) {
        size_m = begin;
        return;
    }

    memmove(data_m + begin, data_m + begin + size, size_m - begin);
    size_m -= size;
    data_m[size_m] = '\0';
}


size_t my_str_t::size() const noexcept {
    return size_m;
}

size_t my_str_t::capacity() const noexcept {
    return capacity_m;
}

const char* my_str_t::c_str() const {
    if (data_m == nullptr)
        return "";

    return data_m;
}

size_t my_str_t::find(const char c, size_t idx) const {
    if (idx > size_m)
        throw std::out_of_range("string_t::find");

    for (; idx < size_m; idx++)
        if (data_m[idx] == c)
            return idx;

    return not_found;
}

size_t my_str_t::find(const std::string& str, size_t idx) const {
    if (idx > size_m)
        throw std::out_of_range("string_t::find");

    if (str.size() > size_m || size_m == 0)
        return not_found;

    for (; idx < size_m - str.size() + 1; idx++) {
        bool flagEqual = true;

        for (size_t j = 0; j < str.size(); j++)
            if (data_m[idx + j] != str[j]) {
                flagEqual = false;
                break;
            }

        if (flagEqual)
            return idx;
    }

    return not_found;
}

size_t my_str_t::find(const char* cstr, size_t idx) const {
    if (idx > size_m)
        throw std::out_of_range("string_t::find");

    for (; idx < size_m; idx++) {
        bool flagEqual = false;
        bool flagNotEqual = false;

        for (size_t j = 0; j < size_m - idx + 1; j++) {
            // We have reached and of cstr => comparison successful
            if (cstr[j] == '\0') {
                flagEqual = true;
                break;
            }

            if (idx + j >= size_m) {
                break;
            }

            if (cstr[j] != data_m[idx + j]) {
                flagNotEqual = true;
                break;
            }
        }

        if (flagEqual)
            return idx;

        // If none of the flags are set then our string exhausted
        // sooner than cstr => no need to continue
        if (!flagNotEqual)
            return not_found;
    }

    return not_found;
}

my_str_t my_str_t::substr(const size_t begin, const size_t size) const {
    if (begin > size_m)
        throw std::out_of_range("string_t::substr");

    if (data_m == nullptr)
        return my_str_t{static_cast<size_t>(0)};

    return my_str_t{
        min(size, size_m - begin),
        data_m + begin
    };
}

void my_str_t::write(const char* buffer, const size_t begin, const size_t size) const {
    memcpy(data_m + begin, buffer, size);
}

my_str_t& my_str_t::operator*=(const size_t times) {
    const size_t new_size = size_m * times;
    if (new_size > capacity_m || capacity_m == 0) {
        reserve(expand(capacity_m, new_size));
    }

    for (size_t i = size_m; i < new_size; i += size_m) {
        memcpy(data_m + i, data_m, size_m);
    }

    size_m = new_size;
    data_m[size_m] = '\0';
    return *this;
}

my_str_t operator+(const my_str_t& str, const char c) {
    my_str_t result{str.size() + 1};
    result[str.size()] = c;
    result.write(str.c_str(), 0, str.size());
    return result;
}

my_str_t operator+(const char c, const my_str_t& str) {
    my_str_t result{str.size() + 1};
    result[0] = c;
    result.write(str.c_str(), 1, str.size());
    return result;
}

my_str_t operator+(const my_str_t& str1, const char* cstr2) {
    const size_t size = get_cstr_size(cstr2);

    my_str_t result{str1.size() + size};
    result.write(str1.c_str(), 0, str1.size());
    result.write(cstr2, str1.size(), size);
    return result;
}

my_str_t operator+(const char* cstr1, const my_str_t& str2) {
    const size_t size = get_cstr_size(cstr1);

    my_str_t result{str2.size() + size};
    result.write(cstr1, 0, size);
    result.write(str2.c_str(), size, str2.size());
    return result;
}

my_str_t operator+(const my_str_t& str1, const my_str_t& str2) {
    my_str_t result{str1.size() + str2.size()};
    result.write(str1.c_str(), 0, str1.size());
    result.write(str2.c_str(), str1.size(), str2.size());
    return result;
}

my_str_t operator*(const my_str_t& str1, size_t times) {
    my_str_t result{str1.size() * times};
    for (size_t i = 0; i < result.size(); i += str1.size()) {
        result.write(str1.c_str(), i, str1.size());
    }
    return result;
}


my_str_t::~my_str_t() {
    delete[] data_m;
}


std::strong_ordering my_str_t::operator<=>(const my_str_t& str2) const {
    for (size_t i = 0; i < min(size_m, str2.size_m); i++) {
        if (data_m[i] > str2.data_m[i])
            return std::strong_ordering::greater;
        if (data_m[i] < str2.data_m[i])
            return std::strong_ordering::less;
    }

    if (size_m < str2.size_m)
        return std::strong_ordering::greater;
    if (size_m > str2.size_m)
        return std::strong_ordering::less;

    return std::strong_ordering::equal;
}

bool my_str_t::operator==(const my_str_t& str2) const {
    if (str2.size_m != size_m)
        return false;

    for (size_t i = 0; i < size_m; i++)
        if (data_m[i] != str2.data_m[i])
            return false;

    return true;
}

std::strong_ordering my_str_t::operator<=>(const char* cstr2) const {
    for (size_t i = 0; i < size_m; i++) {
        if (cstr2[i] == '\0')
            return std::strong_ordering::less;

        if (data_m[i] > cstr2[i])
            return std::strong_ordering::greater;
        if (data_m[i] < cstr2[i])
            return std::strong_ordering::less;
    }

    if (cstr2[size_m] == '\0')
        return std::strong_ordering::equal;

    return std::strong_ordering::greater;
}

bool my_str_t::operator==(const char* cstr2) const {
    for (size_t i = 0; i < size_m; i++)
        if ((cstr2[i] == '\0') || (data_m[i] != cstr2[i]))
            return false;

    return cstr2[size_m] == '\0';
}

std::istream& operator>>(std::istream& stream, my_str_t& str) {
    if (stream.eof())
        return stream;

    char c;

    do {
        stream.get(c);
    }
    while (std::isspace(c) && stream);

    if (stream.eof())
        return stream;

    str.clear();

    do {
        str.append(c);
        stream.get(c);
    }
    while ((!std::isspace(c)) && stream);

    if (!stream.eof())
        stream.unget();

    return stream;
}

std::istream& readline(std::istream& stream, my_str_t& str) {
    if (stream.eof())
        return stream;

    char c;
    str.clear();

    while (stream.get(c)) {
        if (c == '\n')
            break;

        str.append(c);
    }

    return stream;
}
