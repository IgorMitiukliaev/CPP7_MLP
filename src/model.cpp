#include "model.h"

using s21::Model;
s21::Model::Model() {}

void Model::createNetwork() {}

void Model::loadDataset(string const &path) {
  fileloader = new FileLoader;
  fileloader->SetFileStream(path);
  count_images = fileloader->GetCountOfElements();
  while (fileloader->ReadElement()) {
    //    fileloader.PrintOutputValues();  // вывод результирующего вектора
    //    fileloader.PrintInputValues(false);  // вывод значениями
    //    fileloader.PrintInputValues(true);   // вывод звёздочками
    //    qDebug() << fileloader.GetInputValues();
    input = fileloader->GetInputValues();
    normalizeInput();
    break;
  }
};

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
