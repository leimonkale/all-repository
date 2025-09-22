#include "imgbox.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    imgbox w;
    w.show();
    return a.exec();
}
