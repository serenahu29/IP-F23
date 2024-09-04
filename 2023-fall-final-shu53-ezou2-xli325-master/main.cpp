//Emily Zou - ezou2
//Ariel - xli325
//Serena Hu - shu53
#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include "exception.h"
#include "plot.h"
#include "reader.h"
#include "renderer.h"

int main(int argc, char **argv) {
  if (argc != 3) {
    std::cerr << "Usage: plot <input file> <output file>\n";
    return 1;
  }
  try{
    std::ifstream in(argv[1]);
    if (!in.is_open()) {
      throw PlotException("couldn't open input file" + std::string(argv[1]));
    }

    std::ofstream out(argv[2]);
    if (!out.is_open()) {
      throw PlotException("couldn't open output file" + std::string(argv[2]));
    }

    Plot plot;

    // read the plot description
    Reader reader;
    reader.read_input(in, plot);

    // render the plot to an Image
    Renderer renderer(plot);
    std::unique_ptr<Image> img(renderer.render());

    // write the Image as a PNG file
    img->write_png(out);
    std::cout << "Wrote plot image successfully!\n";

  }catch(PlotException &e){
    //catching plot exception and printing error message to cerr.
    //exiting the program with a non-zero return code
    //"Error: description of error"
    std::cerr<<"Error: "<<e.what()<<"\n";
    return 1;
  }

  return 0;
}
