#include "mainwindow.h"

#include <QDebug>

#include "./ui_mainwindow.h"
#include "paintwindow.h"

using s21::Controller;

// C:\msys64\home\buste\mlp\CPP7_MLP-0\misc\images

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
  _controller->loadDataset(fileName.toStdString());
  num_images = _controller->getCountOfElements();
  num_curr_image = 0;
  drawPreview();
  updatePreviewLabel();
  UpdateAnswerLabel();
  UpdateMLPState();
  enableButtons();
}

void MainWindow::drawPreview(int img_num) {
  QPixmap p;
  QByteArray pData;
  QLabel *wg = (QLabel *)ui->lblPreview;
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
  wg->setPixmap(pixmap);
  wg->show();
}

void MainWindow::updatePreviewLabel() {
  QString lbl = " of " + QString::number(num_images);
  ui->lblTotalImgs->setText(lbl);
  ui->inpNumCurrImg->setText(QString::number(num_curr_image));
  std::vector<double> out = _controller->getOutValues();
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
  //  double success_rate =
  //      _controller->getErr().count > 0 ? _controller->getErr().count_success
  //      / _controller->getErr().count : 0;
  //  text = "Success rate " + QString::number(success_rate * 100, 'f', 1) +
  //  "%";
  text = "Success count " +
         QString::number(_controller->getErr().count_success, 'f', 0);
  ui->lblError->setText(text);
}

void MainWindow::on_btnImgUp_clicked() {
  for (int i = 0; i < ui->valEpochNum->text().toInt(); i++) {
    for (int i = 0; i < ui->valEpochNum->text().toInt(); i++) {
      num_curr_image++;
      _controller->loadNextDataset();
      drawPreview();
      UpdateAnswerLabel();
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
  _controller->SetVectorPixelsOfImage(_vectorPixels);

  // auto _vector = _vectorPixels;
  // if (_vector.size() > 0) {
  //     std::cout << _vector.size() << std::endl;
  //     for (int i = 0; i < 28; ++i) {
  //         for (int j = 0; j < 28; ++j) {
  //             if (_vector[i * 28 + j] > 0) {
  //                 std::cout << "#"
  //                           << " ";
  //             } else {
  //                 std::cout << "  ";
  //             }
  //         }
  //         std::cout << std::endl;
  //     }
  // }
}

void MainWindow::CreateVectorPixels(QImage &image) {
  if (!image.isNull()) {
    if (!_vectorPixels.empty()) {
      _vectorPixels.clear();
    }
    QImage smallImage(image.scaled(_countNeurons, _countNeurons));
    for (int i = 0; i < _countNeurons; ++i) {
      for (int j = 0; j < _countNeurons; ++j) {
        _vectorPixels.push_back(!smallImage.pixelColor(j, i).blackF());
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

void MainWindow::on_valBatchNum_valueChanged(int arg1) { updateBatchLabel(); }

void MainWindow::on_tabWidget_tabBarClicked(int index) {
  if (_controller->CheckNetworkReady()) {
    ui->tabLearn->setEnabled(true);
    ui->tabTest->setEnabled(true);
  } else {
    ui->tabLearn->setEnabled(false);
    ui->tabTest->setEnabled(false);
  };
}

bool MainWindow::enableButtons() {
  bool res = _controller->CheckDataReady();
  ui->btnImgDown->setEnabled(res);
  ui->btnImgUp->setEnabled(res);
  ui->btnStartLearn->setEnabled(res);
  return res;
};

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

void MainWindow::on_btnSaveNetworkConfiguration_clicked() {
  QString filters("Conf files (*.bin);;All files (*.*)");
  QString q_filename =
      QFileDialog::getSaveFileName(this, "Save configuration", ".", filters);
  if (!q_filename.isEmpty()) {
    _controller->SaveConfiguration((q_filename).toStdString());
  }
}

void MainWindow::on_btnLoadNetworkConfiguration_clicked() {
  QString filters("Conf files (*.bin);;All files (*.*)");
  QString q_filename =
      QFileDialog::getOpenFileName(this, "Load configuration", ".", filters);
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
  qDebug() << out;
  int maxElementIndex = std::max_element(out.begin(), out.end()) - out.begin();
  ui->lblAnswer->setText(QString(QChar::fromLatin1(maxElementIndex + 65)));
}

void MainWindow::on_CreateGraph_clicked() {
  _graphWindow->show();
  std::vector<double> v;
  _graphWindow->DrawGraph(v);
}
