#ifndef GRAPHNEURALNETWORK_H
#define GRAPHNEURALNETWORK_H
#include <QDebug>

#include "neuralnetwork.h"

namespace s21 {
class Neuron {
 public:
  std::vector<double> w;
  std::vector<double> dw;
  std::vector<Neuron *> n;

  double sum = 0, out = 0, dout = 0, err_ = 0, delta_ = 0;
  double sigmoid(double x);
  double dsigmoid(double x);

 public:
  Neuron();
  ~Neuron(){};
  std::vector<Neuron *> p;
  Neuron(std::vector<Neuron> *input_layer);
  void activate(const double input);
  double getResponse() { return out; };
  double getDResponse() { return dout; };
  double getInput() { return sum; };
  void evaluateErr(unsigned int i, double correct);
  void refreshWeight(double const &a_, double const &g_);
  //  void refreshWeight(double value) { delta_ = value; };
  double getDelta() { return delta_; };
  std::vector<double> getWeights();
  double getWeight(int i) {
    if (i < 0 or i >= w.size()) throw std::runtime_error("index out of bounds");
    return w[i];
  };
};

class GraphNeuralNetwork : public NeuralNetwork {
 private:
  float const a_ = 0.5, g_ = 0.2;
  std::vector<Neuron> input_layer;
  std::vector<Neuron> out_layer;
  std::vector<Neuron> hidden_layer[5];

 public:
  GraphNeuralNetwork(){};
  ~GraphNeuralNetwork(){};
  void InitNetwork(InitConfig *config) override;
  bool CheckNetworkReady() override;
  //  void LearningNetwork(LearnConfig *config);
  //  int Predicate(std::vector<double> input);
  //  void SaveWeights(std::string *filename);
  void Activate(std::vector<double> &input) override;
  std::vector<double> getOutput() override;
  void teachNetwork(const std::vector<double> &correct) override;
  s21::InitConfig GetConfiguration() override {
    s21::InitConfig config;
    return config;
  };
};
};      // namespace s21
#endif  // GRAPHNEURALNETWORK_H
