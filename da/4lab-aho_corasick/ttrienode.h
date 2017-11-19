#ifndef TTRIENODE_H
#define TTRIENODE_H
#include <map>
#include <string>

class TTrieNode {
private:
    std::map<char, TTrieNode *> children;
    bool isLeaf;
    TTrieNode *failLink;

    static TTrieNode *root;

    static int count;
    int number;
public:
    TTrieNode(bool leaf);

    void NodeInsert(std::string &str);
    bool NodeSearch(std::string &str);
    void NodeDelete(std::string &str);
    void BuildFailLink(char x);
    int Count();

    virtual ~TTrieNode();
};

#endif // TTRIENODE_H
