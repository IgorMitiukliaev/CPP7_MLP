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
  on_Data_Loaded();
  drawPreview();
}

void MainWindow::on_Data_Loaded() {
  //  std::vector<double> input = c->getInputValues();
}

void MainWindow::drawPreview() {
  QPixmap p;
  QByteArray pData;
  QLabel *wg = (QLabel *)ui->lblPreview;
  std::vector<double> input = c->getInputValues();
  std::for_each(input.begin(), input.end(), [&pData](double const &value) {
    pData.insert(0, ~0);
    pData.insert(0, (1 - value) * 255);
    pData.insert(0, (1 - value) * 255);
    pData.insert(0, (1 - value) * 255);
  });
  const unsigned char *imageData =
      reinterpret_cast<const unsigned char *>(pData.constData());
  QImage qim = QImage(imageData, 28, 28, QImage::Format_ARGB32_Premultiplied);
  qim = qim.transformed(QTransform().rotate(270)).scaled(280,280);
  QPixmap pixmap = QPixmap::fromImage(qim);
  wg->setPixmap(pixmap);
  wg->show();
};
