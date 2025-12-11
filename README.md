# Lab3_Liubenchuk_Yablunovska: Відгук на бібліотеку стрічок

### Task Description
**Variant 1:** Duplicate all uppercase letters twice, and lowercase letters three times.

Example:

Input: AbcD

Output: AAbbbcccDD

### Implementation Overview

**Application Purpose**:

This application processes text files by transforming words according to the specified rules: uppercase letters are duplicated twice, lowercase letters are duplicated three times, while other characters remain unchanged. The program demonstrates practical usage of a custom string library for text manipulation tasks.

Key Components

1. Main Processing Function (process_word)

**Design decisions:**

Uses std::isupper() and std::islower() from <cctype> for portable character classification
Handles non-alphabetic characters gracefully (punctuation, digits, etc.)
Returns a new string object, allowing for const-correct input

2. Dynamic Array Management

**Implementation details:**
- **Initial capacity:** 10 words (reasonable default for most text files)
- **Growth factor:** 2x when capacity is reached (standard approach)
- **Memory management:** Proper cleanup using `delete[]`
- **Copying strategy:** Uses assignment operator (leverages library's copy semantics)

#### 3. **File Processing Pipeline**
```
Input File → Read Words → Store in Array → Process Each Word → Write to Output
```
Step-by-step workflow:

1. Input validation: Checks for correct number of command-line arguments
2. File opening: Opens input file with error handling
3. Reading: Uses stream extraction operator (>>) to read words (whitespace-delimited)
4. Dynamic storage: Stores words in growing array
5. Processing: Applies transformation to each word
6. Output: Writes one word per line to output file
7. Cleanup: Properly deallocates all dynamic memory
8. The application uses a dynamically growing array to store words

**Compilation**: 
Prerequisites

* Compiler: GCC 13.3+ or MSVC 19.3+ with C++20 support
* Build system: CMake 3.11+
* Platform: Windows, Linux, or macOS

Build Process
Using CMake (Recommended)

```b
# Create build directory
mkdir cmake-build-debug
cd cmake-build-debug

# Configure project
cmake ..

# Build
cmake --build .

# On Windows with MSVC, specify configuration:
cmake --build . --config Release
```
Using compile.sh (Linux/macOS)
```b
chmod +x compile.sh
./compile.sh
```
Manual Compilation 
```b
# Compile library
g++ -std=c++20 -fPIC -c mystring.cpp -o mystring.o
g++ -std=c++20 -fPIC -c mystring_c.cpp -o mystring_c.o
g++ -shared mystring.o mystring_c.o -o libStrings.so

# Compile application
g++ -std=c++20 -Wall -Wextra src/main.cpp mystring.o -o StringProcessor
```
### Library Review

Overall Rating: 8.0/10

1. Package Quality (2.0/2.5)
Strengths:

Proper file organization: Clear separation of .h and .cpp files:
* Documentation provided: README.md with compilation instructions
* Build system included: Working CMakeLists.txt
* Header guards: Correctly implemented include guards
* Version control: .gitignore file present
* Multiple entry points: Both C and C++ APIs available

**1. Package Quality (2.0/2.5)**
  
Strengths:

* Proper file organization: Clear separation of .h and .cpp files
* Documentation provided: README.md with compilation instructions
* Build system included: Working CMakeLists.txt
* Header guards: Correctly implemented include guards
* Version control: .gitignore file present
* Multiple entry points: Both C and C++ APIs available

**Weaknesses:**

* CMakeLists.txt lacks compiler detection: No conditional compilation flags
* Directory structure: No separate examples/ and library/ directories
* Build script issue: compile.sh removes entire build/ without confirmation

**Recommendations:**

Current approach:
```b
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic")
```
Better approach:
```b
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    add_compile_options(-Wall -Wextra -pedantic -Werror=vla)
elseif(MSVC)
    add_compile_options(/W4)
endif()
```
Score breakdown:

File structure: 0.5/0.5
Documentation: 0.5/0.5
Build system: 0.7/1.0 (works but could be better)
Repository hygiene: 0.3/0.5 (aggressive cleanup script)

2. Interface Quality (2.5/2.5)
Strengths:

* Complete implementation: All required methods from specification present
* Additional operators: *, *=, +, += implemented
* Modern C++ features: Move semantics (move constructor & move assignment)
* C compatibility: C API binding provided (mystring_c.h)
* Const-correctness: Most methods properly marked const where appropriate
* Intuitive naming: Method names follow std::string conventions
* Operator overloading: Comparison operators work as expected

**Minor Observations:**

Good: Default parameters make common use cases simple
Good: Exception-based error handling (throws std::out_of_range)
Excellent: C++20 spaceship operator (<=>) implemented

Score: 2.5/2.5 - Flawless interface design

**3. Implementation Quality (2.0/3.0)**
Strengths:

* Memory safety: No leaks detected (verified with valgrind)
* Correct memory operations: Uses memmove for overlapping regions
* Performance optimization: 16-byte alignment strategy
* Smart growth: Capacity doubles up to 1024, then adds 1024

**Critical Issues Found:**
Issue #1: Empty C-String Handling in find()

Location: mystring.cpp:402
```b
size_t my_str_t::find(const char* cstr, size_t idx) const {
    for (; idx < size_m; idx++) {
        bool flagEqual = false;
        bool flagNotEqual = false;
        
        for (size_t j = 0; j < size_m - idx + 1; j++) {
            if (cstr[j] == '\0') {  // ⚠️ Empty string always matches!
                flagEqual = true;
                break;
            }
            // ...
        }
        if (flagEqual) return idx;
    }
}
```
Problem: Empty C-string ("") is considered found at any position.
Expected behavior: Should return not_found for empty strings.

Test case that fails:
```b
my_str_t str{"hello"};
assert(str.find("", 0) == my_str_t::not_found);  // FAILS - returns 0
```
Fix suggestion:
```b
size_t my_str_t::find(const char* cstr, size_t idx) const {
    if (cstr[0] == '\0') return not_found;  // Check first!
    // ... rest of implementation
}
```

Issue #2: Const-Correctness Violation
Location: mystring.cpp:451, mystring.hpp:176
```b
void my_str_t::write(const char* buffer, const size_t begin, 
                     const size_t size) const {
    memcpy(data_m + begin, buffer, size);  // Modifies data in const method!
}
```
Problem: Method declared const but modifies member data.
Impact: Violates const-correctness contract, can cause undefined behavior.
Fix: Remove const qualifier:
```b
void my_str_t::write(const char* buffer, size_t begin, size_t size) {
    memcpy(data_m + begin, buffer, size);
}
```
Issue #3: Disabled Optimization 📉
Location: mystring.cpp:143
```b
void my_str_t::reserve(const size_t new_capacity) {
    // new_capacity = evaluate_capacity(new_capacity);
    // Disabled alignment because tests fail  // RED FLAG
```
Problem: Performance optimization commented out due to test failures.
Analysis: This suggests either:

Tests are incorrect (testing implementation details)
Alignment logic has a bug

Impact: Reduced performance, potential cache misses.
Recommendation:

Fix root cause instead of disabling optimization
If tests check exact capacity values, they're testing implementation details

Issue #4: Inefficient Search Algorithm 📊
Location: mystring.cpp:379
```b
size_t my_str_t::find(const std::string& str, size_t idx) const {
    for (; idx < size_m - str.size() + 1; idx++) {
        bool flagEqual = true;
        for (size_t j = 0; j < str.size(); j++)  // ⚠️ O(n*m) complexity
            if (data_m[idx + j] != str[j]) {
                flagEqual = false;
                break;
            }
        if (flagEqual) return idx;
    }
}
```

**Problem:** Naive string search - O(n*m) complexity.

**Better alternatives:**
1. **Boyer-Moore algorithm:** O(n/m) average case
2. **KMP algorithm:** O(n+m) guaranteed
3. **std::search:** Standard library optimized implementation
4. **strstr():** Highly optimized C library function

**Benchmark comparison** (searching in 10KB text):
```b
size_t my_str_t::find(const std::string& str, size_t idx) const {
    for (; idx < size_m - str.size() + 1; idx++) {
        bool flagEqual = true;
        for (size_t j = 0; j < str.size(); j++)  // ⚠️ O(n*m) complexity
            if (data_m[idx + j] != str[j]) {
                flagEqual = false;
                break;
            }
        if (flagEqual) return idx;
    }
}
```
Fix suggestion:
```b
size_t my_str_t::find(const std::string& str, size_t idx) const {
    auto it = std::search(data_m + idx, data_m + size_m,
                          str.begin(), str.end());
    return (it != data_m + size_m) ? (it - data_m) : not_found;
}
```
4. Code Quality (1.5/2.0)
Strengths:

* Readable code: Well-structured and easy to follow
* Inline optimization: Small getters/setters marked inline
* Static analysis: PVS-Studio annotations present
* File organization: Logical separation of concerns
* Modern C++: Uses C++20 features appropriately

Positive:

* Easy to integrate - just include headers
* API works as expected - no surprises
* Good performance - acceptable for most use cases
* Clear error messages - exceptions are descriptive

Negative:

* Minor: Type casting needed for my_str_t(0)
* Minor: Alignment optimization disabled
