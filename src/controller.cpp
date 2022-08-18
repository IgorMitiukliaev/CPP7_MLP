#include "controller.h"

#include <QDebug>

#include "model.h"

using s21::Controller, s21::InitConfig, s21::InitConfig, s21::Model;

void Controller::loadDataset(string const &path) {
  m->loadDataset(path);
  m->activate(m->getInputValues());
}

std::vector<double> Controller::getInputValues(int img_num) {
  return m->getInputValues(img_num);
};

std::vector<double> Controller::getOutValues() { return m->getOutValues(); };

void Controller::loadNextDataset() {
  m->loadNextDataset();
  m->activate(m->getInputValues());
}

void Controller::InitNetwork(s21::InitConfig &config) {
  m->InitNetwork(config);
};

unsigned Controller::getCorrectValue() {
  std::vector<double> const &correct = m->getCorrectValue(0);
  int i = 0;
  for (; correct[i] == 0; i++) {
  };
  return i;
};

void Controller::TeachNetwork(LearnConfig &learn_config) {
  unsigned int num_epochs_ = learn_config.num_epochs;
  unsigned int num_batches_ = learn_config.num_batches;
  unsigned int const &num_images_ = m->getCountOfElements();
  m->activate(m->getInputValues());
  if (num_batches_ == 1) {
    long max_count = num_epochs_ * num_images_;
    for (unsigned int i = 0; (i < max_count) & !stop_; i++) {
      m->TeachNetwork();
      loadNextDataset();
      m->activate(m->getInputValues());
      if (i % 100 == 0) {
        emit progressChanged_(100, 100 * i / max_count);
      }
    }
  } else {
    bool teach_on = false;
    long teach_count = 0;
    long eval_count = 0;
    long max_count = num_batches_ * num_images_;
    for (unsigned int i = 0; (i < max_count) & !stop_; i++) {
      if (teach_on) {
        m->TeachNetwork();
        teach_count++;
      } else {
        m->EvaluateErr();
        eval_count++;
      }
      if (eval_count >= num_images_ / num_batches_) {
        eval_count = 0;
        teach_on = true;
      }
      if (teach_count >= num_images_) {
        teach_count = 0;
        teach_on = false;
      }
      loadNextDataset();
      m->activate(m->getInputValues());
      if (i % 100 == 0) {
        emit progressChanged_(100, 100 * i / max_count);
      }
    }
  }
  emit progressChanged_(100, 100);
  m->TeachNetwork();
};
