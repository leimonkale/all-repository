#include <iostream>
using namespace std;
#include <cstring>


class Student{    //声明一个学生类
    int eys;
public:
    char name[12];
protected:
    float money;
};

int main()
{
    // class Student stu;
    Student stu;     //定义一个类对象，创造一个实例
    strcpy(stu.name, "hhhh");
    // stu.money = 1.2; //错误，money为 protected保护权限，不能通过对象访问
    // stu.eys = 2;     //错误，C++class中默认为 privat私有权限，不能通过对象访问

    Student stu1;
    stu1 = stu;                   //1、默认赋值运算
    cout << stu1.name << endl;

    Student *stu2;      // 定义对象指针
    stu2 = &stu;        // 2、&默认的地址运算
    cout << stu2->name << endl;

    Student stu3 = stu;   //定义初始化一个对象，3、默认拷贝构造
    cout << stu3.name << endl;

    Student stu4(stu);    //定义初始化一个对象，默认拷贝构造
    cout << stu4.name << endl;
}