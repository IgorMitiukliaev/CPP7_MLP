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
  void activate(std::vector<double> &input) override;  //  Прямое распространение сигнала
 private:
  std::vector<Matrix> weights_;
  std::vector<Matrix> neurons_values_;
  void InitWeights();
  
};
}  // namespace s21
#endif  // MATRIXNEURALNETWORK_H
