#include <QApplication>

#include "mainwindow.h"
#include "neuralnetwork.h"

int main(int argc, char* argv[]) {
  s21::Model m;
  s21::Controller c(&m);
  QApplication a(argc, argv);
  MainWindow w(&c);
  w.show();

  // testing NN activation
  s21::initConfig init = {.num_neurons_input = 28 * 28,
                          .num_layers_hidden = 5,
                          .num_neurons_hidden = 300,
                          .num_neurons_out = 26,
                          .isGraph = true};
  std::vector<s21::NeuronGraph> n_prev_layer(10);
  s21::NeuronGraph n0;
  s21::NeuronGraph n1(&n_prev_layer);
  s21::NeuralNetwork nn(init);
  return a.exec();
}
