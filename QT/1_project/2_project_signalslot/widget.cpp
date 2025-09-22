#include "widget.h"
#include "ui_widget.h"
#include <QDebug>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //this->setGeometry(0,0,640,480);
    //this->setFixedSize(640,480);
    this->resize(640,480);

    connect(ui->pushButton_4,&QPushButton::clicked,this,&Widget::dateRead);
    //新风格：&QPushButton::clicked:取信号的首地址，并声明信号在QPushButton类域必须与参数1的类名保持一致
    //旧风格：SIGNAL():宏函数：求信号的首地址     SLOT(）：求槽函数首地址
    //connect（ui->pushButton_4,SIGNAL(clicked(bool)),this,SLOT(dateRead()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    qDebug() << "点击";

    ui->lineEdit->setText("是兄弟就来砍我");
}


void Widget::on_pushButton_2_clicked()
{

    ui->lineEdit->setText("你*****");
}

void Widget::on_pushButton_3_clicked()
{
    close();
}

void Widget::dateRead()
{
    qDebug() << ".................";

    //text():获取文本数据，返回Qstring类型
    //QString date = ui->lineEdit_2->text();

    //tonInt();将Qstring转换为int类型
    //int num = 1 + date.toInt();

    //QString::number（）：将数值转换为Qstring类型
    //ui->lineEdit->setText(QString::number(num));
    //ui->lineEdit->setText(QString("%1").arg(num));

    //QString ttt = "123+456";
    // toStdString(): 将QString转换为 C++的string类型 data(): 将string转换为 C语言的char *类型
    //char *p = ttt.toStdString().data();
    //qDebug() << p;

    // 1、QSS盒子模型
    // 2、Qt设计器样式表设置

    //ctrl A ctrl I 全部格式化（重复格式）
}

