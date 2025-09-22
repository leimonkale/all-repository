#ifndef PHOTO_H
#define PHOTO_H

#include <QMainWindow>
#include <QMovie>
QT_BEGIN_NAMESPACE
namespace Ui {
class photo;
}
QT_END_NAMESPACE

class photo : public QMainWindow
{
    Q_OBJECT

public:
    photo(QWidget *parent = nullptr);
    ~photo();

private:
    Ui::photo *ui;

    QMovie *movie;
};
#endif // PHOTO_H
