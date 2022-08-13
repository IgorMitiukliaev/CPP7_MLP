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
  std::vector<double> getInputValues(int img_num = 0);
  int getCountOfElements();
  void loadNextDataset();
  void InitNetwork(InitConfig &config);
  std::vector<double> getOutValues();
    unsigned getCorrectValue();
};
}  // namespace s21
#endif  // CONTROLLER_H
