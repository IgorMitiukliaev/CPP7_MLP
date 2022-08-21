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
  bool load_ = false;

  void loadDataset(string const &path);
  std::vector<double> getInputValues(int img_num = 0);

  void loadNextDataset();
  void InitNetwork(InitConfig &config);
  std::vector<double> getOutValues();
  auto getCorrectValue() -> unsigned;
  void TeachNetwork(LearnConfig &learn_config);
  void TestNetwork(unsigned int percent);
  void ResetNetworkConfiguration();

  // simple functions
  auto getCountOfElements() -> long { return m->getCountOfElements(); }
  auto CheckNetworkReady() -> bool { return m->CheckNetworkReady(); };
  auto CheckDataReady() -> bool { return m->CheckDataReady(); };
  auto StopTeachLoop(bool val) -> void { stop_ = val; };
  auto SaveConfiguration(const std::string &filename) -> void {
    m->SaveConfiguration(filename);
  };
  auto LoadConfiguration(const std::string &filename, bool is_graph) -> void {
    m->LoadConfiguration(filename, is_graph);
    load_ = true;
  };
  auto GetConfiguration() -> s21::InitConfig { return m->GetConfiguration(); };
  auto getErr() -> s21::ErrorData & { return m->getErr(); }
  auto resetErr() -> void { m->resetErr(); }
  auto EvaluateErr() -> void {m->EvaluateErr(); };

  auto SetVectorPixelsOfImage(std::vector<double> &vector_pixels) -> void {
    m->SetVectorPixelsOfImage(vector_pixels);
    m->activate(vector_pixels);
  }

 signals:
  void progressChanged_(int value, int value2);
  void progressTestChanged_(int value, int value2);
};
}  // namespace s21
#endif  // CONTROLLER_H