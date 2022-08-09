#ifndef GRAPHNEURALNETWORK_H
#define GRAPHNEURALNETWORK_H

#include "neuralnetwork.h"

namespace s21 {

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

class GraphNeuralNetwork : public NeuralNetwork {
 private:
  std::vector<NeuronGraph> input_layer;
  std::vector<NeuronGraph> out_layer;
  std::vector<NeuronGraph> hidden_layer[5];

 public:
  GraphNeuralNetwork(){};
  ~GraphNeuralNetwork(){};
  void InitNetwork(InitConfig *config);
//  void LearningNetwork(LearnConfig *config);
//  int Predicate(std::vector<double> input);
//  void SaveWeights(std::string *filename);
};
};      // namespace s21
#endif  // GRAPHNEURALNETWORK_H
