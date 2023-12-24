#ifndef BASE_TYPES_HPP
#define BASE_TYPES_HPP

namespace erohin
{
  struct point_t
  {
    double x = 0.0;
    double y = 0.0;
  };

  struct rectangle_t
  {
    double width = 0.0;
    double height = 0.0;
    point_t pos{0.0, 0.0};
  };
}

#endif
