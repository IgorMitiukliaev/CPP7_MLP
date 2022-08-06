#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QFileDialog>
#include <QMainWindow>

#include "controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT
 private:
  s21::Controller *c;

 public:
  MainWindow(s21::Controller *c, QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_btnLoadImage_clicked();

  void on_sizeLayer1_valueChanged(int arg1);

  void on_btnInit_clicked();

  void on_btnLoadDataset_clicked();

private:
  Ui::MainWindow *ui;
};
#endif  // MAINWINDOW_H
