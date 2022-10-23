#ifndef ARRAY_H
#define ARRAY_H
#include <stdio.h>
#include <ostream>
template <class T> class Array {
public:
  Array(int initCapacity);
  Array();
  bool push(T value);
  bool remove(int index);
  T getElementAt(int index);
  int getSize();
  
  template <class C> friend std::ostream& operator<<(std::ostream& os, Array<C>& a);

private:
  bool allocMem(); 
  int capacity;
  int size;
  T * container;
};


template <class T> 
Array<T>::Array() {
  this->capacity = 10;
  this->size = 0;
  container = new T[capacity];
}

template <class T> 
Array<T>::Array(int initCapacity) {
    this->capacity = initCapacity;
    this->size = 0;
   container = new T[capacity];
}

template <class T>
int Array<T>::getSize(){
  return this->size;
}

template <class T>
T Array<T>::getElementAt(int index){
  if(index>this->size){
    return T();
  }
  return this->container[index];
}

template <class T> 
bool Array<T>::push(T value) {
  if(size>=capacity){
    allocMem();
  }
  container[size] = value;
  size++;
  return true;

}

template <class T> 
bool Array<T>::remove(int index){
  if(!container[index]){
    return false;
  }
  T removedVal = this->container[index];
  int lastPos = this->size-1;
  this->size--;
  if(size<=1){
    return removedVal;
  }
  this->container[index] = this->container[lastPos];
  this->container[lastPos] = T();
  
  return removedVal;
}

template <class T> 
bool  Array<T>::allocMem(){
  int newCapacity = this->capacity*2;
  this->capacity = newCapacity;
  T * newContainer = new T[newCapacity];
  std::copy(container, container + std::min(this->capacity, newCapacity), newContainer);
  delete[] container;
  container = newContainer;
  return true;
}

template <class T> std::ostream& operator<<(std::ostream& os, Array<T>& a){
    for(int i = 0;i<a.size;i++){
      os << a.container[i];
      os<< " ";
    }
    os<<"\n";
    return os;
}

#endif
