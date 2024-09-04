//Emily Zou - ezou2
//Ariel - xli325
//Serena Hu - shu53
#ifndef FUNC_H
#define FUNC_H

#include <string>
#include "expr.h"
#include "color.h"

class Function {
private:
  //a function has a name and an expression computing its value (given x)
  std::string m_name;
  Expr *m_expr;
  Color color; //function's color
  bool hasColor;
  bool hasName;

  // value semantics prohibited
  Function(const Function &);
  Function &operator=(const Function &);


public:
  Function(const std::string &name, Expr *expr); //function constructor
  ~Function(); //destructor

  //get values
  std::string get_name() const { return m_name; }
  Expr *get_expr() const       { return m_expr; }
  Color getColor();
  //set color
  void setColor(uint8_t red, uint8_t green, uint8_t blue);
  bool isColor();
  bool isName();
  
};

#endif // FUNC_H


