
#include "matrix_perceptron.h"

s21::MatrixPerceptron::MatrixPerceptron(int num_layers_hidden, int num_neurons_hidden) {
  num_layers_hidden_ = num_layers_hidden;
  num_neurons_hidden_ = num_neurons_hidden;
  InitWeights();
}

void s21::MatrixPerceptron::InitWeights() {
  weights_.push_back(s21::Matrix(NUM_INPUT_NEURONS, num_neurons_hidden_, true));
  for (auto i = 1; i < num_layers_hidden_; i++) {
    weights_.push_back(s21::Matrix(num_neurons_hidden_, num_neurons_hidden_, true));
  }
  weights_.push_back(s21::Matrix(num_neurons_hidden_, NUM_OUTPUT_NEURONS, true));
}

void s21::MatrixPerceptron::ForwardPropagation(std::vector<double> input) {
  s21::Matrix input_matrix(input);
  //input_matrix.PrintMatrix();
  hidden_neurons_values_.push_back(input_matrix.Mult(weights_[0]));
  hidden_neurons_values_[0].PrintMatrix();
  for (auto i = 1; i <= num_layers_hidden_; i++) {
    hidden_neurons_values_.push_back(hidden_neurons_values_[i-1].Mult(weights_[i]));
    hidden_neurons_values_[i].PrintMatrix();
  }
}
