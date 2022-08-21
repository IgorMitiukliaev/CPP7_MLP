#ifndef GRAPHWINDOW_H
#define GRAPHWINDOW_H

#include <QDialog>
#include <QImage>
#include <QPaintEvent>
#include <QPainter>
#include <vector>

namespace Ui {
class GraphWindow;
}

class GraphWindow : public QDialog
{
    Q_OBJECT

public:
    explicit GraphWindow(QWidget *parent = nullptr);
    ~GraphWindow();
    auto DrawGraph(std::vector<double> &values) -> void;

protected:
 virtual void paintEvent(QPaintEvent *p) override;

private:
    Ui::GraphWindow *ui;
    QImage _image;
    const int _width = 512;
    const int _height = 512;
    const int _penWidth = 5;
};

#endif // GRAPHWINDOW_H
