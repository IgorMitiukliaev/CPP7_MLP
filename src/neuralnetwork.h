#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

namespace s21 {
struct initConfig {
  unsigned int num_layers_hidden;
  unsigned int num_neurons_hidden;
  bool isGraph;
};
class NeuralNetwork {
 public:
  NeuralNetwork();
  NeuralNetwork(initConfig config);
};
}  // namespace s21

#endif  // NEURALNETWORK_H
