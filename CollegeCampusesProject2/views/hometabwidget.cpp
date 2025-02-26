#include "hometabwidget.h"
#include <QPainter>

HomeTabWidget::HomeTabWidget(QWidget *parent)
    : QWidget(parent)
{
    backgroundImage = QPixmap(":/images/background.jpg");
}

void HomeTabWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(rect(), backgroundImage.scaled(size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
    QWidget::paintEvent(event);
} 