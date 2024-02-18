#ifndef DIAMOND_HPP
#define DIAMOND_HPP
#include <stdexcept>
#include "shape.hpp"
#include "base-types.hpp"

namespace arakelyan
{
  class Diamond: public Shape
  {
  public:
    Diamond(const point_t fp, const point_t sp, const point_t tp);
    virtual double getArea() const;
    virtual rectangle_t getFrameRect() const;
    virtual void move(const point_t point);
    virtual void move(const double delX, const double delY);
    virtual void scale(const double k);
    virtual ~Diamond() = default;
  private:

    point_t p1_;
    point_t p2_;
    point_t p3_;
  };
}

#endif
