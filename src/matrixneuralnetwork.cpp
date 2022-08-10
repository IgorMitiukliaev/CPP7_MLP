#include "matrixneuralnetwork.h"
#include <QDebug>

void s21::MatrixNeuralNetwork::InitNetwork(s21::InitConfig* config) {
  num_layers_hidden = config->num_layers_hidden;
  num_neurons_hidden = config->num_neurons_hidden;
  num_neurons_input = config->num_neurons_input;
  num_neurons_out = config->num_neurons_out;
  InitWeights();
}

void s21::MatrixNeuralNetwork::InitWeights() {
  qDebug("I m here");
  weights_.push_back(s21::Matrix(num_neurons_input, num_neurons_hidden, true));
  for (auto i = 1; i < num_layers_hidden; i++) {
    weights_.push_back(s21::Matrix(num_neurons_hidden, num_neurons_hidden, true));
  }
  weights_.push_back(s21::Matrix(num_neurons_hidden, num_neurons_out, true));
  for (auto i = 0; i < num_layers_hidden; i++) {
    weights_[i].PrintMatrix();
  }
}

void s21::MatrixNeuralNetwork::activate(std::vector<double> &input) {
  s21::Matrix input_matrix(input);
  neurons_values_.push_back(input_matrix.ForwardSignal(weights_[0]));
  neurons_values_[0].PrintMatrix();
  for (auto i = 1; i <= num_layers_hidden; i++) {
    neurons_values_.push_back(neurons_values_[i-1].ForwardSignal(weights_[i]));
    neurons_values_[i].PrintMatrix();
  }
}
