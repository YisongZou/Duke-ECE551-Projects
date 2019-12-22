#ifndef _LL_H_
#define _LL_H_
#include <assert.h>

#include <cstdlib>
#include <exception>
#include <iostream>

//YOUR CODE GOES HERE
//void testList(void);
class myexception : public std::exception {
 public:
  virtual const char * what() const throw() { return "Request item doesn't exist"; }
};

template<typename T>
class LinkedList {
 private:
  class Node {
   public:
    T data;
    Node * next;
    Node * prev;
    Node() : data(0), next(NULL), prev(NULL) {}
    Node(const T & d, Node * next, Node * prev) : data(d), next(next), prev(prev) {}
  };

  Node * head;
  Node * tail;
  int size;

 public:
  LinkedList() : head(NULL), tail(NULL), size(0) {}

  void addFront(const T & item) {
    head = new Node(item, head, NULL);
    if (tail == NULL) {
      tail = head;
    }
    else {
      head->next->prev = head;
    }
    size++;
  }

  void addBack(const T & item) {
    tail = new Node(item, NULL, tail);
    if (head == NULL) {
      head = tail;
    }
    else {
      tail->prev->next = tail;
    }
    size++;
  }

  bool remove(const T & item) {
    Node * current = NULL;
    Node * current1 = NULL;
    if (head == NULL) {
      return false;
    }
    for (current = head; current != NULL; current = current->next) {
      if (current->data == item) {
        current1 = current;
        break;
      }
    }
    if (current1 == NULL) {
      return false;
    }
    else if ((current1->prev == NULL) && (current1->next == NULL)) {
      head = NULL;
      tail = NULL;
    }
    else if (current1->prev == NULL) {
      head = current1->next;
      head->prev = NULL;
    }
    else if (current1->next == NULL) {
      tail = current1->prev;
      tail->next = NULL;
    }
    else {
      current1->prev->next = current1->next;
      current1->next->prev = current1->prev;
    }
    delete current1;
    size--;
    return true;
  }

  T & operator[](int index) {
    try {
      if (index < 0 || index >= size) {
        throw myexception();
      }
    }
    catch (std::exception & e) {
      std::cout << e.what();
    }
    Node * temp = head;
    for (int i = 0; i < index; i++) {
      temp = temp->next;
    }
    return temp->data;
  }

  const T & operator[](int index) const {
    try {
      if (index < 0 || index >= size) {
        throw myexception();
      }
    }
    catch (std::exception & e) {
      std::cout << e.what();
    }
    Node * temp = head;
    for (int i = 0; i < index; i++) {
      temp = temp->next;
    }
    return temp->data;
  }

  int find(const T & item) const {
    if (size == 0) {
      return -1;
    }
    Node * temp = head;
    for (int i = 0; i < size; i++) {
      if (item == temp->data) {
        return i;
      }
      temp = temp->next;
    }
    return -1;
  }

  LinkedList(const LinkedList & rhs) : head(NULL), tail(NULL), size(0) {
    Node * temp = rhs.head;
    while (temp != NULL) {
      this->addBack(temp->data);
      temp = temp->next;
    }
  }

  ~LinkedList() {
    while (head != NULL) {
      Node * temp = head->next;
      delete head;
      head = temp;
    }
    tail = NULL;
    size = 0;
  }

  LinkedList & operator=(const LinkedList & rhs) {
    if (this != &rhs) {
      while (head != NULL) {
        Node * temp = head->next;
        delete head;
        head = temp;
      }
      tail = NULL;
      size = 0;
      Node * temp = rhs.head;
      while (temp != NULL) {
        this->addBack(temp->data);
        temp = temp->next;
      }
      size = rhs.size;
    }
    return *this;
  }
  int getSize() const { return size; }
};

#endif
