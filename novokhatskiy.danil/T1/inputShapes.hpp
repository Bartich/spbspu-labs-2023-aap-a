#ifndef INPUT_SHAPES_HPP
#define INPUT_SHAPES_HPP
#include "shape.hpp"
#include <istream>

namespace novokhatskiy
{
  Shape **inputShapes(std::istream &input, size_t &shapeCounter);
}
#endif
