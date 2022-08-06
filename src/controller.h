#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <string>

#include "model.h"

namespace s21 {
class Controller {
 private:
  s21::Model *m;

 public:
  Controller(s21::Model *model) : m(model){};
  void loadDataset(string const &path);
  std::vector<double> getInputValues();
};
}  // namespace s21
#endif  // CONTROLLER_H
