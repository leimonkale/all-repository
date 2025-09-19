#include <iostream>
using namespace std;

class Complex
{
public:
    Complex(float x, float y) : real(x), imag(y) {
        cout << "Constructor called" << endl;
    }
    friend ostream &operator<<(ostream &out, Complex &c)
    {
        out << c.real;
        if (c.imag > 0)
            out << " + " << c.imag << "i";
        else if (c.imag < 0)
            out << " - " << -c.imag << "i";
        else
            out << " + 0i";

        return out;
    }
    Complex operator+(Complex &c){
        return Complex(real+c.real, imag+c.imag);       //返回匿名对象，是一个局部的
    }

private:
    float real;
    float imag;
};

int main()
{
    Complex c1(3.0, 4.0);  // 3+4i
    Complex c2(1.0, -1.0); // 1-i

    cout << "c1: " << c1 << endl; // 输出 3 + 4i
    cout << "c2: " << c2 << endl; // 输出 1 - i

    Complex sum = c1 + c2;
    cout << "Sum: " << sum << endl; // 输出 4 + 3i
}

// 2、设计一个复数类Complex，实现以下内容：

//         Complex c1(3.0, 4.0); // 3+4i
//         Complex c2(1.0, -1.0); // 1-i

//         cout << "c1: " << c1 << endl; // 输出 3 + 4i
//         cout << "c2: " << c2 << endl; // 输出 1 - i

//         Complex sum = c1 + c2;
//         cout << "Sum: " << sum << endl; // 输出 4 + 3i