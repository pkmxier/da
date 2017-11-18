#ifndef TBTREENODE_H
#define TBTREENODE_H
#include "tstring.h"

struct TItem {
    TString word;
    uint64_t val;

    TItem(){}
    TItem & operator =(TItem &rhs) {
        word.Swap(rhs.word);
        val = rhs.val;
        return *this;
    }
};


class TBTreeNode {
public:
    bool leaf;
    int t;
    int dataCount;
    TItem *data;
    TBTreeNode **children;


    TBTreeNode(int, bool);
    ~TBTreeNode();

    void DeleteNode();

    TItem * Search(const TString &);
    void InsertNonFull(const TItem &item);
    void SplitChild(int);

    void Delete(const TString &);
    void DeleteFromLeaf(int);
    void DeleteFromInternalNode(int);
    void Merge(int);
    void RestoreBalance(int);
    void GetFromLeftChild(int);
    void GetFromRightChild(int);
    TBTreeNode * FindPredecessor(int);
    TBTreeNode * FindSuccessor(int);

    bool Serialize(FILE *file);
    bool Deserialize(FILE *file);
};

#endif // TBTREENODE_H
