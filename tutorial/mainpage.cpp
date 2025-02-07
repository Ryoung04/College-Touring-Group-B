#include "mainpage.h"
#include "ui_mainpage.h"
#include "collegetourpage.h"

MainPage::MainPage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainPage)
    , collegeTourPage(nullptr)  // Initialize pointer
{
    ui->setupUi(this);
}

MainPage::~MainPage()
{
    delete ui;
}

void MainPage::on_pushCollegeButton_clicked()
{
    this->hide();  // Hide the current page

    if (!collegeTourPage) {
        collegeTourPage = new CollegeTourPage(this);
    }

    collegeTourPage->show();
}
