#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include <algorithm>
#include <cmath>
#include <random>
#include <vector>

namespace s21 {
struct initConfig {
  unsigned int num_neurons_input;
  unsigned int num_layers_hidden;
  unsigned int num_neurons_hidden;
  unsigned int num_neurons_out;
  bool isGraph;
};

class Neuron {
 private:
  std::vector<double> w;
  std::vector<Neuron *> n;
  double res;
  double sigmoid(double x);

 public:
  double activate(double input = 1);
  double getResponse();
};

class NeuronGraph : public s21::Neuron {
 public:
  NeuronGraph();
  NeuronGraph(std::vector<NeuronGraph> *n);
  std::vector<double> getWeights();

 private:
  std::vector<double> w;
  std::vector<NeuronGraph *> n;
  double res;
};

class NeuralNetwork {
 public:
  NeuralNetwork();
  NeuralNetwork(initConfig config);
  //  std::vector<s21::NeuronGraph> layer;

 private:
  unsigned int num_layers_hidden, num_neurons_hidden;
  unsigned int const num_neurons_input = 28 * 28, num_neurons_out = 26;
  std::vector<NeuronGraph> input_layer;
  std::vector<NeuronGraph> out_layer;
};

}  // namespace s21

#endif  // NEURALNETWORK_H
