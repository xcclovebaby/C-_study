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
 * 4.bool类型
 * 5.三目运算符
 * 6.const
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

/** 3.using声明 */
/* usingg声明可以使得指定的标识符可用
 * 拿上面定义的namespace A来演示
 * using A::a;
 * 这样后面使用a可以无需再指定是哪个命名空间下的a
 * 在全局使用using来指定的话，还需要注意不要重名
 */
using A::foo;
void test3() {
    using A::a;
    using namespace A;
    cout << a << endl;
    cout << c << endl;
}

/** 4.bool类型 */
/* C++新增bool类型
 * bool类型有两个内建的常量：true/false. true转换为整数1,false转换为整数0
 * bool类型只有这两个值：true(1)/false(0)
 * bool类型占1个字节
 * 给bool类型赋值时,非0会自动转换为true,0会自动转换为false
 */
void test4() {
    cout << "test4:" << endl;
    cout << "sizeof(false) = " << sizeof(false) <<endl;
    bool flag = true;
    cout << "flag = " << flag << endl;
    flag = 100;
    cout << "flag = " << flag << endl;
}

/** 5.三目运算符 */
/* C中三目运算符返回的是一个常量
 * C++中三目运算符返回的是一个变量
 * 既然是变量则可以赋值
 */
void test5() {
    int a = 10, b = 20;
    (a < b? a: b) = 100;
}

/** 6.const */
/* c++中const修饰局部变量时会把变量保存在符号表中
 * 对const修饰的变量取地址 编译器会临时产生一个变量来保存a的地址
 * 所以取出来的地址就是临时变量所在空间的地址
 * int temp = a;
 * int *p = &temp;
 *
 * const修饰的全局变量和c语言一样都放在常量区
 * 但在c++中想使用外部的全局常量都需要用extern来修饰
 */
extern const int i = 1000; //在同级目录的文件中也得是用相同的语句来连接该常量
void test6() {
    const int a = 10;
    int *p = (int *)&a; //C++中对数据类型比较敏感， &a的类型是int 而p的类型是 int *所以在赋值时需要强制类型转换
    *p = 100;
    cout<< a<< endl; //这里依然是10
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
    test3();
    test4();
    test6();
    return 0;
}
