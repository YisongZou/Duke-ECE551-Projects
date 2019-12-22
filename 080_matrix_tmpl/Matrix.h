#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>

#include <cstdlib>
#include <iostream>
#include <vector>

//YOUR CODE GOES HERE!
template<typename T>
class Matrix;
template<typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs);

template<typename T>
class Matrix {
 private:
  int numRows;
  int numColumns;
  std::vector<T> * rows;

 public:
  Matrix() : numRows(0), numColumns(0), rows(NULL) {}

  Matrix(int r, int c) : numRows(r), numColumns(c), rows(new std::vector<T>[r]()) {
    for (int i = 0; i <= r - 1; i++) {
      rows[i] = std::vector<T>(c);
    }
  }

  Matrix(const Matrix & rhs) :
      numRows(rhs.numRows),
      numColumns(rhs.numColumns),
      rows(new std::vector<T>[rhs.numRows]()) {
    for (int i = 0; i <= rhs.numRows - 1; i++) {
      // rows[i] = new std::vector<T>();
      for (int j = 0; j <= rhs.numColumns - 1; j++) {
        (rows[i]).push_back((rhs.rows[i])[j]);
      }
    }
  }

  ~Matrix() {
    // for (int i = 0; i < numRows; i++) {
    // delete rows[i];
    // }
    delete[] rows;
  }

  Matrix & operator=(const Matrix & rhs) {
    if (this != &rhs) {
      std::vector<T> * temp = new std::vector<T>[rhs.numRows];
      for (int i = 0; i <= rhs.numRows - 1; i++) {
        //  temp[i] = new std::vector<T>;
        for (int j = 0; j <= rhs.numColumns - 1; j++) {
          (temp[i]).push_back((rhs.rows[i])[j]);
        }
      }
      //    for (int i = 0; i < numRows; i++) {
      //  delete rows[i];
      // }
      delete[] rows;
      rows = temp;
      numRows = rhs.numRows;
      numColumns = rhs.numColumns;
    }
    return *this;
  }

  int getRows() const { return numRows; }

  int getColumns() const { return numColumns; }

  const std::vector<T> & operator[](int index) const {
    assert((index < numRows) && (index >= 0));
    return rows[index];
  }

  std::vector<T> & operator[](int index) {
    assert((index < numRows) && (index >= 0));
    return rows[index];
  }

  bool operator==(const Matrix & rhs) const {
    if (numRows == rhs.numRows) {
      if (numColumns == rhs.numColumns) {
        for (int i = 0; i < numRows; i++) {
          for (int j = 0; j < numColumns; j++) {
            if ((rows[i])[j] != (rhs.rows[i])[j]) {
              return false;
            }
          }
        }
        return true;
      }
    }
    return false;
  }

  Matrix operator+(const Matrix & rhs) const {
    assert((numRows == rhs.numRows) && (numColumns == rhs.numColumns));
    Matrix ans(numRows, numColumns);
    for (int i = 0; i < numRows; i++) {
      for (int j = 0; j < numColumns; j++) {
        (ans.rows[i])[j] = (rows[i])[j] + (rhs.rows[i])[j];
      }
    }
    return ans;
  }
};

template<typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs) {
  if (rhs.getRows() == 0) {
    s << "[  ]";
    return s;
  }
  s << "[ ";

  for (int i = 0; i < rhs.getRows() - 1; i++) {
    if (rhs[i].size() == 0) {
      s << "{},\n";
    }
    else {
      s << "{";
      for (size_t j = 0; j < rhs[i].size() - 1; j++) {
        s << rhs[i][j] << ", ";
      }
      s << rhs[i][rhs[i].size() - 1];
      s << "}";
      s << ",\n";
    }
  }

  if (rhs[rhs.getRows() - 1].size() == 0) {
    s << "{}";
  }
  else {
    s << "{";
    for (size_t j = 0; j < rhs[rhs.getRows() - 1].size() - 1; j++) {
      s << rhs[rhs.getRows() - 1][j] << ", ";
    }
    s << rhs[rhs.getRows() - 1][rhs[rhs.getRows() - 1].size() - 1];
    s << "}";
  }
  s << " ]";
  return s;
}
#endif

/*
std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs) {
  if (rhs.getRows() == 0) {
    s << "[ ]";
    return s;
  }
  s << "[ ";
  for (int i = 0; i < rhs.getRows() - 1; i++) {
    s << rhs[i] << ",\n";
  }
  s << rhs[rhs.getRows() - 1];
  s << " ]";
  return s;
}



std::ostream & operator<<(std::ostream & s, const IntArray & rhs) {
  if (rhs.size() == 0) {
    s << "{}";
    return s;
  }
  s << "{";
  for (int i = 0; i < rhs.size() - 1; i++) {
    s << rhs[i] << ", ";
  }
  s << rhs[rhs.size() - 1];
  s << "}";
  return s;
}
*/
