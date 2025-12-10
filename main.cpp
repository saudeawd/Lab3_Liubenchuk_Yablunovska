// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include <cstring>
#include <fstream>
#include "mystring.hpp"


int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "you have to specify path to the test file" << std::endl;
        return -1;
    }
    std::ifstream file(argv[1]);

    my_str_t line{1, ' '};
    readline(file, line);
    std::cout << (line * 2) << std::endl;

    my_str_t name{""};
    file >> name;
    std::cout << my_str_t{"Hello, "} + name + '!' << std::endl;

    file.close();

    name *= 2;
    std::cout << "Double hello, " + name + '!' << std::endl;

    name.append(" :)");
    std::cout << "Glad to see ya, " + name << std::endl;

    my_str_t message{"i love python"};
    std::cout << message.find("love") << " expected " << 2 << std::endl;

    const my_str_t python{std::string{"python"}};
    message.erase(message.find(std::string{"python"}), python.size());

    message.append("c++");
    std::cout << message << std::endl;

    message.insert(2, "<3 ");
    std::cout << message << std::endl;

    message.resize(message.size() + 3, '!');
    std::cout << message << std::endl;

    message.clear();
    if (message.size() != 0)
        std::cout << "bad clear" << std::endl;

    my_str_t c1{static_cast<size_t>(0)};
    c1.append('c');
    c1.append('c');
    c1.append('c');

    const my_str_t c2{3, 'c'};

    std::cout << (c1 == c2) << std::endl;

    my_str_t hello{3, "hello"};
    std::cout << hello << std::endl;
    std::cout << strcmp(hello.c_str(), "hel") << std::endl;

    my_str_t hello_copy{hello};
    hello_copy.append(my_str_t{"lo"});
    std::cout << hello << std::endl;

    // Move semantics btw
    hello = my_str_t{"hello"};
    std::cout << hello << std::endl;

    hello.append('!');
    hello.swap(hello_copy);
    std::cout << hello_copy << std::endl;

    std::cout << hello[hello.size() - 1] << std::endl;
    std::cout << hello[0] << std::endl;
    std::cout << hello.at(hello.size() - 1) << std::endl;
    hello.at(0) = 'H';
    std::cout << hello << std::endl;
    hello[0] = 'h';
    std::cout << hello << std::endl;

    std::cout << hello.capacity() << std::endl;
    hello.shrink_to_fit();
    std::cout << hello.capacity() << std::endl;
    hello.reserve(20);
    std::cout << hello.capacity() << std::endl;

    my_str_t message2{"Goodbye, !"};
    message2.insert(9, name);
    std::cout << message2.find('G') << " " << message << std::endl;

    my_str_t message3{"test"};
    message3.insert(1, 't');
    std::cout << message3 << std::endl;

    my_str_t message4{"msg"};
    std::cout << message4.substr(1, 2) << std::endl;
    message4 += ' ';
    message4 += name;
    message4 += "!!!";
    std::cout << message4 << std::endl;

    std::cout << (message4 < "msg") << std::endl;
    std::cout << (message4 < my_str_t{"msg"}) << std::endl;

    message4.write("sos", 0, 3);
    std::cout << message4 << std::endl;
}
