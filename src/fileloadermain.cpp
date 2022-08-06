#include "fileloader.cpp"

int main () {
  std::string filename = "../datasets/emnist-letters-train.csv";
  s21::FileLoader fileloader;
  fileloader.SetFileStream(filename);
  while (fileloader.ReadElement()) {
    fileloader.PrintOutputValues(); // вывод результирующего вектора
    fileloader.PrintInputValues(false); // вывод значениями
    fileloader.PrintInputValues(true); // вывод звёздочками
    break;
  }
  return 0;
}