#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QApplication>
#include <string>

#include "model.h"

namespace s21 {
class Controller : public QObject {
  Q_OBJECT
 private:
  s21::Model *m;

 public:
  Controller(s21::Model *model) : m(model){};
  bool pause_ = true, stop_ = true;

  void loadDataset(string const &path);
  std::vector<double> getInputValues(int img_num = 0);
  int getCountOfElements();
  void loadNextDataset();
  void InitNetwork(InitConfig &config);
  std::vector<double> getOutValues();
  unsigned getCorrectValue();

  void TeachNetwork(LearnConfig &learn_config);

  // simple functions
  auto CheckNetworkReady() -> bool { return m->CheckNetworkReady(); };
  auto CheckDataReady() -> bool { return m->CheckDataReady(); };
  auto StopTeachLoop(bool val) -> void { stop_ = val; };
  auto SaveConfiguration(const std::string &filename) -> void {
    m->SaveConfiguration(filename);
  };
  auto LoadConfiguration(const std::string &filename, bool is_graph) -> void {
    m->LoadConfiguration(filename, is_graph);
  };
  auto GetConfiguration() -> s21::InitConfig { return m->GetConfiguration(); };

 signals:
  void progressChanged_(int value, int value2);
};
}  // namespace s21
#endif  // CONTROLLER_H
