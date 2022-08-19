#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QDebug>
#include <QFileDialog>
#include <QLabel>
#include <QMainWindow>
#include <QPixmap>
#include <QProgressBar>
#include <QRegularExpression>
#include <iostream>
#include <ctime>

#include "controller.h"
#include "paintwindow.h"
#include "graphwindow.h"

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
  GraphWindow *_graphWindow;
  
  s21::Controller *_controller;
  long num_images = 0, num_curr_image = 0;
  std::vector<double> _vectorPixels;
  QImage _graphics_view_image;
  const int _countNeurons = 28;

  void drawPreview(int img_num = 0);
  void updatePreviewLabel();
  void updateBatchLabel();
  void UpdateMLPState();
  bool enableButtons();
  void UpdateConfigurationView();
  void UpdateAnswerLabel();
  void CreateVectorPixels(QImage &image);
  void GraphicsViewUpdate(QImage &image);
  // методы для исследования
  auto ResearchInitGraphPerceptron() -> void;
  auto ResearchInitMatrixPerceptron() -> void;
  auto ResearchTestingTime(const int count) -> double;

 public:
  MainWindow(s21::Controller *c, QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_btnSaveNetworkConfiguration_clicked();
  void on_btnLoadNetworkConfiguration_clicked();
  void on_btnLoadImage_clicked();
  void on_btnLoadDataset_clicked();
  void on_btnImgUp_clicked();
  void on_pushButton_draw_clicked();
  void on_pushButton_8_clicked();
  void on_btnInit_clicked();
  void on_btnStartLearn_clicked();
  void on_valEpochNum_valueChanged(int arg1);
  void on_valBatchNum_valueChanged(int arg1);
  void on_tabWidget_tabBarClicked(int index);
  void on_progressChanged_(int value, int value2);
  void on_CreateGraph_clicked();
  void on_btnLoadImage_2_clicked();
  void on_btnLoadImage_2_clicked(bool checked);
  void on_pushButton_clicked();
  void on_pushButtonResearch_clicked();
  void on_pushClerLearn_clicked();
};
#endif  // MAINWINDOW_H
