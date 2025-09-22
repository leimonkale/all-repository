#include "widget.h"
#include "ui_widget.h"

#include <QMenu>
/*
 *
 *  匿名函数：不止具体函数名的函数，也就是lambda表达式
 *      1、函数算法简单，代码量少，结构简单，类似与c++内联函数
 *      2、【】代表函数名，
 *          括号中的&符号，表示引用外部的所有变量到匿名函数中
 *          括号中 =赋值符号：表示拷贝外部的所有变量到匿名函数中
 *      3、（）代表形参列表
 *      4、{}代表函数体
 */
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    stdMenu = new QMenu(ui->pushButton);              //构造一个菜单
    stdMenu->addAction("新建文件",[&](){
        ui->plainTextEdit->appendPlainText("新建文件");
    },QKeySequence("ctrl+n"));

    QAction *act = stdMenu->addAction("打开文件",[&](){
        ui->plainTextEdit->appendPlainText("打开文件");
    });
    //设置菜单项快捷键
    act->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));


    stdMenu->addAction("保存文件",[&](){
        ui->plainTextEdit->appendPlainText("保存文件");
    });
    stdMenu->addAction("另存文件",[&](){
        ui->plainTextEdit->appendPlainText("另存文件");
    });
    stdMenu->addAction("关闭文件",[&](){
        ui->plainTextEdit->appendPlainText("关闭文件");
    });
    ui->pushButton->setMenu(stdMenu);  //按钮设置菜单，Qt中的标准写法


}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_2_clicked()
{
    QMenu menu ;//= new QMenu;
    stdMenu->addAction("保存文件",[&](){
        ui->plainTextEdit->appendPlainText("保存文件");
    });
    stdMenu->addAction("另存文件",[&](){
        ui->plainTextEdit->appendPlainText("另存文件");
    });
    stdMenu->addAction("关闭文件",[&](){
        ui->plainTextEdit->appendPlainText("关闭文件");
    });

    menu.exec(ui->pushButton_2->mapToGlobal(QPoint(0,ui->pushButton_2->height())));
}

/*
 * menu.exec(pos):手动控制菜单出现的位置
 * mapToGlobal():将控件的局部坐标转换为屏幕坐标
 * QPoint(0,ui->pushButton_2->height():0表示控件左上角点为基准平移0个像素，height（）：控件高度，表示控件垂直方向平移的距离
 *
 */
