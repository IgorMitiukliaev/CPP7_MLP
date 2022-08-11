#include "fileloader.cpp"
#include <iostream>

int main () {
  std::string filename = "../datasets/emnist-letters-train.csv";
  s21::FileLoader fileloader;
  fileloader.SetFileStream(filename);
  std::cout << "Count of elements:" << fileloader.GetCountOfElements() << std::endl;
  fileloader.StartReadElements();
  while (fileloader.ReadElement()) {
    fileloader.PrintOutputValues(); // вывод результирующего вектора
  //  fileloader.PrintInputValues(false); // вывод значениями
    fileloader.PrintInputValues(true); // вывод звёздочками
    break;
  }
  return 0;
}