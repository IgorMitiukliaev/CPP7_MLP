#include "mainwindow.h"

#include <QDebug>

#include "./ui_mainwindow.h"
#include "paintwindow.h"

using s21::Controller;

// C:\msys64\home\buste\mlp\CPP7_MLP-0\misc\images

MainWindow::MainWindow(s21::Controller *controller, QWidget *parent)
    : controller_(controller),
      QMainWindow(parent),
      ui(new Ui::MainWindow),
      paintWindow(new PaintWindow),
      _graphWindow(new GraphWindow) {
  ui->setupUi(this);
  ui->barLearnProgress->setRange(0, 100);
  QObject::connect(qobject_cast<QObject *>(controller_),
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
  controller_->loadDataset(fileName.toStdString());
  num_images = controller_->getCountOfElements();
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
  std::vector<double> input = controller_->getInputValues(img_num);
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
  std::vector<double> out = controller_->getOutValues();
  int num_letter = controller_->getCorrectValue() + 65;
  ui->lblLetter->setText(QString(QChar::fromLatin1(num_letter)));
  updateBatchLabel();
}

void MainWindow::UpdateMLPState() {
  std::vector<double> out = controller_->getOutValues();
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
  //      controller_->getErr().count > 0 ? controller_->getErr().count_success
  //      / controller_->getErr().count : 0;
  //  text = "Success rate " + QString::number(success_rate * 100, 'f', 1) +
  //  "%";
  text = "Success count " +
         QString::number(controller_->getErr().count_success, 'f', 0);
  ui->lblError->setText(text);
}

void MainWindow::on_btnImgUp_clicked() {
  for (int i = 0; i < ui->valEpochNum->text().toInt(); i++) {
    for (int i = 0; i < ui->valEpochNum->text().toInt(); i++) {
      num_curr_image++;
      controller_->loadNextDataset();
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
  controller_->InitNetwork(config);
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

// void MainWindow::on_pushButton_8_clicked() {
//     if (paintWindow->isVisible()) {
//         GraphicsViewUpdate(paintWindow->GetImage());
//     }
//     CreateVectorPixels(_graphics_view_image);
//     _controller->SetVectorPixelsOfImage(_vectorPixels);

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
//}

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
  if (controller_->stop_) {
    controller_->StopTeachLoop(false);
    qDebug() << controller_->stop_;
    s21::LearnConfig learn_config;
    ui->btnStartLearn->setText("Stop");
    learn_config.num_batches = ui->valBatchNum->text().toInt();
    learn_config.num_epochs = ui->valEpochNum->text().toInt();
    controller_->TeachNetwork(learn_config);
    ui->btnStartLearn->setText("Start");
  } else {
    controller_->StopTeachLoop(true);
    qDebug() << controller_->stop_;
    ui->btnStartLearn->setText("Start");
  }
}

void MainWindow::on_pushButton_8_clicked() {
  auto _vector = paintWindow->GetVectorPixels();
  std::cout << _vector.size() << std::endl;
  for (int i = 0; i < 28; ++i) {
    for (int j = 0; j < 28; ++j) {
      if (_vector[i * 28 + j] > 0) {
        std::cout << "#"
                  << " ";
      } else {
        std::cout << "  ";
      }
    }
    std::cout << std::endl;
  }
}
  // C:\msys64\home\buste\mlp\CPP7_MLP-0\misc\images
