/********************************************************************************
** Form generated from reading UI file 'mainpage.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINPAGE_H
#define UI_MAINPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainPage
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QLabel *backgroundImage;

    void setupUi(QMainWindow *MainPage)
    {
        if (MainPage->objectName().isEmpty())
            MainPage->setObjectName("MainPage");
        MainPage->resize(798, 603);
        MainPage->setAutoFillBackground(false);
        MainPage->setStyleSheet(QString::fromUtf8("QMainWindow\n"
"{\n"
"	background-color:rgb(52,50,64);\n"
"}"));
        centralwidget = new QWidget(MainPage);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setStyleSheet(QString::fromUtf8(""));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 20, 391, 61));
        QFont font;
        font.setFamilies({QString::fromUtf8("Cascadia Code")});
        font.setPointSize(21);
        font.setBold(true);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"	background-color: rgb(170, 170, 127);\n"
"	\n"
"	color: rgb(0, 0, 0);\n"
"}"));
        backgroundImage = new QLabel(centralwidget);
        backgroundImage->setObjectName("backgroundImage");
        backgroundImage->setGeometry(QRect(0, 0, 801, 611));
        backgroundImage->setStyleSheet(QString::fromUtf8("background-image: url(:/res/images/students-touring-college-campus.jpeg);"));
        MainPage->setCentralWidget(centralwidget);
        backgroundImage->raise();
        label->raise();

        retranslateUi(MainPage);

        QMetaObject::connectSlotsByName(MainPage);
    } // setupUi

    void retranslateUi(QMainWindow *MainPage)
    {
        MainPage->setWindowTitle(QCoreApplication::translate("MainPage", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainPage", " College Campus Touring", nullptr));
        backgroundImage->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainPage: public Ui_MainPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINPAGE_H
