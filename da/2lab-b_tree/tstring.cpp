#include "tstring.h"

TString::TString() {
    len = 0;
    size = 1;
    buffer = new char[size];
    buffer[len] = '\0';
}

TString::TString(const TString &copy) {
    len = copy.len;
    size = copy.size;
    buffer = new char[size];
    strcpy(buffer, copy.buffer);
}

TString::TString(const char *string) {
    len = strlen(string);

    size = len + 1;
    buffer = new char[size];

    strcpy(buffer, string);
}

TString::~TString() {
    delete [] buffer;
}

int TString::length() {
    return len;
}

void TString::Swap(TString &rhs) {
    char *temp = buffer;
    buffer = rhs.buffer;
    rhs.buffer = temp;
    int tmp = size;
    size = rhs.size;
    rhs.size = tmp;
    tmp = len;
    len = rhs.len;
    rhs.len = tmp;
}

char & TString::operator [](int i) const {
    return buffer[i];
}
TString & TString::operator =(const TString &rhs) {
    if (this != &rhs) {
        delete [] buffer;
        buffer = new char[rhs.size];

        strcpy(buffer, rhs.buffer);

        len = rhs.len;
        size = rhs.size;
    }
    return *this;
}

bool operator >(const TString &lhs, const TString &rhs) {
    return strcmp(lhs.buffer, rhs.buffer) > 0;
}

bool operator <(const TString &lhs, const TString &rhs) {
    return strcmp(lhs.buffer, rhs.buffer) < 0;
}

bool operator ==(const TString &lhs, const TString &rhs) {
    return strcmp(lhs.buffer, rhs.buffer) == 0;
}

std::ostream & operator <<(std::ostream &os, const TString &string) {
    for (int i = 0; i < string.len; ++i) {
        os << string.buffer[i];
    }
    return os;
}

std::istream & operator >>(std::istream &is, TString &string) {
    if (string.buffer != NULL) {
        delete [] string.buffer;
    }
    string.len = 0;
    string.size = 16;
    string.buffer = new char[string.size];
    string.buffer[string.len] = '\0';
    char inputChar;
    while (is.get(inputChar)) {
        if (inputChar == '\n' || inputChar == ' ') {
            break;
        } else {
            if (string.len + 1 == string.size) {
                string.size *= 2;
                char *tempBuffer = new char[string.size];
                for (int i = 0; i < string.len; ++i) {
                    tempBuffer[i] = string.buffer[i];
                }
                delete [] string.buffer;
                string.buffer = tempBuffer;
            }
        }
        if (inputChar >= 'A' && inputChar <= 'Z') {
            inputChar += 'a' - 'A';
        }
        string.buffer[string.len++] = inputChar;
    }
    string.buffer[string.len] = '\0';
    return is;

}
