#include "collegetourpage.h"
#include "ui_collegetourpage.h"

collegetourpage::collegetourpage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::collegetourpage)
{
    ui->setupUi(this);
}

collegetourpage::~collegetourpage()
{
    delete ui;
}
