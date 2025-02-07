#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QMainWindow>

class CollegeTourPage;

namespace Ui {
class MainPage;
}

class MainPage : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainPage(QWidget *parent = nullptr);
    ~MainPage();

public slots:
    void on_pushCollegeButton_clicked();

private:
    Ui::MainPage *ui;
    CollegeTourPage *collegeTourPage;
};

#endif // MAINPAGE_H
