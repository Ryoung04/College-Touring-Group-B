#ifndef COLLEGETOURPAGE_H
#define COLLEGETOURPAGE_H

#include <QMainWindow>
#include "ui_collegeTourPage.h"  // Include the generated UI header file

class CollegeTourPage : public QMainWindow
{
    Q_OBJECT

public:
    explicit CollegeTourPage(QWidget *parent = nullptr);
    ~CollegeTourPage();

private:
    Ui::collegeTourPage *ui;  // Pointer to the UI class
};

#endif // COLLEGETOURPAGE_H
