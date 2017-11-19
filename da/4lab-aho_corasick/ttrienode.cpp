#include "ttrienode.h"

int TTrieNode::count = 0;

TTrieNode::TTrieNode(bool leaf) : isLeaf(leaf), failLink(nullptr) {
}

void TTrieNode::NodeInsert(std::string &str) {
    TTrieNode *cur = this;

    for (int i = 0; i < str.size(); ++i) {
        if (!cur->children[str[i]]) {
            TTrieNode *tmp = new TTrieNode(false);
            cur->children[str[i]] = tmp;
        }

        cur = cur->children[str[i]];
    }

    cur->isLeaf = true;
    ++count;
    number = count;
}

bool TTrieNode::NodeSearch(std::string &str) {
    TTrieNode *cur = this;

    for (int i = 0; i < str.size(); ++i) {
        if (!cur->children[str[i]]) {
            return false;
        }

        cur = cur->children[str[i]];
    }

    return (cur != nullptr && cur->isLeaf);
}

void TTrieNode::BuildFailLink(char x) {
    TTrieNode *cur = failLink;

    while (!cur->children[x] && cur != root) {
        cur = cur->failLink;
    }

    if (cur->children[x]) {
        children[x]->failLink = cur->failLink;
    } else {
        children[x]->failLink = root;
    }
}

int TTrieNode::Count() {
    return count;
}

TTrieNode::~TTrieNode() {
    for (std::map<char, TTrieNode *>::iterator it = children.begin(); it != children.end(); ++it) {
        delete it->second;
    }
}
