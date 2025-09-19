

#include <iostream>
using namespace std;

class Temperature
{
public:
    Temperature(double value, char scale) : temp(value), scale(scale)
    { 
    }
    friend ostream &operator<<(ostream &out, Temperature &t)
    {
        out << t.temp << t.scale;
        return out;
    }
    Temperature operator+(const Temperature &t)
    {
        if(scale == 'F'){   //判断第一操作数的单位
            if(t.scale == 'F') //判断第二操作数
                return Temperature(temp + t.temp, 'F');
            else 
                //将摄氏度转为 华氏度
                return Temperature(temp + t.temp * 1.8 + 32, 'F');
        } else 
            if( t.scale == 'C')
                return Temperature(temp + t.temp, 'C');
            else
                return Temperature(temp + (t.temp - 32) / 1.8, 'C');
    }
private:
    float temp;
    char scale;
};

Temperature operator""_F(long double x)  //用户自定义字面量 参数 浮点型 必须 long double
{
    return Temperature(x, 'F');
}
Temperature operator""_C(long double x)
{
    return Temperature(x, 'C');
}
int main()
{
    Temperature t1(25.0, 'C');
    Temperature t2(77.0, 'F');

    cout << "t1: " << t1 << endl; // 输出 25.0C
    cout << "t2: " << t2 << endl; // 输出 77.0F

    Temperature t3 = t1 + 77.0_F;
    cout << "t1 + 77.0_F: " << t3 << endl; // 输出 50.0_

    Temperature t4 = t2 + 25.0_C;
    cout << "t2 + 77.0_F: " << t4 << endl; // 输出 154F
}