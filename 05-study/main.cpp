#include <iostream>
#include <mystring.h>
#include <string.h>

using namespace std;

/** ==========================
 * 学习目录：
 * 1.封装string
 * 2.继承
 * 3.继承中子类与父类构造函数的调用
 * 4.多继承
 * 5.菱形继承
 * 6.虚拟继承
 *  ==========================
 */

/** 1.封装string */
//定义友元函数
ostream& operator<<(ostream &out, MyString &str) {
    out<< str.p;
    return out;
}
istream& operator>>(istream &in, MyString &str) {
    if(str.p != NULL) {
        delete[] str.p;
        str.p = NULL;
    }
    char tmp[1024];
    in >> tmp;
    str.p = new char[strlen(tmp) + 1];
    strcpy(str.p, tmp);
    str.size = strlen(tmp);
    return in;
}

//定义构造函数
MyString::MyString(const char *str) {
    this->p = new char[strlen(str) + 1];
    strcpy(this->p, str);
    this->size = strlen(str);
}
MyString::MyString(const MyString &str){
    this->p = new char[strlen(str.p) + 1];
    strcpy(this->p, str.p);
    this->size = str.size;
}
//定义析构函数
MyString::~MyString(){
    if(this->p != NULL) {
        delete[] this->p;
        this->p = NULL;
    }
}
//重载运算符
char& MyString::operator[](int index) {
    if(this->p == NULL) {
        return this->p[this->size];
    }
    if(index >= this->size) {
        return this->p[this->size];
    }
    return this->p[index];
}
MyString& MyString::operator=(const char *str) {
    if(this->p != NULL) {
        delete[] this->p;
        this->p = NULL;
    }
    this->p = new char[strlen(str) + 1];
    strcpy(this->p, str);
    this->size = strlen(str);
    return *this;
}
MyString& MyString::operator=(const MyString &str) {
    if(this->p != NULL) {
        delete[] this->p;
        this->p = NULL;
    }
    this->p = new char[strlen(str.p) + 1];
    strcpy(this->p, str.p);
    this->size = str.size;
    return *this;
}
MyString MyString::operator+(const char *str) {
    int newSize = this->size + strlen(str) + 1;
    char *tmp = new char[newSize];
    //动态申请空间
    memset(tmp, 0, newSize);
    strcat(tmp, this->p);
    strcat(tmp, str);

    //创建新对象
    MyString result(tmp);
    delete tmp;
    return result;
}
MyString MyString::operator+(const MyString &str) {
    int newSize = this->size + strlen(str.p) + 1;
    char *tmp = new char[newSize];
    //动态申请空间
    memset(tmp, 0, newSize);
    strcat(tmp, this->p);
    strcat(tmp, str.p);

    //创建新对象
    MyString result(tmp);
    delete tmp;
    return result;
}
void test1() {
    MyString str = "abc";
    str = str + "def";
    cout<< str<< endl;

    MyString s1 = "111";
    MyString s2 = "222";
    MyString s3 = s1+s2;
    cout<< s3 <<endl;
}

/** 2.继承 */
/* class 子类名: 继承方式 父类名 {}
 * 子类无法访问父类的私有化成员变量和成员函数
 * 三种继承方式：
 * public: 公有继承 父类中是什么控制权限，继承到子类中也是什么权限
 * private: 私有继承 被继承的所有权限均为private
 * protected: 保护继承 父类中的公共权限会变为 protected权限 private权限不变
 *
 * 注意：父类与子类中有重名的变量或者函数会被子类覆盖
 */
class P2 { //父类
public:
    int age;
    void show() {
        cout<< this->age<< endl;
    }
private: //不可被子类访问
    int a;
protected: //可以被子类访问
    int b;
};
class M2: public P2 {
public:
    int sex;
    void show() {
        cout<< this->age<< " "<< this->b<< endl;
    }
};
class A2: protected P2 {
/* 继承过来的成员变量
protected:
    int age;
private:
    int a;
protected:
    int b;
 */
public:
    void show() {
        cout<< this->age<< " "<< this->b<< endl;
    }
};
class B2: private P2 {
/* 继承过来的成员变量
private:
    int a;
    int b;
    int age;
 */
};
void test2() {
    M2 m2 = M2();
    m2.age = 10;
    m2.sex = 1;
    m2.show();

    A2 a2 = A2();
    a2.show();

    B2 b2 = B2();
//    b2.show();
}

/** 3.继承中子类与父类构造函数的调用 */
/* 创建子类对象时，必须先构建父类，需要调用父类的构造函数
 * 构造函数从最开始的父类开始依次创建
 * 析构函数从最底层的子类依次析构
 */
class P3 {
public:
    int id;
    P3(int id) {
        this->id = id;
        cout<< "P3 constructor"<< endl;
    }
    ~P3() {
        cout<< "free P3"<< endl;
    }
};
class A3: public P3 {
public:
    int age;
    A3(int id, int age):P3(id) {
        this->age = age;
        cout<< "A3 constructor"<< endl;
    }
    ~A3() {
        cout<< "free A3"<< endl;
    }
};
void test3() {
    A3 a3(1, 2);
    cout<< a3.age<< endl;
}

/** 4.多继承 */
/* C++不光可以继承一个类，也可以多个类继承
 * class 子类: 继承方式 父类A, 继承方式 父类B
 */
class P4 {
public:
    int age;
};
class A4: public P4 {};
class B4: public P4 {};
class C4: public A4, public B4 {
public:
    void show() {
        cout<< this->A4::age<< " "<< this->B4::age<< endl;
    }
};

/** 5.菱形继承 */
/* 由于C++可以多继承，那么会出现多个父类中重名的变量或函数被子类所继承
 * 在子类对象调用时，需要指定使用哪个父类中的成员：
 * 子类对象.父类::成员变量
 * 子类对象.父类::成员函数
 *
 * 可以使用virtual让编译器来帮忙优化,只继承一个同名变量
 */
class A5: virtual public P4 {};
class B5: virtual public P4 {};
class C5: public A5, public B5 {
public:
    void show() {
        cout<< this->age<< endl;
    }
};
void test5() {
    C4 c4 = C4();
//    c4.age = 10; //会报错，没有指定是用哪个age
    c4.B4::age = 10;
    c4.A4::age = 1;
    c4.show();

    C5 c5 = C5();
    c5.age = 100;
    c5.show();
}

/** 6.虚拟继承 */
/* 虚拟继承是多重继承中特有的概念。虚拟基类是为解决多重继承而出现的
 * 虚拟继承使用继承虚基类来代替 继承基类的做法
 * 当使用虚拟继承时，原本的父类成员 会被替换为 一个虚基表指针，这个指针指向一张虚基表，虚基表里存放 虚基类与虚基表指针的偏移量。
 */

int main()
{
    test1();
    test2();
    test3();
    test5();
    return 0;
}
