#ifndef TV_H
#define TV_H

#include <QMainWindow>
#include <QMovie>
#include <QMediaPlayer>

QT_BEGIN_NAMESPACE
namespace Ui {
class TV;
}
QT_END_NAMESPACE

class TV : public QMainWindow
{
    Q_OBJECT

public:
    TV(QWidget *parent = nullptr);
    ~TV();

private slots:



    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    //void on_pushButton_4_clicked();

private:
    Ui::TV *ui;

    int flag=0;
    QMetaObject::Connection *conn;
    QMovie *movie;
};
#endif // TV_H
