#ifndef MATRIX_H
#define MATRIX_H

#include <cmath>
#include <fstream>
#include <vector>

namespace s21 {
class Matrix {
 public:
  Matrix(){};
  Matrix(int rows, int columns);
  ~Matrix(){};
  void InitRand(int rows, int columns);
  static void Mult(const Matrix &m, const std::vector<double> &b,
                   std::vector<double> &c);
  static void TransposeMult(const Matrix &m, const std::vector<double> &b,
                            std::vector<double> &c);
  double &operator()(int i, int j);
  void Save(std::ofstream &out);
  void Load(std::ifstream &in);
  void PrintMatrix();

 private:
  int rows_;
  int columns_;
  double **matrix_;
};

};  // namespace s21
#endif  // MATRIX_H
