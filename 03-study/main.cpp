#include <iostream>
#include <string.h>
#include <string>

using namespace std;

/** ==========================
 * 学习目录：
 * 1.C和C++中struct的区别
 * 2.类
 * 3.类的封装练习
 * 4.对象的构造和析构
 * 5.匿名对象
 * 6.拷贝构造函数调用的时机
 * 7.构造函数的浅拷贝和深拷贝
 * 8.初始化列表
 * 9.动态对象的创建
 *  ==========================
 */

/** 1.C和C++中struct的区别 */
/* C中struct的成员只能是变量
 * C++中struct的成员可以有变量和函数
 * 使用结构体时可以不写struct来声明
 */
struct student {
    int age;
    int sex;
    char name[20];
    void print_stu() {
        cout << age << sex << name <<endl;
    }
};
void test1() {
    student stu;
    stu.age = 20;
    stu.sex = 1;
    strcpy(stu.name, "abc");
    stu.print_stu();
}

/** 2.类 */
/* 定义方法 class 类名称 {};
 * 类中的所有成员默认是私有的,使用public来修改访问权限
 * public 公共的,类外可以访问
 * protected 可以继承的,只有继承者有权限访问
 * private 私有的,类内可以访问
 */
class Person {
public: //公有成员变量
    int tall;
    char name[128];
    void eat() {
        printf("%s 在吃饭\n", name);
    }
protected: //可继承成员变量
    int money;

private: //私有成员变量
    int age;
};

/** 3.类的封装练习 */
/* 设计一个person类,类具有name和age属性，提供初始化函数init，并提供name和age的读写函数set/get
 * 必须保证age赋值范围是0-100，并提供输出姓名和年龄的方法
 */
class PersonTest{
private:
    char name[128];
    int age;
public:
    void init(char *name, int age) {
        setName(name);
        setAge(age);
    }
    void setName(char *name) {
        strcpy(this->name, name);
    }
    char * getName() {
        return this->name;
    }
    void setAge(int age) {
        if(age >= 0 && age <= 100) {
            this->age = age;
        }
    }
    int getAge() {
        return this->age;
    }
    void toString() {
        printf("name = %s \nage = %d \n", name, age);
    }
};
void test3() {
    PersonTest person;
    person.init("cc", 20);
    person.toString();
}

/** 4.对象的构造和析构 */
/* 构造函数：函数名和类名一致，不能写返回值，可以有形参，也可以重载
 * 析构函数：构造函数前面加~ 没有返回值 不能有参数 不能重载
 *
 * 构造函数是在实例化时会开辟内存空间
 * 在实例化对象销毁前调用析构函数
 *
 * 如果一个类中没有构造函数则系统会默认提供一个无参构造
 * 如果一个类中提供了一个有参数或无参数的构造，系统则不会再默认提供无参构造
 *
 * explicit关键字：不能用于隐式转换和复制初始化
 */
class Person4{
public:

    //无参构造
    Person4() {
        cout<< "init Person4"<< endl;
    }

    //构造函数
    Person4(int age, string name) {
        this->age = age;
        this->name = name;
    }

    //拷贝构造
    //explicit 不能用于隐式转换和复制初始化
    Person4(const Person4 &p) {
        this->age = p.age;
        this->name = p.name;
    }

    //析构函数
    ~Person4() {
        cout<< "free Person4"<< endl;
    }

    int age;
    string name;
};
//实例化类
void test4() {
    Person4 p(10, "lucy");
    //Person4 p1; //调用无参构造时不能加括号
    Person4 p2(p); //使用拷贝构造创建新的实例对象
}

/** 5.匿名对象 */
/* 匿名对象没有变量名，生命周期在当前行
 * 可以把匿名对象赋值给对象实例
 *
 * 显示法创建对象：Person4 p = Person4();
 * 隐式法创建对象: Person4 p = {10, "lucy"}; 隐式法无法使用无参构造创建对象实例
 */
void test5() {
    //匿名对象
    Person4(19, "luxi");

    //显示法创建对象
    Person4 p1 = Person4(10, "lucy");

    //隐式法创建对象
    Person4 p = {10, "lucy"};
}

/** 6.拷贝构造函数调用的时机 */
/* 拷贝构造函数用于旧对象初始化新对象
 * 什么时候会执行拷贝构造函数：
 * 1.旧对象初始化新对象
 * 2.形参是一个对象
 */
class Person6{
 public:
    Person6() {
        cout<< "no param contructor"<< endl;
    }

    Person6(int age) {
        this->age = age;
        cout<< "param contructor"<< endl;
    }

    Person6(const Person6 &p) {
        this->age = p.age;
        cout<< "copy contructor"<< endl;
    }

    int age;
};
//形参为Person6的对象实例
void createPerson6(Person6 p) {}
void test6(){
    Person6 p1(6);
    Person6 p2(p1);
    Person6 p3 = Person6(p1);
    Person6 p4 = p1;
    createPerson6(p1);
}

/** 7.构造函数的浅拷贝和深拷贝 */
/* 使用拷贝构造函数只是进行浅拷贝，所有指针类型的变量拷贝的是内存地址值
 * 这样当拷贝出的新对象实例在析构时会出错
 * 应该使用新地址来报错旧对象中的参数值
 */
class Person7{
public:
    Person7(int age, char *name) {
        this->age = age;
        this->name = (char *)malloc(strlen(name) + 1);
        strcpy(this->name, name);
    }

    Person7(const Person7 &p) {
        this->age = p.age;
//        this->name = name; //这样浅拷贝会出错

        //应该使用新地址来报错旧对象中的参数值
        this->name = (char *)malloc(strlen(p.name) + 1);
        strcpy(this->name, p.name);
    }

    ~Person7() {
        if(this->name != NULL) {
            free(this->name);
            this->name = NULL;
        }
        cout<< "free"<< endl;
    }

    void show() {
        cout<< name<< " "<< age<< endl;
    }

    int age;
    char *name;
};

void test7() {
    Person7 p = Person7(12, "xiao");
    p.show();
    Person7 p1 = Person7(p);
    p1.show();
}

/** 8.初始化列表 */
/* 使用初始化列表的方式创建对象实例并给成员变量赋值
 * 注意初始化列表定义时的参数和声明顺序一致
 */
class Person8{
public:
    int a,b,c;
    //初始化列表,形参顺序应该和定义顺序一致
    Person8(int a, int b, int c): a(a), b(b), c(c) {
        cout<< "param constructor"<< endl;
    }
    void show() {
        cout<< a<< " "<< b<< " "<< c<< endl;
    }
};
//使用初始化列表初始化类成员
class Phone {
public:
    string name;
    Phone(string name) {
        this->name = name;
    }
};
class Game {
public:
    string name;
    Game(string name) {
        this->name = name;
    }
};
class Man {
public:
    string name;
    Phone phone;
    Game game;
    Man(string name, string phoneName, string gameName): name(name), phone(phoneName), game(gameName) {
        cout<< "class param constructor"<< endl;
    }
};

void test8() {
    Person8 p = Person8(1,2,3);
    p.show();
    //使用初始化列表初始化类成员
    Man m = Man("cc", "ihone12 Mini", "艾尔登法环");
}

/** 9.动态对象的创建 */
/* C中的malloc和free等一些动态申请内存的函数在C++中不能很好地运行
 * 因为不能帮忙完成对象的初始化工作
 * malloc在申请内存时不会调用类中的构造函数
 * free在释放空间时也不会调用类中的析构函数
 * C++通过new这个关键字来解决动态内存分配和创建对象的操作
 * 类型 *p = new 类型
 * 通过delete来释放申请的空间
 *
 * new一个单一对象时，使用delete释放单一对象
 * new一个数组时，使用delete []释放这个数组
 */
void test9() {
    //创建一个整型对象
    int *p = new int; //申请一块内存 sizeof(int)大小 并对这块空间进行初始化
    *p = 100;
    delete p;
    cout<< *p<< endl;

    //创建一个类对象
    Person4 *person = new Person4;
    delete person;

    //创建一个数组对象
    int *arr = new int[10];
    delete []arr; //注意，数组释放时需要加[]

    //delete void *不会调用析构函数
    void *v = new Person4;
    delete v;
}

int main() {
    test1();
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();
    test9();
    return 0;
}
