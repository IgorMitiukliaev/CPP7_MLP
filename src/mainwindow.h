#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QFileDialog>
#include <QMainWindow>
#include <QPixmap>

#include "paintwindow.h"
#include "controller.h"

#include <iostream>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}  // namespace Ui
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT
 private:
  Ui::MainWindow *ui;
  PaintWindow *paintWindow;
  s21::Controller *c;
  qint16 num_images = 0, num_curr_image = 0;
  void drawPreview(int img_num = 0);
  void on_Data_Loaded();
  void updatePreviewLabel();

 public:
  MainWindow(s21::Controller *c, QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_btnLoadImage_clicked();
  void on_sizeLayer1_valueChanged(int arg1);
  void on_btnInit_clicked(s21::initConfig config);
  void on_btnLoadDataset_clicked();
  void on_inpNumCurrImg_textChanged(const QString &arg1);
  void on_btnImgUp_clicked();
  void on_pushButton_draw_clicked();
  void on_pushButton_8_clicked();
};
#endif  // MAINWINDOW_H
