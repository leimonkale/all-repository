#include "tv.h"
#include "ui_tv.h"

#include <QDebug>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QUrl>

TV::TV(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TV)
{
    ui->setupUi(this);
    ui->label_2->setScaledContents(true);
}

TV::~TV()
{
    delete ui;
}

void TV::on_pushButton_clicked()
{
    QPixmap pixmap((":/"+ui->lineEdit_2->text()));
    if(pixmap.isNull()){
        ui->lineEdit_2->setText("图片加载失败");
    }else{
        ui->label_2->setPixmap(QPixmap(":/"+ui->lineEdit_2->text()).scaled(ui->label_2->width(),ui->label_2->height()));
    }
}


void TV::on_pushButton_2_clicked()
{
    movie = new QMovie;
    movie->setFileName(":/"+ui->lineEdit_2->text());
    ui->label_2->setScaledContents(true);
    ui->label_2->setMovie(movie);
    movie->start(); //启动动画 stop(): 停止
}


void TV::on_pushButton_3_clicked()
{
    movie->stop();
}


// void TV::on_pushButton_4_clicked()
// {
//     int argc;
//     char *argv[1024];
//     QApplication a(argc, argv);

//     // 创建播放器
//     QMediaPlayer player;
//     // 创建视频显示窗口
//     QVideoWidget videoWidget;

//     // 设置视频输出
//     player.setVideoOutput(&videoWidget);

//     // 设置要播放的资源文件中的MP4
//     // 注意替换为你的实际资源路径
//     player.setMedia(QMediaContent(QUrl("qrc:/videos/sample.mp4")));

//     // 显示视频窗口
//     videoWidget.show();

//     // 开始播放
//     player.play();

// }

// void Widget::on_pushButton_clicked()
// {
//     QString filename = ui->lineEdit->text();
//     if(filename.isEmpty())
//         return;
//     //判断文件名的后缀 xxx.gif.png  xxx.jpeg
//     QStringList lst = filename.split('.');      //split(): 字符串的分割
//     if(lst.isEmpty())                           //isEmpty(): 判断是否为空
//         return;
//     if(lst.last() == "gif"){
//         movie->setFileName(":/" + filename);
//         ui->label->setMovie(movie);
//         if( movie->state() == QMovie::Running)
//             movie->stop();
//         else
//             movie->start();
//     } else {
//         ui->label->setPixmap(QPixmap(":/" + filename)
//                                  .scaled(ui->label->width(), ui->label->height()));
//     }
// }

