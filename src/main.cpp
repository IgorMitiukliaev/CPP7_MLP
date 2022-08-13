#include <QApplication>

#include "graphneuralnetwork.h"
#include "mainwindow.h"
#include "neuralnetwork.h"

int main(int argc, char* argv[]) {
  s21::Model m;
  s21::Controller c(&m);
  QApplication a(argc, argv);
  MainWindow w(&c);
  w.show();
  return a.exec();
}
