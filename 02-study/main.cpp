#include <iostream>

using namespace std;

/** ==========================
 * 学习目录：
 * 1.引用的基本用法
 * 2.函数中的引用
 * 3.引用的原理
 * 4.常量的引用
 * 5.内联函数
 * 6.函数的默认参数
 * 7.占位参数
 * 8.函数的重载
 * 9.extern C
 *  ==========================
 */


/** 1.引用的基本用法 */
/* 引用的本质是取别名:
 * 数据类型 &别名 = 旧名
 * 引用必须初始化
 * 引用不能设置NULL值
 * 引用一旦初始化不能改变
 */
void test1() {
    //基本数据类型引用
    int a = 10;
    int &b = a;
    cout << "b = " << b << endl;
    b = 100;
    cout << "a = " << a << endl;
    int c = 1;
//    &b = c; //引用一旦初始化不能改变
//    int &d; //这样是错误的

    //数组的引用
    int i[5] = {1,2,3,4,5};
    //方式1
    int (&ar)[5] = i;
    //方式2
    typedef int ARR[5]; //定义一个数组类型ARR
    ARR &arr = i;
}

/** 2.函数中的引用 */
/* C语言中如果想写一个交换参数值的函数需要用到指针
 * C++中可以不使用指针,可以引用可以当成函数的形参传递
 */
//利用指针交换数据值
void swap(int *x, int *y) {
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}
//利用引用交换数据值
void swap_ref(int &x, int &y) {
    int temp;
    temp = x;
    x = y;
    y = temp;
}
//利用函数来给指针申请空间
void get_mem(int **q) {
    *q = (int *)malloc(sizeof(int *));
}
//通过引用的方式来给指针申请空间
void get_mem_ref(int *&q) {
    q = (int *)malloc(sizeof(int *));
}
//函数也可以返回引用类型
int & test2() {
    int x = 10, y = 20;
//    swap(&x, &y);
    swap_ref(x, y);
    cout << "x = " << x << " y = " << y << endl;

    int *p = NULL;
//    get_mem(&p);
    get_mem_ref(p);
    cout << "&p = " << &p << endl;
    free(p);
    p = NULL;
    return x;
}

/** 3.引用的原理 */
/* 引用底层是C++通过一个指针常量来实现的
 * Type &ref = val -> Type * const ref = &val
 * fun(int *&q) -> fun(int ** const q)
 */
void test3() {
    int a = 10;
    int &b = a; //编译器优化 int &b = a -> int * const b = &a;
    int * const c = &a; //int &c = a; 拆分 &c = a -> int * const c = &a
}

/** 4.常量的引用 */
void test4() {
    //被const修饰的常量引用可以直接赋值
    const int &a = 1; //int temp = 1; const int &a = &temp;
}

/** 5.内联函数
 * 内联函数为了继承C语言中的宏函数.
 * 在C中经常把一些短且频繁计算的写成宏,这样是为了执行效率,宏避免函数调用时的开销,都是由预处理来完成
 * C++预处理器不允许访问类成员
 * 为了保持预处理宏的效率又增加安全性,还能在类中访问自如, C++引入了内联函数
 * 内联函数继承宏的效率,没有函数调用时的开销,又可以像普通函数那样进行参数和返回值的检查,又可以作成员函数
 *
 * 内联编译会有一定的限制,有些时候编译器不会把函数内联编译,所以需要注意以下:
 * 1.不能存在任何形式的循环语句
 * 2.不能存在过多条件判断语句
 * 3.函数体不能过于庞大
 * 4.不能对函数进行取地址
 */
//定义一个简单的宏
#define ADD(a,b) a+b
//定义一个内联函数
inline int add(int a, int b) {
    return a + b;
}

void test5() {
    //使用宏
    int a = 1, b = 2;
    cout << "a+b=" << ADD(a, b) <<endl; //这样普通的加法没有任何问题
    cout << "a+b=" << ADD(a, b)*5 <<endl; //但是这种运算就错了, 按照a+b然后*5 需要在宏那里:a+b替换成(a+b)
    cout << "a+b=" << add(a, b)*5 <<endl; //使用内联函数就可以了
    ADD(a, b); //替换发生在预处理阶段
    add(a, b); //替换发生在编译阶段
}

/** 6.函数的默认参数 */
/* C++在声明函数时可以给一个或多个参数设置默认值
 * void fun(int a = 10, int b = 20);
 * void fun(int a, int b = 10, int c = 20); 形参b设置了默认值,那么后面位置的形参c也得设置默认值
 * void fun(int a = 10, int b = 20);
 * void fun(int a, int b) {} 如果函数声明和函数定义分开,函数声明设置了默认参数则函数定义不能再设置
 */
void fun(int a, int b = 10, int c = 20);
void fun(int a, int b, int c) {
    cout << a << " " << b << " " << c << endl;
}
void test6() {
    int a = 10;
    fun(a);
}

/** 7.占位参数 */
/* C++在声明函数时，可以设置占位参数
 * 占位参数只有参数类型声明，没有参数名
 */
void test7_fun(int a, int b, int) {
    //内部无法使用占位参数
}
//占位参数可以设置默认值
void test7_fun1(int a, int b, int = 10) {
}

/** 8.函数的重载 */
/* 函数的重载就是函数名相同，但是函数形参不一样
 * 函数的重载需要在同一作用域下
 * void fun(int a);
 * void fun(int a, int b);
 */

/** 9.extern C */
/* 如果C++中需要引用C的代码
 * 在头文件中需要声明一个跟c函数一样的函数
 * extern "C" int myadd(int a, int b);
 */
#include <head.h>
void test9() {
    int a = 10, b = 20;
    cout << myadd(a, b) << endl;
}

int main() {
    test1();
    test2();
    test5();
    test6();
    test9();
    return 0;
}
