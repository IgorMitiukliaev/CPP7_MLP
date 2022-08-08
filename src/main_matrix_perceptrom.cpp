#include "matrix_perceptron.h"
#include "fileloader.h"

int main() {
  s21::MatrixPerceptron MLP(2, 2);
  s21::FileLoader loader;
  loader.SetFileStream("../datasets/emnist-letters-test.csv");
  loader.StartReadElements();
  while (loader.ReadElement()) {
    auto input = loader.GetInputValues(); 
    MLP.ForwardPropagation(input);
    break;
  }
}