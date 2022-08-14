#include "graphneuralnetwork.h"

using s21::NeuralNetwork, s21::Neuron, s21::GraphNeuralNetwork;

double Neuron::sigmoid(double x) { return 1 / (1 + exp(-x)); }
double Neuron::dsigmoid(double x) { return sigmoid(x) * (1 - sigmoid(x)); }

void Neuron::activate(const double input = 1) {
  sum = 0;
  for (int i = 0; i < n.size(); i++) {
    sum += w[i] * ((n[i] == nullptr) ? input : n[i]->getResponse());
  }
  out = sigmoid(sum);
  dout = dsigmoid(sum);
}

void GraphNeuralNetwork::InitNetwork(InitConfig *config) {
  num_layers_hidden = config->num_layers_hidden;
  num_neurons_hidden = config->num_neurons_hidden;
  num_neurons_input = config->num_neurons_input;
  num_neurons_out = config->num_neurons_out;
  input_layer = std::vector<Neuron>(config->num_neurons_input);

  for (unsigned int i = 0; i < config->num_layers_hidden; i++) {
    for (unsigned int j = 0; j < num_neurons_hidden; j++) {
      if (i == 0) {
        hidden_layer[i].push_back(Neuron(&input_layer));
      } else {
        hidden_layer[i].push_back(Neuron(&hidden_layer[i - 1]));
      }
    }
  }
  for (unsigned int i = 0; i < config->num_neurons_out; i++) {
    out_layer.push_back(Neuron(&hidden_layer[num_layers_hidden - 1]));
  }

  for (unsigned int i = 0; i < num_neurons_input; i++) {
    input_layer[i].p.clear();
    for (unsigned int j = 0; j < num_neurons_hidden; j++) {
      input_layer[i].p.push_back(&hidden_layer[0][j]);
    }
  }

  for (unsigned int i = 0; i < num_neurons_hidden; i++) {
    hidden_layer[num_layers_hidden - 1][i].p.clear();
    for (unsigned int j = 0; j < num_neurons_out; j++) {
      hidden_layer[num_layers_hidden - 1][i].p.push_back(&out_layer[j]);
    }
  }

  for (unsigned int i = 0; i < num_layers_hidden - 1; i++) {
    for (unsigned int j = 0; j < num_neurons_hidden; j++) {
      hidden_layer[i][j].p.clear();
      for (unsigned int k = 0; k < num_neurons_hidden; k++) {
        hidden_layer[i][j].p.push_back(&hidden_layer[i + 1][k]);
      }
    }
  }
};

Neuron::Neuron()
    : w(std::vector<double>(1)),
      dw(std::vector<double>(1)),
      n(std::vector<Neuron *>(1)),
      p(std::vector<Neuron *>(1)) {
  n[0] = nullptr;
  w[0] = 1;
  p[0] = nullptr;
};

Neuron::Neuron(std::vector<Neuron> *input_layer) : Neuron() {
  n.resize(input_layer->size());
  w.resize(input_layer->size());
  dw.resize(input_layer->size());
  for (int i = 0; i < n.size(); i++) n[i] = &(*input_layer)[i];
  std::random_device rd;
  std::default_random_engine eng(rd());
  std::uniform_real_distribution<double> distr(-1, 1);
  std::for_each(w.begin(), w.end(),
                [&distr, &eng](double &el) { el = distr(eng); });
};

void GraphNeuralNetwork::Activate(std::vector<double> &input) {
  for (unsigned int i = 0; i < num_neurons_input; i++) {
    input_layer[i].activate(input[i]);
  }
  for (unsigned int i = 0; i < num_layers_hidden; i++) {
    for (unsigned int j = 0; j < num_neurons_hidden; j++) {
      hidden_layer[i][j].activate();
    }
  }
  for (unsigned int i = 0; i < num_neurons_out; i++) {
    out_layer[i].activate();
  }
};

std::vector<double> GraphNeuralNetwork::getOutput() {
  std::vector<double> res;
  for_each(out_layer.begin(), out_layer.end(),
           [&res](Neuron &el) { res.push_back(el.getResponse()); });
  return res;
};

void Neuron::evaluateErr(unsigned int num_pos = 0, double correct = 0) {
  delta_ = 0;
  if (p[0] == nullptr) {
    delta_ = (correct - out) * dout;
  } else {
    std::for_each(p.begin(), p.end(), [&](Neuron *el) {
      delta_ = el->getWeight(num_pos) * el->getDelta();
    });
    delta_ *= dout;
  }
};

void Neuron::refreshWeight(double const &a_, double const &g_) {
  for (unsigned int i = 0; i < dw.size(); i++) {
    dw[i] *= g_;
    dw[i] += a_ * delta_ * n[i]->getResponse();
    w[i] += dw[i];
  }
};

void GraphNeuralNetwork::teachNetwork(const std::vector<double> &correct) {
  for (unsigned int i = 0; i < num_neurons_out; i++) {
    out_layer[i].evaluateErr(i, correct[i]);
  }
  for (int i = num_layers_hidden - 1; i >= 0; i--) {
    for (unsigned int j = 0; j < num_neurons_hidden; j++) {
      hidden_layer[i][j].evaluateErr(j, 0);
    }
  }
  for (unsigned int i = 0; i < num_neurons_input; i++) {
    input_layer[i].evaluateErr(i, 0);
  }
  for (unsigned int i = 0; i < num_neurons_out; i++) {
    out_layer[i].refreshWeight(a_, g_);
  }
  for (int i = num_layers_hidden - 1; i >= 0; i--) {
    for (unsigned int j = 0; j < num_neurons_hidden; j++) {
      hidden_layer[i][j].refreshWeight(a_, g_);
    }
  }
};
