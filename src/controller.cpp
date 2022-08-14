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

std::vector<double> Controller::getOutValues() { return m->getOutValues(); };

int Controller::getCountOfElements() { return m->getCountOfElements(); }

void Controller::loadNextDataset() {
  m->loadNextDataset();
  m->activate(m->getInputValues());
  m->teachNetwork();
}

void Controller::InitNetwork(InitConfig &config) { m->InitNetwork(config); };

unsigned Controller::getCorrectValue() {
  std::vector<double> correct = m->getCorrectValue(0);
  int i = 0;
  for (; correct[i] == 0; i++) {
  };
  return i;
};

void Controller::SaveConfiguration(const std::string& filename) {
  m->SaveConfiguration(filename);
}

void Controller::LoadConfiguration(const std::string& filename, bool is_graph) {
  m->LoadConfiguration(filename, is_graph);
}

s21::InitConfig Controller::GetConfiguration() {
  return m->GetConfiguration();
}
