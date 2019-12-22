#include <cstdlib>
#include <sstream>
#include <string>

class Expression {
 public:
  virtual std::string toString() const = 0;
  virtual ~Expression() {}
};

class NumExpression : public Expression {
  long num;

 public:
  NumExpression(long a) : num(a) {}
  virtual std::string toString() const {
    std::stringstream sstream;
    sstream << num;
    return sstream.str();
  }
};

class PlusExpression : public Expression {
  Expression * lhs;
  Expression * rhs;

 public:
  PlusExpression(Expression * lhs, Expression * rhs) : lhs(lhs), rhs(rhs) {}
  virtual std::string toString() const {
    std::stringstream sstream;
    sstream << '(' << lhs->toString() << " + " << rhs->toString() << ')';
    return sstream.str();
  }
  virtual ~PlusExpression() {
    delete lhs;
    delete rhs;
  }
};
