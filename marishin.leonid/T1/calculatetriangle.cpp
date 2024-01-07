#include "calculatetriangle.hpp"

double calculateDistance(const point_t& p1, const point_t& p2)
{
  return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}
