//Emily Zou - ezou2
//Ariel - xli325
//Serena Hu - shu53
#ifndef BOUNDS_H
#define BOUNDS_H


class Bounds {
private:
  // TODO: add fields
  double xmin = 0; //stores maximum and minimum x and y values and width and height of plot
  double xmax = 0;
  double ymin = 0;
  double ymax = 0;
  int w = 0;
  int h = 0;

public:
  // TODO: add member functions
  Bounds(); //default constructor (all values are 0)
  Bounds(double minx, double miny, double maxx, double maxy, int width, int height); //constructor

  // get values
  double getxmax();
  double getxmin();
  double getymax();
  double getymin();
  int getwidth();
  int getheight();
  //set values
  void setxmax(double n);
  void setxmin(double n);
  void setymax(double n);
  void setymin(double n);
};

#endif // BOUNDS_H
