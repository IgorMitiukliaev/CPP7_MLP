#include "model.h"

#include "graphneuralnetwork.h"
#include "matrix_neural_network.h"

using s21::Model;
s21::Model::Model() {
  fileloader_ = new FileLoader;
  network_ = nullptr;
  num_images_ = 0;
}

s21::Model::~Model() {
  delete fileloader_;
  delete network_;
}

void Model::InitNetwork(s21::InitConfig &config) {
  num_layers_hidden_ = config.num_layers_hidden;
  num_neurons_hidden_ = config.num_neurons_hidden,
  num_neurons_input_ = config.num_neurons_input,
  num_neurons_out_ = config.num_neurons_out;
  if (config.is_graph) {
    network_ = new GraphNeuralNetwork();
  } else {
    network_ = new MatrixNeuralNetwork();
  }
  network_->InitNetwork(&config);
}

void Model::loadDataset(string const &path) {
  fileloader_->SetFileStream(path);
  num_images_ = fileloader_->GetCountOfElements();
  fileloader_->ReadElement();
  input_ = fileloader_->GetInputValues();
  correct_ = fileloader_->GetOutputValues();
  input_value_ = fileloader_->GetOutputValues();
  normalizeInput();
};

void Model::loadNextDataset() {
  fileloader_->ReadElement();
  input_ = fileloader_->GetInputValues();
  normalizeInput();
  correct_ = fileloader_->GetOutputValues();
}

void Model::normalizeInput() {
  double max = *max_element(input_.begin(), input_.end());
  double min = *min_element(input_.begin(), input_.end());
  if (max > min) {
    std::for_each(input_.begin(), input_.end(), [min, max](double &value) {
      value = (value - min) / (max - min);
    });
  } else {
    std::for_each(input_.begin(), input_.end(),
                  [](double &value) { value = 0; });
  }
}

void Model::activate(std::vector<double> input_) {
  network_->Activate(input_);
  out_ = network_->getOutput();
};

void Model::TeachNetwork() { network_->teachNetwork(); }

void Model::TeachNetwork(LearnConfig &learn_config) {
  num_epochs_ = learn_config.num_epochs,
  num_batches_ = learn_config.num_batches;
  for (unsigned int i = 0, j = 0; i < num_epochs_; i++) {
    while (j++ < num_images_) {
      network_->teachNetwork(correct_);
      loadNextDataset();
    }
    fileloader_->StartReadElements();
  }
}
