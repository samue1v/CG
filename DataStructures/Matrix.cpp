/*
#include "Matrix.h"
#include <stdio.h>

template <class T> Matrix<T>::Matrix(int lines, int columns) {
  this->nLines = lines;
  this->nColumns = columns;
  T **m[lines];
  this->matrix = *m;
  for (int i = 0; i < lines; i++) {
    T c[columns];
    T *l = c;
    this->matrix[i] = l;
  }
}

template <class T> Matrix<T>::Matrix(){}

template <class T> T Matrix<T>::getVal(int x, int y) {
  return (this->matrix)[x][y];
}

template <class T> bool Matrix<T>::setVal(int x, int y, T val) {
  (this->matrix)[x][y] = val;
  return true;
}
*/


