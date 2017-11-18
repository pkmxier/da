#include "tbtree.h"

TBTree::TBTree(int t1) {
    root = new TBTreeNode(t1, true);
    t = t1;
}

TBTree::~TBTree() {
    if (root != NULL) {
        root->DeleteNode();
    }
}

TItem * TBTree::Search(const TString &string) {
    if (root == NULL) {
        return NULL;
    } else {
        return root->Search(string);
    }
}

void TBTree::Insert(TItem &item) {
    if (root->dataCount == 2 * t - 1) {
        TBTreeNode *oldRoot = root;
        TBTreeNode *newRoot = new TBTreeNode(t, false);

        root = newRoot;
        newRoot->children[0] = oldRoot;

        newRoot->SplitChild(0);

        if (newRoot->data[0].word > item.word) {
            newRoot->children[0]->InsertNonFull(item);
        } else {
            newRoot->children[1]->InsertNonFull(item);
        }

    } else {
        root->InsertNonFull(item);
    }
}

void TBTree::Delete(const TString &string) {
    if (root != NULL) {
        root->Delete(string);
    } else {
        return;
    }

    if (!root->leaf && root->dataCount == 0) {
        TBTreeNode *temp = root;
        root = root->children[0];
        temp->children[0] = NULL;
        delete temp;
    }
}

bool TBTree::Serialize(const char *path) {
    FILE *file = fopen(path, "wb");

    if (file == NULL) {
        return false;
    }

    if (fwrite(&t, sizeof(t), 1, file) != 1) {
        return false;
    }

    bool isSuccess = root->Serialize(file);

    fclose(file);

    return isSuccess;
}

bool TBTree::Deserialize(const char *path) {
    FILE *file = fopen(path, "rb");

    if (file == NULL) {
        return false;
    }

    if (fread(&t, sizeof(t), 1, file) != 1) {
        return false;
    }

    TBTreeNode *newRoot = new TBTreeNode(t, true);
    bool isSuccess = newRoot->Deserialize(file);

    fclose(file);

    if (isSuccess) {
        if (root != NULL) {
            delete root;
        }
        root = newRoot;
    } else {
        delete newRoot;
    }

    return isSuccess;
}
