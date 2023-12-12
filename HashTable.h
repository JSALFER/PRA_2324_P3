#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream> 
#include <stdexcept> 
#include "Dict.h" 
#include "TableEntry.h"

#include "../PRA_2324_P1/ListLinked.h" //Inclusión del fichero ListLinked

template <typename V>
class HashTable : public Dict<V> {
//Atributos
private: 
  int n; //Núm de elementos almacenados en la tabla hash
  int max; //Tamaño de la tabla hash
  ListLinked<TableEntry<V>>* table; //Tabla de cubetas, representada por un array de punteros a listas enlazadas que almacenan pares clave->valor
  
//Métodos
private:
  int h(string key){ //Función hash
    int sum = 0;
    int size = key.length();
    for(int i = 0; i < size; i++){
      char c = key.at(i); //Obtiene caracter en posición i
      sum += int(c); //Obtiene valor ASCII de caracter
    }
    return sum % max;
  }
public: 
  HashTable(int size){ //Constructor
    table = new ListLinked<TableEntry<V>>[size]; //Reserva de espacio en memoria dinámica
    n = 0;
    max = size;
  } 
  ~HashTable(){ //Liberación de memoria dinámica reservada
    delete[] table;
  }
  int capacity(){ //Devuelve el número total de cubetas en la tabla
    return max;
  }
  friend ostream& operator<<(ostream &out, HashTable<V> &th){ //Sobrecarga global del operador << para imprimir el contenido de la tabla hash por pantalla
    out << "HashTable [entries: " << th.entries() << ", capacity: " << th.capacity() << "]" << endl;
    out << "==============" << endl << endl;
    
    for(int i = 0; i < th.max; i++){
      out << "== Cubeta " << i << " ==" << endl << endl;
      out << "List => [" << endl;
      for(int j = 0; j < th.table[i].size(); j++){
        out << "	" << th.table[i].get(j) << endl;
      }
      out << "]" << endl << endl;
    }
    return out;
  }
  V search(string key) override{ //Busca el valor correspondiente a key
    int pos = h(key);
    for(int i = 0; i < table[pos].size(); i++){
      if(table[pos].get(i).key == key){
        return table[pos].get(i).value;
      }
    }
    string str = "Key '" + key + "' not found!\n";
    throw runtime_error(str);
  }
  V operator[](string key){ //Sobrecarga del operador []. Devuelve el valor correspondiente a key
    int pos = h(key);
    return search(key);
  }
  void insert(string key, V value) override{ //Inserta el par key->value en el diccionario
    int pos = h(key);
    for(int i = 0; i < table[pos].size(); i++){
      if(table[pos].get(i).key == key){
        string str = "";
        str += "Key '";
        str += key;
        str += "' already exists!\n";
        throw runtime_error(str);
      }
    }
    TableEntry<V> aux(key, value);
    table[pos].prepend(aux);
    n++;
  }
  V remove(string key) override{ //Elimina el par key->value si se encuentra en el diccionario
    int pos = h(key);
    for(int i = 0; i < table[pos].size(); i++){
      if(table[pos].get(i).key == key){
        int x = table[pos].get(i).value;
        table[pos].remove(i);
        return x;
      }
    }
    string str = "Key '" + key + "' not found!\n";
    throw runtime_error(str);
  }
  int entries() override{ //Devuelve el núm de elementos en el diccionario
    return n;
  }
};

#endif
