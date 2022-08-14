#ifndef MODEL_H
#define MODEL_H
#include <QDebug>
#include <cmath>
#include <string>

#include "fileloader.h"
#include "neuralnetwork.h"

using std::string;

namespace s21 {
class Model {
 private:
  s21::FileLoader *fileloader_;
  s21::NeuralNetwork *network_;
  std::vector<double> input_, out_, correct_;
  s21::NeuralNetwork *nn_;
  std::vector<double> input_value_;
  unsigned int num_images_, num_layers_hidden_, num_neurons_hidden_,
      num_neurons_input_, num_neurons_out_, num_epochs_, num_batches_;
  void normalizeInput();

 public:
  Model();
  ~Model();
  void InitNetwork(InitConfig &config);
  void loadDataset(string const &path);
  void activate(std::vector<double> input);
  void loadNextDataset();
  void TeachNetwork();
  void TeachNetwork(LearnConfig &learn_config);
  void createNetwork(InitConfig config);

  // simple functions
  auto CheckNetworkReady() -> bool { return network_ != nullptr; };
  auto CheckDataReady() -> bool { return num_images_ != 0; };
  auto getInputValues(int img_num = 0) -> std::vector<double> {
    return input_;
  };
  auto getOutValues() -> std::vector<double> { return out_; };
  auto getCorrectValue(int img_num) -> std::vector<double> { return correct_; };
  auto getCountOfElements() -> int { return num_images_; }
//  auto GetCurrentImageNumber() -> unsigned int;
  std::vector<double> getOutValues();
  void SaveConfiguration(const std::string& filename);
  void LoadConfiguration(const std::string& filename, bool is_graph);
  InitConfig GetConfiguration();
};
}  // namespace s21
#endif  // MODEL_H
