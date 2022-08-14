#ifndef MATRIXNEURALNETWORK_H
#define MATRIXNEURALNETWORK_H

#include "neuralnetwork.h"
#include "matrix.h"

namespace s21 {
class MatrixNeuralNetwork : public NeuralNetwork {
 public:
  MatrixNeuralNetwork(){};
  ~MatrixNeuralNetwork(){};
  void InitNetwork(InitConfig* config) override;  // Инициализация весов
  void Activate(std::vector<double> &input) override;  //  Прямое распространение сигнала
  std::vector<double> getOutput() override;
  void teachNetwork(const std::vector<double> &correct) override;
  void SaveConfiguration(const std::string& filename) override;
  void LoadConfiguration(const std::string& filename) override;
  s21::InitConfig GetConfiguration() override;
  void PrintOutputValues();
  
 private:
  Matrix * weights_;
  double **neurons_val_;
  double **neurons_err_;
  void InitWeights();
  void InitNeuronsValues();
  void InitNeuronsErrors();
  void Sigmoid(double *a, int n);
  double DerSigmoid(double a);
  void BackPropagationSignal(const std::vector<double>& correct);
  void CalcWeights(double learning_rate);
};
}  // namespace s21
#endif  // MATRIXNEURALNETWORK_H
