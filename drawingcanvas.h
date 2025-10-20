#ifndef DRAWINGCANVAS_H
#define DRAWINGCANVAS_H

#include <QWidget>
#include <QVector>
#include <QPoint>
#include <QPainter>
#include <QMouseEvent>
#include <iostream>
#include <iomanip>
#include <QPixmap>
#include <QColor>
#include "CustomMatrix.h"

using namespace std;

class DrawingCanvas : public QWidget
{
    Q_OBJECT
private:
    const int WINDOW_WIDTH = 600;
    const int WINDOW_HEIGHT = 400;

public:
    explicit DrawingCanvas(QWidget *parent = nullptr);

    void clearPoints();
    void paintLines();
    void segmentDetection();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    QVector<QPoint> m_points;
    QVector<QRect> candidateRects;
    bool isPaintLinesClicked = false;
};

#endif // DRAWINGCANVAS_H
