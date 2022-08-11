#include "matrix_neural_network.h"

void s21::MatrixNeuralNetwork::InitNetwork(s21::InitConfig* config) {
  num_layers_hidden = config->num_layers_hidden;
  num_neurons_hidden = config->num_neurons_hidden;
  num_neurons_input = config->num_neurons_input;
  num_neurons_out = config->num_neurons_out;
  InitWeights();
}

void s21::MatrixNeuralNetwork::InitWeights() {
  weights_.push_back(s21::Matrix(num_neurons_input, num_neurons_hidden, true));
  delta_weights_.push_back(s21::Matrix(num_neurons_input, num_neurons_hidden, false));
  for (auto i = 1; i < num_layers_hidden; i++) {
    weights_.push_back(s21::Matrix(num_neurons_hidden, num_neurons_hidden, true));
    delta_weights_.push_back(s21::Matrix(num_neurons_hidden, num_neurons_hidden, false));
  }
  weights_.push_back(s21::Matrix(num_neurons_hidden, num_neurons_out, true));
  delta_weights_.push_back(s21::Matrix(num_neurons_hidden, num_neurons_out, false));
  // std::cout <<"Weights"<<std::endl;
  // for (auto i = 0; i <= num_layers_hidden; i++) {
  //   weights_[i].PrintMatrix();
  // }
}

void s21::MatrixNeuralNetwork::Activate(std::vector<double> &input) {
  s21::Matrix input_matrix(input);
  neurons_values_.clear();
  neurons_values_.push_back(input_matrix.ForwardSignal(weights_[0]));
  for (auto i = 1; i <= num_layers_hidden; i++) {
    neurons_values_.push_back(neurons_values_[i-1].ForwardSignal(weights_[i]));
  }
  // std::cout <<"Outs"<<std::endl;
  // for (auto i = 0; i <= num_layers_hidden; i++) {
  //   neurons_values_[i].PrintMatrix();
  // }
}

void s21::MatrixNeuralNetwork::CalcError(const std::vector<double> &output) {
  errors_.clear();
  auto predicate = neurons_values_[num_layers_hidden].ToVector();
  for (auto i = 0; i < output.size(); i++) errors_.push_back(predicate[i]-output[i]);
}

void s21::MatrixNeuralNetwork::CalcOutputError(const std::vector<double> &output) {
  std::vector<double> output_error;
  neurons_errors_.clear();
  auto predicate = neurons_values_[num_layers_hidden].ToVector();
  for (auto i = 0; i < output.size(); i++) {
    auto err = -predicate[i]*(1-predicate[i])*(output[i]-predicate[i]);
    output_error.push_back(err);
  }
  neurons_errors_.push_back(s21::Matrix(output_error));
}

std::vector<double> s21::MatrixNeuralNetwork::getOutput() {
  return neurons_values_[num_layers_hidden].ToVector();
}

void s21::MatrixNeuralNetwork::CalcNewWeights(const std::vector<double> &output) {
  CalcOutputError(output);
  CalcHiddenErrors();
  CalcDeltaWeights();
  CalcWeights();
}

void s21::MatrixNeuralNetwork::CalcHiddenErrors() {
  auto j = num_layers_hidden - 1;
  for (auto i = 1; i <= num_layers_hidden; i++) {
    neurons_errors_.push_back(neurons_errors_[i-1].BackSignalError(neurons_values_[j],weights_[j]));
    j--;
  }
  // std::cout <<"Errors"<<std::endl;
  // for (auto i = 0; i <= num_layers_hidden; i++) {
  //   neurons_errors_[i].PrintMatrix();
  // }
}

void s21::MatrixNeuralNetwork::CalcDeltaWeights() {
  auto j = num_layers_hidden;
  for (auto i = 0; i <= num_layers_hidden; i++) {
    delta_weights_[i].CalcDeltaWeights(delta_weights_[i],neurons_values_[i], neurons_errors_[j]);
    j--;
  }
  // std::cout <<"Deltas"<<std::endl;
  // for (auto i = 0; i <= num_layers_hidden; i++) {
  //   delta_weights_[i].PrintMatrix();
  // }
}

void s21::MatrixNeuralNetwork::CalcWeights() {
  for (auto i = 0; i < num_layers_hidden; i++) {
    weights_[i+1].CalcWeights(weights_[i], delta_weights_[i+1]);
  }
}

void s21::MatrixNeuralNetwork::PrintOutputValues() {
  std::vector<double> output = getOutput();
  for (auto iter:output) {
    std::cout << iter;
  }
  std::cout << std::endl;
}