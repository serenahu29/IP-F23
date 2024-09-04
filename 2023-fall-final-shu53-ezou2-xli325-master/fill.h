//Emily Zou - ezou2
//Ariel - xli325
//Serena Hu - shu53
#ifndef FILL_H
#define FILL_H

#include <cstdint>
#include <string>
#include "image.h"
#include "func.h"
#include "bounds.h"

class Fill {
private:
  // TODO: add fields to represent the fill
  Color * color;
  float opacity;
  std::string m_name1;
  std::string m_name2; //only for fill between
  int location; // location 1 = fill above, 2 = fill below, 3 = fill between

public:
  // TODO: add appropriate constructors
  Fill(); //default constructor
  Fill(const std::string name, float opacity, Color * color, const int loc); //constructor for fill with one function (above and below)
  Fill(const std::string name1,const std::string name2, float op, Color * col, const int loc); //constructor for fill with two functions (between)
  ~Fill(); // Fill destructor

  // TODO: add appropriate member functions

  //get values
  int getLocation() const;
  Color * getCol();
  std::string getName1();
  std::string getName2();
  float getOpacity();
};

#endif // FILL_H


