#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream> 
#include <stdexcept> 
#include "Dict.h" 
#include "BSTree.h" 
#include "TableEntry.h" 

template <typename V> 
class BSTreeDict : public Dict<V>{
private: 
  BSTree<TableEntry<V>> *tree; //ABB con elementos de tipo TableEntry<V> para gestionar elementos de un diccionario
  
public: 
  BSTreeDict(){
    tree = new BSTree<TableEntry<V>>; //Guarda el espacio en memoria
  }
  ~BSTreeDict(){ //Método destructor
    delete tree;
  }
  friend ostream& operator<<(ostream &out, const BSTreeDict<V> &bs){ //Sobrecarga del operador << para imprimir el contenido del Diccionario por pantalla
    out << *bs.tree;
    return out;
  }
  V operator[](string key){ //Sobrecarga del operador []
    return search(key); //Interfaz al método search
  }
  
  //Métodos heredados de la clase Dict<V>
  void insert(string key, V value) override{
    TableEntry<V> *table = new TableEntry<V>(key, value); //Crea una nueva entrada del diccionario
    tree->insert(*table); //Inserta la clave-valor creada en el árbol
    delete table;
  }
  V search(string key) override{
    return (tree->search(key)).value; //Busca la clave-valor en el árbol, y devuelve el value
  }
  V remove(string key) override{
    V value = (tree->search(key)).value; //Busca la clave-valor en el árbol, y guarda value
    tree->remove(key); //Remueve la clave del árbol
    return value; //Retorna value
  }
  int entries() override{
    return tree->size(); //Devuelve el tamaño del árbol
  }
};

#endif
