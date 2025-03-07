#ifndef ANIMATEDBACKGROUND_H
#define ANIMATEDBACKGROUND_H

#include <QWidget>
#include <QColor>
#include <QList>
#include <QPropertyAnimation>
#include <QTimer>
#include <QPainter>

class AnimatedBackground : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor currentColor READ currentColor WRITE setCurrentColor)

public:
    explicit AnimatedBackground(QWidget *parent = nullptr);
    ~AnimatedBackground();

    void setColors(const QList<QColor>& colors);
    void startAnimation();
    void stopAnimation();
    QColor currentColor() const;
    void setCurrentColor(const QColor& color);

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    QList<QColor> m_colors;
    QColor m_currentColor;
    QPropertyAnimation* m_animation;
    int m_currentIndex;
    QTimer* m_timer;
    
    void setupAnimation();
    void nextColor();
};

#endif // ANIMATEDBACKGROUND_H 