#include <iostream>
#include "tbtree.h"
#include <string>

int main() {
    TBTree tree(3);
    char c;
    TItem *result;

    std::cin.tie(NULL);
    std::ios_base::sync_with_stdio(false);
    
    TString path;
    while (!std::cin.eof()) {
        TItem item;
        
        std::cin.get(c);
        if (std::cin.eof()) {
            break;
        }
        switch (c) {
            case '\n':
                break;
            case '+':
                std::cin.get();
                std::cin >> item.word;
                std::cin >> item.val;
                
                result = tree.Search(item.word);

                if (result != NULL) {
                    std::cout << "Exist" << '\n';
                } else {
                    tree.Insert(item);
                    std::cout << "OK" << '\n';
                }
                break;
            case '-':
                std::cin.get();
                std::cin >> item.word;
                tree.Delete(item.word);
                break;
            case '!':
                std::cin.get();
                std::cin >> item.word >> path;
                if (item.word == "save") {
                    if (tree.Serialize(path.buffer)) {
                        std::cout << "OK" << '\n';
                    } else {
                        std::cout << "ERROR: Couldn't create file" << '\n';
                    }
                } else {
                    if (tree.Deserialize(path.buffer)) {
                        std::cout << "OK" << '\n';
                    } else {
                        std::cout << "ERROR: Couldn`t read from file" << '\n';
                    }
                }
                break;
            default:
                std::cin.unget();
                std::cin >> item.word;
                result = tree.Search(item.word);
                
                if (result == NULL) {
                    std::cout << "NoSuchWord" << '\n';
                } else {
                    std::cout << "OK: " << result->val << '\n';
                }
                break;
        }
    }
    
    return 0;
}

