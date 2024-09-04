//Emily Zou - ezou2
//Ariel - xli325
//Serena Hu - shu53
#include <cassert>
#include "bounds.h"
#include "plot.h"
#include "color.h" 
#include "exception.h"

Plot::Plot()
{

}

Plot::~Plot()
{
}

// TODO: implementations of Plot member functions
void Plot::setBounds(double minx, double miny, double maxx, double maxy, int w, int h){ // to be used in reader
  bounds = new Bounds(minx, miny, maxx, maxy, w, h); //sets bounds with a Bounds constructor
}
void Plot::setFunction(std::string name, Expr * expression){ //used in reader
  function = new Function(name, expression); //sets function with Function constructor
  std::string func_name = function->get_name(); //gets name of function
  functions[func_name] = function; //makes new map with the function name and the function
}
//getting values from bounds
double Plot::get_width()const {
  return bounds->getwidth(); 
}
double Plot::get_height() const{
  return bounds->getheight();
}
double Plot::get_xmin()const{
  return bounds->getxmin();
}
double Plot::get_xmax() const{
  return bounds->getxmax();
}
double Plot::get_ymin()const{
  return bounds->getymin();
}
double Plot::get_ymax() const{
  return bounds->getymax();
}

void Plot::setFill(std::string func_name, float opacity, Color *col, int loc){ //to be used in reader
  Fill fill(func_name, opacity, col, loc); //setting fill with fill contructor with one function (fill above and below)
  fills.push_back(fill); //adds the fill to the fills vector
}
void Plot::setFill(std::string func_name1, std::string func_name2, float opacity, Color * col, int loc){ //to be used in reader
  Fill fill(func_name1, func_name2, opacity, col, loc); //setting fill with fill constructor of 2 functions (fill between)
  fills.push_back(fill); //adds the fill to the fill vector
}

Function* Plot::getFunction(std::string name) const{
  if(functions.find(name) == functions.end())
  {
    throw PlotException("referring to a nonexistent function name");
  }
  Function *func = functions.at(name); //gets function using the map of functions
  return func;
}
std::map<std::string, Function*> Plot::getFunctions() const{ //returns the functions map
  return functions;
}
std::vector<Fill> Plot::getFillsVec() const{ //returns the vector of fills
  return fills;
}



