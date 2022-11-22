#include <iostream>

using namespace std;

/** ==========================
 * 学习目录：
 * 1.vector容器
 * 2.vector相关api
 * 3.string容器
 *  ==========================
 */

/**
 * STL基本概念：
 * STL标准模板库,从广义上分为：容器、算法、迭代器
 * 容器和算法之间通过迭代器进行无缝衔接
 * STL几乎所有的代码都采用了模板类和模板函数
 * STL大体分为六大组件：容器、算法、迭代器、仿函数、适配器、空间配置器
 * 1.容器：各种数据结构，如vector、list、deque、set、map等,用来存放数据
 * 2.算法：各种常用算法，如sort、find、copy、for_each等
 * 3.迭代器：扮演了容器与算法之间的胶合剂
 * 4.仿函数：类似函数，可以作为算法的某种策略
 * 5.适配器：一种用来修饰容器或者仿函数或迭代器接口的东西
 * 6.空间配置器：负责空间的配置与管理
 */

/** 1.vector容器 */
/* vector是STL中最常用的容器
 * 容器：vector
 * 算法：for_each
 * 迭代器：vector<int>::iterator
 */
#include <vector>
//算法头文件
#include <algorithm>

void printInt(int val) {
    cout<< "printInt:"<< val<< endl;
}

void test1() {
    //创建一个vector容器
    vector<int> v;
    //向容器添加数据
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);

    //通过迭代器访问容器中的数据
    vector<int>::iterator begin = v.begin(); //起始迭代器
    vector<int>::iterator end = v.end(); //结束迭代器
    //遍历方式1：
    //迭代器其实就相当于一个指针
    while(begin != end) {
        cout<< *begin<< endl;
        begin++;
    }

    //遍历方式2：
    for(vector<int>::iterator it = v.begin(); it !=  v.end(); it++) {
        cout<< *it<< endl;
    }

    //遍历方式3(需要包含算法头文件 <algorithm>):
    for_each(v.begin(), v.end(), printInt);
}

/** 2.vector相关api */
void test2() {

}

/** 3.string容器 */
#include <string>
/* string()
 * string(const char *s)
 * string(const string &str)
 * string(int n, char c)
 */
void test3() {
    //string构造函数
    string s1;
    char *p = "hello world";
    string s2(p);
    string s3("hello s3");
    string s4(5, 'A');

    cout<< s1<<endl;
    cout<< s2<<endl;
    cout<< s3<<endl;
    cout<< s4<<endl;

    //赋值函数assign
    string s5;
    s5.assign("hello C++", 5); //赋值函数，也可以截取字符串
    string s6;
    s6.assign(s5);
    cout<< s5<<endl;
    cout<< s6<<endl;

    //字符串拼接 += 和 append
    string s7;
    s7.append(s5).append(" ").append(s6); //可以拼接char* 和 string&
    s7.append(" hello world", 6); //拼接char*的前6个字符
    s7.append(" hello world", 6, 12); //拼接char*的第6个-第12个字符
    cout<< s7<<endl;
    string s8 = "";
    s8 += s7;
    cout<< s8<<endl;

    //字符串比较
    int a = s5.compare(s6); //大于返回1 小于返回-1 相等返回0
    int b = s5.compare("hello");
    cout<< a<<endl;
    cout<< b<<endl;

    //获取子字符串
    string s9 = s7.substr(0, 6); //含头不含尾
    cout<< s9<< endl;
}

int main()
{
    test1();
    test2();
    test3();
    return 0;
}
