#ifndef SRC_MLP_MODEL_H_
#define SRC_MLP_MODEL_H_
#include <QDebug>
#include <cmath>
#include <string>

#include "fileloader.h"
#include "neuralnetwork.h"

using std::string;

namespace s21 {
struct ErrorData {
    long count;
    double sum_sqr_err;
    double average_sq_err;
    long count_success;
    double precision, recall, f_measure, accuracy;
    s21::Matrix *confusion_matrix;
};

class Model {
 private:
    s21::FileLoader fileloader_;
    s21::NeuralNetwork *network_;
    std::vector<double> input_, out_, correct_, sum_err_;
    ErrorData err_;
    std::vector<double> input_value_;
    long num_images_;
    unsigned int num_layers_hidden_ = 2;
    unsigned int num_neurons_hidden_ = 100;
    unsigned int num_neurons_input_ = 784;
    unsigned int num_neurons_out_ = 26;
    unsigned int num_epochs_ = 0;
    unsigned int num_batches_ = 0;
    void normalizeInput();

 public:
    Model();
    ~Model();
    void InitNetwork(InitConfig &config);
    void loadDataset(string const &path);
    void activate(std::vector<double> input);
    void loadNextDataset();
    void TeachNetwork();
    void TeachNetwork(LearnConfig &learn_config);
    void createNetwork(InitConfig config);
    void UpdateErrData();
    void EvaluateErr();

    // simple functions
    auto CheckNetworkReady() -> bool { return network_ != nullptr; };
    auto CheckDataReady() -> bool { return num_images_ != 0; };
    auto getInputValues(int img_num = 0) -> std::vector<double> { return input_; }
    auto getOutValues() -> std::vector<double> { return out_; }
    auto getCorrectValue(int img_num) -> std::vector<double> { return correct_; }
    auto getCountOfElements() -> long { return num_images_; }
    auto resetErr() -> void;
    auto getErr() -> s21::ErrorData & { return err_; }
    auto ResetNetworkConfiguration() -> void {
        if (network_) delete network_;
        network_ = nullptr;
    };

    auto SetVectorPixelsOfImage(const std::vector<double> &vector_pixels) -> void {
        input_ = vector_pixels;
    }
    //  auto GetCurrentImageNumber() -> unsigned int;

    void SaveConfiguration(const std::string &filename);
    void LoadConfiguration(const std::string &filename, bool is_graph);
    InitConfig GetConfiguration();
};
}  // namespace s21
#endif  // SRC_MLP_MODEL_H_
