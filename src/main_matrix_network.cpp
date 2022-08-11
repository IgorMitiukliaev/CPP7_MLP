#include "matrix_neural_network.h"
#include "fileloader.h"

int main() {
  s21::InitConfig init = {.num_neurons_input = 28 * 28,
                           .num_layers_hidden = 2,
                           .num_neurons_hidden = 10,
                           .num_neurons_out = 26,
                           .is_graph = false};
  s21::MatrixNeuralNetwork network;
  network.InitNetwork(&init);
  s21::FileLoader loader;
  loader.SetFileStream("../datasets/emnist-letters-test.csv");
  loader.StartReadElements();
  while (loader.ReadElement()) {
    auto input = loader.GetInputValues(); 
    network.Activate(input);
    network.CalcNewWeights(loader.GetOutputValues());
    break;
  }
}