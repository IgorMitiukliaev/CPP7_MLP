#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include <cmath>
#include <vector>

namespace s21 {
struct initConfig {
  unsigned int num_layers_hidden;
  unsigned int num_neurons_hidden;
  bool isGraph;
};
class NeuralNetwork {
 public:
  NeuralNetwork();
  NeuralNetwork(initConfig config);

 private:
  unsigned int num_layers_hidden, num_neurons_hidden;
  unsigned int const num_neurons_input = 28 * 28, num_neurons_out = 26;
};

class NeuronGraph {
 public:
  std::vector<double> getWeights();
  double activate();
  double getResponse();
  NeuronGraph(std::vector<NeuronGraph*> n);

 private:
  NeuronGraph();
  std::vector<double> w;
  std::vector<NeuronGraph*> n;
  double res;
  double sigmoid(double x);
};
}  // namespace s21

#endif  // NEURALNETWORK_H
