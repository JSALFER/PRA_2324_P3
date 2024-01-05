//Declaración e implementación de la clase TableEntry

#ifndef TABLEENTRY_H
#define TABLEENTRY_H

#include <string> 
#include <ostream> 

using namespace std;

template <typename V>
class TableEntry{
public: 
  string key; //Clave del par
  V value; //Valor del par
  
public: 
  TableEntry(string key, V value){ //Método constructor
    this->key = key;
    this->value = value;
  }
  TableEntry(string key){ //Crea una entrada solo con clave
    this->key = key;
  }  
  TableEntry(){ //Crea una entrada con la clave "" y sin valor
    key = "";
  }
  friend bool operator==(const TableEntry<V> &te1, const TableEntry<V> &te2){ //Sobrecarga global del operador == para determinar si dos instancias son iguales
    if(te1.key == te2.key){
      return true;
    }
    else{ 
      return false;
    }
  }
  friend bool operator !=(const TableEntry<V> &te1, const TableEntry<V> &te2){ //Sobrecarga global del operador != para determinar si dos instancias son diferentes
    if(te1.key != te2.key){
      return true;
    }
    else{ 
      return false;
    }
  }
  friend ostream& operator<<(ostream &out, const TableEntry<V> &te){ //Sobrecarga global del operador << para imprimir el contenido de la entrada por pantalla
    out << "('" << te.key << "' => " << te.value << ")";
    return out;
  }
  friend bool operator<(const TableEntry<V> &te1, const TableEntry<V> &te2){ //Sobrecarga global del operador < para comparar dos valores del árbol
    if(te1.key < te2.key){
      return true;
    }
    else{
      return false;
    }
  }
  friend bool operator>(const TableEntry<V> &te1, const TableEntry<V> &te2){ //Sobrecarga global del operador > para comparar dos valores del árbol
    if(te1.key > te2.key){
      return true;
    }
    else{
      return false;
    }
  }  
};

#endif 
    
