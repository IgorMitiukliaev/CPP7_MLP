#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "model.h"

namespace s21 {
class Controller {
 private:
  s21::Model *model;

 public:
  Controller(s21::Model *m) : model(m){};
  void createNetwork();
};
}  // namespace s21
#endif  // CONTROLLER_H
