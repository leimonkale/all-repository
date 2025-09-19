#include <iostream>
using namespace std;
#include <cstring>

template <class T, int max>
class Array
{
public:
    Array();
    T &operator[](int index);

private:
    T arr[max];
};

template <class T, int len>
Array<T, len>::Array()
{
    memset(arr, 0, sizeof(arr));
    for (int i = 0; i < max; i++)
        arr[i] = i;
}

template <class T, int size>
T & Array<T, size>::operator[](int index)
{
    if (index >= 0 && index < max)
        return arr[index];
    return arr[0];
}
int main()
{
    Array<int, 10> a;
    for (int i = 0; i < 10; i++)
        cout << a[i] << " ";
    cout << endl;
}