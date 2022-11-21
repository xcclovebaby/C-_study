#ifndef ARRAYLIST_HPP
#define ARRAYLIST_HPP

#pragma once //防止头文件重复
#include <iostream>

using namespace std;

/**
 * 实现的功能：
 * 1.可以对任意数据类型进行存储
 * 2.数组中的元素存放在堆区
 * 3.构造函数中可以传入数组的容量
 * 4.提供拷贝函数并重载= 防止浅拷贝
 * 5.提供尾插法和尾删除法
 * 6.可以通过下标方式访问数组元素
 * 7.可以获取数组容量和数组元素个数
 */
template<class T>
class ArrayList {
public:
    //构造函数
    ArrayList(const int a_size){
        this->init(NULL, a_size);
    }

    void init(T arr[], const int a_size) {
        if(a_size == NULL) {
            this->a_size = 10;
        }else {
            this->a_size = a_size;
        }
        this->arr = new T[this->a_size];
        cout<< "ArrayList init"<< endl;
    }

    \
    //拷贝函数
    ArrayList(ArrayList<T> &list) {
        this->arr = new T[list.size()];
        this->a_len = list.len();
        this->a_size = list.size();

        for(int i = 0; i < list.len(); i++) {
            this->arr[i] = list.get(i);
        }
    }

    //析构函数
    ~ArrayList() {
        delete[] this->arr;
        this->arr == NULL;
        cout<< "delete ArrayList"<< endl;
    }

    //添加
    ArrayList& add(T t){
        if(this->a_size <= this->a_len) {
            T *tmp = this->arr;
            this->a_size = this->a_size * 2;
            this->arr = new T[this->a_size];
            for(int i = 0; i < this->a_len; i++) {
                this->arr[i] = tmp[i];
            }
            delete[] tmp;
        }
        this->arr[this->a_len] = t;
        this->a_len += 1;
    }
    //删除
    void remove(){
        this->arr[this->a_len - 1] = NULL;
        this->a_len -= 1;
    }
    //获取
    T& get(const int index){
        return this->arr[index];
    }
    //当前数组容量
    int size(){
        return this->a_size;
    }
    //当前数组元素个数
    int len() {
        return this->a_len;
    }
    //重载运算符
    ArrayList& operator=(ArrayList<T> &list){
        if(this->arr != NULL) {
            delete[] this->arr;
            this->arr = NULL;
        }
        this->arr = new T[list.size()];
        this->a_size = list.size();
        this->a_len = list.len();
        for(int i = 0; i < list.len(); i++) {
            this->arr[i] = list.get(i);
        }
        return *this;
    }

private:
    T *arr; //保存数组地址的指针
    int a_size; //当前数组容量
    int a_len = 0; //当前数组元素个数
};

#endif // ARRAYLIST_HPP
