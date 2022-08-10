#ifndef MATRIXNEURALNETWORK_H
#define MATRIXNEURALNETWORK_H
#include <iostream>

#include "neuralnetwork.h"

namespace s21 {
class MatrixNeuralNetwork : public NeuralNetwork {
 public:
  MatrixNeuralNetwork(){};
  ~MatrixNeuralNetwork(){};
  void InitNetwork(InitConfig* config) override {
    std::cout << "Matrix" << std::endl;
  };
};
}  // namespace s21
#endif  // MATRIXNEURALNETWORK_H
