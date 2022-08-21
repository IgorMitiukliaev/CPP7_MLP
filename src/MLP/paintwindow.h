#ifndef SRC_MLP_PAINTWINDOW_H_
#define SRC_MLP_PAINTWINDOW_H_

#include <QDialog>
#include <QImage>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <vector>

namespace Ui {
class PaintWindow;
}

class PaintWindow : public QDialog {
    Q_OBJECT

 public:
    explicit PaintWindow(QWidget *parent = nullptr);
    ~PaintWindow();

    QImage &GetImage();

 protected:
    void paintEvent(QPaintEvent *p);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

 private:
    Ui::PaintWindow *ui;
    QPoint _lastPoint;
    QImage _image;
    bool _isLeftButtonPressed = false;
    const int _penWidth = 70;
};

#endif  // SRC_MLP_PAINTWINDOW_H_
