#ifndef HOMETABWIDGET_H
#define HOMETABWIDGET_H

#include <QWidget>
#include <QPaintEvent>

class HomeTabWidget : public QWidget
{
    Q_OBJECT
public:
    explicit HomeTabWidget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QPixmap backgroundImage;
};

#endif // HOMETABWIDGET_H 