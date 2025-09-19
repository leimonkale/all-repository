#include <iostream>
#include <stdexcept>
using namespace std;

int fileOperation(const char *fileName)
{
    if(fileName == NULL)
    {
        throw invalid_argument("File name is null");
    }
    FILE *fp = fopen(fileName, "r");
    if (fp == NULL)
    {
        throw runtime_error("File not found");
    }
    // ....
    fclose(fp);
    return 0;
}

int main()
{
    char buf[32];
    cin >> buf;
    try
    {
        fileOperation(buf);
    } 
    // catch(const invalid_argument &e)
    // {
    //     cout << "fileName:" << e.what() << endl;
    // }
    // catch(const runtime_error &e)
    // {
    //     cout << "fopen： " << e.what() << endl;
    // }
    catch(const exception &e){
        cout << "Exception: " << e.what() << endl;
    }
}