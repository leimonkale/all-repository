#include <iostream>
using namespace std;

#include <stdexcept>

float test(int x, int y)
{
    if (y != 0) // 检查错误
        return x / y;
    else
        // 抛出异常（携带具体错误信息）， 实际是抛出一个匿名对象,该函数立即结束运行
        throw runtime_error("除数不能为0");
}

int main()
{
    int a, b;
    while (1)
    {
        cin >> a >> b;
        try
        {
            cout << test(a, b) << endl;
        }
        catch (const runtime_error &e)
        {                                         // 捕获异常
            cout << "异常：" << e.what() << endl; // 输出错误信息
            break;
        }
    }
}