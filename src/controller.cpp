#include "controller.h"
#include "fileloader.h"
#include "model.h"

using s21::Controller, s21::Model;

void Controller::createNetwork() {}

void Controller::loadDataset(string const &path){
  s21::FileLoader fileloader;
  fileloader.SetFileStream(path);
  while (fileloader.ReadElement()) {
    fileloader.PrintOutputValues(); // вывод результирующего вектора
    fileloader.PrintInputValues(false); // вывод значениями
    fileloader.PrintInputValues(true); // вывод звёздочками
//    break;
  }
};
