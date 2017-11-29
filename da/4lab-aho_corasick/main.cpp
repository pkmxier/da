#include <iostream>
#include <vector>
#include "ttrie.h"

int main() {
    TTrie tree;
    std::string input;

    std::getline(std::cin, input);
    while (input != "") {
        ToLower(input);
        tree.Insert(input);
        std::getline(std::cin, input);
    }

    tree.BuildFail();


    tree.Search();
}
