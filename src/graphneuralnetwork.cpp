#include "graphneuralnetwork.h"

using s21::NeuralNetwork, s21::NeuronGraph, s21::Neuron,
    s21::GraphNeuralNetwork;

double Neuron::sigmoid(double x) { return 1 / (1 + exp(-x)); }

double Neuron::activate(double input) {
  for (int i = 0, res = 0; i < n.size(); i++) {
    res += w[i] * (n[i] == nullptr ? n[i]->getResponse() : input);
  }
  res = sigmoid(res);
  return res;
}

double Neuron::getResponse() { return res; }

void GraphNeuralNetwork::InitNetwork(InitConfig *config) {
  num_layers_hidden = config->num_layers_hidden;
  num_neurons_hidden = config->num_neurons_hidden;
  input_layer = std::vector<NeuronGraph>(config->num_neurons_input);

  for (unsigned int i = 0; i < config->num_layers_hidden; i++) {
    for (unsigned int j = 0; j < num_neurons_hidden; j++) {
      if (i == 0) {
        hidden_layer[i].push_back(NeuronGraph(&input_layer));
      } else {
        hidden_layer[i].push_back(NeuronGraph(&hidden_layer[i - 1]));
      }
    }
  }
  for (unsigned int i = 0; i < config->num_neurons_out; i++) {
    out_layer.push_back(NeuronGraph(&hidden_layer[num_layers_hidden - 1]));
  }
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
