#include "tbtreenode.h"

TBTreeNode::TBTreeNode(int t1, bool leaf1) {
    t = t1;
    leaf = leaf1;
    data = new TItem[2 * t - 1];
    children = new TBTreeNode *[2 * t];
    for (int i = 0; i < 2 * t; ++i) {
        children[i] = NULL;
    }
    dataCount = 0;
}

TBTreeNode::~TBTreeNode() {
    delete [] data;
    delete [] children;
}

void TBTreeNode::DeleteNode() {
    if (this != NULL) {
        for (int i = 0; i < dataCount + 1; ++i) {
            if (children[i] != NULL ) {
                children[i]->DeleteNode();
            }
        }
        delete this;
    }
}

TItem * TBTreeNode::Search(const TString &string) {
    int i = 0;
    while (i < dataCount && data[i].word < string) {
        ++i;
    }
    if (i < dataCount && data[i].word == string) {
        return &data[i];
    }
    if (leaf) {
        return NULL;
    }
    return children[i]->Search(string);
}

void TBTreeNode::InsertNonFull(const TItem &item) {
    int i = dataCount - 1;

    if (leaf) {
        while (i >= 0 && item.word < data[i].word) {
            data[i + 1] = data[i];
            --i;
        }

        data[i + 1].word = item.word;
        data[i + 1].val = item.val;

        ++dataCount;
    } else {
        while (i >= 0 && item.word < data[i].word) {
            --i;
        }

        ++i;

        if (children[i]->dataCount == 2 * t - 1) {
            SplitChild(i);

            if (data[i].word < item.word) {
                ++i;
            }
        }

        children[i]->InsertNonFull(item);
    }
}

void TBTreeNode::SplitChild(int i) {
    TBTreeNode *leftChild = children[i];
    TBTreeNode *rightChild = new TBTreeNode(t, leftChild->leaf);
    rightChild->dataCount = t - 1;

    int j;
    for (j = 0; j < t - 1; ++j) {
        rightChild->data[j] = leftChild->data[j + t];
    }
    if (!leftChild->leaf) {
        for (j = 0; j < t; ++j) {
            rightChild->children[j] = leftChild->children[j + t];
        }
    }
    leftChild->dataCount = t - 1;

    for (j = dataCount; j >= i + 1; --j) {
        children[j + 1] = children[j];
    }
    children[i + 1] = rightChild;

    for (j = dataCount - 1; j >= i; --j) {
        data[j + 1] = data[j];
    }

    data[i] = leftChild->data[t - 1];
    ++dataCount;
}

void TBTreeNode::Delete(const TString &string) {
    int i = 0;
    while (i < dataCount && data[i].word < string) {
        ++i;
    }

    if (i < dataCount && data[i].word == string) {
        if (leaf) {
            DeleteFromLeaf(i);
        } else {
            DeleteFromInternalNode(i);
        }
    } else {
        if (leaf) {
            std::cout << "NoSuchWord" << '\n';
        } else {
            bool isLast = (i == dataCount);

            if (children[i]->dataCount < t) {
                RestoreBalance(i);
            }

            if (isLast && i > dataCount) {
                children[i - 1]->Delete(string);
            } else {
                children[i]->Delete(string);
            }
        }
    }
}

void TBTreeNode::DeleteFromLeaf(int i) {
    for (int j = i + 1; j < dataCount; ++j) {
        data[j - 1] = data[j];
    }

    --dataCount;
    
    std::cout << "OK" << '\n';
}

void TBTreeNode::DeleteFromInternalNode(int i) {
    TString temp;
    temp = data[i].word;
    
    if (children[i]->dataCount >= t) {
        TBTreeNode *predecessor;
        predecessor = FindPredecessor(i);

        data[i].word = predecessor->data[predecessor->dataCount - 1].word;
        data[i].val = predecessor->data[predecessor->dataCount - 1].val;
        
        children[i]->Delete(data[i].word);
    } else if (children[i + 1]->dataCount >= t) {
        TBTreeNode *successor;
        successor = FindSuccessor(i);

        data[i].word = successor->data[0].word;
        data[i].val = successor->data[0].val;
        children[i + 1]->Delete(data[i].word);
    } else {
        Merge(i);
        children[i]->Delete(temp);
    }
}

void TBTreeNode::Merge(int i) {
    TBTreeNode *child = children[i];
    TBTreeNode *sibling = children[i + 1];

    child->data[t - 1] = data[i];

    for (int j = 0; j < sibling->dataCount; ++j) {
        child->data[j + t] = sibling->data[j];
    }

    if (!child->leaf) {
        for (int j = 0; j <= sibling->dataCount; ++j) {
            child->children[j + t] = sibling->children[j];
        }
    }

    for (int j = i + 1; j < dataCount; ++j) {
        data[j - 1] = data[j];
    }

    for (int j = i + 2; j <= dataCount; ++j) {
        children[j - 1] = children[j];
    }

    child->dataCount += sibling->dataCount + 1;
    dataCount--;
    delete sibling;
}

void TBTreeNode::RestoreBalance(int i) {
    if (i != 0 && children[i - 1]->dataCount >= t) {
        GetFromLeftChild(i);
    } else if (i != dataCount && children[i + 1]->dataCount >= t) {
        GetFromRightChild(i);
    } else {
        if (i != dataCount) {
            Merge(i);
        } else {
            Merge(i - 1);
        }
    }
}

void TBTreeNode::GetFromLeftChild(int i) {
    TBTreeNode *leftChild = children[i - 1];
    TBTreeNode *rightChild = children[i];

    for (int j = rightChild->dataCount - 1; j >= 0; --j) {
        rightChild->data[j + 1] = rightChild->data[j];
    }

    if (!rightChild->leaf) {
        for (int j = rightChild->dataCount; j >= 0; --j) {
            rightChild->children[j + 1] = rightChild->children[j];
        }

        rightChild->children[0] = leftChild->children[leftChild->dataCount];
    }

    rightChild->data[0] = data[i - 1];

    data[i - 1] = leftChild->data[leftChild->dataCount - 1];

    ++rightChild->dataCount;
    --leftChild->dataCount;
}

void TBTreeNode::GetFromRightChild(int i) {
    TBTreeNode *leftChild = children[i];
    TBTreeNode *rightChild = children[i + 1];

    leftChild->data[leftChild->dataCount] = data[i];

    if (!leftChild->leaf) {
        leftChild->children[leftChild->dataCount + 1] = rightChild->children[0];
    }

    data[i] = rightChild->data[0];

    for (int j = 1; j < rightChild->dataCount; ++j) {
        rightChild->data[j - 1] = rightChild->data[j];
    }

    if (!rightChild->leaf) {
        for (int j = 1; j <= rightChild->dataCount; ++j) {
            rightChild->children[j - 1] = rightChild->children[j];
        }
    }

    ++leftChild->dataCount;
    --rightChild->dataCount;
}

TBTreeNode * TBTreeNode::FindPredecessor(int i) {
    TBTreeNode *current = children[i];
    while (!current->leaf) {
        current = current->children[current->dataCount];
    }
    return current;
}

TBTreeNode * TBTreeNode::FindSuccessor(int i) {
    TBTreeNode *current = children[i + 1];
    while (!current->leaf) {
        current = current->children[0];
    }
    return current;
}

bool TBTreeNode::Serialize(FILE *file) {
    if (fwrite(&leaf, sizeof(leaf), 1, file) != 1) {
        return false;
    }

    if (fwrite(&dataCount, sizeof(dataCount), 1, file) != 1) {
        return false;
    }

    for (int i = 0; i < dataCount; ++i) {
        int len = data[i].word.length();
        char *str = data[i].word.buffer;
        if (fwrite(&len, sizeof(len), 1, file) != 1) {
            return false;
        }

        if (fwrite(str, sizeof(char), len, file) != len) {
            return false;
        }

        if (fwrite(&data[i].val, sizeof(data[i].val), 1, file) != 1) {
            return false;
        }
    }

    if (!leaf) {
        for (int i = 0; i < dataCount + 1; ++i) {
            if (!children[i]->Serialize(file)) {
                return false;
            }
        }
    }
    return true;
}

bool TBTreeNode::Deserialize(FILE *file) {
    if (fread(&leaf, sizeof(leaf), 1, file) != 1) {
        return false;
    }

    if (fread(&dataCount, sizeof(dataCount), 1, file) != 1) {
        return false;
    }

    for (int i = 0; i < dataCount; ++i) {

        if (fread(&data[i].word.len, sizeof(data[i].word.len), 1, file) != 1) {
            return false;
        }

        delete [] data[i].word.buffer;
        data[i].word.size = data[i].word.len + 1;
        data[i].word.buffer = new char[data[i].word.size];

        if (fread(data[i].word.buffer, sizeof(char), data[i].word.len, file) != data[i].word.len) {
            return false;
        }

        data[i].word.buffer[data[i].word.len] = '\0';

        if (fread(&data[i].val, sizeof(data[i].val), 1, file) != 1) {
            return false;
        }
    }

    if (!leaf) {
        for (int i = 0; i < dataCount + 1; ++i) {
            children[i] = new TBTreeNode(t, false);

            if (!children[i]->Deserialize(file)) {
                return false;
            }
        }
    }
    return true;
}


