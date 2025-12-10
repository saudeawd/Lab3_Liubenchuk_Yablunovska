# Lab work 1: String implementation


## Prerequisites

GCC of version `13.3` or later

### Compilation

```bash
./comile.sh
```

Output of the compilation will be available at `build/`.

### Usage

#### Library

To use strings library simply use dynamic library in `build/libString.so`.
If you use library in C-code, then use header from `mystring_c.h`, if in C++-code, then from `mystring.hpp`.

#### Examples

There are two available examples: for C and C++.
To run C-example simply run executable `build/MainC`.
To run C++-example run executable `build/Main [example]`, where example is a two-line test txt file, for example from
`test.txt`.

### Important!

When allocating memory for the string there is alignment to 16-bytes for internal char buffer, so if you create a string
of length 1,
you will actually create an underlying buffer of size 16 (15 available as capacity and 1 byte reserved for
null-terminator).
To change buffer size you can call `shrink_to_fit`/`reserve`, there is no automatic alignment on those methods.
All other methods when reallocating memory will use alignment.

When appending/inserting or applying other operations which
require larger buffer, it increases its size in the following way:

```
if old_capacity > 1024:
  new_capacity := old_capacity + 1024
else:
  new_capacity := old_capacity * 2

if new_capacity < required_size:
  new_capacity := required_size

new_capacity := align(new_capacity)
```

`align` function simply finds the smallest number that is larger than the given one, but when dividing by 16 gives a
remainder of 1.

There is also a specific state of the string which is defined by `size = 0`, `capacity = 0` and `data = nullptr`.
Most methods handle this situation well, but some of them (for example `const char* c_str()`) have separate if
statement.
You can't create a string in such a state manually, but it shows up when using move semantics together with move
constructor.

### Results

I have implemented my own small string type which mimics behavior of `std::string`. I learned about memory management in
C++, especially
interesting I found rvalue and lvalue references, which I learned when creating move constructor and move assignment.

# Additional tasks

- Additional operators: `+`, `+=`, `*`, `*=`; move constructor and move assignment;
- C API bindings available in `mystring_c.cpp` and `mystring_c.h`.
