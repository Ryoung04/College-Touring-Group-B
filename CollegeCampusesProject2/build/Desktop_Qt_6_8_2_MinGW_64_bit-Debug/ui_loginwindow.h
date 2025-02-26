/********************************************************************************
** Form generated from reading UI file 'loginwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINWINDOW_H
#define UI_LOGINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_LoginWindow
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *usernameInput;
    QLabel *label_2;
    QLineEdit *passwordInput;
    QHBoxLayout *horizontalLayout;
    QPushButton *loginButton;
    QPushButton *registerButton;

    void setupUi(QDialog *LoginWindow)
    {
        if (LoginWindow->objectName().isEmpty())
            LoginWindow->setObjectName("LoginWindow");
        LoginWindow->resize(400, 200);
        verticalLayout = new QVBoxLayout(LoginWindow);
        verticalLayout->setObjectName("verticalLayout");
        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        label = new QLabel(LoginWindow);
        label->setObjectName("label");

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        usernameInput = new QLineEdit(LoginWindow);
        usernameInput->setObjectName("usernameInput");

        formLayout->setWidget(0, QFormLayout::FieldRole, usernameInput);

        label_2 = new QLabel(LoginWindow);
        label_2->setObjectName("label_2");

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        passwordInput = new QLineEdit(LoginWindow);
        passwordInput->setObjectName("passwordInput");
        passwordInput->setEchoMode(QLineEdit::Password);

        formLayout->setWidget(1, QFormLayout::FieldRole, passwordInput);


        verticalLayout->addLayout(formLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        loginButton = new QPushButton(LoginWindow);
        loginButton->setObjectName("loginButton");

        horizontalLayout->addWidget(loginButton);

        registerButton = new QPushButton(LoginWindow);
        registerButton->setObjectName("registerButton");

        horizontalLayout->addWidget(registerButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(LoginWindow);

        QMetaObject::connectSlotsByName(LoginWindow);
    } // setupUi

    void retranslateUi(QDialog *LoginWindow)
    {
        LoginWindow->setWindowTitle(QCoreApplication::translate("LoginWindow", "Login", nullptr));
        label->setText(QCoreApplication::translate("LoginWindow", "Username:", nullptr));
        label_2->setText(QCoreApplication::translate("LoginWindow", "Password:", nullptr));
        loginButton->setText(QCoreApplication::translate("LoginWindow", "Login", nullptr));
        registerButton->setText(QCoreApplication::translate("LoginWindow", "Register", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginWindow: public Ui_LoginWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWINDOW_H
