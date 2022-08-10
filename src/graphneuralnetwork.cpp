#include "graphneuralnetwork.h"

using s21::NeuralNetwork, s21::Neuron, s21::GraphNeuralNetwork;

double Neuron::sigmoid(double x) { return 1 / (1 + exp(-x)); }

void Neuron::activate(const double input = 1) {
  for (int i = 0, sum = 0; i < n.size(); i++) {
    sum += w[i] * (n[i] != nullptr ? n[i]->getResponse() : input);
  }
  out = sigmoid(sum);
}

double Neuron::getResponse() { return out; }

void GraphNeuralNetwork::InitNetwork(InitConfig *config) {
  num_layers_hidden = config->num_layers_hidden;
  num_neurons_hidden = config->num_neurons_hidden;
  num_neurons_input = config->num_neurons_input;
  num_neurons_out = config->num_neurons_out;
  input_layer = std::vector<Neuron>(config->num_neurons_input);

  for (unsigned int i = 0; i < config->num_layers_hidden; i++) {
    for (unsigned int j = 0; j < num_neurons_hidden; j++) {
      if (i == 0) {
        hidden_layer[i].push_back(Neuron(&input_layer));
      } else {
        hidden_layer[i].push_back(Neuron(&hidden_layer[i - 1]));
      }
    }
  }
  for (unsigned int i = 0; i < config->num_neurons_out; i++) {
    out_layer.push_back(Neuron(&hidden_layer[num_layers_hidden - 1]));
  }
};

Neuron::Neuron()
    : w(std::vector<double>(1)), n(std::vector<Neuron *>(1)), sum(.0) {
  n[0] = nullptr;
  w[0] = 1;
};

Neuron::Neuron(std::vector<Neuron> *input_layer) {
  n = std::vector<Neuron *>(input_layer->size());
  for (int i = 0; i < n.size(); i++) n[i] = &(*input_layer)[i];
  w = std::vector<double>(input_layer->size());
  std::random_device rd;
  std::default_random_engine eng(rd());
  std::uniform_real_distribution<double> distr(-1, 1);
  std::for_each(w.begin(), w.end(),
                [&distr, &eng](double &el) { el = distr(eng); });
};

void GraphNeuralNetwork::Activate(std::vector<double> &input) {
  for (unsigned int i = 0; i < num_neurons_input; i++) {
    input_layer[i].activate(input[i]);
  }
  for (unsigned int i = 0; i < num_layers_hidden; i++) {
    for (unsigned int j = 0; j < num_neurons_hidden; j++) {
      hidden_layer[i][j].activate();
    }
  }
};

std::vector<double> GraphNeuralNetwork::getOutput() {
  std::vector<double> res;
  for_each(out_layer.begin(), out_layer.end(),
           [&res](Neuron &el) { res.push_back(el.getResponse()); });
  return res;
};

void GraphNeuralNetwork::teachNetwork(std::vector<double> err) {  qDebug() << "err: " << err;};
