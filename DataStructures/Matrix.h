#ifndef MATRIX_H
#define MATRIX_H
#include <stdio.h>
#include <iostream>
#include "Vector.h"
#include "MeshUtils.h"
#include "Pair.h"
#include "Coordinate.h"
#include "DataConsts.h"

template <class T,int rows, int columns >class Matrix {
private:
  int nLines;
  int nColumns;
  T matrix[rows][columns];

public:
  Matrix(Vector3D v);
  Matrix(Vector4D v);
  
  Matrix(Vertex v);
  Matrix(Coordinate coord);
  
  
  Coordinate toCoordinate();
  Vector3D toVector3D();
  Vertex toVertex();
  

  T * operator[](int i) {
        return matrix[i];
  }
  Matrix(){
    this->nLines = rows;
    this->nColumns = columns;
    for(int i=0;i<rows;i++){
      for(int j=0;j<columns;j++){
        this->setVal(i,j,T());
      }
    }
  }

  T getVal(int x, int y) {
    return (this->matrix)[x][y];
  }

  Pair<int,int> getDimensions(){
    return {this->nLines,this->nColumns};
  }

  bool setVal(int x, int y, T val) {
    matrix[x][y] = val;
    return true;
  }

  static Matrix<T,rows,columns> identity(){
    Matrix<T,rows,columns> t = Matrix<T,rows,columns>();
    for(int i = 0;i<rows;i++){
      for(int j = 0;j<columns;j++){
         if(i==j){
           t.setVal(i,j,1);
         }
         else{
           t.setVal(i,j,0);
         }
      }
    }
    return t;
  }
  template <class C,int l,int k>
  Matrix<C,rows,k> operator*(Matrix<C,l,k> md){
    /*
    if(this->nColumns != md.getDimensions().left){
      return Matrix<C,rows,k>();
    }*/

    Matrix<C,rows,k> m = Matrix<C,rows,k>();
    for(int i =0;i<rows;i++){
      for(int j = 0;j<k;j++){
        T sum = 0;
        for(int s = 0;s<columns;s++){
          sum = sum + (this->getVal(i,s)*md.getVal(s,j));
        }
        m.setVal(i,j,sum);
      }
    }
    return m;
  }
  
  template <int l,int k>
  [[deprecated("not used anymore!!")]]
  T calcSum(Matrix<T,l,k> md,int line,int column){
  T sum = 0;
  for(int i =0;i<this->nColumns;i++){
    sum = sum + (this->getVal(line,i)*md.getVal(i,column));
  }
  return sum;
  }
  
  Matrix<T,rows,columns> operator-(Matrix<T,rows,columns> md){
    /*
    if((this->nLines != md.getDimensions().left)&&(this->nColumns != md.getDimensions().right)){
      return Matrix<T,rows,columns>();
    }*/
    Matrix<T,rows,columns> m = Matrix<T,rows,columns>();
    for(int i =0;i<rows;i++){
      for(int j = 0;j<columns;j++){
        m.setVal(i,j,this->getVal(i,j) - md.getVal(i,j));
      }
    }
    return m;
  }

  Matrix<T,rows,columns> operator*(double scalar){
    Matrix<T,rows,columns> m = Matrix<T,rows,columns>();
    for(int i =0;i<rows;i++){
      for(int j = 0;j<columns;j++){
        m.setVal(i,j,this->getVal(i,j)*scalar);
      }
    }
    return m;
  }

  Matrix<T,columns,rows> transpose(){
    Matrix<T,columns,rows> t = Matrix<T,columns,rows>();
    for(int i = 0;i<this->nLines;i++){
      for(int j = 0;j<this->nColumns;j++){
         t.setVal(j,i,this->getVal(i,j));
      }
    }
  return t;
}

  
};

template<class T,int n1 ,int n2 > inline std::ostream& operator<<(std::ostream& os, Matrix<T,n1,n2>& m){
    Pair<int,int> dim = m.getDimensions(); 
    T val;
    for(int i=0;i<dim.left;i++){
      for(int j=0;j<dim.right;j++){
        val = m.getVal(i,j);
        os<<val;
        os <<"  ";
      }
      os<<"\n";
    }
    return os;
}




template <class T,int l, int k> Matrix<T,l,k>::Matrix(Vector3D v){  
  //std::cout<<v.getElementAt(2)<<'\n';
  this->nLines = l;
  this->nColumns = 1;
  for (int i = 0; i < l-1; i++) {
    this->matrix[i][0] = v.getElementAt(i);
  }
  this->matrix[3][0] = 0;
}

template <class T,int l, int k> Matrix<T,l,k>::Matrix(Vector4D v){  
  //std::cout<<v.getElementAt(2)<<'\n';
  this->nLines = l;
  this->nColumns = 1;
  for (int i = 0; i < l; i++) {
    this->matrix[i][0] = v.getElementAt(i);
  }
}

template <class T,int l, int k> Matrix<T,l,k>::Matrix(Vertex v){  
  //std::cout<<v.getElementAt(2)<<'\n';
  this->nLines = l;
  this->nColumns = 1;
  this->matrix[0][0] = v.x;
  this->matrix[1][0] = v.y;
  this->matrix[2][0] = v.z;
  this->matrix[3][0] = 1;
}

template <class T,int l, int k> Matrix<T,l,k>::Matrix(Coordinate c){  
  //std::cout<<v.getElementAt(2)<<'\n';
  this->nLines = l;
  this->nColumns = 1;
  this->matrix[0][0] = c.x;
  this->matrix[1][0] = c.y;
  this->matrix[2][0] = c.z;
  this->matrix[3][0] = 1;
}

template <class T,int l, int k>
Coordinate  Matrix<T,l,k>::toCoordinate(){
    return Coordinate(matrix[0][0],matrix[1][0],matrix[2][0]);
  }

template <class T,int l, int k>
Vector3D Matrix<T,l,k>::toVector3D(){
    return Vector3D(matrix[0][0],matrix[1][0],matrix[2][0]);
  }

template <class T,int l, int k>
Vertex Matrix<T,l,k>::toVertex(){
    return Vertex(matrix[0][0],matrix[1][0],matrix[2][0]);
  }









/*
template <class T> Vector3D Matrix<T>::toVector(){
  Matrix<T> m = this;
  if(this->nLines>this->nColumns){
    m = this->transpose();
  }
  return Vector3D(m->getVal(0,0),m->getVal(0,1),m->getVal(0,2));
}
*/


#endif