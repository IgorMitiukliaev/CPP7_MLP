#include "model.h"

using s21::Model;
s21::Model::Model() { fileloader = new FileLoader; }

void Model::createNetwork() {}

void Model::loadDataset(string const &path) {
  fileloader->SetFileStream(path);
  count_images = fileloader->GetCountOfElements();
  fileloader->ReadElement();
  //    fileloader.PrintOutputValues();  // вывод результирующего вектора
//  fileloader->PrintInputValues(false);  // вывод значениями
  //    fileloader.PrintInputValues(true);   // вывод звёздочками
  input = fileloader->GetInputValues();
  normalizeInput();
};

void Model::loadNextDataset() {
  fileloader->ReadElement();
  input = fileloader->GetInputValues();
  normalizeInput();
}

std::vector<double> Model::getInputValues(int img_num) { return input; };

double Model::sigmoid(double x) { return 1 / (1 + exp(-x)); }

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

int Model::getCountOfElements() { return count_images; }
