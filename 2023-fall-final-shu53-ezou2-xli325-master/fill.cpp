//Emily Zou - ezou2
//Ariel - xli325
//Serena Hu - shu53
#include <cassert>
#include <cstddef>
#include <tuple>
#include "fill.h"
#include "func.h"
#include "bounds.h"

// TODO: implement constructors

Fill::Fill(){ //default constructor sets pixel to black
  m_name1 = "null";
  opacity = 1.0;
  color->r = 255;
  color->g = 255;
  color->b = 255;
  location = 0;
}
Fill::Fill(const std::string name, float op, Color * col, const int loc){ //constructor for above and below (only 1 function)
  m_name1 = name;
  opacity = op;
  color = col;
  location = loc;
}
Fill::Fill(const std::string name1,const std::string name2, float op, Color * col, const int loc){ //constructor for between (2 functions)
  m_name1 = name1; 
  m_name2 = name2;
  opacity = op;
  color = col;
  location = loc;
}
Fill::~Fill() {
}

// TODO: implement member functions

//get values
int Fill::getLocation() const{
  return location;
}
Color * Fill::getCol(){
  return color;
}
std::string Fill::getName1(){
  return m_name1;
}
std::string Fill::getName2(){
  return m_name2;
}
float Fill::getOpacity(){
  return opacity;
}
