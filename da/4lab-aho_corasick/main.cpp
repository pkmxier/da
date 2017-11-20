
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

    tree.BuildFailLinks();



    /*while (!std::cin.eof()) {
        ToLower(input);
        text.push_back(input);
        std::getline(std::cin, input);
    }*/

}
