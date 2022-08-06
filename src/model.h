#ifndef MODEL_H
#define MODEL_H
#include <QDebug>
#include <string>
#include <cmath>
#include "fileloader.h"

using std::string;

namespace s21 {
class Model {
 private:
  std::vector<double> input;
  double sigmoid(double x);
  void normalizeInput();

 public:
  Model();
  void createNetwork();
  void loadDataset(string const &path);
  std::vector<double> getInputValues();
};

}  // namespace s21
#endif  // MODEL_H
