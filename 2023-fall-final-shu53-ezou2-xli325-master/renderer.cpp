//Emily Zou - ezou2
//Ariel - xli325
//Serena Hu - shu53
#include <iostream>
#include <cmath>
#include <cassert>
#include <memory>
#include "exception.h"
#include "renderer.h"
#include "fill.h"

//#define DEBUG_FILL
//#define DEBUG_PLOT

Renderer::Renderer(const Plot &plot)
  : m_plot(plot)
  , m_img(nullptr) {
}

Renderer::~Renderer() {
  // Note: the Renderer object does not "own" the Image object,
  // since the render() member function transfers ownership of
  // the Image object to the caller (in the main function)
}

Image *Renderer::render() {
  int width = m_plot.get_width();
  int height = m_plot.get_height();

  // the unique_ptr will take care of deleting the Image object
  // if an exception is thrown
  std::unique_ptr<Image> img(new Image(width, height));
  m_img = img.get();

  // TODO: render the plot image
  for(size_t i = 0; i< m_plot.getFillsVec().size(); i++){ //for each fill in plot
    filling(m_plot.getFillsVec()[i]); //call filling with each fill
  }
  std::map<std::string, Function*> map = m_plot.getFunctions(); //gets map of functions from plot
  for(std::map<std::string, Function*>::iterator it = map.begin(); it != map.end(); it++) //for each function in map
  {
    Function *func = it->second;
      graphFunc(func); //graph the function
  }

  return img.release();
}

// TODO: implement private helper functions
void Renderer::filling(Fill f){
  for(int j = 0 ; j< m_img->get_width(); j++){ //traveling through the image horzontally
    double xmin = m_plot.get_xmin();
    double xmax = m_plot.get_xmax();
    double ymin = m_plot.get_ymin();
    double ymax = m_plot.get_ymax();
    int h = m_plot.get_height();
    int w = m_plot.get_width();
    Function *func = m_plot.getFunction(f.getName1());
    double x = xmin + ((double)j/w) * (xmax-xmin); //corresponding x in the plot to the j in the image
    double yeval = func->get_expr()->eval(x); //evaluated y from the function's expression evaluated at x
    //fill above, below, or between according to the location of the fill
    //Fill Above
    if(f.getLocation() == 1){
      for(int i = 0; i<m_img->get_height(); i++){ //for every row i in the column j in the image
        double y = ymin + ((h-1-(double)i)/h)*(ymax-ymin); //calculate the corresponding y to the i
        if (y>yeval){ //if the corresponding y is greater than the evaluated y, change the pixel
          m_img->change_pixel(i, j, *f.getCol(), f.getOpacity());
        }
      }  
    }
    //Fill Below
    if(f.getLocation() == 2){
    for(int i = 0; i<m_img->get_height(); i++){ //for every row i in the column j in the image
        double y = ymin + ((h-1-(double)i)/h)*(ymax-ymin); //calculate the corresponding y to the i
        if (y<yeval){ //if the corresponding y is less than the evaluated y, change the pixel
          m_img->change_pixel(i, j, *f.getCol(), f.getOpacity());
        }
      }
    }
    //Fill Between
    if(f.getLocation() == 3){
      Function *func2 = m_plot.getFunction(f.getName2());
      double x = xmin + ((double)j/w) * (xmax-xmin);
      double yeval2 = func2->get_expr()->eval(x);
      
    for(int i = 0; i<m_img->get_height(); i++){
        double y = ymin + ((h-1-(double)i)/h)*(ymax-ymin); //calculates the corresponding y
        //if y is in between yeval1 and yeval2 (could be the case that either yeval1 is greater than yeval2 or yeval2 is greater than yeval1,)
        if ((y>yeval && y<yeval2)||(y<yeval && y>yeval2)){
          m_img->change_pixel(i, j, *f.getCol(), f.getOpacity()); //change the pixel
        }
      } 
    } 
  }
}

void Renderer::graphFunc(Function *func){ //graph function
  double xmin = m_plot.get_xmin();
  double xmax = m_plot.get_xmax();
  double ymin = m_plot.get_ymin();
  double ymax = m_plot.get_ymax();
  int h = m_plot.get_height();
  int w = m_plot.get_width();
  
  for(int j = 0 ; j< m_img->get_width(); j++){ //for every column in the image
    double x = xmin + ((double)j/w) * (xmax-xmin); //find the corresponding x
    double y = func->get_expr()->eval(x); //the y value evaluated at that x value in the function's ecpression
    int i = h - 1 - floor(((y-ymin)/(ymax-ymin))*h); //the i value of the image according to the y value that was found

    //we need to make a "cross" mark for a point, 
    //not just change the color of the pixel, but the pixels on top, bottom, left, and right
    m_img->change_pixel(i, j, func->getColor(), 1.0); //change pixel
    m_img->change_pixel(i-1, j, func->getColor(), 1.0); //add pixel on top and bottom (for cross)
    m_img->change_pixel(i+1, j, func->getColor(), 1.0);
    
    if(j != 0) //if not at the left edge of image
    {
      m_img->change_pixel(i, j-1, func->getColor(), 1.0); //add a pixel to the left of pixel (for cross)
    }
    if(j != m_img->get_width() - 1) //if not at the right edge of the image
    {
      m_img->change_pixel(i, j+1, func->getColor(), 1.0); //add a pixel to the right of the pixel (for cross)
    }
  }
}



