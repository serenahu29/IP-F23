//Emily Zou - ezou2
//Ariel - xli325
//Serena Hu - shu53
#ifndef EXPR_H
#define EXPR_H

#include <vector>

// Base expression class
class Expr {
private:
  // value semantics are prohibited
  Expr(const Expr &);
  Expr &operator=(const Expr &);

protected:
  //field(s) to store links to child Expr nodes
  std::vector<Expr*> children;

public:
  Expr();
  virtual ~Expr();

  virtual double eval(double x) const = 0;

  void addChild(Expr* child);
  const std::vector<Expr*>& getChildren() const;

};

//derived classes
//derived nodes
class X : public Expr {
public:
  X();
  ~X();

  double eval(double x) const override;
};

class Pi : public Expr {
public:
  Pi();
  ~Pi();

  double eval(double x) const override;
};

class NumericLiteral : public Expr {
private:
 double value;

public:
  NumericLiteral(double val);
  ~NumericLiteral();

  double eval(double x) const override;
};

class Sin : public Expr {
public:
  Sin();
  ~Sin();

  double eval(double x) const override;
};

class Cos : public Expr {
public:
  Cos();
  ~Cos();

  double eval(double x) const override;
};

class Add : public Expr {
public:
  Add();
  ~Add();

  double eval(double x) const override;
};

class Subtract : public Expr {
public:
  Subtract();
  ~Subtract();

  double eval(double x) const override;
};

class Multiply : public Expr {
public:
  Multiply();
  ~Multiply();

  double eval(double x) const override;
};

class Divide : public Expr {
public:
  Divide();
  ~Divide();

  double eval(double x) const override;
};

#endif // EXPR_H
