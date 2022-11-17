#include <iostream>
#include <string>

using namespace std;

/** ==========================
 * 学习目录：
 * 1.静态成员变量
 * 2.静态成员函数
 * 3.const修饰静态成员变量
 * 4.单例模式(重点)
 * 5.成员变量和函数的存储
 * 6.this指针
 * 7.const修饰成员函数
 * 8.友元
 * 9.运算符重载
 * 10.使用运算符重载和友元重写cout<<
 * 11.重载自增(++)和自减(--)运算符
 * 12.智能指针
 * 13.重载等号(=)
 * 14.重载等于(==)和不等于(!=)
 *  ==========================
 */

/** 1.静态成员变量 */
/* 静态成员变量需要使用static声明
 * 不管创建了多少对象，静态成员变量都只有一个，属于所有对象共享的
 * 静态成员变量在编译时就分配了内存，存在静态全局区
 * 静态成员变量不能在声明时初始化
 * 声明方式：
 * class Person{
 *  static int a;
 * }
 * 初始化方法：
 * int person::b = 10;
 */
class P1{
public:
    int a;
    static int b;
};

//初始化
int P1::b = 10;

void test1() {
    P1 p1;
    p1.b = 100;
    cout<< p1.b<< endl;

    P1 p2;
    cout<< p2.b<< endl;
}

/** 2.静态成员函数 */
/* 静态成员函数和静态成员变量一样都是前面使用static修饰
 * 静态成员函数不能访问普通成员变量
 * 静态成员函数只能访问静态成员变量
 * 普通成员函数可访问静态成员变量、也可访问普通成员变量
 */
class P2{
public:
    int a;
    static int b;

    void show() {
        cout<< a<< " "<< b<< endl;
    }

    static void static_show() {
        cout<< b<< endl;
    }
};
int P2::b = 10;
void test2() {
    P2::static_show();
}

/** 3.const修饰静态成员变量 */
/* 如果一个类的成员变量想实现共享又不想被改变，就是用const static来修饰
 * 使用const修饰静态成员变量可以在声明时初始化
 */
class P3{
public:
    const static int a = 100;
    static void show() {
        cout<< a<< endl;
    }
};
void test3() {
    P3::show();
}

/** 4.单例模式(重点) */
/* 将无参构造私有化
 * 将拷贝构造私有化
 * 定义一个私有化的类指针静态成员变量
 * 提供一个公共静态函数返回私有化的类指针静态成员变量
 */
class P4{
public:
    int a;
    //公共静态函数返回私有化的类指针静态成员变量
    static P4* get() {
        return single;
    }
private:
    static P4 *single; //类指针静态成员变量
    P4() {} //私有化构造器
    P4(const P4 &p) {} //避免编译器默认提供拷贝构造函数
};

P4* P4::single = new P4; //初始化单例静态成员变量

void test4() {
    P4::get()->a = 199;
    P4 *p = P4::get();
    cout<< p->a<< endl;
}

/** 5.成员变量和函数的存储 */
/* 空类的大小是1字节
 * 静态成员变量不存储于类对象中
 * 普通成员函数不存储于类对象中
 * 静态成员函数不存储于类对象中
 */
class P5{
public:
    int a;
    static int b;
    void show() {}
    static void static_show() {}
};
void test5() {
    P5 p; //只有一个int a的大小为4字节
    cout<< sizeof(p)<< endl;
}

/** 6.this指针 */
/* this指针就是指执行调用该函数的对象
 * 对象调用成员函数会将对象的地址传给this指针
 * this->a
 */
class P6{
public:
    int age;
    string name;
    P6(int age, string name) {
        this->age = age;
        this->name = name;
    }
    void show() {
        cout<< this->age<< " "<< this->name<< endl;
    }
    P6 add(P6 &p) {
        return P6(this->age + p.age, this->name + p.name);
    }
};

void test6() {
    P6 p1 = P6(22, "cc");
    P6 p2 = P6(21, "dd");
    P6 p3 = p1.add(p2);
    p3.show();
}

/** 7.const修饰成员函数 */
/* 常量函数：不能通过this修改this指向对象的内容
 * 函数括号后面加const来定义常量函数
 */
class P7{
public:
    int age;
    string name;
    P7(int age, string name) {
        this->age = age;
        this->name = name;
    }
    //函数括号后面加const来定义常量函数
    //表示不能通过this来修改当前对象中的成员变量
    P7 add(P7 &p) const {
        //使用就会报错
//        this->age = 100;
    }
};

/** 8.友元 */
/* 友元函数是一种特权函数,C++允许这种特权函数访问类的私有成员
 * 可以把一个全局函数/类的成员函数/类 声明成友元
 * 使用friend关键字来定义友元
 */
class P8 {
    //定义友元函数
    friend void show(P8 &p);
    //定义友元类
    friend class Good;
public:
    P8(string name) {
        this->name = name;
    }
private:
    string name;
};
//声明一个访问私有变量的函数
void show(P8 &p) {
    cout<< p.name<< endl;
}
//友元类
class Good{
public:
    Good(string name); //构造器可以放在类外面来声明
    void visit(); //函数也可以放在类外面声明
private:
    P8 *p;
};
Good::Good(string name) {
    this->p = new P8(name);
}
//访问P8的私有化成员变量
void Good::visit() {
    cout<< this->p->name<< endl;
}
void test8() {
    P8 *p = new P8("cc");
    show(*p);
    Good *g = new Good("cc");
    g->visit();
}

/** 9.运算符重载 */
/* 运算符重载就是对已有的运算符重新定义,赋予其另一种功能
 * operator@来给运算符重新定义, @就代表运算符
 */
class P9{
public:
    int age;
    P9(int age) {
        this->age = age;
    }
    void show() {
        cout<< this->age<< endl;
    }
    //方式1:类成员函数的方式给+赋予一个新的功能
//    P9 operator+(P9 &p2) {
//        return P9(this->age + p2.age);
//    }
};
//方式2:全局函数的方式给+赋予一个新的功能
P9 operator+(P9 &p1, P9 &p2) {
   return P9(p1.age + p2.age);
}
void test9() {
    P9 p1(10), p2(20);
    P9 p3 = p1 + p2;
    p3.show();
}

/** 10.使用运算符重载和友元重写cout<< */
/* cout类型是ostream类型
 */
class P10{
    //定义友元函数
    friend ostream & operator<<(ostream &cout, P10 &p);
public:
    P10(int age) {
        this->age = age;
    }
private:
    int age;
};
//重载cout<<
ostream & operator<<(ostream &cout, P10 &p) {
    cout<< p.age;
    return cout;
}
void test10() {
    P10 p = P10(40);
    cout<< p<< endl;
}

/** 11.重载自增(++)和自减(--)运算符 */
class P11{
public:
    P11(int num) {
        this->num = num;
    }
    int num;
    //实现++p
    P11 & operator++() {
        this->num += 1;
        return *this;
    }
    //实现--p
    P11 & operator--() {
        this->num -= 1;
        return *this;
    }
    //实现p++
    P11 operator++(int) {
        P11 tmp = *this;
        this->num = this->num + 1;
        return tmp; //局部变量随着函数的结束而被释放,所以需要返回一个新的对象
    }
    //实现p--
    P11 operator--(int) {
        P11 tmp = *this;
        this->num -= 1;
        return tmp;
    }
};
ostream & operator<<(ostream &cout, P11 &p) {
    cout<< p.num;
    return cout;
}
void test11() {
    P11 p = P11(1);
    cout<< ++p<< endl;
    P11 p1 = p++;
    cout<< p1<< endl;
}

/** 12.智能指针 */
/* 定义一个帮助释放指针变量的类
 */
class P12 {
public:
    P12(P11 *p) {
        this->p = p;
    }
    ~P12() {
        delete this->p;
    }
    P11 * operator->() {
        return p;
    }

    P11 *p;
};
void test12() {
    P11 *p11 = new P11(10);
    P12 p12 = P12(p11);
    cout<< p12->num<< endl;
}

/** 13.重载等号(=) */
class P13{
public:
    int age;
    char *name;
    P13(int age, char *name) {
        this->age = age;
        this->name = (char *)malloc(strlen(name) + 1);
        strcpy(this->name, name);
    }
    P13 & operator=(P13 &p) {
        this->age = age;
        this->name = (char *)malloc(strlen(p.name) + 1);
        strcpy(this->name, p.name);
    }
    void show() {
        cout<< this->age<< " "<< this->name<< endl;
    }
};
void test13() {
    P13 p1(11, "123");
    P13 p2 = p1;
    p2.show();
}

/** 14.重载等于(==)和不等于(!=) */
class P14{
public:
    int age;
    string name;
    P14(int age, string name) {
        this->age = age;
        this->name = name;
    }
    bool operator==(P14 &p) {
        return this->age == p.age? true: false;
    }
};
void test14() {
    P14 p1(10, "lucy"), p2(12, "lilei");
    if(p1 == p2) {
        cout<< "p1 == p2"<< endl;
    }else {
        cout<< "p1 != p2"<< endl;
    }
}

int main()
{
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test8();
    test9();
    test10();
    test11();
    test12();
    test13();
    test14();
    return 0;
}
