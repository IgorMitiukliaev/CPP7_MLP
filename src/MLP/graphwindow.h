#ifndef SRC_MLP_GRAPHWINDOW_H_
#define SRC_MLP_GRAPHWINDOW_H_

#include <QDialog>
#include <QImage>
#include <QPaintEvent>
#include <QPainter>
#include <vector>

namespace Ui {
class GraphWindow;
}

class GraphWindow : public QDialog {
    Q_OBJECT

 public:
    explicit GraphWindow(QWidget *parent = nullptr);
    ~GraphWindow();
    auto DrawGraph(std::vector<double> &values) -> void;

 protected:
    void paintEvent(QPaintEvent *p);

 private:
    Ui::GraphWindow *ui;
    QImage _image;
    const int _width = 512;
    const int _height = 512;
    const int _penWidthForAxis = 1;
    const int _penWidthForLine = 2;

};

#endif  // SRC_MLP_GRAPHWINDOW_H_
