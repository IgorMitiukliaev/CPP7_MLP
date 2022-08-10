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
  Neuron();
  ~Neuron(){};
  Neuron(std::vector<Neuron> *input_layer);
//  void activate();
//  void activate(std::vector<double> const &input);
  void activate(const double input);
  double getResponse();
  std::vector<double> getWeights();
};

class GraphNeuralNetwork : public NeuralNetwork {
 private:
  std::vector<Neuron> input_layer;
  std::vector<Neuron> out_layer;
  std::vector<Neuron> hidden_layer[5];

 public:
  GraphNeuralNetwork(){};
  ~GraphNeuralNetwork(){};
  void InitNetwork(InitConfig *config) override;
  //  void LearningNetwork(LearnConfig *config);
  //  int Predicate(std::vector<double> input);
  //  void SaveWeights(std::string *filename);
  void activate(std::vector<double> &input) override;
  std::vector<double> getOutput() override;

};
};      // namespace s21
#endif  // GRAPHNEURALNETWORK_H
