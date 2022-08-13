#include "mainwindow.h"
#include "paintwindow.h"
#include "./ui_mainwindow.h"

using s21::Controller;

MainWindow::MainWindow(s21::Controller *controller, QWidget *parent)
    : c(controller),
      QMainWindow(parent),
      ui(new Ui::MainWindow),
      paintWindow(new PaintWindow) {
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
  QImage image(fileName);
  QGraphicsScene *scene = new QGraphicsScene();
  scene->addPixmap(QPixmap::fromImage(image));
  scene->setSceneRect(0,0,image.width(),image.height());
  ui->graphicsView->setScene(scene);
}

// C:\msys64\home\buste\mlp\CPP7_MLP-0\misc\images

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
  num_images = c->getCountOfElements();
  num_curr_image = 0;
  on_Data_Loaded();
  drawPreview();
  updatePreviewLabel();
  UpdateMLPState();
}

void MainWindow::on_Data_Loaded() {
  //  std::vector<double> input = c->getInputValues();
}

void MainWindow::drawPreview(int img_num) {
  QPixmap p;
  QByteArray pData;
  QLabel *wg = (QLabel *)ui->lblPreview;
  std::vector<double> input = c->getInputValues(img_num);
  std::for_each(input.begin(), input.end(), [&pData](double const &value) {
    pData.insert(0, ~0);
    pData.insert(0, (1 - value) * 255);
    pData.insert(0, (1 - value) * 255);
    pData.insert(0, (1 - value) * 255);
  });
  const unsigned char *imageData =
      reinterpret_cast<const unsigned char *>(pData.constData());
  QImage qim = QImage(imageData, 28, 28, QImage::Format_ARGB32_Premultiplied);
  qim = qim.transformed(QTransform().rotate(90)).scaled(280, 280);
  qim = qim.mirrored(false, true);
  QPixmap pixmap = QPixmap::fromImage(qim);
  wg->setPixmap(pixmap);
  wg->show();
}

void MainWindow::updatePreviewLabel() {
  QString lbl = " of " + QString::number(num_images);
  ui->lblTotalImgs->setText(lbl);
  ui->inpNumCurrImg->setText(QString::number(num_curr_image));
  std::vector<double> out = c->getOutValues();
  int num_letter = c->getCorrectValue() + 65;
  ui->lblLetter->setText(QString(QChar::fromLatin1(num_letter)));
}

void MainWindow::UpdateMLPState() {
  std::vector<double> out = c->getOutValues();
  for (int i{0}; i < ui->gridMLP->rowCount(); ++i) {
    for (int j{0}; j < ui->gridMLP->columnCount(); ++j) {
      auto *label =
          static_cast<QLabel *>(ui->gridMLP->itemAtPosition(i, j)->widget());
      QString text = QString(QChar::fromLatin1(j * 13 + i + 65));
      text += ": " + QString::number(out[j * 13 + i] * 100, 'f', 2) + "%";
      label->setText(text);
    }
  }
}

void MainWindow::on_inpNumCurrImg_textChanged(const QString &arg1) {}

void MainWindow::on_btnImgUp_clicked() {
  for (int i = 0; i < ui->spnEpoch->text().toInt(); i++) {
    num_curr_image++;
    c->loadNextDataset();
    drawPreview();
    updatePreviewLabel();
    UpdateMLPState();
  }
}

void MainWindow::on_btnInit_clicked() {
  s21::InitConfig config;
  config.is_graph = ui->rbtnGraph->isChecked();
  config.num_layers_hidden = ui->num_layers_hidden->value();
  config.num_neurons_hidden = ui->num_neurons_hidden->value();
  config.num_neurons_input = pow(ui->num_neurons_input->text().toInt(), 2);
  config.num_neurons_out = ui->num_neurons_out->text().toInt();
  qDebug() << config.is_graph;
  c->InitNetwork(config);
}

void MainWindow::on_pushButton_draw_clicked()
{
    paintWindow->show();
}


void MainWindow::on_pushButton_8_clicked()
{
  auto _vector = paintWindow->GetVectorPixels();
  std::cout << _vector.size() << std::endl;
  for (int i = 0; i < 28; ++i) {
    for (int j = 0; j < 28; ++j) {
      if (_vector[i * 28 + j] > 0) {
        std::cout << "#" << " ";
      } else {
        std::cout << "  ";
      }
    }
    std::cout << std::endl;
  } 
}

