//Emily Zou - ezou2
//Ariel - xli325
//Serena Hu - shu53
#include "func.h"

Function::Function(const std::string &name, Expr *expr) //constructor
  : m_name(name)
  , m_expr(expr) {
  hasColor = false;
  //initialize the function color into white
  color.r = 255;
  color.g = 255;
  color.b = 255;

}

Function::~Function() {
  // TODO: deallocate objects if necessary
  delete m_expr;
}

bool Function::isColor()
{
  return hasColor;
}


void Function::setColor(uint8_t red, uint8_t green, uint8_t blue){ //set color function
  color.r = red;
  color.g = green;
  color.b = blue;
  hasColor = true;
}

Color Function::getColor(){ //get color function
  return color;
}

