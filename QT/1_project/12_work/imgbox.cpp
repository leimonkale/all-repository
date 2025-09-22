#include "imgbox.h"
#include "ui_imgbox.h"

imgbox::imgbox(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::imgbox)
{
    ui->setupUi(this);
}

imgbox::~imgbox()
{
    delete ui;
}

#include <QDebug>
#include <QFileDialog>

void imgbox::on_pushButton_2_clicked()
{
    QFileDialog::getOpenFileNames(this, "文件", "C:", "所有文件(*);;图片(*.jpg *.png *.gif)");
    // 参数1：父对象 参数2：对话框的标题 参数3：对话框的工作路径 参数：筛选器选项
    QStringList files = QFileDialog::getOpenFileNames();
    if(files.isEmpty()){
        return;
    }
    qDebug() << files;

    foreach (QString file, files) {
        QListWidgetItem* item1 = new QListWidgetItem;
        ui->listWidget->setIconSize(QSize(120, 160));
        item1->setIcon(QIcon(file)); // 设置图标，注意路径正确
        item1->setData(Qt::UserRole, file);
        ui->listWidget->addItem(item1);
    }




}

// void Widget::on_pushButton_2_clicked()
// {
//     // 参数1: 父对象 参数2: 对话框的标题 参数3: 对话框的工作路径 参数: 筛选器选项
//     files = QFileDialog::getOpenFileNames(this, "文件", "C:", "所有文件(*);;图片(*.jpg *.png *.gif)");
//     if(files.isEmpty())
//         return;

//     currentIndex = 0;
//     img_show(files[currentIndex]);

//     foreach (QString file, files) {
//         QListWidgetItem *item = new QListWidgetItem;
//         item->setIcon(QIcon(file));
//     }
// }
// void Widget::on_pushButton_3_clicked()
// {
//     if(files.isEmpty())
//         return;
//     if(currentIndex == files.size() - 1)
//         QMessageBox::warning(this, "警告", "已是最后一张图片");
//     else
//         img_show(files[++currentIndex]);
// }

// void Widget::img_show(QString filename)
// {
//     if(movie->state() == QMovie::Running)
//         movie->stop();
//     if(filename.split(".").last() == "gif"){
//         movie->setFileName(filename);
//         ui->label->setMovie(movie);
//         movie->start();
//     } else {
//         ui->label->setPixmap(QPixmap(filename));
//     }
// }
// #include <QDebug>
// void Widget::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
// {
//     //获得当前被双击项的行号
//     int row1 = item->listWidget()->currentRow();
//     int row2 = ui->listWidget->row(item);
//     int row3 = ui->listWidget->currentRow();

//     qDebug() << row1 << row2 << row3;
//     currentIndex = row1;
//     img_show(files[currentIndex]);
// }

void imgbox::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    ui->label_2->setPixmap(QPixmap(item->data(Qt::UserRole).toString()));
    ui->label_2->setScaledContents(true);
}

