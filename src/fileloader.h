#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>

namespace s21 {

class FileLoader {
 public:
  FileLoader() {};
  ~FileLoader() {};
  bool SetFileStream(std::string filename);
  std::vector<double> GetOutputValues();
  std::vector<double> GetInputValues();
  bool ReadElement();
  void PrintOutputValues();  //  потом удалить
  void PrintInputValues(bool view);  //  потом удалить
 private:
  std::ifstream filestream_;
  std::vector<double> output_values_;
  std::vector<double> input_values_;
  void SetOutputValues(int value);
  void ClearData();
  std::string GetLine();
  std::string GetToken(const std::string& line, size_t pos);
  size_t FindSeparatorPosition(const std::string& line);
  void EraseToken(std::string& line, size_t pos);
  void AddValueToOutputVector(const std::string& value);
};

};
