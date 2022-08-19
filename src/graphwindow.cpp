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
    QString procentage[] = {"90%", "80%", "70%", "60%", "50%", "40%", "30%", "20%", "10%", "0%"};
    QPainter painter(&_image);
    painter.setPen(QPen(Qt::black, _penWidthForAxis, Qt::SolidLine));

    for (int i = 1; i < 10; ++i) {
        painter.drawLine(0, _height * 0.1 * i, _width, _height * 0.1 * i);
        painter.drawText(2, _height * 0.1 * i - 5, procentage[i - 1]);
    }
    painter.setPen(QPen(Qt::black, _penWidthForLine, Qt::SolidLine));
    QPoint oldPoint(0, _height);
    const size_t vectorSize = values.size();
    const int dx = _width / vectorSize;
    for (int i = 0; i < vectorSize; ++i) {
        QPoint newPoint(dx * (i + 1), _height * (1.0 - values[i]));
        painter.drawLine(oldPoint.rx(), oldPoint.ry(), newPoint.rx(), newPoint.ry());
        oldPoint = newPoint;
    }
    update();
}

GraphWindow::~GraphWindow()
{
    delete ui;
}
