/********************************************************************************
** Form generated from reading UI file 'qcheck.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QCHECK_H
#define UI_QCHECK_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_qcheck
{
public:
    QWidget *centralwidget;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QLineEdit *lineEdit;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *qcheck)
    {
        if (qcheck->objectName().isEmpty())
            qcheck->setObjectName("qcheck");
        qcheck->resize(800, 600);
        centralwidget = new QWidget(qcheck);
        centralwidget->setObjectName("centralwidget");
        checkBox = new QCheckBox(centralwidget);
        checkBox->setObjectName("checkBox");
        checkBox->setGeometry(QRect(200, 240, 99, 24));
        checkBox_2 = new QCheckBox(centralwidget);
        checkBox_2->setObjectName("checkBox_2");
        checkBox_2->setGeometry(QRect(200, 290, 99, 24));
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(130, 90, 491, 51));
        qcheck->setCentralWidget(centralwidget);
        menubar = new QMenuBar(qcheck);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 24));
        qcheck->setMenuBar(menubar);
        statusbar = new QStatusBar(qcheck);
        statusbar->setObjectName("statusbar");
        qcheck->setStatusBar(statusbar);

        retranslateUi(qcheck);

        QMetaObject::connectSlotsByName(qcheck);
    } // setupUi

    void retranslateUi(QMainWindow *qcheck)
    {
        qcheck->setWindowTitle(QCoreApplication::translate("qcheck", "qcheck", nullptr));
        checkBox->setText(QCoreApplication::translate("qcheck", "\350\256\260\344\275\217\345\257\206\347\240\201", nullptr));
        checkBox_2->setText(QCoreApplication::translate("qcheck", "\350\207\252\345\212\250\347\231\273\345\275\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class qcheck: public Ui_qcheck {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QCHECK_H
