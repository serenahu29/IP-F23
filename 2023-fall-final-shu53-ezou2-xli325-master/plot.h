//Emily Zou - ezou2
//Ariel - xli325
//Serena Hu - shu53
#ifndef PLOT_H
#define PLOT_H

#include <cstdint>
#include <vector>
#include <map>
#include <string>
#include "bounds.h"
#include "expr_parser.h"
#include "image.h"
#include "func.h"
#include "fill.h"
#include "color.h"

class Plot {
private:
  // TODO: add fields to represent plot bounds, functions, fills, etc.
  Bounds *bounds; //to store bounds (xmin, xmax, ymin, ymax, width, and height)
  Function *function; //stores a function
  std::map<std::string, Function*> functions; //keeps all functions in a map where the function name is the key to the function (so that functions are identifiable)
  std::vector<Fill> fills; //stores all of the fills
  
  // value semantics are prohibited
  Plot(const Plot &);
  Plot &operator=(const Plot &);

public:
  Plot(); //constructor
  ~Plot(); //destructor

  // TODO: add member functions to set and modify plot data
  void setBounds(double minx, double miny, double maxx, double maxy, int w, int h); //sets bounds of plot
  void setFunction(std::string name, Expr * expression); //sets a function in plot
  //getting values from bounds
  double get_width() const;
  double get_height() const;
  double get_xmin() const;
  double get_xmax() const;
  double get_ymin() const;
  double get_ymax() const;
  void setFill(std::string func_name, float opacity, Color * col, int loc); //sets a fill for fill above or below
  void setFill(std::string func_name1, std::string func_name2, float opacity, Color * col, int loc); //sets a fill for fill between
  Function* getFunction(std::string name) const; //finds function with function name
  std::map<std::string, Function*> getFunctions() const; //gets map of functions
  std::vector<Fill> getFillsVec() const; //gets the vector of fills
};

#endif // PLOT_H
