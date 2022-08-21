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
}

std::vector<double> Controller::getOutValues() { return m->getOutValues(); }

void Controller::loadNextDataset() {
    m->loadNextDataset();
    m->activate(m->getInputValues());
}

void Controller::InitNetwork(s21::InitConfig &config) {
    m->InitNetwork(config);
}

unsigned Controller::getCorrectValue() {
    std::vector<double> const &correct = m->getCorrectValue(0);
    int i = 0;
    for (; correct[i] == 0; i++) {}
    return i;
}

void Controller::TeachNetwork(LearnConfig &learn_config) {
    m->resetErr();
  const int p_bar_increment = 250;
  unsigned int num_epochs_ = learn_config.num_epochs;
    unsigned int num_batches_ = learn_config.num_batches;
    int batches_count = 0;
  unsigned int const &num_images_ = m->getCountOfElements();
    m->activate(m->getInputValues());
    if (num_batches_ == 1) {
        errorDataVector.resize(num_epochs_);
    long max_count = num_epochs_ * num_images_;
        for (unsigned int i = 0; (i < max_count) && !stop_; i++) {
            m->TeachNetwork();
            loadNextDataset();
            if (i % p_bar_increment == 0 && i > 0) {
                m->EvaluateErr();
                emit progressChanged_(p_bar_increment, 100 * i / max_count);
      }
      if (i % num_images_ == 0 && i > 0) {
        m->EvaluateErr();
        errorDataVector[batches_count++] = m->getErr();
        emit progressChanged_(p_bar_increment, 100 * i / max_count);
                m->resetErr();
              std::for_each(errorDataVector.begin(), errorDataVector.end(),
                      [](ErrorData el) {
                        qDebug() << "success / count = " << el.count_success
                                 << " / " << el.count;
                      });
      }
        }
    } else {
        bool teach_on = false;
        long teach_count = 0;
        long eval_count = 0;
        long max_count = (1 + num_batches_) * num_images_;
        errorDataVector.resize(num_batches_);
    for (unsigned int i = 0; (i < max_count) && !stop_; i++) {
            if (teach_on) {
                m->TeachNetwork();
                teach_count++;
            } else {
                eval_count++;
            }
            if (eval_count >= num_images_ / num_batches_) {
                eval_count = 0;
                teach_on = true;
                m->EvaluateErr();
                errorDataVector[batches_count++] = m->getErr();
        emit progressChanged_(0, 100 * i / max_count);
                m->resetErr();
              std::for_each(errorDataVector.begin(), errorDataVector.end(),
                      [](ErrorData el) {
                        qDebug() << "success / count = " << el.count_success
                                 << " / " << el.count;
                      });
      }
            if (teach_count >= num_images_) {
                teach_count = 0;
                teach_on = false;
              m->resetErr();
      }
            loadNextDataset();
            if (i % p_bar_increment == 0 && i > 0) {
                m->EvaluateErr();
        emit progressChanged_(p_bar_increment, 100 * i / max_count);
            }
        }
    }
    emit progressChanged_(p_bar_increment, 100);
  std::for_each(errorDataVector.begin(), errorDataVector.end(),
                [](ErrorData el) {
                  qDebug() << "success / count = " << el.count_success << " / "
                           << el.count;
                });
}

void Controller::TestNetwork(unsigned int percent) {
    unsigned int const &num_images_ = m->getCountOfElements();
    auto num_test_images = num_images_ * percent / 100;
    m->activate(m->getInputValues());
    unsigned int i;
    for (i = 1; (i < num_test_images) && !stop_; i++) {
        loadNextDataset();
        if (i % 100 == 0) {
            m->EvaluateErr();
            emit progressTestChanged_(100, 100 * i / num_test_images);
        }
    }
    if (i == num_test_images) {
        stop_ = true;
        emit progressTestChanged_(100, 100);
    }
}

void Controller::ResetNetworkConfiguration() {
    if (!load_) m->ResetNetworkConfiguration();
    load_ = false;
}
