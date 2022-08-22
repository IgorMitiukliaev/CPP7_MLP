#include <gtest/gtest.h>

#include "../MLP/graphneuralnetwork.h"
#include "../MLP/matrixneuralnetwork.h"

void InitMatrixNeuralNetwork(s21::MatrixNeuralNetwork *const matrix_neural_network,
                             const unsigned int num_layers_hidden = 2,
                             const unsigned int num_neurons_hidden = 100,
                             const unsigned int num_neurons_input = pow(28, 2),
                             const unsigned int num_neurons_out = 26) {
    s21::InitConfig config;
    config.is_graph = false;
    config.num_layers_hidden = num_layers_hidden;
    config.num_neurons_hidden = num_neurons_hidden;
    config.num_neurons_input = num_neurons_input;
    config.num_neurons_out = num_neurons_out;
    matrix_neural_network->InitNetwork(&config);
}

void InitGraphNeuralNetwork(s21::GraphNeuralNetwork *const graph_neural_network,
                            const unsigned int num_layers_hidden = 2,
                            const unsigned int num_neurons_hidden = 100,
                            const unsigned int num_neurons_input = pow(28, 2),
                            const unsigned int num_neurons_out = 26) {
    s21::InitConfig config;
    config.is_graph = false;
    config.num_layers_hidden = num_layers_hidden;
    config.num_neurons_hidden = num_neurons_hidden;
    config.num_neurons_input = num_neurons_input;
    config.num_neurons_out = num_neurons_out;
    graph_neural_network->InitNetwork(&config);
}

TEST(matrix_neural_network, InitNetwork) {
    s21::MatrixNeuralNetwork matrix_neural_network;
    InitMatrixNeuralNetwork(&matrix_neural_network);
    ASSERT_TRUE(true);
}

TEST(matrix_neural_network, Activate) {
    s21::MatrixNeuralNetwork matrix_neural_network;
    InitMatrixNeuralNetwork(&matrix_neural_network);
    std::vector<double> input(pow(28, 2));
    matrix_neural_network.Activate(input);
    ASSERT_TRUE(true);
}

TEST(matrix_neural_network, getOutput) {
    bool result = true;
    s21::MatrixNeuralNetwork matrix_neural_network;
    InitMatrixNeuralNetwork(&matrix_neural_network);
    std::vector<double> output;
    output = matrix_neural_network.GetOutput();
    if (output.size() != 26)
        result = false;
    ASSERT_TRUE(result);
}

TEST(matrix_neural_network, SaveConfiguration) {
    s21::MatrixNeuralNetwork matrix_neural_network;
    InitMatrixNeuralNetwork(&matrix_neural_network);
    matrix_neural_network.SaveConfiguration("configurations/test.bin");
    ASSERT_TRUE(true);
}

TEST(matrix_neural_network, LoadConfiguration) {
    s21::MatrixNeuralNetwork matrix_neural_network;
    InitMatrixNeuralNetwork(&matrix_neural_network);
    matrix_neural_network.LoadConfiguration("configurations/test.bin");
    ASSERT_TRUE(true);
}

TEST(matrix_neural_network, GetConfiguration) {
    s21::MatrixNeuralNetwork matrix_neural_network;
    InitMatrixNeuralNetwork(&matrix_neural_network);
    matrix_neural_network.LoadConfiguration("configurations/test.bin");
    s21::InitConfig config = matrix_neural_network.GetConfiguration();
    ASSERT_TRUE(true);
}

TEST(matrix_neural_network, teachNetwork) {
    s21::MatrixNeuralNetwork matrix_neural_network;
    InitMatrixNeuralNetwork(&matrix_neural_network);
    std::vector<double> vector(26);
    matrix_neural_network.TeachNetwork(vector);
    ASSERT_TRUE(true);
}

// Graphneuralnetwork

TEST(graph_neural_network, InitNetwork) {
    s21::GraphNeuralNetwork graph_neural_network;
    InitGraphNeuralNetwork(&graph_neural_network);
    ASSERT_TRUE(true);
}

TEST(graph_neural_network, Activate) {
    s21::GraphNeuralNetwork graph_neural_network;
    InitGraphNeuralNetwork(&graph_neural_network);
    std::vector<double> input(pow(28, 2));
    graph_neural_network.Activate(input);
    ASSERT_TRUE(true);
}

TEST(graph_neural_network, getOutput) {
    bool result = true;
    s21::GraphNeuralNetwork graph_neural_network;
    InitGraphNeuralNetwork(&graph_neural_network);
    std::vector<double> output;
    output = graph_neural_network.GetOutput();
    if (output.size() != 26)
        result = false;
    ASSERT_TRUE(result);
}

TEST(graph_neural_network, SaveConfiguration) {
    s21::GraphNeuralNetwork graph_neural_network;
    InitGraphNeuralNetwork(&graph_neural_network);
    graph_neural_network.SaveConfiguration("configurations/test.bin");
    ASSERT_TRUE(true);
}

TEST(graph_neural_network, LoadConfiguration) {
    s21::GraphNeuralNetwork graph_neural_network;
    InitGraphNeuralNetwork(&graph_neural_network);
    graph_neural_network.LoadConfiguration("configurations/test.bin");
    ASSERT_TRUE(true);
}

TEST(graph_neural_network, GetConfiguration) {
    s21::GraphNeuralNetwork graph_neural_network;
    InitGraphNeuralNetwork(&graph_neural_network);
    graph_neural_network.LoadConfiguration("configurations/test.bin");
    s21::InitConfig config = graph_neural_network.GetConfiguration();
    ASSERT_TRUE(true);
}

TEST(graph_neural_network, teachNetwork) {
    s21::GraphNeuralNetwork graph_neural_network;
    InitGraphNeuralNetwork(&graph_neural_network);
    std::vector<double> vector(26);
    graph_neural_network.TeachNetwork(vector);
    ASSERT_TRUE(true);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
