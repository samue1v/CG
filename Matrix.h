#ifndef MATRIX_H
#define MATRIX_H
#include <stdio.h>
#include <iostream>

template <class T >class Matrix {
public:
  Matrix(int lines, int columns);
  Matrix();
  bool setVal(int x, int y, T val);
  T getVal(int x, int y);
  static float dot(Matrix a, Matrix b){
    if (!(a.nColumns == b.nColumns && a.nLines == b.nLines)) {
      return 0;
    } 
    else {
      return a.getVal(0, 0) * b.getVal(0, 0) + a.getVal(1, 0) * b.getVal(1, 0) +
            a.getVal(2, 0) * b.getVal(2, 0);
    }
  }

private:
  int nLines;
  int nColumns;
  T **matrix;
};
template <class T> Matrix<T>::Matrix(int lines, int columns) : matrix(new T * [lines]){
  this->nLines = lines;
  this->nColumns = columns;
  /*
  T **m[lines];
  this->matrix = *m;*/
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

#endif