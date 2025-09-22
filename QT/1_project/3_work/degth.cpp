#include "degth.h"
#include "ui_degth.h"
using namespace std;

Degth::Degth(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Degth)
{
    ui->setupUi(this);
}

Degth::~Degth()
{
    delete ui;
}

void Degth::updateLineEdit(){
    enter[flag] = '\0';
    QString text = QString::fromLocal8Bit(enter);
    ui->lineEdit->setText(text);
}

void Degth::on_pushButton_8_clicked()
{
    incrementFlag("1");
    updateLineEdit();
}


void Degth::on_pushButton_2_clicked()
{
    incrementFlag("2");
    updateLineEdit();
}


void Degth::on_pushButton_3_clicked()
{
    incrementFlag("3");
    updateLineEdit();
}


void Degth::on_pushButton_4_clicked()
{
    incrementFlag("4");
    updateLineEdit();
}


void Degth::on_pushButton_7_clicked()
{
    incrementFlag("5");
    updateLineEdit();
}


void Degth::on_pushButton_10_clicked()
{
    incrementFlag("6");
    updateLineEdit();
}


void Degth::on_pushButton_clicked()
{
    incrementFlag("7");
    updateLineEdit();
}


void Degth::on_pushButton_5_clicked()
{
    incrementFlag("8");
    updateLineEdit();
}


void Degth::on_pushButton_12_clicked()
{
    incrementFlag("9");
    updateLineEdit();
}


void Degth::on_pushButton_9_clicked()
{
    incrementFlag("0");
    updateLineEdit();
}


void Degth::on_pushButton_6_clicked()
{
    incrementFlag(".");
    updateLineEdit();
}


void Degth::on_pushButton_11_clicked()
{
    QString text = QString::fromLocal8Bit(calculateAndGetResult());
    ui->lineEdit_2->setText(text);
}


void Degth::on_pushButton_16_clicked()
{
    incrementFlag("/");
    updateLineEdit();
}


void Degth::on_pushButton_15_clicked()
{
    incrementFlag("*");
    updateLineEdit();
}


void Degth::on_pushButton_14_clicked()
{
    incrementFlag("-");
    updateLineEdit();
}


void Degth::on_pushButton_13_clicked()
{
    incrementFlag("+");
    updateLineEdit();
}



void Degth::on_pushButton_17_clicked()
{
    flag = 0;
    clearEnterArray();
    updateLineEdit();
    ui->lineEdit_2->setText("");
}
