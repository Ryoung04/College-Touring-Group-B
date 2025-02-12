#include "loginwindow.h"
#include <QMessageBox>

LoginWindow::LoginWindow(QWidget *parent)
    : QWidget(parent)
    , isSignUpMode(false)
{
    auto layout = new QVBoxLayout(this);

    auto titleLabel = new QLabel("College Distance Finder", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(16);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);

    emailInput = new QLineEdit(this);
    emailInput->setPlaceholderText("Email");

    passwordInput = new QLineEdit(this);
    passwordInput->setPlaceholderText("Password");
    passwordInput->setEchoMode(QLineEdit::Password);

    confirmPasswordInput = new QLineEdit(this);
    confirmPasswordInput->setPlaceholderText("Confirm Password");
    confirmPasswordInput->setEchoMode(QLineEdit::Password);
    confirmPasswordInput->hide();

    submitButton = new QPushButton("Sign In", this);
    toggleButton = new QPushButton("Don't have an account? Sign Up", this);

    errorLabel = new QLabel(this);
    errorLabel->setStyleSheet("color: red;");
    errorLabel->hide();

    layout->addWidget(titleLabel);
    layout->addWidget(emailInput);
    layout->addWidget(passwordInput);
    layout->addWidget(confirmPasswordInput);
    layout->addWidget(errorLabel);
    layout->addWidget(submitButton);
    layout->addWidget(toggleButton);

    layout->setAlignment(Qt::AlignCenter);
    setLayout(layout);

    connect(submitButton, &QPushButton::clicked, this, &LoginWindow::onLoginClicked);
    connect(toggleButton, &QPushButton::clicked, this, &LoginWindow::toggleSignUp);
}

void LoginWindow::clearFields()
{
    emailInput->clear();
    passwordInput->clear();
    confirmPasswordInput->clear();
    errorLabel->hide();
}

void LoginWindow::onLoginClicked()
{
    QString email = emailInput->text();
    QString password = passwordInput->text();

    if (email.isEmpty() || password.isEmpty()) {
        errorLabel->setText("Please fill in all fields");
        errorLabel->show();
        return;
    }

    if (isSignUpMode) {
        if (password != confirmPasswordInput->text()) {
            errorLabel->setText("Passwords do not match");
            errorLabel->show();
            return;
        }
        // In a real app, you would create the account here
    }

    // For demo purposes, accept any non-empty email/password
    emit loginSuccess();
}

void LoginWindow::toggleSignUp()
{
    isSignUpMode = !isSignUpMode;
    confirmPasswordInput->setVisible(isSignUpMode);
    submitButton->setText(isSignUpMode ? "Sign Up" : "Sign In");
    toggleButton->setText(isSignUpMode ?
                              "Already have an account? Sign In" :
                              "Don't have an account? Sign Up");
}
