#include "widget.h"
#include "ui_widget.h"

#include <QMenu>
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    stdMenu = new QMenu(ui->pushButton);              //构造一个菜单
    stdMenu->addAction(QPixmap(":/1.png").scaled(30,30,Qt::KeepAspectRatio,Qt::SmoothTransformation),"新建",this,&Widget::buildnewfile,QKeySequence("ctrl+n"));
    stdMenu->addAction(QPixmap(":/2.png").scaled(30,30,Qt::KeepAspectRatio,Qt::SmoothTransformation),"打开",this,&Widget::openfile,QKeySequence("ctrl+l"));
    stdMenu->addAction(QPixmap(":/3.png").scaled(30,30,Qt::KeepAspectRatio,Qt::SmoothTransformation),"保存",this,&Widget::savefile,QKeySequence("ctrl+l"));
    stdMenu->addAction(QPixmap(":/4.png").scaled(30,30,Qt::KeepAspectRatio,Qt::SmoothTransformation),"另存",this,&Widget::savefileat,QKeySequence("ctrl+l"));
    stdMenu->addAction(QPixmap(":/5.png").scaled(30,30,Qt::KeepAspectRatio,Qt::SmoothTransformation),"关闭",this,&Widget::closefile,QKeySequence("ctrl+l"));
    stdMenu->setStyleSheet("QMenu::icon { width: 50px; height: 50px; }");
    ui->pushButton->setMenu(stdMenu);
}

Widget::~Widget()
{
    delete ui;
}

#include <QFileDialog>
void Widget::openfile(){
    if(flage_open){
        QMessageBox::warning(this,"error","有文件正在被打开");
    }
    else{
    std::function<void(const QString &, const QByteArray &)> handler =
        [this](const QString &filePath, const QByteArray &content) {
            qDebug() << "选中的文件路径：" << filePath;
            qDebug() << "文件内容：" << content.toStdString();
            ui->textEdit->setText(QString(content));
            files = filePath;
            flage_open = 1;
        };
    QFileDialog::getOpenFileContent("所有文件(*);;所有文件(* *.txt *.png)",handler,this);

    }
}

void Widget::buildnewfile(){
    if(flage_open){
        QMessageBox::warning(this,"error","有文件正在被打开");
    }else{
        ui->textEdit->clear();
        flage_open = 1;
    }
}

void Widget::savefileat(){
    if(flage_open){
    QByteArray content = ui->textEdit->toPlainText().toUtf8();

    QFileDialog::saveFileContent(content, "filename.txt", this);

    }else{
        QMessageBox::warning(this,"error","没有有文件正在被打开");
    }
}

#include <QFile>
void Widget::savefile(){
    if(flage_open){
        QFile file(files);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QString content = ui->textEdit->toPlainText();

            //写入内容（QString需转换为QByteArray，常用UTF-8编码）
            file.write(content.toUtf8());

            //关闭文件（确保内容被正确写入磁盘）
            file.close();

            qDebug() << "文件保存成功：" ;
        } else {
            qDebug() << "error" ;
        }
    }else{
        QMessageBox::warning(this,"error","没有有文件正在被打开");
    }
}

void Widget::closefile(){
    QMessageBox::StandardButton result = QMessageBox::question(
        this,                  //父窗口 QWidget *parent
        "提示",                // 对话框标题 const QString &title
        "内容已修改，是否保存？", // 提示消息 const QString &text,
        QMessageBox::Save |    // 保存按钮 StandardButtons buttons = StandardButtons(Yes | No),
        QMessageBox::Discard | // 不保存按钮
        QMessageBox::Cancel,   // 取消按钮
        QMessageBox::Save      // 默认选中按钮 StandardButton defaultButton = NoButton);
        );

    switch (result) {
    case QMessageBox::Save:
        savefile();
        ui->textEdit->clear();
        flage_open = 0;
        break;
    case QMessageBox::Discard:
        ui->textEdit->clear();
        flage_open = 0;
        break;
    case QMessageBox::Cancel:
        break;
    default:
        break;
    }
}
