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

class AnyExpression : public Expression {
  Expression * lhs;
  Expression * rhs;
  char oper;

 public:
  AnyExpression(Expression * lhs, Expression * rhs, char oper) :
      lhs(lhs),
      rhs(rhs),
      oper(oper) {}
  virtual std::string toString() const {
    std::stringstream sstream;
    sstream << '(' << lhs->toString() << " " << oper << " " << rhs->toString() << ')';
    return sstream.str();
  }
  virtual ~AnyExpression() {
    delete lhs;
    delete rhs;
  }
};

class PlusExpression : public AnyExpression {
 public:
  PlusExpression(Expression * lhs, Expression * rhs) : AnyExpression(lhs, rhs, '+') {}
};

class MinusExpression : public AnyExpression {
 public:
  MinusExpression(Expression * lhs, Expression * rhs) : AnyExpression(lhs, rhs, '-') {}
};

class TimesExpression : public AnyExpression {
 public:
  TimesExpression(Expression * lhs, Expression * rhs) : AnyExpression(lhs, rhs, '*') {}
};

class DivExpression : public AnyExpression {
 public:
  DivExpression(Expression * lhs, Expression * rhs) : AnyExpression(lhs, rhs, '/') {}
};
