#include <iostream>
#include <vector>
#include "ttrie.h"

void ToLower(std::string &str) {
    for (std::string::iterator it = str.begin(); it != str.end(); ++it) {
        *it = tolower(*it);
    }
}

int main() {
    TTrie tree;
    std::vector<std::string> text;
    std::string input;

    std::getline(std::cin, input);
    while (input != "") {
        ToLower(input);
        tree.Insert(input);
        std::getline(std::cin, input);
    }

    while (!std::cin.eof()) {
        ToLower(input);
        text.push_back(input);
        std::getline(std::cin, input);
    }

    for (auto i : text) {
        std::cout << i << std::endl;
    }
}
