#ifndef TTRIENODE_H
#define TTRIENODE_H
#include <map>
#include <string>

class TTrieNode {
//private:
public:
    std::map<char, TTrieNode *> children;
    bool isLeaf;
    TTrieNode *failLink;

    static TTrieNode *root;

    static int count;
    int number;
//public:
    TTrieNode(bool leaf);

    void NodeInsert(std::string &str);
    bool NodeSearch(std::string &str);
    void NodeDelete(std::string &str);
    void BuildFailLinks();
    void BuildOneFailLink(char x);
    void SetRoot(TTrieNode *r);
    int Count();

    virtual ~TTrieNode();
};

#endif // TTRIENODE_H
