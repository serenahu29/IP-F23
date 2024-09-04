//Emily Zou - ezou2
//Ariel - xli325
//Serena Hu - shu53
#include "bounds.h"

Bounds::Bounds() {} //default constructor
Bounds::Bounds(double minx, double miny, double maxx, double maxy, int width, int height){ //constructor
    xmin = minx;
    xmax = maxx;
    ymin = miny;
    ymax = maxy;
    w = width;
    h = height;
}

// TODO: implement member functions
//get values
double Bounds::getxmax(){
    return xmax;
}
double Bounds::getxmin(){
    return xmin;
}
double Bounds::getymax(){
    return ymax;
}
double Bounds::getymin(){
    return ymin;
}
int Bounds::getwidth(){
    return w;
}
int Bounds::getheight(){
    return h;
}
//set values
void Bounds::setxmax(double n){
    xmax = n;
}
void Bounds::setxmin(double n){
    xmin = n;
}
void Bounds::setymax(double n){
    ymax = n;
}
void Bounds::setymin(double n){
    ymin = n;
}