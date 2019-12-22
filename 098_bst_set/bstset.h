#include <cstdlib>
#include <iostream>
#include <stdexcept>

#include "set.h"

template<typename T>
class BstSet : public Set<T> {
 private:
  class Node {
   public:
    T key;
    Node * left;
    Node * right;
    Node() : key(0), left(NULL), right(NULL) {}
    Node(const T & key) : key(key), left(NULL), right(NULL) {}
  };
  Node * root;

 public:
  //Default constructor
  BstSet() : root(NULL) {}

  //Preorder traversal and copy(helper function)
  void copyPreorder(Node * current) {
    if (current != NULL) {
      this->add(current->key);
      copyPreorder(current->left);
      copyPreorder(current->right);
    }
  }

  //Copy Constructor
  BstSet(const BstSet & rhs) : root(NULL) {
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
  virtual ~BstSet<T>() {
    des(root);
    root = NULL;
  }

  //Assignment operator
  BstSet & operator=(const BstSet & rhs) {
    if (this != &rhs) {
      des(root);
      root = NULL;
      Node * current = rhs.root;
      copyPreorder(current);
    }
    return *this;
  }

  Node * addhelp(Node * current, const T & key) {
    if (current == NULL) {
      current = new Node(key);
      return current;
    }
    else {
      if (key < current->key) {
        current->left = addhelp(current->left, key);
      }
      else if (key > current->key) {
        current->right = addhelp(current->right, key);
      }
      return current;
    }
  }

  virtual void add(const T & key) { root = addhelp(root, key); }

  //contains
  virtual bool contains(const T & key) const {
    Node * current = root;
    while (current != NULL) {
      if (key == current->key) {
        return true;
      }
      else if (key < current->key) {
        current = current->left;
      }
      else {
        current = current->right;
      }
    }
    return false;
  }

  //remove helper
  Node * removehelp(Node * current, const T & key) {
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
        T k = current->key;
        remove(current->key);
        place->key = k;
        return place;
      }
    }
    return current;
  }

  //remove
  virtual void remove(const T & key) { root = removehelp(root, key); }

  //  inorder helper
  void inorderhelp(Node * current) {
    if (current != NULL) {
      inorderhelp(current->left);
      std::cout << current->key << "|\n";
      inorderhelp(current->right);
    }
  }

  //for testing use(inorder traverse)
  void inorder() {
    Node * current = root;
    inorderhelp(current);
  }
};
