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
  delete err_.confusion_matrix;
}

void Model::InitNetwork(s21::InitConfig &config) {
  num_layers_hidden_ = config.num_layers_hidden;
  num_neurons_hidden_ = config.num_neurons_hidden,
  num_neurons_input_ = config.num_neurons_input,
  num_neurons_out_ = config.num_neurons_out;
  if (network_) delete network_;
  if (config.is_graph) {
    network_ = new GraphNeuralNetwork();
  } else {
    network_ = new MatrixNeuralNetwork();
  }
  network_->InitNetwork(&config);
  err_ = {0};
  err_.confusion_matrix = new Matrix(num_neurons_out_, num_neurons_out_);
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
  bool check = fileloader_->ReadElement();
  if (!check) {
    fileloader_->StartReadElements();
    check = fileloader_->ReadElement();
  }
  if (!check) throw std::runtime_error("Error reading file: rewind failed");
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
  UpdateErrData();
};

void Model::TeachNetwork() { network_->teachNetwork(correct_); }

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

void Model::SaveConfiguration(const std::string &filename) {
  network_->SaveConfiguration(filename);
}

void Model::LoadConfiguration(const std::string &filename, bool is_graph) {
  if (network_) delete network_;
  if (is_graph) {
    network_ = new GraphNeuralNetwork();
  } else {
    network_ = new MatrixNeuralNetwork();
  }
  network_->LoadConfiguration(filename);
}

s21::InitConfig Model::GetConfiguration() {
  return network_->GetConfiguration();
}

void Model::UpdateErrData() {
  err_.count++;
  for (int i = 0; i < out_.size(); i++)
    err_.sum_sqr_err += pow(correct_[i] - out_[i], 2);
  err_.average_sq_err = std::sqrt(err_.sum_sqr_err / err_.count);
  int correctLetterIndex =
      std::max_element(correct_.begin(), correct_.end()) - correct_.begin();
  int answerLetterIndex =
      std::max_element(out_.begin(), out_.end()) - out_.begin();
  if (correctLetterIndex == answerLetterIndex) err_.count_success++;
  ((*err_.confusion_matrix)(answerLetterIndex, correctLetterIndex))++;
}
