//Emily Zou - ezou2
//Ariel - xli325
//Serena Hu - shu53
#include <string>
#include <sstream>
#include <memory>
#include <deque>
#include "exception.h"
#include "expr.h"
#include "expr_parser.h"

ExprParser::ExprParser() {
}

ExprParser::~ExprParser() {
}

Expr *ExprParser::parse(std::istream &in) {
  // Recommended strategy: read all of the tokens in the expression
  // from the istream and put them in a sequence collection
  // such as a vector or deque. The call a recursive helper function
  // which parses the tokens and returns a pointer to an Expr object
  // repersenting the parsed expression.
  std::deque<std::string> tokens;
  std::string token;
  while (in >> token) {
    tokens.push_back(token);
  }
  return parsePrefixExpr(tokens);
}

//assume tokens is a sequence of tokens comprising the prefix expression
Expr* ExprParser::parsePrefixExpr(std::deque<std::string>& tokens){
  //base case, check if token is empty, if so return error
  if (tokens.empty()) {
    throw PlotException("unexpected end of expression");
  }
  std::string n = tokens.front();
  tokens.pop_front();

  if (n=="x" || n=="pi" || isNumericLiteral(n)) {
    return createExprNode(n);
  } else if (n == "(") {
    n = tokens.front();
    tokens.pop_front();
    if (!isValidFunctionName(n)){
      throw PlotException( "unknown function name in expression: " + std::string(n)); //invalid function name
    }
    Expr* result = createFunctionNode(n);

    while (tokens.front() != ")") {
      Expr* arg = parsePrefixExpr(tokens);
      result->addChild(arg);
    }

    tokens.pop_front();//remove right parenthesis

    return result;
  } else {
    throw PlotException( "error parsing prefix expression, unexpected token: " + std::string(n) );//unexpected token
  }
}

//check if token is a literal number
bool ExprParser::isNumericLiteral(const std::string& token) {
  try {
    std::stod(token);
    return true;
  } catch (const std::invalid_argument& e) {
    return false;
  }
}

//check if funcName is a valid function name
bool ExprParser::isValidFunctionName(const std::string& funcName) {
  if (funcName == "sin" || funcName == "cos" || funcName == "+" || funcName == "-" || funcName == "*" || funcName == "/"){
    return true;
  } else return false;
}

//create appropriate expression node
//leaf nodes, no child node
Expr* ExprParser::createExprNode(const std::string& token) {
  Expr* exprNode;
  if (token == "x") {
    exprNode = new X();
  } else if (token == "pi") {
    exprNode = new Pi();
  } else {
    exprNode = new NumericLiteral(stod(token));
  }
  return exprNode;
}

//create appropriate function node
Expr* ExprParser::createFunctionNode(const std::string& funcName) {
  Expr* funcNode;
  if (funcName == "sin") {
    funcNode = new Sin(); 
  } else if (funcName == "cos") {
    funcNode = new Cos();
  } else if (funcName == "+") {
    funcNode = new Add();
  } else if (funcName == "-") {
    funcNode = new Subtract();
  } else if (funcName == "*") {
    funcNode = new Multiply();
  } else if (funcName == "/") {
    funcNode = new Divide();
  }

  return funcNode;
}