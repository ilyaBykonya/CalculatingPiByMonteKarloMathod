#include "CalculatingPiByMonteKarloMethod.h"

CalculatingPiByMonteKarloMethod::CalculatingPiByMonteKarloMethod(QWidget *parent)
    :QWidget{ parent },
     _currentIterationData{ nullptr },
     _sceneObject{ new QGraphicsScene(this) },
     _viewWindow{ new QGraphicsView(_sceneObject) },
     _amountOfFilledPoints{ new QLabel("0") },
     _amountOfPointsInCircle{ new QLabel("0") },
     _currentPiValue{ new QLabel("0") }
    {
        //==================================
        QGroupBox* currentPiValueGroupBox = new QGroupBox;
        currentPiValueGroupBox->setTitle("Current Pi:");
            QHBoxLayout* currentPiValueLayout = new QHBoxLayout;
            currentPiValueLayout->addWidget(_currentPiValue, 1);
        currentPiValueGroupBox->setLayout(currentPiValueLayout);
        //==================================
        QGroupBox* currentPointsInCircleGroupBox = new QGroupBox;
        currentPointsInCircleGroupBox->setTitle("Points in circle:");
            QHBoxLayout* currentPointsInCircleLayout = new QHBoxLayout;
            currentPointsInCircleLayout->addWidget(_amountOfPointsInCircle, 1);
        currentPointsInCircleGroupBox->setLayout(currentPointsInCircleLayout);
        //==================================
        QGroupBox* currentFilledPointsGroupBox = new QGroupBox;
        currentFilledPointsGroupBox->setTitle("Filled points:");
            QHBoxLayout* currentFilledPointsLayout = new QHBoxLayout;
            currentFilledPointsLayout->addWidget(_amountOfFilledPoints, 1);
        currentFilledPointsGroupBox->setLayout(currentFilledPointsLayout);
        //==================================
        QVBoxLayout* leftInfoPanelLayout = new QVBoxLayout;
        leftInfoPanelLayout->setSpacing(4);
            leftInfoPanelLayout->addWidget(currentPiValueGroupBox, 0);
            leftInfoPanelLayout->addWidget(currentPointsInCircleGroupBox, 0);
            leftInfoPanelLayout->addWidget(currentFilledPointsGroupBox, 0);
            leftInfoPanelLayout->addStretch(1);
        //==================================
        QHBoxLayout* windowLayout = new QHBoxLayout;
        this->setLayout(windowLayout);
            windowLayout->addLayout(leftInfoPanelLayout, 0);
            windowLayout->addWidget(_viewWindow, 1);
        //==================================
    }

void CalculatingPiByMonteKarloMethod::startAnimation(qreal circleRadius, quint64 amountOfPoints, quint32 animationDurationMillisecons)
{
    _sceneObject->clear();
    _currentIterationData = QSharedPointer<IterationData>(new IterationData);
    _currentIterationData->_amountOfPoints = amountOfPoints;
    _currentIterationData->_circleRadius = circleRadius;
    _currentIterationData->_animationDurationMillisecons = animationDurationMillisecons;

    _sceneObject->setSceneRect(QRectF{ -circleRadius - 20, -circleRadius - 20, circleRadius * 2 + 20, circleRadius * 2 + 20 });
    _viewWindow->setFixedSize(QSizeF{ circleRadius * 2 + 40, circleRadius * 2 + 40 }.toSize());

    _sceneObject->addRect(QRectF{ -circleRadius, -circleRadius, circleRadius * 2, circleRadius * 2 });
    _sceneObject->addEllipse(QRectF{ -circleRadius, -circleRadius, circleRadius * 2, circleRadius * 2 });

    _currentIterationData->_timerId = startTimer(_currentIterationData->_timerDuration);
}
void CalculatingPiByMonteKarloMethod::stopAnimation()
{
    if(!_currentIterationData)
        return;

    killTimer(_currentIterationData->_timerId);
    _currentIterationData = nullptr;
}

void CalculatingPiByMonteKarloMethod::timerEvent(QTimerEvent*)
{
    if(!_currentIterationData)
        return;

    int amountOfIterations = _currentIterationData->_animationDurationMillisecons / _currentIterationData->_timerDuration;
    if(amountOfIterations == 0)
        amountOfIterations = 1;

    quint32 pointOnIteration = _currentIterationData->_amountOfPoints / amountOfIterations;

    for(quint32 i = 0; i < pointOnIteration && _currentIterationData->_currentAmountOfPointInRect < _currentIterationData->_amountOfPoints; ++i, ++_currentIterationData->_currentAmountOfPointInRect)
    {
        QPointF currentPoint;
        currentPoint.rx() = -_currentIterationData->_circleRadius + static_cast<qreal>(rand()) / RAND_MAX * _currentIterationData->_circleRadius * 2;
        currentPoint.ry() = -_currentIterationData->_circleRadius + static_cast<qreal>(rand()) / RAND_MAX * _currentIterationData->_circleRadius * 2;
        if(currentPoint.x() * currentPoint.x() + currentPoint.y() * currentPoint.y() <= _currentIterationData->_circleRadius * _currentIterationData->_circleRadius) {
            _sceneObject->addEllipse(QRectF{ currentPoint.x(), currentPoint.y(), 1, 1 }, QPen(QBrush(QColor(0, 255, 0)), 1));
            ++_currentIterationData->_currentAmountOfPointInCircle;
        } else {
            _sceneObject->addEllipse(QRectF{ currentPoint.x(), currentPoint.y(), 1, 1 }, QPen(QBrush(QColor(255, 0, 0)), 1));
        }
    }

    _currentPiValue->setText(QString::number(4.0 * _currentIterationData->_currentAmountOfPointInCircle / _currentIterationData->_currentAmountOfPointInRect));
    _amountOfFilledPoints->setText(QString::number(_currentIterationData->_currentAmountOfPointInRect));
    _amountOfPointsInCircle->setText(QString::number(_currentIterationData->_currentAmountOfPointInCircle));

    if(_currentIterationData->_currentAmountOfPointInRect >= _currentIterationData->_amountOfPoints) {
        this->stopAnimation();
    }
}
























