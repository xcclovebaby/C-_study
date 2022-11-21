#include <iostream>
#include <string>
#include <typeinfo>

using namespace std;

/** ==========================
 * 学习目录：
 * 1.函数模板
 * 2.函数模板-选择排序
 * 3.普通函数和函数模板的区别
 * 4.函数模板具象化使用
 * 5.类模板
 * 6.类模板对象做函数参数
 * 7.类模板与继承
 * 8.类模板成员函数的类外实现
 * 9.类模板分文件编写
 * 10.类模板和友元
 * 11.类模板案例：通用数组类封装
 *  ==========================
 */

/** 1.函数模板 */
/* C++另一种变成思想称为泛型变成，主要利用的就是模板
 * C++提供两种模板机制：函数模板和类模板
 * 函数模板的作用：
 * 建立一个通用函数，其函数返回值类型和形参类型可以不具体制定，用一个虚拟类型来代表
 * 函数模板的定义：template<typename T>
 * template 声明创建模板
 * typename 表明其后面的符号是一种数据类型 可以用class代替
 * T 通用的数据类型，名词可以替换，通常为大写字母
 */
template<typename T>
void mySwap(T &a, T &b) {
    T tmp;
    tmp = a;
    a = b;
    b = tmp;
}
void test1() {
    int a = 10, b = 20;
    //自动类型推导
    mySwap(a, b);
    cout<< a<< " "<< b<< endl;
    double c = 1.5, d = 10.15;
    //显示指定类型
    mySwap<double>(c, d);
    cout<< c<< " "<< d<< endl;
}

/** 2.函数模板-选择排序 */
/* 选择排序、冒泡排序 时间复杂度都是 T(n)=O(n２)
 */
template<typename T>
void mySort(T arr[], int len) {
    for(int i = 0; i < len; i++) {
        int max = i; //认定最大值为下标
        for(int j = i + 1; j < len; j++) {
            if(arr[max] > arr[j]) {
                max = j; //更新最大值下标
            }
        }
        if(max != i) {
            mySwap(arr[i], arr[max]);
        }
    }
}
template<typename T>
void show(T arr[], int len) {
    for(int i = 0; i < len; i++) {
        cout<< arr[i]<< " ";
    }
    cout<< endl;
}
void test2() {
    int i_arr[] = {1,5,3,6,2,8,10,2,4,7,9};
    mySort<int>(i_arr, sizeof(i_arr) / sizeof(int));
    show<int>(i_arr, sizeof(i_arr) / sizeof(int));
}

/** 3.普通函数和函数模板的区别 */
/* 普通函数调用可以发生隐式类型转换
 * 函数模板用自动类型推导时，不可以发生隐式类型转换
 * 函数模板用指定类型时，可以发生隐式类型转换
 *
 * 普通函数和函数模板可以重载，优先调用普通函数
 * 可以通过空模板参数列表来强制调用函数模板
 * 函数模板也可以重载
 */
int myAdd3(int a, int b) {
    return a + b;
}
template<typename T>
T myAdd3(T a, T b) {
    return a + b;
}
void test3() {
    int a = 10;
    char c = 'c'; //c的ASCII码值为99 a=97
    int i = myAdd3(a, c);
    cout<< i<< endl;
//    myAdd3T(a, c); //这样会报错
    int j = myAdd3<int>(a, c);
    cout<< j<< endl;

    int b = 20;
    //通过空模板参数列表来强制调用函数模板
    int k = myAdd3<>(a, b);
    cout<< k<< endl;
}

/** 4.函数模板具象化使用 */
template<typename T>
bool b(T &a, T &b) {
    return a == b;
}
//具象化函数模板
template<> bool b(int &a, int &b) {
    return a == b;
}

/** 5.类模板 */
/* 类模板没有自动类型推导，使用时必须要指定类型
 * 类模板在声明时可以指定默认的类型
 *
 * 类模板中的成员函数在调用时才会去创建
 */
template<class NameType, class AgeType = int>
class Person {
public:
    Person(NameType name, AgeType age): name(name), age(age) {}
    void show() {
        cout<< "name:"<< this->name<< " age:"<< this->age<< endl;
    }
    NameType name;
    AgeType age;
};
void test5() {
    Person<string,int> p1("cc", 20);
}

/** 6.类模板对象做函数参数 */
//1.指定类模板
void printPerson1(Person<string, int> &p) {
    p.show();
}
//2.参数模板化
template<class NameType, class AgeType = int>
void printPerson2(Person<NameType, AgeType> &p) {
    p.show();

    //typeid需要引入头文件：#include <typeinfo>
    cout<< "NameType type is:"<< typeid(NameType).name()<< endl;
    cout<< "AgeType type is:"<< typeid(AgeType).name()<< endl;
}
//3.类模板化
template<class T>
void printPerson3(T &p) {
    p.show();
}
void test6() {
    Person<string,int> p1("p1", 120);
    Person<string,int> p2("p2", 90);
    Person<string,int> p3("p3", 30);
    printPerson1(p1);
    printPerson2(p2);
    printPerson3(p3);
}

/** 7.类模板与继承 */
/* 当子类继承的父类是一个类模板时，子类声明的时候需要指定父类模板的类型，也可以把子类也变成类模板
 */
template<class T>
class Base{
    T t;
};
//1.指定父类模板类型
class Son1: public Base<int> {

};
//2.子类也声明成类模板
template<class T>
class Son2: public Base<T> {

};
template<class P, class T>
class Son3: public Base<T> {
    P p;
};
void test7() {
    Base<int> b = Son2<int>();
    Son3<char, int> s = Son3<char, int>();
}

/** 8.类模板成员函数的类外实现 */
template<class T1, class T2>
class Test8{
public:
    Test8(T1 name, T2 age);
    void show();
    T1 name;
    T2 age;
};
//类模板的构造函数
template<class T1, class T2>
Test8<T1, T2>::Test8(T1 name, T2 age) {
    this->name = name;
    this->age = age;
}
//类模板的成员函数
template<class T1, class T2>
void Test8<T1, T2>::show() {
    cout<< "name:"<< this->name<< " age:"<< this->age<< endl;
}
void test8() {
    Test8<string, int> t("cc", 123);
    t.show();
}

/** 9.类模板分文件编写 */
/* 源文件.h和类模板.cpp文件一起使用就是类模板文件.hpp
 * 类模板的成员函数是调用时才会去创建,所以引用源文件时可能会出现引用异常,
 * 为了避免引用异常,所以把类模板的声明和实现放在一个文件里就是.hpp文件
 */
#include "person.hpp"
void test9() {
    BasePerson<string, int> p("test9", 9);
    p.show();
}

/** 10.类模板和友元 */
/* 类模板外部友元函数需要先声明类模板类型
 * 友元函数要定义在类模板的实现之前
 * 友元函数在类模板中定义时需要加<>
 */

//类模板外部友元函数需要先声明类模板类型
template<class T1, class T2>
class Test10;

template<class T1, class T2>
void showTest10(Test10<T1,T2> t) {
    cout<< "Test10 name = "<< t.name<< " age = "<< t.age<< endl;
}

template<class T1, class T2>
class Test10 {

    //类内友元函数声明后可以全局调用，省略了类外的实现
    friend void printTest10(Test10<T1,T2> t) {
        cout<< "Test10 name = "<< t.name<< " age = "<< t.age<< endl;
    }

    //类模板外部友元函数需要函数名加<>
    friend void showTest10<>(Test10<T1,T2> t);

public:
    Test10(T1 name, T2 age): name(name), age(age){}
private:
    T1 name;
    T2 age;
};

void test10() {
    Test10<string, int> t("test10", 10);
    printTest10(t);
    showTest10(t);
}

/** 11.类模板案例：通用数组类封装 */
#include "arraylist.hpp"

class Test11 {
public:
    string name;
    int age;
    Test11() {}
    Test11(string name, int age): name(name), age(age){}
};

void test11() {
    ArrayList<int> list(3);
    list.add(1);
    list.add(2);
    list.add(3);
    list.add(4);
    cout<< list.size()<< " "<< list.len()<< endl;
    cout<< list.get(2)<<endl;;

    Test11 t1("t1", 10);
    Test11 t2("t2", 10);
    Test11 t3("t3", 10);
    Test11 t4("t4", 10);
    Test11 t5("t5", 10);
    Test11 t6("t6", 10);
    Test11 t7("t7", 10);
    Test11 t8("t8", 10);
    Test11 t9("t9", 10);
    ArrayList<Test11> l(5);
    l.add(t1);
    l.add(t2);
    l.add(t3);
    l.add(t4);
    l.add(t5);
    l.add(t6);
    l.add(t7);
    l.add(t8);
    l.add(t9);

    ArrayList<Test11> a(5);
    a = l;
    for(int i = 0; i < a.len(); i++) {
        cout<< a.get(i).name<< " "<< a.get(i).age<< endl;
    }

    ArrayList<Test11> b(a);

}


int main()
{
    test1();
    test2();
    test3();
    test5();
    test6();
    test7();
    test8();
    test9();
    test10();
    test11();
    return 0;
}
