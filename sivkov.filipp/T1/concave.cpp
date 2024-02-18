#include "concave.hpp"
#include "othersFun.hpp"
#include <stdexcept>
#include <algorithm>
sivkov::Concave::Concave(const point_t ver1, const point_t ver2, const point_t ver3, const point_t ver4) :
  ver1_(ver1),
  ver2_(ver2),
  ver3_(ver3),
  ver4_(ver4)
{
  if (!isTriangle(ver1_, ver2_, ver3_))
  {
    throw std::invalid_argument("The first three points do not form a triangle.");
  }
  if (!isInsideTriangle(ver1_, ver2_, ver3_, ver4_))
  {
    throw std::invalid_argument("The fourth point is not inside the triangle formed by the first three points.");
  }
}

sivkov::Concave::~Concave() = default;

double sivkov::Concave::getArea() const
{
  double area = ((ver2_.x - ver1_.x) * (ver3_.y - ver1_.x)) - ((ver3_.x - ver1_.x) * (ver2_.y - ver1_.y));
  if (area < 0)
  {
    area = area * -0.5;
  }
  else
  {
    area = area * 0.5;
  }
  double secondArea = ((ver4_.x - ver1_.x) * (ver3_.y - ver1_.x)) - ((ver3_.x - ver1_.x) * (ver4_.y - ver1_.y));
  if (secondArea < 0)
  {
    secondArea = secondArea * -0.5;
  }
  else
  {
    secondArea = secondArea * 0.5;
  }
  if ((area - secondArea) < 0)
  {
    return (area - secondArea) * -1.0;
  }
  else
  {
    return (area - secondArea);
  }
};

sivkov::rectangle_t sivkov::Concave::getFrameRect() const
{
  double xmin = std::min({ ver1_.x, ver2_.x, ver3_.x, ver4_.x });
  double xmax = std::max({ ver1_.x, ver2_.x, ver3_.x, ver4_.x });
  double ymin = std::min({ ver1_.y, ver2_.y, ver3_.y, ver4_.y });
  double ymax = std::max({ ver1_.y, ver2_.y, ver3_.y, ver4_.y });

  return rectangle_t{point_t{xmin + (xmax - xmin) / 2, ymin + (ymax - ymin) / 2} ,(xmax - xmin), (ymax - ymin)};
}

void sivkov::Concave::move(point_t newPos)
{
  point_t oldPos = ver4_;
  double dx = newPos.x - oldPos.x;
  double dy = newPos.y - oldPos.y;
  move(dx,dy);
}

void sivkov::Concave::move(double x, double y)
{
  point_t newXY = { x,y };
  ver1_ = shift(newXY, ver1_);
  ver2_ = shift(newXY, ver2_);
  ver3_ = shift(newXY, ver3_);

}

void sivkov::Concave::scale(double k)
{
  point_t center = ver4_;
  ver1_ = doCenterShift(k, center, ver1_);
  ver2_ = doCenterShift(k, center, ver2_);
  ver3_ = doCenterShift(k, center, ver3_);
}

