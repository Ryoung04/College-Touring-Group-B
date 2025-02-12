#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    void clearFields();

signals:
    void loginSuccess();

private slots:
    void onLoginClicked();
    void toggleSignUp();

private:
    QLineEdit* emailInput;
    QLineEdit* passwordInput;
    QLineEdit* confirmPasswordInput;
    QPushButton* submitButton;
    QPushButton* toggleButton;
    QLabel* errorLabel;
    bool isSignUpMode;
};
