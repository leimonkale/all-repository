#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->radioButton,&QRadioButton::toggled,this,&MainWindow::radio_check);
    connect(ui->radioButton_2,&QRadioButton::toggled,this,&MainWindow::radio_check);
    connect(ui->radioButton_3,&QRadioButton::toggled,this,&MainWindow::radio_check);
    connect(ui->radioButton_4,&QRadioButton::toggled,this,&MainWindow::radio_check);

    //设置勾选
    ui->radioButton->setChecked(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::radio_check(bool flag){
    //sender();获取当前槽函数的信号触发者
    QRadioButton *ra = static_cast<QRadioButton *> (sender());
    if(flag){
        ui->lineEdit->setText(ra->text());
    }
}
