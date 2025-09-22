#include "widge.h"
#include "ui_widge.h"

widge::widge(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::widge)
{
    ui->setupUi(this);
}

widge::~widge()
{
    delete ui;
}

#include <QDebug>
#include <QFileDialog>

void widge::on_pushButton_clicked()
{
    // getOpenFileNames(): 弹出文件对话框，返回选中的多个文件名
    QStringList files = QFileDialog::getOpenFileNames();
    if(files.isEmpty()){
        return;
    }
    qDebug() << files;
}

