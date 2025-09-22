/********************************************************************************
** Form generated from reading UI file 'photo.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PHOTO_H
#define UI_PHOTO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_photo
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QLabel *label_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *photo)
    {
        if (photo->objectName().isEmpty())
            photo->setObjectName("photo");
        photo->resize(889, 442);
        photo->setStyleSheet(QString::fromUtf8("background-image: url(:/1.png);"));
        centralwidget = new QWidget(photo);
        centralwidget->setObjectName("centralwidget");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(330, -10, 511, 271));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(130, 100, 131, 131));
        photo->setCentralWidget(centralwidget);
        menubar = new QMenuBar(photo);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 889, 20));
        photo->setMenuBar(menubar);
        statusbar = new QStatusBar(photo);
        statusbar->setObjectName("statusbar");
        photo->setStatusBar(statusbar);

        retranslateUi(photo);

        QMetaObject::connectSlotsByName(photo);
    } // setupUi

    void retranslateUi(QMainWindow *photo)
    {
        photo->setWindowTitle(QCoreApplication::translate("photo", "photo", nullptr));
        label->setText(QString());
        label_2->setText(QCoreApplication::translate("photo", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class photo: public Ui_photo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PHOTO_H
