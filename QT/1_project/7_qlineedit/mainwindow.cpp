#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit->setEchoMode(QLineEdit::NoEcho);  //不显示
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);    //直接密码显示
    ui->lineEdit_3->setEchoMode(QLineEdit::PasswordEchoOnEdit);   //显示明文，失去焦点后，密码显示
    ui->lineEdit_4->setAlignment(Qt::AlignRight | Qt::AlignBottom);

    connect(ui->lineEdit_6,&QLineEdit::textChanged,this,&MainWindow::edt_text);
}

MainWindow::~MainWindow()
{
    delete ui;
}

#include <QDebug>
//textEdited (const QString &): 这个信号在行编辑器被编辑时触发，形参表示新的文本数据
// 如果绑定的槽函数也设计形参，则表示用槽函数的形参 接受信号传递的数据。即将数据传递给槽函数
void MainWindow::on_lineEdit_5_textEdited(const QString &arg1)
{
    qDebug() << "arg1:" << arg1;
    ui->lineEdit_6->setText(arg1);
}

void MainWindow::edt_text(QString arg){
    qDebug() <<"手动绑定" << arg;
}

void MainWindow::on_lineEdit_4_selectionChanged()
{
    qDebug() << "被选中的：" << ui->lineEdit_4->selectedText();
}

//槽函数的形参个数应该小于等于信号的形参个数
//槽函数的形参类型应该与信号形参类型要匹配
//信号带参数的目的：像槽函数传递数据，常用于两个不同对象（控件）间的数据传递

