//Emily Zou - ezou2
//Ariel - xli325
//Serena Hu - shu53
#include "pnglite.h"
#include "exception.h"
#include "image.h"
#include <cstdint>
#include <tuple>

namespace {

struct InitializePnglite {
  InitializePnglite() {
    ::png_init(0, 0);
  }
};

InitializePnglite init_pnglite;

unsigned ostream_png_write_callback(void* input, size_t size, size_t numel, void* user_pointer) {
  std::ostream &out = *(reinterpret_cast<std::ostream *>(user_pointer));
  out.write(reinterpret_cast<const char *>(input), size * numel);
  if (!out.good()) {
    throw PlotException("Error writing output data");
  }
  return numel;
}

} // end anonymous namespace

Image::Image(int width, int height) //consturctor
  : m_width(width)
  , m_height(height)
  , m_pixels(new Color[width * height]) {
  // TODO: initialize pixel data
  m_pixels->r = 0; //setting all pixels to 0
  m_pixels->g = 0;
  m_pixels->b = 0;
}

Image::~Image() {
  // TODO: deallocate memory
  delete[] m_pixels;
}

// TODO: implement member functions
Color * Image::get_pixels() const{
  return m_pixels;
}
void Image::change_pixel(int i, int j, Color fillCol, float opacity){
  int width = get_width(); //get width from image
  Color &target = m_pixels[width * (i) + j]; //find target pixel that you want to change according to i and j values
  Color og_color; //temporary color to store original color of the target pixel you want to change
  og_color.r = target.r;
  og_color.g = target.g;
  og_color.b = target.b;
//changing the color and opacity (if needed) of the target pixel
  target.r = (1-opacity) * og_color.r + opacity * fillCol.r;
  target.g = (1-opacity) * og_color.g + opacity * fillCol.g;
  target.b = (1-opacity) * og_color.b + opacity * fillCol.b;
}

void Image::write_png(std::ostream &out)
{
  // Set up png_t object for output
  png_t png;
  int rc;

  rc = png_open_write(&png, ostream_png_write_callback, static_cast<void*>(&out));
  if (rc != PNG_NO_ERROR) {
    throw PlotException("Error opening PNG output");
  }

  // get pixel data as unsigned char *
  const unsigned char *pixels_raw_const = reinterpret_cast<const unsigned char *>(get_pixels());
  unsigned char *pixels_raw = const_cast<unsigned char *>(pixels_raw_const);

  // Write PNG data
  rc = png_set_data(&png, unsigned(m_width), unsigned(m_height), 8, PNG_TRUECOLOR,
                   pixels_raw);
  if (rc != PNG_NO_ERROR) {
    throw PlotException("Error converting writing image data as PNG");
  }
}
