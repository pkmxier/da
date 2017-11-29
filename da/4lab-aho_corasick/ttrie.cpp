#include "ttrie.h"

void ToLower(std::string &str) {
    for (std::string::iterator it = str.begin(); it != str.end(); ++it) {
        *it = tolower(*it);
    }
}

TTrie::TTrie() {
    root = new TTrieNode;
    root->failLink = root;
    patternLengths.push_back(0);
    patternsNumber = 0;
}

void TTrie::Insert(std::string &str) {
    int patternLength = 0;
    std::stringstream line(str);
    std::string word;
    TTrieNode *cur = root;

    while (line >> word) {
        std::map<std::string, TTrieNode *>::iterator res = cur->children.find(word);
        if (res != cur->children.end()) {
            cur = res->second;
        } else {
            TTrieNode *next = new TTrieNode;
            cur->children.insert({word, next});
            cur->isLeaf = false;
            cur = next;
        }

        ++patternLength;
    }

    ++patternsNumber;
    cur->number = patternsNumber;
    patternLengths.push_back(patternLength);

    patternLengths[0] < patternLength ?
                patternLengths[0] = patternLength : true;
}

void TTrie::Search() {
    TTrieNode *cur = root;
    TTrieNode *next;

    std::string word;
    std::string str;
    std::getline(std::cin, str);
    std::stringstream line(str);

    std::pair<int, int> curPosition(1, 1);

    std::vector< std::pair<int, int> > positions(patternLengths[0]);
    int i = 0;

    bool isEnd = false;

    positions[i] = curPosition;

    line >> word;
    ToLower(word);

    while (true) {
        while (cur->children.find(word) != cur->children.end()) {
            next = cur->children.find(word)->second;

            TTrieNode *exit = next->exitLink;
            if (next->number > 0) {
                int j = i - patternLengths[next->number] + 1;
                if (j < 0) {
                    j += patternLengths[0];
                }
                std::cout << positions[j].second << ", " << positions[j].first << ", " << next->number << std::endl;
            }

            while (exit) {
                int j = i - patternLengths[exit->number] + 1;
                if (j < 0) {
                    j += patternLengths[0];
                }

                std::cout << positions[j].second << ", " << positions[j].first << ", " << exit->number << std::endl;
                exit = exit->exitLink;
            }

            cur = next;
            if (line >> word) {
                ++curPosition.first;
                ++i;
                if (i == patternLengths[0]) {
                    i = 0;
                }
            } else {
                curPosition.first = 1;
                ++curPosition.second;
                ++i;
                if (i == patternLengths[0]) {
                    i = 0;
                }

                if (!std::getline(std::cin, str)) {
                    isEnd = true;
                }

                if (str.size() == 0) {
                    while (str.size() == 0 && !isEnd) {
                        ++curPosition.second;

                        if (!std::getline(std::cin, str)) {
                            isEnd = true;
                        }
                    }
                }

                line.clear();
                line.str(str);
                line >> word;
            }

            ToLower(word);

            positions[i] = curPosition;
        }

        if (cur == root) {
            if (line >> word) {
                ++curPosition.first;
                ++i;
                if (i == patternLengths[0]) {
                    i = 0;
                }
            } else {
                curPosition.first = 1;
                ++curPosition.second;
                ++i;
                if (i == patternLengths[0]) {
                    i  = 0;
                }

                if (!std::getline(std::cin, str)) {
                    isEnd = true;
                }

                if (str.size() == 0) {
                    while (str.size() == 0 && !isEnd) {
                        ++curPosition.second;
                        if (!std::getline(std::cin, str)) {
                            isEnd = true;
                        }
                    }
                }

                line.clear();
                line.str(str);
                line >> word;
            }

            ToLower(word);

            positions[i] = curPosition;
        } else {
            cur = cur->failLink;
        }

        if (isEnd) {
            break;
        }
    }
}

void TTrie::BuildFail() {
    for (std::map<std::string, TTrieNode *>::iterator it = root->children.begin(); it != root->children.end(); ++it) {
        it->second->failLink = root;
    }

    root->failLink = root;

    std::queue<TTrieNode *> q;
    q.push(root);
    while (!q.empty()) {
        TTrieNode *cur = q.front();
        q.pop();

        if (cur != root && !cur->isLeaf) {
            for (std::map<std::string, TTrieNode *>::iterator it = cur->children.begin(); it != cur->children.end(); ++it) {
                TTrieNode *curFail = cur->failLink;
                TTrieNode *next = it->second;

                std::string word = it->first;
                while (curFail->children.find(word) == curFail->children.end() && curFail != root) {
                    curFail = curFail->failLink;
                }

                if (curFail->children.find(word) != curFail->children.end()) {
                    next->failLink = curFail->children.find(word)->second;
                } else {
                    next->failLink = root;
                }

                if (next->failLink->number > 0) {
                    next->exitLink = next->failLink;
                } else {
                    next->exitLink = next->failLink->exitLink;
                }
            }
        }

        if (!cur->isLeaf) {
            for (std::map<std::string, TTrieNode *>::iterator it = cur->children.begin(); it != cur->children.end(); ++it) {
                q.push(it->second);
            }
        }
    }
}

TTrie::~TTrie() {
    delete root;
}


TTrieNode::TTrieNode() {
    isLeaf = true;
    exitLink = NULL;
    number = 0;
}

TTrieNode::~TTrieNode() {
    for (std::map<std::string, TTrieNode *>::iterator it = children.begin(); it != children.end(); ++it) {
        delete it->second;
    }
}
