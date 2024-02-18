#ifndef SHAPE_CREATION_HPP
#define SHAPE_CREATION_HPP
#include <cstddef>

#include "base-types.hpp"
#include "shape.hpp"

namespace arakelyan
{
  Shape * defineAndCreateShape(const char * sting);
  Shape * createPar(const char * string);
  Shape * createRect(const char * string);
  Shape * createDiam(const char * string);
  void extractDataForParAndDiam(const char * string, point_t & p1, point_t &p2, point_t &p3, const size_t wordLen);
  void extractDataForRect(const char * string, point_t &p1, point_t &p2);
}
#endif
