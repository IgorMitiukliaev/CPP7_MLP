#include <vector>
#include <cmath>

namespace s21{
class Matrix {
  public:
    Matrix(int rows, int columns, bool rand);
    Matrix(std::vector<double> values);
    Matrix(Matrix&& other);
    Matrix(const Matrix& other);

    double Sigmoid(double value);
    Matrix ForwardSignal(Matrix& m);
    Matrix BackSignalError(Matrix& err, Matrix& w);
    void CalcDeltaWeights(Matrix& m, Matrix& o, Matrix& s);
    void CalcWeights(Matrix& w, Matrix& d);
    std::vector<double> ToVector();
    void PrintMatrix();
    ~Matrix(){};

  private:
    int rows_;
    int columns_;
    std::vector<std::vector<double>> matrix_;
};

};
