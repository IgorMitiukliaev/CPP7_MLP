#ifndef MODEL_H
#define MODEL_H
#include <QDebug>
#include <cmath>
#include <string>

#include "fileloader.h"

using std::string;

namespace s21 {
class Model {
 private:
  s21::FileLoader *fileloader;
  std::vector<double> input;
  int count_images;
  double sigmoid(double x);
  void normalizeInput();

 public:
  Model();
  void createNetwork();
  void loadDataset(string const &path);
  std::vector<double> getInputValues(int img_num = 0);
  int getCountOfElements();
  void loadNextDataset();
};

}  // namespace s21
#endif  // MODEL_H
