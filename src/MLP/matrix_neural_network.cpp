#include "matrix_neural_network.h"

void s21::MatrixNeuralNetwork::InitNetwork(s21::InitConfig* config) {
  num_layers_hidden = config->num_layers_hidden;
  num_neurons_hidden = config->num_neurons_hidden;
  num_neurons_input = config->num_neurons_input;
  num_neurons_out = config->num_neurons_out;
  InitWeights();
  InitNeuronsValues();
  InitNeuronsErrors();
}

void s21::MatrixNeuralNetwork::InitWeights() {
  weights_.resize(num_layers_hidden + 1);
  weights_[0].InitRand(num_neurons_hidden, num_neurons_input);
  for (auto i = 1; i <= num_layers_hidden - 1; i++) {
    weights_[i].InitRand(num_neurons_hidden, num_neurons_hidden);
  }
  weights_[num_layers_hidden].InitRand(num_neurons_out, num_neurons_hidden);
}

void s21::MatrixNeuralNetwork::InitNeuronsValues() {
  neurons_val_.resize(num_layers_hidden + 2);
  neurons_val_[0].resize(num_neurons_input);
  for (auto i = 1; i <= num_layers_hidden; i++)
    neurons_val_[i].resize(num_neurons_hidden);
  neurons_val_[num_layers_hidden + 1].resize(num_neurons_out);
}

void s21::MatrixNeuralNetwork::InitNeuronsErrors() {
  neurons_err_.resize(num_layers_hidden + 2);
  neurons_err_[0].resize(num_neurons_input);
  for (auto i = 1; i <= num_layers_hidden; i++) {
    neurons_err_[i].resize(num_neurons_hidden);
  }
  neurons_err_[num_layers_hidden + 1].resize(num_neurons_out);
}

void s21::MatrixNeuralNetwork::Sigmoid(std::vector<double>& a, int n) {
  for (auto i = 0; i < n; i++) a[i] = 1 / (1 + exp(-a[i]));
}

double s21::MatrixNeuralNetwork::DerSigmoid(double a) {
  return a = a * (1 - a);
}

void s21::MatrixNeuralNetwork::Activate(std::vector<double>& input) {
  for (auto i = 0; i < num_neurons_input; i++) {
    neurons_val_[0][i] = input[i];
  }
  for (int i = 1; i <= num_layers_hidden; i++) {
    Matrix::Mult(weights_[i - 1], neurons_val_[i - 1], neurons_val_[i]);
    Sigmoid(neurons_val_[i], num_neurons_hidden);
  }
  auto i = num_layers_hidden + 1;
  Matrix::Mult(weights_[i - 1], neurons_val_[i - 1], neurons_val_[i]);
  Sigmoid(neurons_val_[i], num_neurons_out);
}

std::vector<double> s21::MatrixNeuralNetwork::getOutput() {
  std::vector<double> out;
  for (auto i = 0; i < num_neurons_out; i++)
    out.push_back(neurons_val_[num_layers_hidden + 1][i]);
  return out;
}

void s21::MatrixNeuralNetwork::BackPropagationSignal(
    const std::vector<double>& correct) {
  auto k = num_layers_hidden + 1;
  for (auto i = 0; i < num_neurons_out; i++) {
    neurons_err_[k][i] =
        (correct[i] - neurons_val_[k][i]) * DerSigmoid(neurons_val_[k][i]);
  }
  for (auto k = num_layers_hidden; k > 1; k--) {
    Matrix::TransposeMult(weights_[k], neurons_err_[k + 1], neurons_err_[k]);
    for (auto j = 0; j < num_neurons_hidden; j++) {
      neurons_err_[k][j] *= DerSigmoid(neurons_val_[k][j]);
    }
  }
  k = 0;
  Matrix::TransposeMult(weights_[k], neurons_err_[k + 1], neurons_err_[k]);
  for (auto j = 0; j < num_neurons_input; j++) {
    neurons_err_[k][j] *= DerSigmoid(neurons_val_[k][j]);
  }
}

void s21::MatrixNeuralNetwork::CalcWeights(double learning_rate) {
  auto i = 0;
  for (auto j = 0; j < num_neurons_hidden; j++) {
    for (auto k = 0; k < num_neurons_input; k++) {
      weights_[i](j, k) +=
          neurons_val_[i][k] * neurons_err_[i + 1][j] * learning_rate;
    }
  }
  for (auto i = 1; i < num_layers_hidden; i++) {
    for (auto j = 0; j < num_neurons_hidden; j++) {
      for (auto k = 0; k < num_neurons_hidden; k++) {
        weights_[i](j, k) +=
            neurons_val_[i][k] * neurons_err_[i + 1][j] * learning_rate;
      }
    }
  }
  i = num_layers_hidden;
  for (auto j = 0; j < num_neurons_out; j++) {
    for (auto k = 0; k < num_neurons_hidden; k++) {
      weights_[i](j, k) +=
          neurons_val_[i][k] * neurons_err_[i + 1][j] * learning_rate;
    }
  }
}

void s21::MatrixNeuralNetwork::teachNetwork(
    const std::vector<double>& correct) {
  BackPropagationSignal(correct);
  CalcWeights(0.1);
}

void s21::MatrixNeuralNetwork::PrintOutputValues() {
  for (auto i = 0; i < num_neurons_out; i++) {
    std::cout << neurons_val_[num_layers_hidden + 1][i] << "|";
  }
  std::cout << std::endl;
}

void s21::MatrixNeuralNetwork::SaveConfiguration(const std::string& filename) {
  std::ofstream out(filename, std::ios::binary | std::ios::out);
  s21::InitConfig config = GetConfiguration();
  out.write((char*)&config, sizeof(config));

  for (auto i = 0; i < num_layers_hidden + 1; i++) {
    weights_[i].Save(out);
    weights_[i].PrintMatrix();
  }

  out.close();
}

void s21::MatrixNeuralNetwork::LoadConfiguration(const std::string& filename) {
  std::ifstream in(filename, std::ios::binary | std::ios::in);
  s21::InitConfig config;
  in.read((char*)&config, sizeof(config));
  InitNetwork(&config);
  for (auto i = 0; i < num_layers_hidden + 1; i++) {
    weights_[i].Load(in);
    weights_[i].PrintMatrix();
  }
  in.close();
}

s21::InitConfig s21::MatrixNeuralNetwork::GetConfiguration() {
  s21::InitConfig config = {.num_neurons_input = num_neurons_input,
                            .num_layers_hidden = num_layers_hidden,
                            .num_neurons_hidden = num_neurons_hidden,
                            .num_neurons_out = num_neurons_out,
                            .is_graph = false};
  return config;
}
