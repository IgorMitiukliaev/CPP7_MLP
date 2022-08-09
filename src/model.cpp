#include "model.h"

#include "matrixneuralnetwork.h"
#include "graphneuralnetwork.h"

using s21::Model;
s21::Model::Model() { fileloader = new FileLoader; }

void Model::InitNetwork(s21::InitConfig *config) {
  if (config->is_graph) {
    network_ = new GraphNeuralNetwork();
  } else {
    network_ = new MatrixNeuralNetwork();
  }
  network_->InitNetwork(config);
}

void Model::loadDataset(string const &path) {
  qDebug() << fileloader->SetFileStream(path);
  num_images = fileloader->GetCountOfElements();
  qDebug() << fileloader->ReadElement();
  //    fileloader.PrintOutputValues();  // вывод результирующего вектора
  //  fileloader->PrintInputValues(false);  // вывод значениями
  //    fileloader.PrintInputValues(true);   // вывод звёздочками
  input = fileloader->GetInputValues();
  input_value = fileloader->GetOutputValues();
  normalizeInput();
};

void Model::loadNextDataset() {
  fileloader->ReadElement();
  input = fileloader->GetInputValues();
  normalizeInput();
}

std::vector<double> Model::getInputValues(int img_num) { return input; };

void Model::normalizeInput() {
  double max = *max_element(input.begin(), input.end());
  double min = *min_element(input.begin(), input.end());
  if (max > min) {
    std::for_each(input.begin(), input.end(), [min, max](double &value) {
      value = (value - min) / (max - min);
    });
  } else {
    std::for_each(input.begin(), input.end(), [](double &value) { value = 0; });
  }
}

int Model::getCountOfElements() { return num_images; }
