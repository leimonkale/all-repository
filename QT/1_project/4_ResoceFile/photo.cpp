#include "photo.h"
#include "ui_photo.h"

#include <QPalette>   //画板类

photo::photo(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::photo)
{
    ui->setupUi(this);

    QPalette pal = this->palette();//获取当前界面默认的画板
    pal.setBrush(QPalette::Window,QPixmap(":/1.png"));  //：表示资源   /表示前缀
    this->setPalette(pal); //设置当前界面的画板

    // 设置内容的缩放，也就是图片的自适应
    ui->label->setScaledContents(true);
    // setPixmap() 设置label的图像
    ui->label->setPixmap(QPixmap(":/1.png"));

    movie = new QMovie;
    movie->setFileName(":/th.gif");
    ui->label_2->setScaledContents(true);
    ui->label_2->setMovie(movie);
    movie->start(); //启动动画 stop(): 停止
}

photo::~photo()
{
    delete ui;
}
