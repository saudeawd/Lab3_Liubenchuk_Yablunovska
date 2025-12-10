#include "mystring.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>

my_str_t process_word_variant1(const my_str_t& word) {
    my_str_t result{static_cast<size_t>(0)};

    for (size_t i = 0; i < word.size(); i++) {
        char c = word[i];

        if (std::isupper(c)) {
            result.append(c);
            result.append(c);
        } else if (std::islower(c)) {
            result.append(c);
            result.append(c);
            result.append(c);
        } else {
            result.append(c);
        }
    }

    return result;
}

std::vector<my_str_t> read_words_from_file(const char* filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open input file");
    }

    std::vector<my_str_t> words;
    my_str_t word{static_cast<size_t>(0)};

    while (file >> word) {
        words.push_back(word);
    }

    file.close();
    return words;
}

void write_words_to_file(const char* filename, const std::vector<my_str_t>& words) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open output file");
    }

    for (const auto& word : words) {
        file << word << '\n';
    }

    file.close();
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>\n";
        std::cerr << "Example: " << argv[0] << " input.txt output.txt\n";
        return 1;
    }

    const char* input_filename = argv[1];
    const char* output_filename = argv[2];

    try {
        std::cout << "Reading words from " << input_filename << "...\n";
        std::vector<my_str_t> words = read_words_from_file(input_filename);
        std::cout << "Read " << words.size() << " words.\n";

        std::cout << "Processing words (Variant 1: uppercase x2, lowercase x3)...\n";
        std::vector<my_str_t> processed_words;
        processed_words.reserve(words.size());

        for (const auto& word : words) {
            my_str_t processed = process_word_variant1(word);
            processed_words.push_back(processed);

            if (processed_words.size() <= 5) {
                std::cout << "  " << word << " -> " << processed << "\n";
            }
        }

        std::cout << "Writing results to " << output_filename << "...\n";
        write_words_to_file(output_filename, processed_words);

        std::cout << "Done! Processed " << processed_words.size() << " words.\n";

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}
