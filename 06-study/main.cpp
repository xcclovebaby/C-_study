#include <iostream>
#include <string>

using namespace std;

/** ==========================
 * 学习目录：
 * 1.多态
 * 2.纯虚函数和抽象类
 * 3.案例：制作饮品
 * 4.虚析构和纯虚析构
 * 5.案例：电脑组装
 *  ==========================
 */

/** 1.多态 */
/* 多态分为两类：
 * 静态多态：函数重载和运算符重载、复用函数名
 * 动态多态：子类和虚函数运行时多态
 *
 * 多态：父类的指针或引用指向子类的对象
 *
 * virtual定义在函数是为虚函数,虚函数在运行阶段进行绑定，属于地址晚绑定
 * 虚函数：虚函数(表)指针，这个函数被记录在虚函数表中，记录的是函数地址，通过虚函数表指针指向这个地址，
 * 当子类重写父类的虚函数，在子类的虚函数表中会替换为子类虚函数的地址
 *
 * 重写：函数返回类型 函数名 参数列表要完全相同
 *
 * 动态多态的满足条件：
 * 1.有继承关系
 * 2.子类重写父类的虚函数
 */
class P1 {
public:
    //虚函数(表)指针，这个函数被记录在虚函数表中，记录的是函数地址，通过虚函数表指针指向这个地址
    //当子类重写父类的虚函数，在子类的虚函数表中会替换为子类虚函数的地址
    virtual void speak() {
        cout<< "P1 speak"<< endl;
    }
};
class A1: public P1 {
public:
    //重写父类的虚函数
    void speak() {
        cout<< "A1 speak"<< endl;
    }
};
void doSpeak(P1 &p) {
    p.speak();
}
void test1() {
    A1 a1;
    //未加virtual 执行父类P1的speak函数
    //加virtual 执行子类A1的speak函数
    doSpeak(a1);
}

/** 2.纯虚函数和抽象类 */
/* 在多态中通常父类中的虚函数的实现是毫无意义的，因此可以将虚函数改为纯虚函数
 * 当类中有了纯虚函数，这个类也被称为抽象类
 * 纯虚函数：virtrual 返回值类型 函数名(形参) = 0;
 *
 * 抽象类无法实例化，子类必须重写纯虚函数，否则也属于抽象类
 */
class Base2 {
public:
    //纯虚函数
    virtual void show() = 0;
};
class P2: public Base2 {
public:
    void show() {
        cout<< "P2"<< endl;
    }
};
void test2() {
    P2 p2;
    p2.show();
}

/** 3.案例：制作饮品 */
class Base3 { //抽象父类
public:
    //煮水
    virtual void boil() = 0;
    //冲泡
    virtual void brew() = 0;
    //倒水
    virtual void pourInCup() = 0;
    //加入佐料
    virtual void putSomething() = 0;

    //制作饮品
    void makeDrink() {
        boil();
        brew();
        pourInCup();
        putSomething();
        cout<< "make over ~"<< endl;
    }
};
//制作咖啡
class Coffee: public Base3 {
    //煮水
    virtual void boil(){
        cout<< "coffee boil"<< endl;
    }
    //冲泡
    virtual void brew(){
        cout<< "coffee brew"<< endl;
    }
    //倒水
    virtual void pourInCup(){
        cout<< "coffee pour in cup"<< endl;
    }
    //加入佐料
    virtual void putSomething(){
        cout<< "coffee put something"<< endl;
    }
};
void test3() {
    Base3 *p = new Coffee;
    p->makeDrink();
}

/** 4.虚析构和纯虚析构 */
/* 多态使用时，如果子类有属性开辟空间到堆区，那么父类指针在释放时无法调用子类的析构代码
 * 为了解决这个问题需要将父类的析构函数改为虚析构或纯虚析构
 * 虚析构声明方式：virtual ~类名() {}
 * 纯虚析构声明方式：virtual ~类名() = 0;
 *
 * 一个类中虚析构和纯虚析构只能有一个
 * 纯虚函数需要声明也需要实现
 *
 * 注意：使用纯虚析构的时候需要在外部重写一下纯虚析构函数
 */
class Base4 {
public:
    //虚析构
//    virtual ~Base4() {
//        cout<< "free base4"<< endl;
//    }

    //纯虚析构
    //注意：使用纯虚析构的时候需要在外部重写一下纯虚析构函数
    virtual ~Base4() = 0;
};

//重写纯虚析构
Base4::~Base4() {
    cout<< "free base4"<< endl;
}

class P4: public Base4 {
public:
    string *name;
    P4(string name) {
        this->name = new string(name);
    }

    ~P4() {
        if(this->name != NULL) {
            delete this->name;
        }
        cout<< "free p4"<< endl;
    }

    void show() {
        cout<< *(this->name)<< endl;
    }
};
void test4() {
    P4 *p4 = new P4("abc");
    p4->show();
    delete p4;
}

/** 5.案例：电脑组装 */
/* 多态的抽象类在使用时不能用实例，需要用抽象父类的指针类型接收
 */
class CPU {
public:
    //cpu计算
    virtual void caculate() = 0;
};
class GPU {
public:
    //显卡显示
    virtual void show() = 0;
};
class RAM {
public:
    //内存存储
    virtual void store() = 0;
};
class DISK {
public:
    //硬盘存放数据
    virtual void save() = 0;
};

//电脑类
class Computer {
public:
    Computer(CPU *cpu, GPU *gpu, RAM *ram, DISK *disk):cpu(cpu), gpu(gpu), ram(ram), disk(disk) {
        cout<< "computer init success !"<< endl;
    }

    void start() {
        this->cpu->caculate();
        this->gpu->show();
        this->ram->store();
        this->disk->save();
    }

    //释放指针内存
    ~Computer() {
        delete cpu, gpu, ram, disk;
        cout<< "delete computer success !"<< endl;
    }
private:
    CPU *cpu;
    GPU *gpu;
    RAM *ram;
    DISK *disk;
};

//英特尔大厂商 生产cpu 显卡 内存条 硬盘
class Intel: public CPU, public GPU, public RAM, public DISK {
public:
    void caculate() {
        cout<< "Intel CPU caculate"<< endl;
    }
    void show() {
        cout<< "Intel GPU show"<< endl;
    }
    void store() {
        cout<< "Intel RAM store"<< endl;
    }
    void save() {
        cout<< "Intel DISK save"<< endl;
    }
};

void test5() {
    Intel *cpu = new Intel,
            *gpu = new Intel,
            *ram = new Intel,
            *disk = new Intel;
    //组装电脑
    Computer *com = new Computer(cpu, gpu, ram, disk);
    //电脑开机
    com->start();
    //释放指针
    delete com;
}

int main()
{
    test1();
    test2();
    test3();
    test4();
    test5();
    return 0;
}
