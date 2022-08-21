#ifndef SRC_MLP_NEURALNETWORK_H_
#define SRC_MLP_NEURALNETWORK_H_

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

#include "matrix.h"

namespace s21 {
struct InitConfig {
    unsigned int num_neurons_input;
    unsigned int num_layers_hidden;
    unsigned int num_neurons_hidden;
    unsigned int num_neurons_out;
    bool is_graph;
};

struct LearnConfig {
    unsigned int num_batches;
    unsigned int num_epochs;
};

class NeuralNetwork {
 public:
    NeuralNetwork() {}
    virtual ~NeuralNetwork() {}
    //  NeuralNetwork(InitConfig config)
    virtual void InitNetwork(InitConfig const *config) {}  // инициализация из конфига
    //  virtual void LearningNetwork(LearnConfig *config);
    //  virtual int Predicate(std::vector<double> input);
    virtual void SaveConfiguration(const std::string &filename) {}
    virtual void LoadConfiguration(const std::string &filename) {}
    virtual InitConfig GetConfiguration() {
        return InitConfig();
    }
    virtual void Activate(const std::vector<double> &input) {}
    virtual std::vector<double> getOutput() { return std::vector<double>(1); }
    virtual void teachNetwork() {}
    //  virtual void teachNetwork(std::vector<double> &e){};
    virtual bool CheckNetworkReady() { return true; }
    virtual void teachNetwork(const std::vector<double> &e) {}

 protected:
    unsigned int num_layers_hidden = 2;
    unsigned int num_neurons_hidden = 100;
    unsigned int num_neurons_input = 784;
    unsigned int num_neurons_out = 26;
};

}  // namespace s21

#endif  // SRC_MLP_NEURALNETWORK_H_
