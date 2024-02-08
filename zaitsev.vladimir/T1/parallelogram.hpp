#ifndef PARALLELOGRAM_HPP
#define PARALLELOGRAM_HPP
#include "base-types.hpp"
#include "shape.hpp"

namespace zaitsev
{
  class Parallelogram: public Shape
  {
  public:
    Parallelogram(const point_t* vertices_);
    virtual double getArea() const;
    virtual rectangle_t getFrameRect() const;
    virtual void move(const point_t& dest_pos);
    virtual void move(double x_shift, double y_shift);
    virtual void scale(double factor);
    point_t getCenter() const;
  private:
    point_t def_vertices_[3];
  };
}
#endif
