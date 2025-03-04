#ifndef ANIMATEDBACKGROUND_H
#define ANIMATEDBACKGROUND_H

#include <QWidget>
#include <QTimer>
#include <QVector>
#include <QColor>
#include <QPainterPath>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>

class AnimatedBackground : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(qreal phase READ phase WRITE setPhase)

public:
    explicit AnimatedBackground(QWidget *parent = nullptr);
    ~AnimatedBackground();

    // Set color scheme
    void setColors(const QVector<QColor>& colors);
    
    // Control animation
    void startAnimation();
    void stopAnimation();
    
    // Property accessors
    qreal phase() const { return m_phase; }
    void setPhase(qreal phase);

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    void initializeAnimations();
    void createWavePaths();

    QVector<QColor> m_colors;
    QVector<QPainterPath> m_wavePaths;
    QParallelAnimationGroup* m_animationGroup;
    QPropertyAnimation* m_phaseAnimation;
    
    qreal m_phase;
    int m_waveCount;
    
    // Animation defaults
    static constexpr int ANIMATION_DURATION = 15000; // 15 seconds per cycle
    static constexpr int WAVE_COUNT = 5;
};

#endif // ANIMATEDBACKGROUND_H 