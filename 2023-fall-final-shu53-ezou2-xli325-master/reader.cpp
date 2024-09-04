//Emily Zou - ezou2
//Ariel - xli325
//Serena Hu - shu53
#include <iostream>
#include <locale>
#include <map>
#include <sstream>
#include <cstdint>
#include <string>
#include "exception.h"
#include "plot.h"
#include "reader.h"
#include "expr_parser.h"
#include "fill.h"
#include "expr.h"

using std::string;
using std::getline;

Reader::Reader() {
}

Reader::~Reader() {
}

void Reader::read_input(std::istream &in, Plot &plot) {
  // TODO: read plot input from in, add information to plot
  string value;
  while(getline(in, value)) //use getline to read file line by line
  {
    //read from each line and then assign the values to the
    //corresponding class
    std::stringstream s(value); //use stringstream to read through input file
    s>>value;
    if(value == "Plot"){ //plot directive
      std::vector <double> data; //stores data in an array
      double val;
      while (!s.eof()){ //trying to read everything in the line (even if there is wrong number of arguments)
        s >> val;
        data.push_back(val);
      }
      //(EXCEPTIONS): HANDLE WRONG NUMBER OF ARGUMENTS
      if(data.size() != 6)
      {
        throw PlotException("wrong number of arguments to a plot directive");
      }
      // (EXCEPTIONS:) Note that xmin must be less than xmax, and ymin must be less than ymax.
      if(!(data[0]<data[2]) || !(data[1]<data[3]))
      {
        throw PlotException("invalid plot bound");
      }
      //(EXCEPTIONS) Width and height must both be positive.
      if(data[4]<=0 || data[5]<=0)
      {
        throw PlotException("invalid image dimensions");
      }
      plot.setBounds( data[0], data[1], data [2], data [3], data[4], data[5]); //set the bounds of the plot using the data inputted
    }
    else if(value == "Function"){ //function directive
      string name;
      s>>name; //reads name
      ExprParser parser; //use expr parser to read through expression (exception handling in expr parser)
      Expr *p = parser.parse(s);
      plot.setFunction(name, p); //sets function

    }
    else if(value == "Color"){ //color directive
      string name;
      int count = 0;
      s>>name; //takes function name
      count ++;
      std::vector<uint8_t> rgb; //vector of rgb values to store color data
      unsigned int colorValue; //ints to read into 
      while(!s.eof()) //read rest of all arguments in the color directive
      {
        if(!(s>>colorValue)){
          throw PlotException("invalid value for color");
        }
        rgb.push_back(colorValue);
      }
      //(EXCEPTION) wrong number of arguments passed in
      count += rgb.size();
      if(count!=4)
      {
        throw PlotException("wrong number of arguments to a color directive");
      }
      //check if the color of the function is already set or not
      if(plot.getFunction(name)->isColor())
      {
        throw PlotException("multiple color directives for the same function");
      }
      plot.getFunction(name)->setColor(rgb[0], rgb[1], rgb[2]); //gets the function so that the function can set color
    }

    else if (value == "FillAbove" || value == "FillBelow"){ //fill above directive
      string func_name;
      int count = 0;
      s>>func_name; //check if reads function name correctly, because we need to pass in func_name as parameter into function later, so we don't want core dump.
      count ++;
      //(EXCEPTION) Check if fill directive refer to an existing function name??
      float op;
      if(!(s>>op)){ //reads opacity
        throw PlotException("invalid data value for opacity");
      }
      count ++;
      //(EXCEPTION) opacity should be between 0.0 and 1.0 inclusive
      if(op>1.0 || op<0.0)
      {
        throw PlotException("wrong value for opacity; opacity should be between 0.0 and 1.0 inclusive");
      }
      Color * col = new Color;
      std::vector<uint8_t> rgb; //vector of rgb values to store color data
      int colorValue; //ints to read into
      while(!s.eof()) //read rest of all arguments in the color directive
      {
        if(!(s>>colorValue)){
          throw PlotException("invalid data values for color");
        }
        rgb.push_back(colorValue);
      }
      count += rgb.size();
      //(EXCEPTION) wrong number of arguments passed in
      if(count != 5)
      {
        throw PlotException("wrong number of arguments passed in fill above or fill below directive");
      }
      col->r = rgb[0];
      col->g = rgb[1];
      col->b = rgb[2];
      if(value == "FillAbove")
      {
        plot.setFill(func_name, op, col, 1); //sets fill in plot (location is 1 for fill above)
      }
      else if(value == "FillBelow")
      {
        plot.setFill(func_name, op, col, 2); //sets fill in plot (location is 2 for fill below)
      }
    }
    else if (value == "FillBetween"){
      int count = 0;
      string func_name1;
      s>>func_name1;
      count++;
      string func_name2;
      s>>func_name2; //reads both function names
      count++;
      float op;
      if(!(s>>op)){ //reads opacity
        throw PlotException("invalid data value for opacity");
      }
      count++;
      if(op>1.0 || op<0.0)
      {
        throw PlotException("wrong value for opacity; opacity should be between 0.0 and 1.0 inclusive");
      }
      Color * col = new Color;
      std::vector<uint8_t> rgb; //vector of rgb values to store color data
      int colorValue; //ints to read into
      while(!s.eof()) //read rest of all arguments in the color directive
      {
        if(!(s>>colorValue)){
          throw PlotException("invalid data values for color");
        }
        rgb.push_back(colorValue);
      }
      count += rgb.size();
      //(EXCEPTION) wrong number of arguments passed in
      if(count != 6)
      {
        std::cout << count << std::endl;
        throw PlotException("wrong number of arguments passed in fill between directive");
      }
      col->r = rgb[0];
      col->g = rgb[1];
      col->b = rgb[2];
      plot.setFill(func_name1, func_name2, op, col, 3); //sets fill in plot  (location is 3 for fill between)
    }
    else{
      throw PlotException("invalid name of directive");
    }

  }
}
