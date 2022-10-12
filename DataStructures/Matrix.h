#ifndef MATRIX_H
#define MATRIX_H
#include <stdio.h>
#include <iostream>
#include "Vector.h"
#include "Pair.h"

template <class T >class Matrix {
public:
  Matrix(int lines, int columns);
  Matrix(Vector v);
  Matrix();
  bool setVal(int x, int y, T val);
  Pair<int> getDimensions();
  Matrix<T> * transpose();



  T getVal(int x, int y);

  Vector toVector();

  static double dot(Matrix a, Matrix b){
    if (!(a.nColumns == b.nColumns && a.nLines == b.nLines)) {
      return 0;
    }
    else {
      return a.getVal(0, 0) * b.getVal(0, 0) + a.getVal(1, 0) * b.getVal(1, 0) +
            a.getVal(2, 0) * b.getVal(2, 0);
    }
  }

  static Matrix<T> * identity(int nLines,int nColumns){
    Matrix<T> * t = new Matrix<T>(nColumns,nLines);
    for(int i = 0;i<nLines;i++){
      for(int j = 0;j<nColumns;j++){
         if(i==j){
           t->setVal(i,j,1);
         }
         else{
           t->setVal(i,j,0);
         }
      }
    }
  return t;
  }

  Matrix<T> * operator*(Matrix<T> md){
    if(this->nColumns != md.getDimensions().left){
      std::cout<<"fudeu\n";
      return nullptr;
    }

    Matrix<T> * m = new Matrix<T>(this->nLines,md.getDimensions().right);
    for(int i =0;i<this->nLines;i++){
      for(int j = 0;j<md.getDimensions().right;j++){
        T r = this->calcSum(md,i,j);
        //std::cout<<r;
        //std::cout<<"\n";
        m->setVal(i,j,r);

      }
    }
    return m;
  }
  Matrix<T> * operator-(Matrix<T> md){
    if((this->nLines != md.getDimensions().left)&&(this->nColumns != md.getDimensions().right)){
      return nullptr;
    }
    Matrix<T> * m = new Matrix<T>(this->nLines,md.getDimensions().right);
    for(int i =0;i<this->nLines;i++){
      for(int j = 0;j<md.getDimensions().right;j++){
        m->setVal(i,j,this->getVal(i,j) - md.getVal(i,j));

      }
    }
    return m;
  }

private:
  int nLines;
  int nColumns;
  T calcSum(Matrix<T>,int,int);
  T **matrix;
};

template <class T> Matrix<T>::Matrix(int lines, int columns) : matrix(new T * [lines]){
  this->nLines = lines;
  this->nColumns = columns;
  for (int i = 0; i < lines; i++) {


    T *l = new T [columns];
    this->matrix[i] = l;
  }
}


template <class T> Matrix<T>::Matrix(Vector v) : matrix(new double * [1]){
  this->nLines = 1;
  this->nColumns =3;
  for (int i = 0; i < this->nLines; i++) {


    T *l = new T [this->nColumns];
    this->matrix[i] = l;
  }
  this->setVal(0,0,v.getElementAt(0));
  this->setVal(0,1,v.getElementAt(1));
  this->setVal(0,2,v.getElementAt(2));

}

template <class T> Matrix<T>::Matrix(){}

template <class T> T Matrix<T>::getVal(int x, int y) {
  return (this->matrix)[x][y];
}

template <class T> Pair<int> Matrix<T>::getDimensions(){
  return {this->nLines,this->nColumns};
}

template <class T> bool Matrix<T>::setVal(int x, int y, T val) {
  (this->matrix)[x][y] = val;
  return true;
}

template <class T> Matrix<T> * Matrix<T>::transpose(){
    Matrix<T> * t = new Matrix<T>(this->nColumns,this->nLines);
    for(int i = 0;i<this->nLines;i++){
      for(int j = 0;j<this->nColumns;j++){
         t->setVal(j,i,this->getVal(i,j));
      }
    }
  return t;
}



template <class T> T Matrix<T>::calcSum(Matrix<T> md,int line,int column){
  T sum = 0;
  for(int i =0;i<this->nColumns;i++){
    sum = sum + (this->getVal(line,i)*md.getVal(i,column));
  }
  return sum;
}

template <class T> Vector Matrix<T>::toVector(){
  Matrix<T> *m = this;
  if(this->nLines>this->nColumns){
    m = this->transpose();
  }
  return Vector(m->getVal(0,0),m->getVal(0,1),m->getVal(0,2));
}

#endif