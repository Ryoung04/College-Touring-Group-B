#include "collegetourpage.h"
#include "ui_collegeTourPage.h"

CollegeTourPage::CollegeTourPage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::collegeTourPage)
{
    ui->setupUi(this);
}

CollegeTourPage::~CollegeTourPage()
{
    delete ui;
}
