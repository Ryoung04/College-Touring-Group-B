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
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginWindow
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *titleLabel;
    QLineEdit *emailInput;
    QLineEdit *passwordInput;
    QLineEdit *confirmPasswordInput;
    QLabel *errorLabel;
    QPushButton *submitButton;
    QPushButton *toggleButton;

    void setupUi(QWidget *LoginWindow)
    {
        if (LoginWindow->objectName().isEmpty())
            LoginWindow->setObjectName("LoginWindow");
        LoginWindow->resize(400, 300);
        verticalLayout = new QVBoxLayout(LoginWindow);
        verticalLayout->setObjectName("verticalLayout");
        titleLabel = new QLabel(LoginWindow);
        titleLabel->setObjectName("titleLabel");
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        titleLabel->setFont(font);
        titleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(titleLabel);

        emailInput = new QLineEdit(LoginWindow);
        emailInput->setObjectName("emailInput");

        verticalLayout->addWidget(emailInput);

        passwordInput = new QLineEdit(LoginWindow);
        passwordInput->setObjectName("passwordInput");
        passwordInput->setEchoMode(QLineEdit::Password);

        verticalLayout->addWidget(passwordInput);

        confirmPasswordInput = new QLineEdit(LoginWindow);
        confirmPasswordInput->setObjectName("confirmPasswordInput");
        confirmPasswordInput->setEchoMode(QLineEdit::Password);

        verticalLayout->addWidget(confirmPasswordInput);

        errorLabel = new QLabel(LoginWindow);
        errorLabel->setObjectName("errorLabel");
        errorLabel->setStyleSheet(QString::fromUtf8("color: red;"));

        verticalLayout->addWidget(errorLabel);

        submitButton = new QPushButton(LoginWindow);
        submitButton->setObjectName("submitButton");

        verticalLayout->addWidget(submitButton);

        toggleButton = new QPushButton(LoginWindow);
        toggleButton->setObjectName("toggleButton");
        toggleButton->setFlat(true);

        verticalLayout->addWidget(toggleButton);


        retranslateUi(LoginWindow);

        QMetaObject::connectSlotsByName(LoginWindow);
    } // setupUi

    void retranslateUi(QWidget *LoginWindow)
    {
        LoginWindow->setWindowTitle(QCoreApplication::translate("LoginWindow", "Login", nullptr));
        titleLabel->setText(QCoreApplication::translate("LoginWindow", "College Distance Finder", nullptr));
        emailInput->setPlaceholderText(QCoreApplication::translate("LoginWindow", "Email", nullptr));
        passwordInput->setPlaceholderText(QCoreApplication::translate("LoginWindow", "Password", nullptr));
        confirmPasswordInput->setPlaceholderText(QCoreApplication::translate("LoginWindow", "Confirm Password", nullptr));
        errorLabel->setText(QString());
        submitButton->setText(QCoreApplication::translate("LoginWindow", "Sign In", nullptr));
        toggleButton->setText(QCoreApplication::translate("LoginWindow", "Don't have an account? Sign Up", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginWindow: public Ui_LoginWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWINDOW_H
