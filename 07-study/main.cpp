#include <iostream>
#include <fstream>
#include <string>
#include <string.h>

using namespace std;

/** ==========================
 * 学习目录：
 * 1.文件操作-写文件
 * 2.读文件
 * 3.写二进制文件
 * 4.读二进制文件
 *  ==========================
 */

/** 1.文件操作-写文件 */
/* C++对文件操作需要包含头文件 <fstream>
 * 文件类型分为两种：
 * 1.文本文件：文本以文本的ASCII码形式存储在计算机
 * 2.二进制文件：文件以文本的二进制形式存储在计算机中
 *
 * 操作文件的三大类：
 * 1.ofstream 写操作
 * 2.ifstream 读操作
 * 3.fstream 读写操作
 *
 * 文件的打开方式：
 * ios::in 读文件
 * ios::out 写文件
 * ios::ate 初始位置：文件尾
 * ios::app 追加方式写文件
 * ios::trunc 覆盖文件
 * ios::binary 二进制方式
 * 打开方式可以配合使用，利用 | 操作符
 * 例如：用二进制方式写文件 ios::binary|ios::out
 */
void test1() {
    ofstream out;
    //指定打开方式
    out.open("test.txt", ios::out|ios::trunc);
    //写内容
    out<< "姓名1：张三"<< endl;
    out<< "性别：男"<< endl;
    out<< "年龄：18"<< endl;
    //关闭文件流
    out.close();
}

/** 2.读文件 */
void test2() {
    ifstream in;
    //指定打开方式
    in.open("test.txt", ios::in);
    //判断是否打开成功
    if(!in.is_open()) {
        cout<< "open failed"<< endl;
        goto CLOSE;
    }
    //读内容
    //方式1(字符数组读取)：
//    char buf1[1024];
//    while(in >> buf1) {
//        cout<< buf1<< endl;
//    }

    //方式2(每行读取):
//    char buf2[1024];
//    while (in.getline(buf2, sizeof(buf2))) {
//        cout<< buf2<< endl;
//    }

    //方式3(string读取):
//    string buf;
//    while(getline(in, buf)) {
//        cout<< buf<< endl;
//    }

    //方式4(单个字符读取)
    char c;
    //EOF 代表着 end of file 是否到了文件末尾
    while((c = in.get()) != EOF) {
        cout<< c;
    }

    CLOSE:
    in.close();
    cout<< "in close"<< endl;
}

/** 3.写二进制文件 */
/* 二进制方式写文件主要利用对象调用write函数
 * ofstream& write(const char *buffer, int len);
 * buffer为指针指向的存储空间
 * len为字节数
 */
class Person {
public:
    int age;
    char name[128];
    void show() {
        cout<< this->age<< " "<< this->name<< endl;
    }
};
void test3() {
    //打开文件
    ofstream out("person.txt", ios::binary|ios::out);
    //写文件
    Person p = {18, "张三"};
    out.write((const char *)&p, sizeof(Person));
    //关闭文件流
    out.close();
}

/** 4.读二进制文件 */
/* 二进制方式写文件主要利用对象调用read函数
 * ifstream& read(char *buffer, int len);
 */
void test4() {
    //打开文件
    ifstream in("person.txt", ios::binary|ios::in);
    //判断是否打开成功
    if(!in.is_open()) {
        goto END;
    }

    Person p;
    in.read((char *) &p, sizeof(Person));
    p.show();

    END:
    in.close();
}

int main()
{
    test1();
    test2();
    test3();
    test4();
    return 0;
}
