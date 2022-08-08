#include <vector>
#include <cmath>

namespace s21{
class Matrix {
  public:
    Matrix(int rows, int columns, bool rand);
    Matrix(std::vector<double> values);
    Matrix(Matrix&& other);
    Matrix(const Matrix& other);

    double ActivationFunction(double value);
    Matrix Mult(Matrix& m);
    void PrintMatrix();
    ~Matrix(){};

  private:
    int rows_;
    int columns_;
    std::vector<std::vector<double>> matrix_;
};

};