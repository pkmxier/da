#ifndef TTRIE_H
#define TTRIE_H
#include "ttrienode.h"

class TTrie {
private:
    TTrieNode *root;
public:
    TTrie();

    bool Insert(std::string &str);
    bool Search(std::string &str);
    bool Delete(std::string &str);
    void BuildFailLinks();
    int Count();

    virtual ~TTrie();
};

#endif // TTRIE_H
