#ifndef BSTREE_H
#define BSTREE_H

#include <ostream> 
#include <stdexcept> 
#include "BSNode.h" 

using namespace std;

template <typename T> 
class BSTree{
private: 
  int nelem; //Número de elementos almacenados en el ABB
  BSNode<T> *root; //Nodo raíz del ABB

//CREACIÓN Y TAMAÑO
public: 
  BSTree(){ //Constructor. Crea un ABB vacío
    nelem = 0;
    root = nullptr;
  }
  int size() const{ //Devuelve el número de elementos nelem del ABB
    return nelem;
  }
  
//BÚSQUEDA DE ELEMENTOS
public: 
  T search(T e) const{ //Busca y devuelve el elemento e de tipo T en el ABB. Método lanzadera del método recursivo privado siguiente
    BSNode<T> *found = search(root, e); //Lanza la función *search
    return found->elem;
  }

private: 
  BSNode<T> *search(BSNode<T> *n, T e) const{ //Método recursivo para la búsqueda de elementos en el ABB.
    if(n == nullptr){ //Si se llega al final, se lanza excepción
      throw runtime_error("Element not found!"); 
    }
    else if(n->elem < e){ //Si el elemento del nodo es menor que el buscado, recursión con el nodo de la derecha (los elementos mayores están a la derecha)
      return search(n->right, e);
    }
    else if(n->elem > e){ //Si el elemento del nodo es mayor que el buscado, recursión con el nodo de la izquierda (los elementos menores están a la izquierda)
      return search(n->left, e);
    }
    return n; //Devuelve el nodo encontrado
  }

public: 
  T operator[](T e) const{ //Sobrecarga del operador []. Interfaz del método search(T e)
    return search(e);
  }
  
//INSERCIÓN DE ELEMENTOS
public: 
  void insert(T e){ //Método lanzadera del método insert recursivo
    root = insert(root, e);
    nelem++;
  }
  
private: 
  BSNode<T> *insert(BSNode<T> *n, T e){ //Método recursivo para la inserción ordenada de elementos
    if(n == nullptr){ //Si se llega al final, el elemento está duplicado
      return new BSNode<T>(e);
    }
    else if(n->elem == e){ //Si n.elem = e, el elemento está duplicado
      throw runtime_error("Duplicated element!");
    }
    else if(n->elem < e){ //Si n.elem < e, insertar a la derecha
      n->right = insert(n->right, e);
    }
    else{ //Si n.elem > e, insertar a la izquierda
      n->left = insert(n->left, e);
    }
    return n;
  }

//RECORRIDO E IMPRESIÓN DEL ÁRBOL
public: 
  friend ostream& operator<<(ostream &out, BSTree<T> &bst){ //Sobrecarga del operador << para mostrar a través de out los contenidos del ABB bst, realizando un recorrido inorden o simétrico del árbol para mostrar los elementos ordenados de menor a mayor
    bst.print_inorder(out, bst.root); //Método privado en bst, parámetros out y raíz del árbol
    return out;
  }

private: 
  void print_inorder(ostream &out, BSNode<T> *n) const{ //Recorrido inorden para mostrar a través de out los elementos ordenados de menor a mayor
    if(n != nullptr){
      print_inorder(out, n->left);
      out << " ";
      out << *n;
      print_inorder(out, n->right);
    }
  }

//ELIMINACIÓN DE ELEMENTOS
public: 
  void remove(T e){ //Elimina el elemento de tipo T del ABB. Método lanzadera
    root = remove(root, e);
    nelem--;
  }
  
private: 
  BSNode<T> *remove(BSNode<T> *n, T e){ //Método recursivo para la eliminación de elementos
    if(n == nullptr){ //Si llega al final, lanza excepción
      throw runtime_error("Element not found!");
    }
    else if(n->elem < e){ //Si n->elem < e, elimino el de la derecha
      n->right = remove(n->right, e);
    }
    else if(n->elem > e){ //Si n->elem > e, elimino el de la izquierda
      n->left = remove(n->left, e);
    }
    else{
      if(n->left != nullptr && n->right != nullptr){ //Si tiene 2 descendientes
        n->elem = max(n->left); //Llamada a función max
        n->left = remove_max(n->left); //Llamada a función remove_max
      }
      else{ //1 ó 0 descendientes
        n = (n->left != nullptr) ? n->left : n->right; //Si n->left es diferente a nullptr, devuelve n->left. Sino, devuelve n->right
      }
    }
    return n;
  }
  
  T max(BSNode<T> *n) const{ //Método recursivo que devuelve el elemento de máximo valor contenido en el árbol cuya raíz es n
    if(n == nullptr){
      throw runtime_error("Elemento no encontrado.");
    }
    else if(n->right != nullptr){ //Si n->right != nullptr, recursión con el nodo de la derecha
      return max(n->right);
    }
    else{
      return n->elem;
    }
  }
  
  BSNode<T> *remove_max(BSNode<T> *n){ //Método recursvio que elimina el elemento de máximo valor contenido en el árbol cuya raíz es n
    if(n->right == nullptr){
      return n->left;
    }
    else{
      n->right = remove_max(n->right);
      return n;
    }
  }
  
//DESTRUCCIÓN
public: 
  ~BSTree(){ //Destructor
    delete_cascade(root);
  }
  
private: 
  void delete_cascade(BSNode<T> *n){ //Método recursivo para liberación de la memoria dinámica ocupada por los objetos de tipo BSNode<T> que conforman el árbol cuya raíz es n
    if(n == nullptr){ //Si n = nullptr, retornar. Sino, recursión con derecha e izquierda y eliminar n
      return;
    }
    delete_cascade(n->left);
    delete_cascade(n->right);
    delete n;
  }
};

#endif
