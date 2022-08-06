#include "controller.h"

#include <QDebug>

#include "model.h"

using s21::Controller, s21::Model;

void Controller::loadDataset(string const &path) {
  m->loadDataset(path);
}

std::vector<double> Controller::getInputValues() {
  return m->getInputValues();
};
