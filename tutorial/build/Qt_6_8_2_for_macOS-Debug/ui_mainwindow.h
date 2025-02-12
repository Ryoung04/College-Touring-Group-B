/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGroupBox *groupBox;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *lineEditUsername;
    QLineEdit *lineEditPassword;
    QPushButton *pushButtonLogin;
    QPushButton *pushButtonCancel;
    QLabel *backgroundImage;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(782, 581);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setStyleSheet(QString::fromUtf8(""));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(120, 190, 541, 231));
        QFont font;
        font.setWeight(QFont::DemiBold);
        groupBox->setFont(font);
        groupBox->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 170, 127);\n"
"border-color: rgb(170, 170, 0);\n"
"color: rgb(0, 0, 0);"));
        label = new QLabel(groupBox);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 60, 131, 41));
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        label->setFont(font1);
        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 100, 131, 41));
        label_2->setFont(font1);
        label_2->setStyleSheet(QString::fromUtf8(""));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(240, 10, 91, 41));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Georgia")});
        font2.setPointSize(17);
        font2.setBold(true);
        font2.setUnderline(false);
        label_3->setFont(font2);
        label_3->setStyleSheet(QString::fromUtf8(""));
        lineEditUsername = new QLineEdit(groupBox);
        lineEditUsername->setObjectName("lineEditUsername");
        lineEditUsername->setGeometry(QRect(110, 70, 251, 24));
        lineEditUsername->setFont(font1);
        lineEditPassword = new QLineEdit(groupBox);
        lineEditPassword->setObjectName("lineEditPassword");
        lineEditPassword->setGeometry(QRect(110, 110, 251, 24));
        lineEditPassword->setFont(font1);
        lineEditPassword->setEchoMode(QLineEdit::EchoMode::Password);
        pushButtonLogin = new QPushButton(groupBox);
        pushButtonLogin->setObjectName("pushButtonLogin");
        pushButtonLogin->setGeometry(QRect(110, 170, 131, 31));
        QFont font3;
        font3.setBold(true);
        pushButtonLogin->setFont(font3);
        pushButtonCancel = new QPushButton(groupBox);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(320, 170, 131, 31));
        pushButtonCancel->setFont(font3);
        backgroundImage = new QLabel(centralwidget);
        backgroundImage->setObjectName("backgroundImage");
        backgroundImage->setGeometry(QRect(-10, 0, 801, 601));
        backgroundImage->setStyleSheet(QString::fromUtf8("background-image: url(:/res/images/students-touring-college-campus.jpeg);"));
        MainWindow->setCentralWidget(centralwidget);
        backgroundImage->raise();
        groupBox->raise();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        groupBox->setTitle(QString());
        label->setText(QCoreApplication::translate("MainWindow", "Username: ", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Password:", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "LOGIN", nullptr));
        lineEditUsername->setText(QString());
        pushButtonLogin->setText(QCoreApplication::translate("MainWindow", "Login", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("MainWindow", "Cancel", nullptr));
        backgroundImage->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
