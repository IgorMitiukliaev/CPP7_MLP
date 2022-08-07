#include "neuralnetwork.h"

using s21::NeuralNetwork, s21::NeuronGraph, s21::Neuron;

double Neuron::sigmoid(double x) { return 1 / (1 + exp(-x)); }

double Neuron::activate(double input) {
  for (int i = 0, res = 0; i < n.size(); i++) {
    res += w[i] * (n[i] == nullptr ? n[i]->getResponse() : input);
  }
  res = sigmoid(res);
  return res;
}

double Neuron::getResponse() { return res; }

NeuralNetwork::NeuralNetwork() {}

NeuralNetwork::NeuralNetwork(initConfig config)
    : num_layers_hidden(config.num_layers_hidden),
      num_neurons_hidden(config.num_neurons_hidden) {
  input_layer = std::vector<NeuronGraph>(config.num_neurons_input);
  out_layer = std::vector<NeuronGraph>(config.num_neurons_out);

  //  for (int i = 0; i < config.num_layers_input; i++) {
  //  }
};

NeuronGraph::NeuronGraph()
    : w(std::vector<double>(1)), n(std::vector<NeuronGraph *>(1)), res(.0) {
  n[0] = nullptr;
  w[0] = 1;
};

NeuronGraph::NeuronGraph(std::vector<NeuronGraph> *n_prev_layer) {
  n = std::vector<NeuronGraph *>(n_prev_layer->size());
  for (int i = 0; i < n.size(); i++) n[i] = &(*n_prev_layer)[i];
  w = std::vector<double>(n_prev_layer->size());
  std::random_device rd;
  std::default_random_engine eng(rd());
  std::uniform_real_distribution<double> distr(-1, 1);
  std::for_each(w.begin(), w.end(),
                [&distr, &eng](double &el) { el = distr(eng); });
};
