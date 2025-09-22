#include "combo.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    combo w;
    w.show();
    return a.exec();
}
