#include "graphwindow.h"
#include "ui_graphwindow.h"

GraphWindow::GraphWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GraphWindow),
    _image(512, 512, QImage::Format_RGB16)
{
    ui->setupUi(this);
    this->setWindowTitle("Graph");
    _image.fill(QColor(255, 255, 255));
    update();
}

void GraphWindow::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.drawImage(QPoint(0, 0), _image);
//    update();
}

auto GraphWindow::DrawGraph(std::vector<double> &values) -> void {
    QPainter painter(&_image);
    painter.setPen(QPen(Qt::black, _penWidth, Qt::SolidLine));

    painter.drawLine(0, _height * 0.5f, _width, _height * 0.5f);
    painter.drawLine(_width * 0.5f, 0, _width * 0.5f, _height);
    // painter.drawLine(_lastPoint.x(), _lastPoint.y(), newPoint.x(), newPoint.y());
    update();
}

GraphWindow::~GraphWindow()
{
    delete ui;
}
