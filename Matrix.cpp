#include <stdio.h>
#include "ds.h"

template <typename T> Matrix<T>::Matrix(int lines, int columns) {
  this->nLines = lines;
  this->nColumns = columns;
  int **m[lines];
  this->matrix = *m;
  for (int i = 0; i < lines; i++) {
    int c[columns];
    int *l = c;
    this->matrix[i] = l;
  }
}

template <typename T> T Matrix<T>::getVal(int x, int y) { return (this->matrix)[x][y]; }

template <typename T> bool Matrix<T>::setVal(int x, int y, T val) {
    (this->matrix)[x][y] = val;
    return true;
}

template <typename T> float Matrix<T>::dot(Matrix a, Matrix b) {
  if (!(a.nColumns == b.nColumns && a.nLines == b.nLines)) {
    printf("Erro na definição dos vetores: left_side: (%d,%d); right_side: (%d,%d)",
           a.nLines, a.nColumns, b.nLines, b.nColumns);
    return 0;
  } else {
    return a.getVal(0, 0) * b.getVal(0, 0) + a.getVal(1, 0) * b.getVal(1, 0) +
           a.getVal(2, 0) * b.getVal(2, 0);
  }
}
