#include <vector>
#include <cmath>
#include <fstream>

namespace s21{
class Matrix {
  public:
    Matrix() {};
    ~Matrix(){};
    void InitRand(int rows, int columns);
    static void Mult(const Matrix&m, const double*b, double *c);
    static void TransposeMult(const Matrix&m, const double*b, double *c);
    double& operator ()(int i, int j);
    void Save(std::ofstream& out);
    void Load(std::ifstream& in);
    void PrintMatrix();

  private:
    int rows_;
    int columns_;
    double **matrix_;
};

};
