/*===============================================
*   文件名称：main.c
*   创 建 者：     
*   创建日期：2025年06月24日
*   描    述：
================================================*/

#include "list.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    LIST a;//greate a list!!!

    for(int i=0; i<10; i++)
        a.list_insert(0, i);//add list

    a.list_show();//99-----------0
    a.list_insert(8, 8888);//add list

    a.list_show();//99------8888-----0
    a.list_delete(8);//add list
    a.list_show();//99------8888-----0
    a.list_update(4, 88888);//add list
    a.list_show();//99------8888-----0
    return 0;
} 
