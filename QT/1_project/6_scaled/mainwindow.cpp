#include "mainwindow.h"
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setFixedSize(QSize(640,480));
    setWindowTitle("no ui file");
    setWindowIcon(QIcon(":/1.jpg"));

    lab = new QLabel;
    lab->setParent(this);   //设置父对象为窗口
    lab->resize(100,50);
    lab->setText("hello world");
    lab->setStyleSheet("background-color:yellow;");

    lab2 = new QLabel("label2", this);
    lab2->setFixedSize(200,300);
    lab2->setStyleSheet("background-color: blue;");
    lab2->move(lab->x()+lab->width(),lab->y());//move（x，y）：将控件移动到（x，y）坐标位置

    lab3 = new QLabel(lab2);
    lab3->setFixedSize(lab->size());
    lab3->setText("lab3");
    lab3->setStyleSheet(lab->styleSheet());
    lab3->move(lab2->width() - lab3->width(), 0);

    edt = new QLineEdit(this);
    edt->resize(200,300);
    edt->setPlaceholderText("user");
    edt->setStyleSheet(QString("font:28pt '楷体';"
                        "background-color:rgb(137,110,200;"
                        "border-radius:25px;").arg(edt->height()/2-15));

}

MainWindow::~MainWindow() {}
