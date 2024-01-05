#ifndef BSNODE_H
#define BDNODE_H

#include <iostream>
#include <ostream> 

using namespace std;

template <typename T> 
class BSNode{
public: 
  T elem; //El elemento de tipo T almacenado en el nodo
  BSNode<T> *left; //Puntero al nodo sucesor izquierdo
  BSNode<T> *right; //Puntero al nodo sucesor derecho
  
  BSNode(T elem, BSNode<T> *left = nullptr, BSNode<T> *right = nullptr){ //Constructor, punteros nulos por defecto
    this->elem = elem;
    this->left = left;
    this->right = right;
  }
  friend ostream& operator<<(ostream &out, const BSNode<T> &bsn){ //Sobrecarga del operador <<
    out << bsn.elem; //Imprime el elemento del nodo
    return out;
  }
};

#endif
