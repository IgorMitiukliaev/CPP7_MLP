#include "controller.h"

#include <QDebug>

#include "model.h"

using s21::Controller, s21::Model;

void Controller::loadDataset(string const &path) {
  m->loadDataset(path);
  m->activate(m->getInputValues());
  m->teachNetwork();
}

std::vector<double> Controller::getInputValues(int img_num) {
  return m->getInputValues(img_num);
};

int Controller::getCountOfElements() { return m->getCountOfElements(); }

void Controller::loadNextDataset() {
  m->loadNextDataset();
  m->activate(m->getInputValues());
  m->teachNetwork();
}

void Controller::InitNetwork(InitConfig &config) { m->InitNetwork(config); };
