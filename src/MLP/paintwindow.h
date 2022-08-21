#ifndef PAINTWINDOW_H
#define PAINTWINDOW_H

#include <QImage>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QDialog>
#include <vector>

namespace Ui {
class PaintWindow;
}

class PaintWindow : public QDialog {
  Q_OBJECT

 public:
  explicit PaintWindow(QWidget *parent = nullptr);
  ~PaintWindow();

  QImage& GetImage();

 protected:
  virtual void paintEvent(QPaintEvent *p) override;
  virtual void mouseMoveEvent(QMouseEvent *event) override;
  virtual void mousePressEvent(QMouseEvent *event) override;
  virtual void mouseReleaseEvent(QMouseEvent *event) override;

 private:
  Ui::PaintWindow *ui;
  QPoint _lastPoint;
  QImage _image;
  bool _isLeftButtonPressed = false;
  const int _penWidth = 70;
};

#endif  // PAINTWINDOW_H
