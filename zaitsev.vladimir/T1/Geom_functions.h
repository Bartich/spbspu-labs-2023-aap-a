#ifndef GEOM_FUNCTIONS_H
#define GEOM_FUNCTIONS_H
#include "base-types.h"

namespace zaitsev
{
  double skewProduct(const point_t& vector1, const point_t& vector2);
  double dotProduct(const point_t& vector1, const point_t& vector2);
  bool checkIntersection(const point_t* sections);
  point_t findIntersection(const point_t* sections);
  void setLineCoeff(const point_t& p1, const point_t& p2, double& a, double&b, double& c);
}
#endif
