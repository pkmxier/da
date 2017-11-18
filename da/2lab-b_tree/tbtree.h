#ifndef TBTREE_H
#define TBTREE_H
#include "tbtreenode.h"

class TBTree {
private:
    TBTreeNode *root;
    int t;
public:
    TBTree(int);
    ~TBTree();

    TItem * Search(const TString &);
    void Insert(TItem &item);
    void Delete(const TString &);
    bool Serialize(const char *);
    bool Deserialize(const char *);
};

#endif // TBTREE_H
