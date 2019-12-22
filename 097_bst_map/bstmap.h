#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "map.h"

template<typename K, typename V>
class BstMap : public Map<K, V> {
 private:
  class Node {
   public:
    K key;
    V value;
    Node * left;
    Node * right;
    Node() : key(0), value(0), left(NULL), right(NULL) {}
    Node(const K & key, const V & value) :
        key(key),
        value(value),
        left(NULL),
        right(NULL) {}
  };
  Node * root;

 public:
  //Default constructor
  BstMap() : root(NULL) {}

  //Preorder traversal and copy(helper function)
  void copyPreorder(Node * current) {
    if (current != NULL) {
      this->add(current->key, current->value);
      copyPreorder(current->left);
      copyPreorder(current->right);
    }
  }

  //Copy Constructor
  BstMap(const BstMap & rhs) : root(NULL) {
    Node * current = rhs.root;
    copyPreorder(current);
  }

  //Destruct helper
  void des(Node * current) {
    if (current != NULL) {
      des(current->left);
      des(current->right);
      delete current;
    }
  }

  //Destructor
  virtual ~BstMap<K, V>() {
    des(root);
    root = NULL;
  }

  //Assignment operator
  BstMap & operator=(const BstMap & rhs) {
    if (this != &rhs) {
      des(root);
      root = NULL;
      Node * current = rhs.root;
      copyPreorder(current);
    }
    return *this;
  }

  Node * addhelp(Node * current, const K & key, const V & value) {
    if (current == NULL) {
      current = new Node(key, value);
      return current;
    }
    else {
      if (key < current->key) {
        current->left = addhelp(current->left, key, value);
      }
      else if (key > current->key) {
        current->right = addhelp(current->right, key, value);
      }
      else {
        current->value = value;
      }

      return current;
    }
  }
  virtual void add(const K & key, const V & value) { root = addhelp(root, key, value); }

  //lookup
  virtual const V & lookup(const K & key) const throw(std::invalid_argument) {
    Node * current = root;
    while (current != NULL) {
      if (key == current->key) {
        return current->value;
      }
      else if (key < current->key) {
        current = current->left;
      }
      else {
        current = current->right;
      }
    }
    throw std::invalid_argument("the key is not found");
  }

  //remove helper
  Node * removehelp(Node * current, const K & key) {
    if (current == NULL) {
      return current;
    }
    else if (key < current->key) {
      current->left = removehelp(current->left, key);
    }
    else if (key > current->key) {
      current->right = removehelp(current->right, key);
    }
    else if (current->key == key) {
      if (current->left == NULL) {
        Node * temp = current->right;
        delete current;
        return temp;
      }
      else if (current->right == NULL) {
        Node * temp = current->left;
        delete current;
        return temp;
      }
      else {
        Node * place = current;
        current = current->right;
        while (current->left != NULL) {
          current = current->left;
        }
        K k = current->key;
        V v = current->value;
        remove(current->key);
        place->key = k;
        place->value = v;
        return place;
      }
    }
    return current;
  }

  //remove
  virtual void remove(const K & key) { root = removehelp(root, key); }

  //  inorder helper
  void inorderhelp(Node * current) {
    if (current != NULL) {
      inorderhelp(current->left);
      std::cout << current->key << " " << current->value << "|\n";
      inorderhelp(current->right);
    }
  }

  //for testing use(inorder traverse)
  void inorder() {
    Node * current = root;
    inorderhelp(current);
  }
};
