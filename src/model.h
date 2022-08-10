#ifndef MODEL_H
#define MODEL_H
#include <QDebug>
#include <string>
#include <cmath>
#include "fileloader.h"
#include "neuralnetwork.h"

using std::string;

namespace s21 {
class Model {
 private:
  s21::FileLoader *fileloader;
  s21::NeuralNetwork *network_;
  std::vector<double> input;
  std::vector<double> out, correct;
  unsigned int num_images, num_layers_hidden, num_neurons_hidden;
  unsigned int const num_neurons_input = 28 * 28, num_neurons_out = 26;
  void normalizeInput();

 public:
  Model();
  ~Model(){};
  void InitNetwork(InitConfig &config);
  void loadDataset(string const &path);
  std::vector<double> getInputValues(int img_num = 0);
  std::vector<double> getCorrectValue(int img_num);
  void activate(std::vector<double> input);
  int getCountOfElements();
  void loadNextDataset();
  void teachNetwork();
};

}  // namespace s21
#endif  // MODEL_H
