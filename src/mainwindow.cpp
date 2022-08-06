#include "mainwindow.h"

#include "./ui_mainwindow.h"

using s21::Controller;

MainWindow::MainWindow(s21::Controller *controller, QWidget *parent)
    : c(controller), QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_btnLoadImage_clicked() {
  qDebug() << "clicked";
  QFileDialog dialog(this);
  dialog.setFileMode(QFileDialog::ExistingFile);
  QString fileName = dialog.getOpenFileName(this, tr("Open File"), "/home",
                                            tr("Images (*.bmp)"));
  qDebug() << fileName;
}

void MainWindow::on_sizeLayer1_valueChanged(int arg1) {
  qDebug() << arg1;
  if (arg1 < 3) {
    ui->sizeLayer3->setDisabled(true);
    ui->sizeLayer4->setDisabled(true);
    ui->sizeLayer5->setDisabled(true);
    ui->lblLayer3->setDisabled(true);
    ui->lblLayer4->setDisabled(true);
    ui->lblLayer5->setDisabled(true);
  } else if (arg1 == 3) {
    ui->sizeLayer3->setDisabled(false);
    ui->sizeLayer4->setDisabled(true);
    ui->sizeLayer5->setDisabled(true);
    ui->lblLayer3->setDisabled(false);
    ui->lblLayer4->setDisabled(true);
    ui->lblLayer5->setDisabled(true);
  } else if (arg1 == 4) {
    ui->sizeLayer3->setDisabled(false);
    ui->sizeLayer4->setDisabled(false);
    ui->sizeLayer5->setDisabled(true);
    ui->lblLayer3->setDisabled(false);
    ui->lblLayer4->setDisabled(false);
    ui->lblLayer5->setDisabled(true);
  } else if (arg1 == 5) {
    ui->sizeLayer3->setDisabled(false);
    ui->sizeLayer4->setDisabled(false);
    ui->sizeLayer5->setDisabled(false);
    ui->lblLayer3->setDisabled(false);
    ui->lblLayer4->setDisabled(false);
    ui->lblLayer5->setDisabled(false);
  }
}

void MainWindow::on_btnInit_clicked() {}

void MainWindow::on_btnLoadDataset_clicked() {
  QString fileName;
  QFileDialog *fileDialog = new QFileDialog(this);
  // определить заголовок файла
  fileDialog->setWindowTitle(tr("Open dataset"));
  // Установить путь к файлу по умолчанию
  fileDialog->setDirectory(".");
  // Установить фильтр файлов
  // fileDialog->setNameFilter(tr("Images(*.png *.jpg *.jpeg *.bmp)"));
  // Настройка позволяет выбрать несколько файлов, по умолчанию используется
  // только один файл QFileDialog :: ExistingFiles
  fileDialog->setFileMode(QFileDialog::ExistingFile);
  // Установить режим просмотра
  fileDialog->setViewMode(QFileDialog::Detail);
  // выводим путь ко всем выбранным файлам
  if (fileDialog->exec()) {
    fileName = fileDialog->selectedFiles()[0];
  }
  qDebug() << fileName;
  c->loadDataset(fileName.toStdString());
}
