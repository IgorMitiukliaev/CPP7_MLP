#include "matrix.h"
#include <ctime>
#include <cstdlib>
#include <iostream>

s21::Matrix::Matrix(int rows, int columns, bool rand): rows_(rows), columns_(columns){
  if(rand) { 
    std::srand(time(NULL));
    for (auto i = 0; i < rows_; i++) {
      std::vector<double> row;
      for (auto j = 0; j < columns_; j++) {
        row.push_back(-1+0.00001*(std::rand()%200001));
      }
      matrix_.push_back(row);
    }
  } else {
    for (auto i = 0; i < rows_; i++) {
      std::vector<double> row;
      for (auto j = 0; j < columns_; j++) {
        row.push_back(0);
      }
      matrix_.push_back(row);
    }
  }

}

s21::Matrix::Matrix(std::vector<double> values) {
  rows_ = 1;
  columns_ = values.size();
  std::vector<double> row;
  for (auto i = 0; i < columns_; i++) {
    row.push_back(values[i]);
  }  
  matrix_.push_back(values);
}

s21::Matrix::Matrix(const s21::Matrix& other) {
    rows_ = other.rows_;
    columns_ = other.columns_;
    for (auto i = 0; i < rows_; i++) {
      std::vector<double> row;
      for (auto j = 0; j < columns_; j++) {
        row.push_back(other.matrix_[i][j]);
      }
      matrix_.push_back(row);
    }

}

s21::Matrix::Matrix(s21::Matrix&& other) {
    if (&other != this) {
        rows_ = other.rows_;
        columns_ = other.columns_;
        matrix_ = other.matrix_;
        other.rows_ = 0;
    }
}


s21::Matrix s21::Matrix::ForwardSignal(s21::Matrix& m) {
  Matrix res(rows_, m.columns_, false);
  for (auto i = 0; i < rows_; i++) {
    for (auto j = 0; j < m.columns_; j++) {
      for (auto k = 0; k < columns_; k++) {
        res.matrix_[i][j] += matrix_[i][k]*m.matrix_[k][j];
      }
      res.matrix_[i][j] = Sigmoid(res.matrix_[i][j]);
    }
  }
  return res;
}

void s21::Matrix::PrintMatrix() {
  std::cout << std::endl << std::endl;
  std::cout << "Rows: " <<rows_ <<" Columns:" << columns_ << std::endl;
  for(auto row : matrix_) {
    for(auto element : row) {
      std::cout << element <<" ";
    }
    std::cout << std::endl;
  }
}

double s21::Matrix::Sigmoid(double value) {
  return 1/(1+exp(-value));
}