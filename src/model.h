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
  s21::FileLoader *fileloader;
  s21::NeuralNetwork *nn;
  std::vector<double> input;
  unsigned int num_images, num_layers_hidden, num_neurons_hidden;
  unsigned int const num_neurons_input = 28 * 28, num_neurons_out = 26;

  double sigmoid(double x);
  void normalizeInput();

 public:
  Model();
  void createNetwork(initConfig config);
  void loadDataset(string const &path);
  std::vector<double> getInputValues(int img_num = 0);
  int getCountOfElements();
  void loadNextDataset();
};

}  // namespace s21
#endif  // MODEL_H
