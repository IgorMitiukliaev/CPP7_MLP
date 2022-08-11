#include "matrix_neural_network.h"
#include "fileloader.h"

int main() {
  s21::InitConfig init = {.num_neurons_input = 28 * 28,
                           .num_layers_hidden = 2,
                           .num_neurons_hidden = 50,
                           .num_neurons_out = 26,
                           .is_graph = false};
  s21::MatrixNeuralNetwork network;
  network.InitNetwork(&init);
  s21::FileLoader loader;
  loader.SetFileStream("../datasets/emnist-letters-train.csv");
  loader.StartReadElements();
  for (auto i=0; i<10; i++) {
    loader.ReadElement();
    auto input = loader.GetInputValues(); 
    network.Activate(input);
    network.CalcNewWeights(loader.GetOutputValues());
    
    loader.PrintOutputValues();
    network.PrintOutputValues();
  }
  auto input = loader.GetInputValues(); 
  network.Activate(input);
  
  loader.PrintOutputValues();
  network.PrintOutputValues();
}