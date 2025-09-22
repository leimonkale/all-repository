#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}
#include <QFileDialog>

void Widget::on_pushButton_clicked()
{
    QString file = QFileDialog::getOpenFileName(this, "打开文件", ".",
                                 "所有文件(*);;图片(*.jpg *.png *.gif);;cpp文件(*.cpp);;头文件(*.h)");
    // append(): 在文本编辑器下一行追加数据
    ui->textEdit->append(file);
}

#include <QMessageBox>
void Widget::on_pushButton_2_clicked()
{
    // QMessageBox::warning(this, "警告", "操作有误，是否继续?");

    // int ret = QMessageBox::warning(this, "警告", "操作有误，是否继续?", QMessageBox::Open, QMessageBox::Close);
    // if(ret == QMessageBox::Open)
    //     ui->textEdit->append("打开");
    // if(ret == QMessageBox::Close)
    //     ui->textEdit->append("关闭");


    // int ret = QMessageBox::warning(this, "警告", "操作有误，是否继续?",
    //                                QMessageBox::Open | QMessageBox::Close | QMessageBox::Discard | QMessageBox::Cancel,
    //                                QMessageBox::Open);
    // if(ret == QMessageBox::Open)
    //     ui->textEdit->append("打开");
    // if(ret == QMessageBox::Close)
    //     ui->textEdit->append("关闭");


    int ret = QMessageBox::warning(this, "警告", "操作有误，是否继续?", "确认", "应用", "取消");
    if(ret == 0)
        ui->textEdit->append("确认");
    if(ret == 1)
        ui->textEdit->append("应用");
    if(ret == 2)
        ui->textEdit->append("取消");
}

#include <QInputDialog>
void Widget::on_pushButton_3_clicked()
{
    QString pwd = QInputDialog::getText(this, "密码", "请输入密码：", QLineEdit::Password);
    ui->textEdit->append(pwd);
}

#include <QColorDialog>
void Widget::on_pushButton_4_clicked()
{
    QColor color = QColorDialog::getColor();
    if(color.isValid())
        ui->textEdit->setTextColor(color);          //设置文本颜色
}
#include <QFontDialog>
void Widget::on_pushButton_5_clicked()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, QFont("楷体", 24), this);
    if(ok){
        ui->textEdit->setFont(font);
    }
}

