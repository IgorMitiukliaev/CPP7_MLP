#include "matrix.h"
#include <ctime>
#include <cstdlib>
#include <iostream>

void s21::Matrix::Matrix::InitRand(int rows, int columns) {
  rows_ = rows;
  columns_ = columns;
  std::srand(time(NULL));
  matrix_ = new double* [rows_];
  for (auto i = 0; i < rows_; i++) {
    matrix_[i] = new double[columns_];
  }
  for (auto i = 0; i < rows_; i++) {
    for (auto j = 0; j < columns_; j++) {
      matrix_[i][j] = -1+0.01*(std::rand()%201);
      }
  }
}

void s21::Matrix::Mult(const Matrix&m, const double*b, double *c){
    for (auto i = 0; i < m.rows_; i++) {
        c[i] = 0;
        for (auto j = 0; j < m.columns_; j++) {
            c[i] += m.matrix_[i][j]*b[j];
        }
    }
}

void s21::Matrix::TransposeMult(const Matrix&m, const double*b, double *c){
    for (auto i = 0; i < m.columns_; i++) {
        c[i] = 0;
        for (auto j = 0; j < m.rows_; j++) {
            c[i] += m.matrix_[j][i]*b[j];
        }
    }
}

double& s21::Matrix::operator ()(int i, int j) {
    return matrix_[i][j];
}

void s21::Matrix::PrintMatrix() {
  std::cout << std::endl << std::endl;
  std::cout << "Rows: " <<rows_ <<" Columns:" << columns_ << std::endl;
  for (auto i = 0; i < rows_; i++) {
    for (auto j = 0; j < columns_; j++) {
      std::cout << matrix_[i][j]<< " ";
    }
    std::cout << std::endl;
  }
}