#include "neuralnetwork.h"

using s21::NeuralNetwork, s21::NeuronGraph;
NeuralNetwork::NeuralNetwork() {}
NeuralNetwork::NeuralNetwork(initConfig config)
    : num_layers_hidden(config.num_layers_hidden),
      num_neurons_hidden(config.num_neurons_hidden){

      };

NeuronGraph::NeuronGraph(){};

NeuronGraph::NeuronGraph(std::vector<NeuronGraph*> n){};
double NeuronGraph::sigmoid(double x) { return 1 / (1 + exp(-x)); }

double NeuronGraph::activate() {
  return res;
}
