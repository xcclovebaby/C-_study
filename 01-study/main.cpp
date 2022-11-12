#include <iostream> //引入头文件iostream

using namespace std; //声明一个命名空间，cout对象存在std作用域下

#define PI 3.1415926 //宏常量
const int a = 20; //全局普通常量
const static int b = 30; //全局静态常量


/** ==========================
 * qt下载地址: https://download.qt.io/archive/qt/5.9/5.9.0
 * 学习目录：
 * Hello World
 *
 * 1.冒号的作用域
 * 2.namespace（命名空间/作用域）
 * 3.using声明
 *  ==========================
 */

/** 1.冒号的作用域 */
void test1() {
    int a = 10;
    cout << "a = " << a << endl; //如果直接使用a的话，就近原则会使用函数内的局部变量
    cout << "const a = " << ::a << endl; //如果想使用全局变量a 则需要使用::a
}

/** 2.命名空间namespace */
/* namespace（命名空间）可以更好的控制标识符的作用域
 * 命名空间内可以存放变量、函数、类、结构体...
 * 命名空间的定义必须定义在全局空间
 * 命名空间可以重名，重名相当于合并，但是两个名字相同的命名空间中的内部成员名称不能重复
 * 命名空间中可以给函数声明，在外部实现被定义的函数
 * 命名空间不指定名称则被定义为static的静态无名命名空间，只能被该文件内使用
 * 命名空间可以取别名：namespace newname = oldname
 */
namespace A {
    //成员变量
    int a = 30;

    //函数
    void a_fun() {
        cout << "hello namespace A a_fun()"<< endl;
    }

    //结构体
    struct stu {
        int age;
    } STU;

    //函数定义
    void foo();
}

//在外部给A作用域下的函数实现
void A::foo() {
    cout<< "A::foo" <<endl;
}
namespace A {
    int c = 40;
}

namespace NEW_A = A;

namespace B {
    int a = 10;
    int b = 20;
}
void test2() {
    cout << A::a << endl; //使用a作用域下的变量a
    A::a_fun(); //使用a作用域的函数
    A::STU.age = 23; //使用a作用域的结构体
    cout << A::c << endl;
    A::foo();
    NEW_A::foo();
}


int main()
{
    //cout标准输出流
    //endl 换行
    cout << "Hello World!" << endl;


    //输出一下常量的值
    cout << "PI = " << PI << "\na = " << a << "\nb = " << b << endl;

    test1();
    test2();
    return 0;
}
