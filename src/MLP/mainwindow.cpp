#include "mainwindow.h"

#include <QDebug>

#include "./ui_mainwindow.h"
#include "paintwindow.h"

using s21::Controller;

MainWindow::MainWindow(s21::Controller *controller, QWidget *parent)
    : _controller(controller),
      QMainWindow(parent),
      ui(new Ui::MainWindow),
      paintWindow(new PaintWindow),
      _graphWindow(new GraphWindow) {
  ui->setupUi(this);
  ui->barLearnProgress->setRange(0, 100);
  QObject::connect(qobject_cast<QObject *>(_controller),
                   SIGNAL(progressChanged_(int, int)), this,
                   SLOT(on_progressChanged_(int, int)));
  QObject::connect(qobject_cast<QObject *>(_controller),
                   SIGNAL(progressTestChanged_(int, int)), this,
                   SLOT(on_progressTestChanged_(int, int)));
}

MainWindow::~MainWindow() {
  delete _graphWindow;
  delete paintWindow;
  delete ui;
}

void MainWindow::on_btnLoadImage_clicked() {
  qDebug() << "clicked";
  QFileDialog dialog(this);
  dialog.setFileMode(QFileDialog::ExistingFile);
  QString fileName = dialog.getOpenFileName(this, tr("Open File"), "/home",
                                            tr("Images (*.bmp)"));
  qDebug() << fileName;
  if (!fileName.isEmpty()) {
    QImage image(fileName);
    GraphicsViewUpdate(image);
  }
}

void MainWindow::on_btnLoadDataset_clicked() {
  QString file_name = GetDatasetFileName();
  qDebug() << file_name;
  if (!file_name.isEmpty()) {
    _controller->loadDataset(file_name.toStdString());
    num_images = _controller->getCountOfElements();
    num_curr_image = 0;
    drawPreview();
    updatePreviewLabel();
    UpdateAnswerLabel();
    UpdateMLPState();
    enableButtons();
  }
}

void MainWindow::drawPreview(int img_num) {
  QLabel *wg = (QLabel *)ui->lblPreview;
  QPixmap pixmap = GetPreviewPicture(img_num);
  wg->setPixmap(pixmap);
  wg->show();
}

void MainWindow::updatePreviewLabel() {
  QString lbl = " of " + QString::number(num_images);
  ui->lblTotalImgs->setText(lbl);
  ui->inpNumCurrImg->setText(QString::number(num_curr_image));
  int num_letter = _controller->getCorrectValue() + 65;
  ui->lblLetter->setText(QString(QChar::fromLatin1(num_letter)));
  updateBatchLabel();
}

void MainWindow::UpdateMLPState() {
  std::vector<double> out = _controller->getOutValues();
  QString text;
  for (int i{0}; i < ui->gridMLP->rowCount(); ++i) {
    for (int j{0}; j < ui->gridMLP->columnCount(); ++j) {
      auto *label =
          static_cast<QLabel *>(ui->gridMLP->itemAtPosition(i, j)->widget());
      text = QString(QChar::fromLatin1(j * 13 + i + 65));
      text += ": " + QString::number(out[j * 13 + i] * 100, 'f', 2) + "%";
      label->setText(text);
    }
  }
  text = "Total count " + QString::number(_controller->getErr().count, 'f', 0) +
         "\n";
  text += "Success count " +
          QString::number(_controller->getErr().count_success, 'f', 0) + "\n";
  text += "Accuracy " +
          QString::number(_controller->getErr().accuracy * 100, 'f', 2) + "%\n";
  text += "Precision " +
          QString::number(_controller->getErr().precision * 100, 'f', 2) +
          "%\n";
  text += "Recall " +
          QString::number(_controller->getErr().recall * 100, 'f', 2) + "%\n";
  text += "f-measure " +
          QString::number(_controller->getErr().f_measure * 100, 'f', 2) +
          "%\n";

  ui->lblError->setText(text);
}

void MainWindow::on_btnImgUp_clicked() {
  for (int i = 0; i < ui->valEpochNum->text().toInt(); i++) {
    for (int j = 0; j < ui->valEpochNum->text().toInt(); j++) {
      num_curr_image++;
      _controller->loadNextDataset();
      drawPreview();
      UpdateAnswerLabel();
      updatePreviewLabel();
      UpdateMLPState();
    }
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
  qDebug() << "Is Graph - " << config.is_graph;
  _controller->InitNetwork(config);
}

void MainWindow::on_pushButton_draw_clicked() { paintWindow->show(); }

void MainWindow::GraphicsViewUpdate(QImage &image) {
  if (image.width() <= 512 && image.height() <= 512) {
    _graphics_view_image = image;
    QGraphicsScene *scene = new QGraphicsScene();
    scene->addPixmap(QPixmap::fromImage(_graphics_view_image));
    scene->setSceneRect(0, 0, _graphics_view_image.width(),
                        _graphics_view_image.height());
    ui->graphicsView->setScene(scene);
  }
}

void MainWindow::on_pushButton_8_clicked() {
  if (paintWindow->isVisible()) {
    GraphicsViewUpdate(paintWindow->GetImage());
  }
  CreateVectorPixels(_graphics_view_image);
  if (!_vectorPixels.empty()) {
    _controller->SetVectorPixelsOfImage(_vectorPixels);
  }
  UpdateMLPState();
  drawPreview();

  UpdateAnswerLabel();
}

void MainWindow::CreateVectorPixels(QImage &image) {
  if (!image.isNull()) {
    if (!_vectorPixels.empty()) {
      _vectorPixels.clear();
    }
    QImage smallImage(image.scaled(_countNeurons, _countNeurons));
    for (int i = 0; i < _countNeurons; ++i) {
      for (int j = 0; j < _countNeurons; ++j) {
        _vectorPixels.push_back(smallImage.pixelColor(i, j).blackF());
      }
    }
  }
}

void MainWindow::on_btnStartLearn_clicked() {
  if (_controller->stop_) {
    _controller->StopTeachLoop(false);
    qDebug() << _controller->stop_;
    s21::LearnConfig learn_config;
    ui->btnStartLearn->setText("Stop");
    learn_config.num_batches = ui->valBatchNum->text().toInt();
    learn_config.num_epochs = ui->valEpochNum->text().toInt();
    _controller->TeachNetwork(learn_config);
    ui->btnStartLearn->setText("Start");
  } else {
    _controller->StopTeachLoop(true);
    qDebug() << _controller->stop_;
    ui->btnStartLearn->setText("Start");
  }
}

void MainWindow::on_valEpochNum_valueChanged(int arg1) {
  qDebug() << arg1;
  if (arg1 == 1) {
    ui->valBatchNum->setEnabled(true);
    updateBatchLabel();
  } else {
    ui->valBatchNum->setEnabled(false);
    ui->lblBatchLen->setText("");
  }
}

void MainWindow::updateBatchLabel() {
  if (num_images > 0) {
    unsigned int batch_len = num_images / ui->valBatchNum->text().toInt();
    QString lbl = QString::number(batch_len) + " images / batch";
    ui->lblBatchLen->setText(lbl);
  }
}

void MainWindow::on_valBatchNum_valueChanged(int arg1) {
  qDebug() << arg1;
  if (arg1 == 1) {
    ui->valEpochNum->setEnabled(true);
    updateBatchLabel();
  } else {
    ui->valEpochNum->setEnabled(false);
  }
  updateBatchLabel();
}

void MainWindow::on_tabWidget_tabBarClicked(int index) {
  ui->tabInit->setEnabled(_controller->stop_);
  if (_controller->CheckNetworkReady()) {
    ui->tabLearn->setEnabled(true);
    ui->tabTest->setEnabled(true);
    ui->tabResearch->setEnabled(true);
  } else {
    ui->tabLearn->setEnabled(false);
    ui->tabTest->setEnabled(false);
    ui->tabResearch->setEnabled(false);
  }
}

bool MainWindow::enableButtons() {
  bool res = _controller->CheckDataReady();
  ui->btnImgUp->setEnabled(res);
  ui->btnStartLearn->setEnabled(res);
  return res;
}

void MainWindow::on_progressChanged_(int i, int percentage) {
  ui->barLearnProgress->setValue(percentage);
  num_curr_image =
      (num_curr_image + i >= num_images ? num_curr_image + i - num_images
                                        : num_curr_image + i);
  drawPreview();
  updatePreviewLabel();
  UpdateAnswerLabel();
  UpdateMLPState();
  QCoreApplication::processEvents();
}

void MainWindow::on_progressTestChanged_(int i, int percentage) {
  ui->barTestProgress->setValue(percentage);
  num_curr_image =
      (num_curr_image + i >= num_images ? num_curr_image + i - num_images
                                        : num_curr_image + i);
  UpdateTestSheet();
  if (_controller->stop_) {
    ui->btnStartLearn->setEnabled(true);
    ui->btnStartTest->setText("Start");
  }
  QCoreApplication::processEvents();
}

void MainWindow::on_btnSaveNetworkConfiguration_clicked() {
  QFileDialog dialog;
  QRegularExpression rx("\\..+$");
  QString filters("Conf files (*.bin)");
  dialog.setDefaultSuffix(".bin");
  QString q_filename = dialog.getSaveFileName(this, "Save configuration", ".",
                                              filters, &filters);
  qDebug() << rx.match(q_filename);
  if (!rx.match(q_filename).hasMatch()) q_filename += ".bin";
  qDebug() << q_filename;
  if (!q_filename.isEmpty()) {
    _controller->SaveConfiguration((q_filename).toStdString());
  }
}

void MainWindow::on_btnLoadNetworkConfiguration_clicked() {
  QString filters("Conf files (*.bin);;All files (*)");
  QString q_filename = QFileDialog::getOpenFileName(
      this, tr("Load configuration"), ".", filters);
  if (!q_filename.isEmpty()) {
    _controller->LoadConfiguration(q_filename.toStdString(),
                                   ui->rbtnGraph->isChecked());
    UpdateConfigurationView();
  }
}

void MainWindow::UpdateConfigurationView() {
  s21::InitConfig config = _controller->GetConfiguration();
  ui->num_layers_hidden->setValue(config.num_layers_hidden);
  ui->num_neurons_hidden->setValue(config.num_neurons_hidden);
}

void MainWindow::UpdateAnswerLabel() {
  std::vector<double> out = _controller->getOutValues();
  //  qDebug() << out;
  int maxElementIndex = std::max_element(out.begin(), out.end()) - out.begin();
  ui->lblAnswer->setText(QString(QChar::fromLatin1(maxElementIndex + 65)));
}

void MainWindow::on_CreateGraph_clicked() {
  _graphWindow->show();
  std::vector<double> v;
  std::for_each(_controller->errorDataVector.begin(),
                _controller->errorDataVector.end(),
                [&v](s21::ErrorData el) { v.push_back(el.accuracy); });
  _graphWindow->DrawGraph(v);
}

QString MainWindow::GetDatasetFileName() {
  QString file_name = "";
  QFileDialog *fileDialog = new QFileDialog(this);
  fileDialog->setWindowTitle(tr("Open dataset"));
  fileDialog->setDirectory(".");
  fileDialog->setFileMode(QFileDialog::ExistingFile);
  fileDialog->setViewMode(QFileDialog::Detail);
  if (fileDialog->exec()) {
    file_name = fileDialog->selectedFiles()[0];
  }
  return file_name;
}

void MainWindow::on_btnLoadDatasetTest_clicked() {
  QString file_name = GetDatasetFileName();
  if (!file_name.isEmpty()) {
    _controller->loadDataset(file_name.toStdString());
    _controller->EvaluateErr();
    num_images = _controller->getCountOfElements();
    num_curr_image = 0;
    UpdateTestSheet();
  }
}

QPixmap MainWindow::GetPreviewPicture(int img_num) {
  QByteArray pData;
  std::vector<double> input = _controller->getInputValues(img_num);
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
  return pixmap;
}

void MainWindow::DrawTestPreview(int img_num) {
  QPixmap pixmap = GetPreviewPicture(img_num);
  QImage image = pixmap.toImage();
  GraphicsViewUpdate(image);
}

void MainWindow::UpdateTestPreviewLabel() {
  QString lbl = " of " + QString::number(num_images);
  ui->lblTotalImgsTest->setText(lbl);
  ui->inpNumCurrImgTest->setText(QString::number(num_curr_image));
  int num_letter = _controller->getCorrectValue() + 65;
  ui->lblLetterTest->setText(QString(QChar::fromLatin1(num_letter)));
}

void MainWindow::on_btnImgUpTest_clicked() {
  num_curr_image++;
  _controller->loadNextDataset();
  _controller->EvaluateErr();
  UpdateTestSheet();
}

void MainWindow::UpdateTestSheet() {
  DrawTestPreview();
  UpdateTestPreviewLabel();
  UpdateAnswerLabel();
  UpdateMLPState();
}

void MainWindow::on_btnStartTest_clicked() {
  if (_controller->stop_) {
    _controller->StopTeachLoop(false);
    ui->btnStartTest->setText("Stop");
    _controller->TestNetwork(ui->valTestPercentage->value());
    ui->btnStartTest->setText("Start");
  } else {
    _controller->StopTeachLoop(true);
    ui->btnStartTest->setText("Start");
  }
  ui->btnStartLearn->setEnabled(_controller->stop_);
}

void MainWindow::on_MainWindow_destroyed() { _controller->StopTeachLoop(true); }

void MainWindow::on_rbtnGraph_clicked() {
  _controller->ResetNetworkConfiguration();
}

void MainWindow::on_rbtnMatrix_clicked() {
  _controller->ResetNetworkConfiguration();
}

void MainWindow::on_num_layers_hidden_valueChanged(int arg1) {
  _controller->ResetNetworkConfiguration();
}

void MainWindow::on_num_neurons_hidden_valueChanged(int arg1) {
  _controller->ResetNetworkConfiguration();
}

auto MainWindow::ResearchInitGraphPerceptron() -> void {
  s21::InitConfig config;
  config.is_graph = true;
  config.num_layers_hidden = 2;
  config.num_neurons_hidden = 100;
  config.num_neurons_input = pow(28, 2);
  config.num_neurons_out = 26;
  _controller->InitNetwork(config);
  _controller->LoadConfiguration(
      QDir::currentPath().append("/../src/conf.bin").toStdString(), true);
  _controller->loadDataset(
      QDir::currentPath()
          .append("/../datasets/emnist-letters/emnist-letters-test.csv")
          .toStdString());
}

auto MainWindow::ResearchInitMatrixPerceptron() -> void {
  s21::InitConfig config;
  config.is_graph = false;
  config.num_layers_hidden = 2;
  config.num_neurons_hidden = 100;
  config.num_neurons_input = pow(28, 2);
  config.num_neurons_out = 26;
  _controller->InitNetwork(config);
  _controller->LoadConfiguration(
      QDir::currentPath().append("/../src/conf.bin").toStdString(), false);
  _controller->loadDataset(
      QDir::currentPath()
          .append("/../datasets/emnist-letters/emnist-letters-test.csv")
          .toStdString());
}

auto MainWindow::ResearchTestingTime(const int count) -> double {
  clock_t t1, t2, t3;
  t1 = std::clock();
  for (int i = 0; i < count; ++i) {
    s21::LearnConfig learn_config;
    learn_config.num_batches = 1;
    learn_config.num_epochs = 1;
    _controller->TeachNetwork(learn_config);
  }
  t2 = std::clock();
  return ((double)(t2 - t1) / CLOCKS_PER_SEC);
}

void MainWindow::on_pushButtonResearch_clicked() {
  for (int i = 1; i <= 2; ++i) {
    if (i == 1) {
      ResearchInitMatrixPerceptron();
    } else {
      ResearchInitGraphPerceptron();
    }
    double averageTime(0.0);
    for (int j = 1; j <= 3; ++j) {
      double time(0.0);
      time = ResearchTestingTime(pow(10, j));
      averageTime += time;
      ui->tableWidget->setItem(
          i, j,
          new QTableWidgetItem(QString(QString::number(time).append(" sec"))));
    }
    averageTime /= 1110;
    ui->tableWidget->setItem(i, 4,
                             new QTableWidgetItem(QString(
                                 QString::number(averageTime).append(" sec"))));
  }
}
