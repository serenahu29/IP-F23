//Emily Zou - ezou2
//Ariel - xli325
//Serena Hu - shu53
#ifndef FN_PARSER_H
#define FN_PARSER_H

#include <deque>
#include <iostream>
#include "expr.h"

class ExprParser {
private:
  // value semantics are prohibited
  ExprParser(const ExprParser &);
  ExprParser &operator=(const ExprParser &);

  //helper functions for parsing
  Expr* parsePrefixExpr(std::deque<std::string>& tokens);
  Expr* createExprNode(const std::string& token);
  Expr* createFunctionNode(const std::string& funcName);
  bool isValidFunctionName(const std::string& funcName);
  bool isNumericLiteral(const std::string& token);

public:
  ExprParser();
  ~ExprParser();

  Expr *parse(std::istream &in);
};

#endif // FN_PARSER_H
