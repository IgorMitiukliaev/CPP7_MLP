#include "fileloader.h"

bool s21::FileLoader::SetFileStream(std::string filename) {
  filestream_.open(filename);
  return filestream_.good();
}

void s21::FileLoader::SetOutputValues(int value) {
  int count_letters = 26;
  for (int i = 1; i <= count_letters; i++) {
    if (i == value) {
      output_values_.push_back(1.);
    } else {
      output_values_.push_back(0.);   
    }
  }
}

void s21::FileLoader::ClearData() {
  input_values_.clear();
  output_values_.clear();
}

std::string s21::FileLoader::GetLine() {
  std::string line;
  std::getline(filestream_, line);
  return line;
}

size_t s21::FileLoader::FindSeparatorPosition(const std::string& line) {
  std::string separator = ",";
  size_t pos = line.find(separator);
  return pos;
}

std::string s21::FileLoader::GetToken(const std::string& line, size_t pos) {
  std::string token = line.substr(0, pos);
  return token;
}

void s21::FileLoader::EraseToken(std::string& line, size_t pos) {
  line.erase(0, pos + 1);
}

void s21::FileLoader::AddValueToOutputVector(const std::string& str) {
  double color_max_value = 256;
  double value = std::stod(str) / color_max_value;
  input_values_.push_back(value);
}

bool s21::FileLoader::ReadElement() {
  bool file_is_good = filestream_.good();
  if (file_is_good) {
    ClearData();
    std::string line = GetLine(); 
    size_t pos = FindSeparatorPosition(line);
    auto token = GetToken(line, pos);
    if (pos != std::string::npos) {
      SetOutputValues(std::stoi(token));
      EraseToken(line, pos);
      while ((pos = FindSeparatorPosition(line)) != std::string::npos) {
        token = GetToken(line, pos);
        AddValueToOutputVector(token);
        EraseToken(line, pos);
      }
      AddValueToOutputVector(token);
    } else {
      file_is_good = false;   
    }
  }
  return file_is_good;
}

std::vector<double> s21::FileLoader::GetOutputValues() {
  return output_values_;
}

std::vector<double> s21::FileLoader::GetInputValues() {
  return input_values_;
}

void s21::FileLoader::PrintOutputValues() {
  std::vector<double> output = GetOutputValues();
  for (auto iter:output) {
    std::cout << iter;
  }
  std::cout << std::endl;
}

void s21::FileLoader::PrintInputValues(bool view) {
  std::vector<double> input = GetInputValues();
  int i = 0;
  for (auto iter:input) {
    if (view) { 
      if (iter == 0.0) {
        std::cout << " ";
      } else {
        std::cout << "*";
      }
    } else {
      std::cout << iter;
    }
    i++;
    if (i%28 == 0) std::cout << std::endl;
  }
}