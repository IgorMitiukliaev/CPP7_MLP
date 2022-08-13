#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>

namespace s21 {
struct InitConfig {
  unsigned int num_neurons_input;
  unsigned int num_layers_hidden;
  unsigned int num_neurons_hidden;
  unsigned int num_neurons_out;
  bool is_graph;
};

struct LearnConfig {
  unsigned int num_cross_validation_group;
  unsigned int num_epochs;
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
  NeuralNetwork(){};
  ~NeuralNetwork(){};
  //  NeuralNetwork(InitConfig config);
  virtual void InitNetwork(InitConfig *config){};  //инициализация из конфига
  //  virtual void LearningNetwork(LearnConfig *config);
  //  virtual int Predicate(std::vector<double> input);
  //  virtual void SaveWeights(std::string *filename);
  virtual void activate(std::vector<double> &input){};
  virtual std::vector<double> getOutput() { return std::vector<double>(1); };
  virtual void teachNetwork(std::vector<double> err) {};
 protected:
  unsigned int num_layers_hidden, num_neurons_hidden, num_neurons_input,
      num_neurons_out;
  //  std::vector<s21::NeuronGraph> layer;
 private:
  std::vector<NeuronGraph> input_layer;
  std::vector<NeuronGraph> out_layer;
  std::vector<NeuronGraph> hidden_layer[5];
};

}  // namespace s21

#endif  // NEURALNETWORK_H
