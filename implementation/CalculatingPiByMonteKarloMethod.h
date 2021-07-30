#pragma once
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QLabel>

class CalculatingPiByMonteKarloMethod : public QWidget
{
    Q_OBJECT
private:
    struct IterationData
    {
        qreal _circleRadius;
        quint64 _amountOfPoints;
        quint32 _animationDurationMillisecons;

        const qint16 _timerDuration = 1500;
        qint32 _timerId;

        quint64 _currentAmountOfPointInCircle = 0;
        quint64 _currentAmountOfPointInRect = 0;
    };

    QSharedPointer<IterationData> _currentIterationData;

    QGraphicsScene* _sceneObject;
    QGraphicsView* _viewWindow;

    QLabel* _amountOfFilledPoints;
    QLabel* _amountOfPointsInCircle;
    QLabel* _currentPiValue;

public:
    explicit CalculatingPiByMonteKarloMethod(QWidget *parent = nullptr);

public slots:
    void startAnimation(qreal circleRadius, quint64 amountOfPoints, quint32 animationDurationMillisecons);
    void stopAnimation();

protected slots:
    virtual void timerEvent(QTimerEvent*) override;
};

