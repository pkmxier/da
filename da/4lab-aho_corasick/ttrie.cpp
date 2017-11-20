#include "ttrie.h"
TTrie::TTrie() {
    root = new TTrieNode(true);
    root->SetRoot(root);
}

bool TTrie::Insert(std::string &str) {
    bool isFound = root->NodeSearch(str);

    if (!isFound) {
        root->NodeInsert(str);
    }

    return !isFound;
}

bool TTrie::Search(std::string &str) {
    if (root != nullptr){
        return root->NodeSearch(str);
    }

    return false;
}

void TTrie::BuildFailLinks() {
    root->BuildFailLinks();
}

int TTrie::Count() {
    return root->Count();
}

TTrie::~TTrie() {
    delete root;
}
