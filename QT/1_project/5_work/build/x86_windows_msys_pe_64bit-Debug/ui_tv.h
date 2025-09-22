/********************************************************************************
** Form generated from reading UI file 'tv.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TV_H
#define UI_TV_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TV
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QLabel *label_2;
    QPushButton *pushButton;
    QLineEdit *lineEdit_2;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *TV)
    {
        if (TV->objectName().isEmpty())
            TV->setObjectName("TV");
        TV->resize(800, 600);
        centralwidget = new QWidget(TV);
        centralwidget->setObjectName("centralwidget");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 20, 731, 491));
        label->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(50, 40, 691, 411));
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(255, 255, 255);"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(350, 460, 121, 41));
        pushButton->setStyleSheet(QString::fromUtf8("font: 700 14pt \"Microsoft YaHei UI\";"));
        lineEdit_2 = new QLineEdit(centralwidget);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setGeometry(QRect(50, 460, 291, 41));
        lineEdit_2->setStyleSheet(QString::fromUtf8("font: 700 16pt \"Microsoft YaHei UI\";"));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(480, 460, 121, 41));
        pushButton_2->setStyleSheet(QString::fromUtf8("font: 700 14pt \"Microsoft YaHei UI\";"));
        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(610, 460, 131, 41));
        pushButton_3->setStyleSheet(QString::fromUtf8("font: 700 14pt \"Microsoft YaHei UI\";"));
        pushButton_4 = new QPushButton(centralwidget);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(30, 520, 99, 28));
        TV->setCentralWidget(centralwidget);
        menubar = new QMenuBar(TV);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 24));
        TV->setMenuBar(menubar);
        statusbar = new QStatusBar(TV);
        statusbar->setObjectName("statusbar");
        TV->setStatusBar(statusbar);

        retranslateUi(TV);

        QMetaObject::connectSlotsByName(TV);
    } // setupUi

    void retranslateUi(QMainWindow *TV)
    {
        TV->setWindowTitle(QCoreApplication::translate("TV", "TV", nullptr));
        label->setText(QString());
        label_2->setText(QCoreApplication::translate("TV", "TextLabel", nullptr));
        pushButton->setText(QCoreApplication::translate("TV", "show", nullptr));
        lineEdit_2->setText(QString());
        lineEdit_2->setPlaceholderText(QCoreApplication::translate("TV", "\350\257\267\350\276\223\345\205\245\346\226\207\344\273\266", nullptr));
        pushButton_2->setText(QCoreApplication::translate("TV", "open", nullptr));
        pushButton_3->setText(QCoreApplication::translate("TV", "stop", nullptr));
        pushButton_4->setText(QCoreApplication::translate("TV", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TV: public Ui_TV {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TV_H
