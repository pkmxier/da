#include "ttrienode.h"
#include <iostream>

int TTrieNode::count = 0;

TTrieNode *TTrieNode::root = NULL;

TTrieNode::TTrieNode(bool leaf) : isLeaf(leaf) {
    failLink = this;
    number = 0;
}

void TTrieNode::NodeInsert(std::string &str) {
    TTrieNode *cur = this;

    for (int i = 0; i < str.size(); ++i) {
        if (!cur->children[str[i]]) {
            TTrieNode *tmp = new TTrieNode(false);
            cur->children[str[i]] = tmp;
            ++cur->number;
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

void TTrieNode::BuildFailLinks() {
    for (std::map<char, TTrieNode *>::iterator it = children.begin(); it != children.end(); ++it) {
        BuildOneFailLink(it->first);
    }

    for (std::map<char, TTrieNode *>::iterator it = children.begin(); it != children.end(); ++it) {
        if (it->second) {
            it->second->BuildFailLinks();
        }
    }
}

void TTrieNode::BuildOneFailLink(char x) {
    TTrieNode *cur = failLink;

    while (!cur->children[x] && cur != root) {
        cur = cur->failLink;
    }

    if (cur->children[x]) {
        children[x]->failLink = cur->children[x];
    } else {
        children[x]->failLink = root;
    }

    std::cout << x << " Fail link: " << std::endl;
    for (auto i : children[x]->failLink->children) {
        std::cout << i.first << " ";
    }
    std::cout << std::endl;
}

void TTrieNode::SetRoot(TTrieNode *r) {
    root = r;
}

int TTrieNode::Count() {
    return count;
}

TTrieNode::~TTrieNode() {
    for (std::map<char, TTrieNode *>::iterator it = children.begin(); it != children.end(); ++it) {
        delete it->second;
    }
}
