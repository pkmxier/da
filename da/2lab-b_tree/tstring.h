#ifndef STRING
#define STRING
#include <iostream>
#include <cstring>

class TString {
public:
    int len;
    int size;
    char *buffer;

    TString();
    TString(const TString &);
    TString(const char *);
    ~TString();

    int length();
    void Swap(TString &);

    char & operator [](int) const;
    TString & operator =(const TString &);

    friend bool operator >(const TString &, const TString &);
    friend bool operator <(const TString &, const TString &);

    friend TString & operator +(const TString &, const TString &);
    friend bool operator ==(const TString &, const TString &);
    friend std::ostream & operator <<(std::ostream &, const TString &);
    friend std::istream & operator >>(std::istream &, TString &);
};

#endif // STRING
