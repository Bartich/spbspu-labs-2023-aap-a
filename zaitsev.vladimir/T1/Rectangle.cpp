#include "Rectangle.h"
#include <stdexcept>
#include "base-types.h"

namespace zaitsev
{
  Rectangle::Rectangle(const point_t& left_�orner, const point_t& right_�orner) :
    left_�orner_(left_�orner),
    right_�orner_(right_�orner)
  {
    if (left_�orner.x > right_�orner.x || left_�orner.y > right_�orner.y)
    {
      throw std::invalid_argument("Invalid order of points");
    }
  }

  double Rectangle::getArea() const
  {
    return (right_�orner_.x - left_�orner_.x) * (right_�orner_.y - left_�orner_.y);
  }

  rectangle_t Rectangle::getFrameRect() const
  {
    double width = right_�orner_.x - left_�orner_.x;
    double height = right_�orner_.y - left_�orner_.y;
    point_t pos = { left_�orner_.x + width / 2, left_�orner_.y + height / 2 };
    return { width, height, pos };
  }

  void Rectangle::move(const point_t& dest_pos)
  {
    point_t center = getCenter();
    point_t diff = { dest_pos.x - center.x, dest_pos.y - center.y };
    left_�orner_.x += diff.x;
    left_�orner_.y += diff.y;
    right_�orner_.x += diff.x;
    right_�orner_.y += diff.y;
  }

  void Rectangle::move(double x_shift, double y_shift)
  {
    left_�orner_.x += x_shift;
    left_�orner_.y += y_shift;
    right_�orner_.x += x_shift;
    right_�orner_.y += y_shift;
  }

  point_t Rectangle::getCenter() const
  {
    double width = right_�orner_.x - left_�orner_.x;
    double height = right_�orner_.y - left_�orner_.y;
    return { left_�orner_.x + width / 2, left_�orner_.y + height / 2 };
  }

  void Rectangle::scale(double factor)
  {
    if (factor <= 0)
    {
      throw std::invalid_argument("Scale factor must be positive");
    }
    point_t center = getCenter();
    left_�orner_.x = 2 * left_�orner_.x - center.x;
    right_�orner_.x = 2 * right_�orner_.x - center.x;
    left_�orner_.y = 2 * left_�orner_.y - center.y;
    right_�orner_.y = 2 * right_�orner_.y - center.y;
  }
}
