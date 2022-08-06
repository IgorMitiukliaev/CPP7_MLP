#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <string>

#include "model.h"

using std::string;
namespace s21 {
class Controller {
 private:
  s21::Model *model;

 public:
  Controller(s21::Model *m) : model(m){};
  void createNetwork();
  void loadDataset(string const &path);
};
}  // namespace s21
#endif  // CONTROLLER_H
