#ifndef TTRIE_H
#define TTRIE_H
#include <vector>
#include <iostream>
#include <sstream>
#include <map>
#include <string>
#include <queue>
#include <utility>

void ToLower(std::string &str);

class TTrie;

class TTrieNode {
private:
    friend class TTrie;

    std::map<std::string, TTrieNode *> children;
    bool isLeaf;
    TTrieNode *failLink;
    TTrieNode *exitLink;

    int number;
public:
    TTrieNode();
    virtual ~TTrieNode();
};

class TTrie {
private:
    friend class TTrieNode;

    TTrieNode *root;
    int patternsNumber;
    std::vector<int> patternLengths;
public:
    TTrie();

    void Insert(std::string &str);
    void Search();
    void BuildFail();
    int Count();

    void Print();

    virtual ~TTrie();
};

#endif // TTRIE_H
