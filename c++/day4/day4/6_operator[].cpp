#include <iostream>
using namespace std;

class Array{
public:
    Array(int s):size(s){
        p = new int[size];
    }
    ~Array(){
        delete []p;
    }
    int &operator[](int i){
        return p[i];
    }
private:
    int *p;
    int size;   
};

int main()
{
    Array buf(5);
    for(int i = 0; i < 5; i++)
        buf[i] = i;
    
    for(int i = 0; i < 5; i++)
        cout << buf[i] << " ";
    cout << endl;
}

/*

    自行搜索 "字面量", 非成员非友元的 运算符重载函数
    
    1、设计一个 Temperature类，实现华氏温度 和 摄氏温度的相互转化。
        Temperature t1(25.0, 'C');
        Temperature t2(77.0, 'F');

        cout << "t1: " << t1 << endl;           // 输出 25.0C
        cout << "t2: " << t2 << endl;           // 输出 77.0F

        Temperature t3 = t1 + 77.0_F;
        cout << "t1 + 77.0_F: " << t3 << endl;  // 输出 50.0C

        Temperature t4 = t2 + 25.0_C;      
        cout << "t2 + 77.0_F: " << t4 << endl;  // 输出 154F
     
        

    2、设计一个复数类Complex，实现以下内容：

        Complex c1(3.0, 4.0); // 3+4i
        Complex c2(1.0, -1.0); // 1-i

        cout << "c1: " << c1 << endl; // 输出 3 + 4i
        cout << "c2: " << c2 << endl; // 输出 1 - i

        Complex sum = c1 + c2;
        cout << "Sum: " << sum << endl; // 输出 4 + 3i
*/