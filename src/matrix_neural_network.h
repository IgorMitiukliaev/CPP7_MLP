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
  void CalcError(const std::vector<double> &output);
  void CalcNewWeights(const std::vector<double> &output);
  void CalcOutputError(const std::vector<double> &output);
  void CalcHiddenErrors();
  void CalcDeltaWeights();
  void CalcWeights();
 private:
  std::vector<Matrix> weights_;
  std::vector<Matrix> delta_weights_;
  std::vector<Matrix> neurons_errors_;
  std::vector<Matrix> neurons_values_;
  std::vector<double> errors_;
  void InitWeights();
  
};
}  // namespace s21
#endif  // MATRIXNEURALNETWORK_H
