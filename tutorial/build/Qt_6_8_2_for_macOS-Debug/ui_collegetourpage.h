/********************************************************************************
** Form generated from reading UI file 'collegetourpage.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COLLEGETOURPAGE_H
#define UI_COLLEGETOURPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_collegetourpage
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *collegetourpage)
    {
        if (collegetourpage->objectName().isEmpty())
            collegetourpage->setObjectName("collegetourpage");
        collegetourpage->resize(800, 600);
        centralwidget = new QWidget(collegetourpage);
        centralwidget->setObjectName("centralwidget");
        collegetourpage->setCentralWidget(centralwidget);
        menubar = new QMenuBar(collegetourpage);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 37));
        collegetourpage->setMenuBar(menubar);
        statusbar = new QStatusBar(collegetourpage);
        statusbar->setObjectName("statusbar");
        collegetourpage->setStatusBar(statusbar);

        retranslateUi(collegetourpage);

        QMetaObject::connectSlotsByName(collegetourpage);
    } // setupUi

    void retranslateUi(QMainWindow *collegetourpage)
    {
        collegetourpage->setWindowTitle(QCoreApplication::translate("collegetourpage", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class collegetourpage: public Ui_collegetourpage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COLLEGETOURPAGE_H
