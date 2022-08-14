#include "controller.h"

#include <QDebug>

#include "model.h"

using s21::Controller, s21::Model;

void Controller::loadDataset(string const &path) {
  m->loadDataset(path);
  m->activate(m->getInputValues());
}

std::vector<double> Controller::getInputValues(int img_num) {
  return m->getInputValues(img_num);
};

std::vector<double> Controller::getOutValues() { return m->getOutValues(); };

int Controller::getCountOfElements() { return m->getCountOfElements(); }

void Controller::loadNextDataset() {
  m->loadNextDataset();
  m->activate(m->getInputValues());
}

void Controller::InitNetwork(InitConfig &config) { m->InitNetwork(config); };

unsigned Controller::getCorrectValue() {
  std::vector<double> const &correct = m->getCorrectValue(0);
  int i = 0;
  for (; correct[i] == 0; i++) {
  };
  return i;
};

void Controller::TeachNetwork(LearnConfig &learn_config) {
  m->TeachNetwork(learn_config);
};

