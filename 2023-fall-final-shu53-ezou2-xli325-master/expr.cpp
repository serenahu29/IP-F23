//Emily Zou - ezou2
//Ariel - xli325
//Serena Hu - shu53
#include <cmath>
#include "exception.h"
#include "expr.h"

// Expr (base class)

Expr::Expr() {
}

Expr::~Expr() {
  for (long unsigned int i = 0; i<children.size(); i++) {
    delete children[i];
  }
}

void Expr::addChild(Expr* child) {
  children.push_back(child);
}

const std::vector<Expr*>& Expr::getChildren() const {
  return children;
}

//Derived expression classes

//X
X::X() {}
X::~X() {
  for (long unsigned int i = 0; i<children.size(); i++) {
    delete children[i];
  }
}
//eval value of x
double X::eval(double x) const {
  return x;
}

//Pi
Pi::Pi() {}
Pi::~Pi() {
  for (long unsigned int i = 0; i<children.size(); i++) {
    delete children[i];
  }
}
//value closest to π
double Pi::eval(double) const {
  return M_PI;
}

//NumericLiteral
NumericLiteral::NumericLiteral(double val) : value(val) {}
NumericLiteral::~NumericLiteral() {
  for (long unsigned int i = 0; i<children.size(); i++) {
    delete children[i];
  }
}
//eval the literal numeric value
double NumericLiteral::eval(double) const {
  return value;
}

//Sin
Sin::Sin() {}
Sin::~Sin() {
  for (long unsigned int i = 0; i<children.size(); i++) {
    delete children[i];
  }
}

//eval sin function, have one argument expression (children[0])
double Sin::eval(double x) const {
  if (children.size() != 1){
    throw PlotException("wrong number of arguments are passed to sin function");
  }
  return sin(children[0]->eval(x));
}

//Cos
Cos::Cos() {}
Cos::~Cos() {
  for (long unsigned int i = 0; i<children.size(); i++) {
    delete children[i];
  }
}

//eval cos function, have one argument expression (children[0])
double Cos::eval(double x) const {
  if (children.size() != 1){
    throw PlotException("wrong number of arguments are passed to cos function");
  }
  return cos(children[0]->eval(x));
}

//Add
Add::Add(){}
Add::~Add() {
  for (long unsigned int i = 0; i<children.size(); i++) {
    delete children[i];
  }
}

//eval addition, may have any number (0 or more) of argument expressions
//using for loop to loop through all expressions and add them
double Add::eval(double x) const {
  double result = 0;
  for (long unsigned int i = 0; i<children.size(); i++) {
    result += children[i]->eval(x);
  }
  return result;
}

//Subtract
Subtract::Subtract() {}
Subtract::~Subtract() {
  for (long unsigned int i = 0; i<children.size(); i++) {
    delete children[i];
  }
}

//eval subtraction, have two argument expressions (children[0] and children[1])
double Subtract::eval(double x) const {
  if (children.size() != 2){
    throw PlotException("wrong number of arguments are passed to - function");
  }
  double result = 0;
  result = children[0]->eval(x) - children[1]->eval(x);
  return result;
}

//Multiply
Multiply::Multiply() {}
Multiply::~Multiply() {
  for (long unsigned int i = 0; i<children.size(); i++) {
    delete children[i];
  }
}

//eval multiplication, may have any number (0 or more) of argument expressions
//using for loop to loop through all expressions and multiply them
double Multiply::eval(double x) const {
  double result = 1;
  for (long unsigned int i = 0; i<children.size(); i++) {
    result *= children[i]->eval(x);
  }
  return result;
}

//Divide
Divide::Divide() {}
Divide::~Divide() {
  for (long unsigned int i = 0; i<children.size(); i++) {
    delete children[i];
  }
}

//eval subtraction, have two argument expressions (children[0] and children[1])
//checking exception: denominator (children[1]) cannot be 0
double Divide::eval(double x) const{
  double result = 0;
  if (children.size() != 2){
    throw PlotException("wrong number of arguments are passed to / function");
  }
  if (children[1] == 0) {
    throw PlotException("attempt to divide by 0");
  }
  result = children[0]->eval(x)/children[1]->eval(x);
  return result;
}