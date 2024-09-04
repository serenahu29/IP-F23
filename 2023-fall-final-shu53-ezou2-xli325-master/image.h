//Emily Zou - ezou2
//Ariel - xli325
//Serena Hu - shu53
#ifndef IMAGE_H
#define IMAGE_H

#include <cstdint>
#include <iostream>
#include "color.h"

class Image {
private:
  int m_width, m_height;
  Color *m_pixels;

  // value semantics are prohibited
  Image(const Image &);
  Image &operator=(const Image &);

public:
  Image(int width, int height); //constructor
  ~Image(); //destructor

  int get_width() const { return m_width; }
  int get_height() const { return m_height; }

  // TODO: add member function to access pixel Color data
  Color * get_pixels()const; //get pixels array
  void change_pixel(int i, int j, Color fillCol, float opacity); //change pixel color and opacity if needed

  void write_png(std::ostream &out);
};

#endif // IMAGE_H
