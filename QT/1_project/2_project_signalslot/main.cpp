#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    //设置分辨率缩放使能令窗口大小一致
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling,true);
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
