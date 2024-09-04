//Emily Zou - ezou2
//Ariel - xli325
//Serena Hu - shu53
#include "exception.h"

PlotException::PlotException(const std::string &msg)
  : std::runtime_error(msg) {
}

PlotException::PlotException(const PlotException &other)
  : std::runtime_error(other) {
}

PlotException::~PlotException() {
}
