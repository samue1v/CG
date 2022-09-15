#ifndef TRIPLE_H
#define TRIPLE_H

template <class T> class Triple{
  public:
    Triple(T a, T b, T c);
    T getElementAt(int index);
    bool setElementAt(int index,T ele);
  private:
    T triple[3];
};

template <class T>Triple<T>::Triple(T a,T b,T c) : triple[0](a),triple[1](b),triple[2](2){}
#endif

Triple<float> 