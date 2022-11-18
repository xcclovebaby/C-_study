#ifndef MYSTRING_H
#define MYSTRING_H

#include <iostream>

using namespace std;

class MyString {

    friend ostream& operator<<(ostream &out, MyString &str);
    friend istream& operator>>(istream &in, MyString &str);

public:
    MyString(const char *);
    MyString(const MyString &);
    ~MyString();

    char& operator[](int index);

    MyString& operator=(const char *str);
    MyString& operator=(const MyString &str);

    MyString operator+(const char *str);
    MyString operator+(const MyString &str);

private:
    char *p;
    int size;
};
#endif // MYSTRING_H
