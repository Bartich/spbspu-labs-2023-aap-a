#include "ring.hpp"
#include <math.h>

Ring::Ring(point_t center, const double radius1, const double radius2):
  radius1_(radius1),
  radius2_(radius2),
  center_(center)
{
  if (radius1_ <= 0 || radius2_ <= 0 || radius1_ >= radius2_)
  {
    throw std::logic_error("Invalid ring");
  }
}

Ring::~Ring()
{
}

double Ring::getArea()
{
  return ((M_PI * pow(radius2_, 2)) - (M_PI * pow(radius1_, 2)));
}

rectangle_t Ring::getFrameRect()
{
  point_t pos = center_;
  return { pos, radius2_ * 2, radius2_ * 2 };
}

void Ring::move(const point_t newPos)
{
  center_ = newPos;
}

