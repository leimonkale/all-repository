#include <iostream>
using namespace std;

// #include <string.h>
#include <cstring>


/*
    1、由于C++中对数据的安全性有严格要求，因此结构体中引入了 权限访问限定符

        public：公有的，表示外部可通过结构体变量直接访问操作成员
        protected：保护的，继承中使用
        private：私有的，表示外部不可通过结构体变量直接访问操作成员

    2、C++结构体默认为 公有权限，一般建议将成员变量设置 private权限

    3、为了访问私有成员，结构体引入 成员函数的概念。

    4、结构体成员变量对于所有成员函数都是 共有的.

    5、为了区分函数形参 和 成员变量同名，结构体成员函数引入了 this指针。

    6、为了初始化结构体成员变量，引入了 构造函数：
        1、函数没有返回值
        2、函数名 与 结构体名相同
        3、定义结构体变量时，系统自动调用该函数来完成 成员变量的初始化
*/ 
struct Student{
public:
    Student(const char *n, int a, const char *no);          //构造函数

    void setAge(int a);         //声明成员函数
    int getAge();
private:                    //私有成员区
    char name[12] = "李四";  //默认值
    int age;
    char no[20];
};
Student::Student(const char *n, int a, const char *no)
{
    this->age = a;
    strcpy(name, n);
    strcpy(this->no, no);
}
void Student::setAge(int age)          //外部定义成员函数
{         
    this->age = age;
}
int Student::getAge()
{ 
    return age;
}

int main()
{
    // struct Student stu;      //C语言的结构体变量定义
    // Student stu;                //定义一个结构体变量

    Student stu("王五", 20, "2025111111111");
    // strcpy(stu.name, "张三");   //错误，name为私有成员
    // stu.age = 12;
    // strcpy(stu.no, "202512345678");

    stu.setAge(18);                //修改成员
    cout << stu.getAge() << endl;  //访问成员
    return 0;
}