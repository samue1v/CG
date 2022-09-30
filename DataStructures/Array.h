#ifndef ARRAY_H
#define ARRAY_H
#include <stdio.h>
template <class T> class Array {
public:
  Array(T * value);
  Array();
  bool push(T * value);
	bool setNext(Array<T> * value);
  Array<T> * getNext();

private:
  int pos;
  T * value;
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
	return true;
}

template <class T> bool Array<T>::setNext(Array<T> *next){
	Array<T> * temp = this->next;
	if(next->getNext()){
		next->push(temp);
	}
	this->next = next;
	return true;
}

template <class T> Array<T> * Array<T>::getNext(){
	return this->next;
}

#endif
