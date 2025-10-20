#include "drawingcanvas.h"

DrawingCanvas::DrawingCanvas(QWidget *parent) {
    setMinimumSize(this->WINDOW_WIDTH, this->WINDOW_HEIGHT);
    setStyleSheet("background-color: white; border: 1px solid gray;");
}

void DrawingCanvas::clearPoints() {
    m_points.clear();
    candidateRects.clear();
    update();
}

void DrawingCanvas::paintLines() {
    isPaintLinesClicked = true;
    update();
}

void DrawingCanvas::segmentDetection() {
    if (m_points.isEmpty()) {
        cout << "No drawing detected, skipping detection." << endl;
        return;
    }

    QPixmap pixmap = this->grab();
    QImage image = pixmap.toImage();

    cout << "image width " << image.width() << endl;
    cout << "image height " << image.height() << endl;

    vector<CustomMatrix> windows(image.width() * image.height());
    candidateRects.clear();

    for (int i = 2; i < image.width() - 2; i++) {
        for (int j = 2; j < image.height() - 2; j++) {
            bool local_window[5][5] = {false};

            for (int m = -2; m <= 2; m++) {
                for (int n = -2; n <= 2; n++) {
                    QRgb rgbValue = image.pixel(i + m, j + n);
                    QColor color(rgbValue);

                    int diff = abs(color.red() - 255) + abs(color.green() - 255) + abs(color.blue() - 255);

                    local_window[m + 2][n + 2] = (diff > 80);
                }
            }

            CustomMatrix mat(local_window);

            if (mat.isNonEmpty()) {
                windows.push_back(mat);
                candidateRects.append(QRect(i - 2, j - 2, 5, 5));
            }
        }
    }

    QVector<QRect> mergedRects;
    for (const QRect &r : candidateRects) {
        bool merged = false;
        for (QRect &mr : mergedRects) {
            if (mr.intersects(r)) {
                mr = mr.united(r);
                merged = true;
                break;
            }
        }
        if (!merged) mergedRects.append(r);
    }
    candidateRects = mergedRects;

    cout << "Total detected merged windows: " << candidateRects.size() << endl;
    update();
}

void DrawingCanvas::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QPen purplePen(Qt::magenta, 1);
    purplePen.setStyle(Qt::SolidLine);
    painter.setPen(purplePen);
    painter.setBrush(Qt::NoBrush);
    for (const QRect &rect : candidateRects) {
        painter.drawRect(rect);
    }

    QPen pen(Qt::blue, 5);
    painter.setPen(pen);
    painter.setBrush(QBrush(Qt::blue));
    for (const QPoint &point : std::as_const(m_points)) {
        painter.drawEllipse(point, 3, 3);
    }

    if (isPaintLinesClicked) {
        cout << "paint lines block is called" << endl;
        pen.setColor(Qt::red);
        pen.setWidth(4);
        pen.setStyle(Qt::SolidLine);
        painter.setPen(pen);

        for (int i = 0; i < m_points.size() - 1; i += 2) {
            painter.drawLine(m_points[i], m_points[i + 1]);
        }
        isPaintLinesClicked = false;
    }
}

void DrawingCanvas::mousePressEvent(QMouseEvent *event) {
    m_points.append(event->pos());
    update();
}
