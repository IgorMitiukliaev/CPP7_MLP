#include <vector>
#include "matrix.h"

#define NUM_INPUT_NEURONS 784
#define NUM_OUTPUT_NEURONS 26

namespace s21 {
class MatrixPerceptron{
  public:
    MatrixPerceptron(int num_layers_hidden, int num_neurons_hidden);
    void ForwardPropagation(std::vector<double> input);
    ~MatrixPerceptron(){};
  private:
    int num_layers_hidden_;
    int num_neurons_hidden_;
    std::vector<double> output_layer_;
    std::vector<s21::Matrix> weights_;
    std::vector<s21::Matrix> hidden_neurons_values_;
    void InitWeights();
};

};  // namespace s21