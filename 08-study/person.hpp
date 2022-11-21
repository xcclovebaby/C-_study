#pragma once //防止头文件重复
#include <iostream>

using namespace std;

#include <string>

template<class T1, class T2>
class BasePerson {
public:
    BasePerson(T1 name, T2 age);
    void show();
    T1 name;
    T2 age;
};

template<class T1, class T2>
BasePerson<T1, T2>:: BasePerson(T1 name, T2 age): name(name), age(age) {
    cout<< "init BasePerson"<< endl;
}

template<class T1, class T2>
void BasePerson<T1, T2>:: show() {
    cout<< "name = "<< this->name<< " age = "<< this->age<< endl;
}
