#include "combo.h"
#include "ui_combo.h"

combo::combo(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::combo)
{
    ui->setupUi(this);
}

combo::~combo()
{
    delete ui;
}

//activated(index):用户选择某个项触发
void combo::on_comboBox_activated(int index)     //将（文本）数据传递给槽函数
{
    ui->lineEdit->setText(ui->comboBox->itemText(index));
}


void combo::on_pushButton_clicked()
{
    QString date = ui->lineEdit->text();
    //addItem():在下拉框末尾添加item项
    ui->comboBox->addItem(QIcon(":/xx.jpg"),date);
}


void combo::on_pushButton_3_clicked()
{
    //在index索引处插入
    ui->comboBox->insertItem(1,ui->lineEdit->text());
}


void combo::on_pushButton_2_clicked()
{
    ui->comboBox->removeItem(ui->comboBox->currentIndex());
}

