#ifndef DISPLAYOUTPUT_HPP
#define DISPLAYOUTPUT_HPP

#include <ostream>
#include <iomanip>
#include "shape.hpp"
#include <cmath>

namespace marishin
{
  void outputShapesInfo(std::ostream& out, size_t shapeCount, Shape** shapes);
}

#endif
