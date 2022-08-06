#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QFileDialog>
#include <QMainWindow>
#include <QPixmap>

#include "controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT
 private:
  Ui::MainWindow *ui;
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
  void on_btnInit_clicked();
  void on_btnLoadDataset_clicked();
  void on_inpNumCurrImg_textChanged(const QString &arg1);
};
#endif  // MAINWINDOW_H
