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
/*
 */

int main()
{
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    return 0;
}
