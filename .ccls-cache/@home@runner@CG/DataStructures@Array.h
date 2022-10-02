#ifndef ARRAY_H
#define ARRAY_H
#include <stdio.h>
template <class T> class Array {
public:
  Array(T * value);
  Array();
  bool push(T * value);
	bool setLast(Array<T> * value);
	bool setPos(int pos);
  Array<T> * getNext();

private:
  int pos;
  T * value;
	Array<T> *first;
  Array<T> *next;
  Array<T> *last;
};

template <class T> Array<T>::Array() {}

template <class T> Array<T>::Array(T * value) {
  this->value = value;
  this->pos = 0;
  this->next = NULL;
  this->last = this;
}
template <class T> bool Array<T>::push(T * value) {
  Array<T> *newItem = new Array<T>(value);
	this->last->setNext(newItem);
	this->last = newItem;
	newItem->setPos((this -> pos)+1);
	newItem->first = this;
	return true;
}


template <class T> Array<T> * Array<T>::getNext(){
	return this->next;
}

template <class T> bool Array<T>::setPos(int pos){
	this->pos = pos;
}

#endif
