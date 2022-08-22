#ifndef SRC_MLP_CONTROLLER_H_
#define SRC_MLP_CONTROLLER_H_
#include <QApplication>
#include <string>

#include "model.h"

namespace s21 {
class Controller : public QObject {
  Q_OBJECT

 private:
  s21::Model *m;
  std::vector<ErrorData> errorDataVector;

 public:
  explicit Controller(s21::Model *model) : m(model) {}
  bool stop_ = true;
  bool load_ = false;
  void loadDataset(string const &path);
  void loadNextDataset();
  void InitNetwork(const InitConfig &config);
  std::vector<double> getOutValues();
  auto getCorrectValue() -> unsigned;
  void TeachNetwork(LearnConfig const &learn_config);
  void TestNetwork(unsigned int percent);
  void ResetNetworkConfiguration();

  // simple functions
  auto getCountOfElements() -> long { return m->getCountOfElements(); }
  auto getInputValues(int img_num = 0) -> std::vector<double>;
  auto CheckModelState() -> s21::ModelState { return m->CheckModelState(); };
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
  auto getErrVector() -> const std::vector<s21::ErrorData> & {
    return errorDataVector;
  }
  auto resetErr() -> void { m->resetErr(); }
  auto EvaluateErr() -> void { m->EvaluateErr(); };

  auto SetVectorPixelsOfImage(const std::vector<double> &vector_pixels)
      -> void {
    m->SetVectorPixelsOfImage(vector_pixels);
    m->activate(vector_pixels);
  }

 signals:
  void progressChanged_(int value, int value2);
  void progressTestChanged_(int value, int value2);
};
}  // namespace s21
#endif  // SRC_MLP_CONTROLLER_H_
