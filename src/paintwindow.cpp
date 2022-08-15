#include "paintwindow.h"

#include "ui_paintwindow.h"

PaintWindow::PaintWindow(QWidget *parent) : QDialog(parent),
                                            ui(new Ui::PaintWindow),
                                            _image(512, 512, QImage::Format_RGB16) {
    ui->setupUi(this);
    this->setMouseTracking(true);
    this->setWindowTitle("Painter");
    _image.fill(QColor(255, 255, 255));
    update();
}

void PaintWindow::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.drawImage(QPoint(0, 0), _image);
//    update();
}

void PaintWindow::mouseMoveEvent(QMouseEvent *event) {
    if (_isLeftButtonPressed) {
        QPainter painter(&_image);
        painter.setPen(QPen(Qt::black, _penWidth, Qt::SolidLine));
        QPoint newPoint = event->pos();
        painter.drawLine(_lastPoint.x(), _lastPoint.y(), newPoint.x(), newPoint.y());
        _lastPoint = newPoint;
        update();
    }
}

void PaintWindow::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        _isLeftButtonPressed = true;
        _lastPoint = event->pos();
    } else if (event->button() == Qt::RightButton) {
        _image.fill(QColor(255, 255, 255));
    }
}

void PaintWindow::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        _isLeftButtonPressed = false;
    }
}

QImage& PaintWindow::GetImage() {
    return _image;
}

PaintWindow::~PaintWindow() {
    delete ui;
}
