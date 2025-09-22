#include "degth.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling,false);
    QApplication a(argc, argv);
    Degth w;
    w.show();
    return a.exec();
}
