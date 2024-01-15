#include <iostream>

#include "shape.hpp"
#include "inputShapes.hpp"
#include "outputShapes.hpp"
#include "scale.hpp"

int main()
{
  using namespace baranov;
  Shape * shapes[1000]{};
  size_t count = 0;
  point_t scalePoint = { 0, 0 };
  size_t scaleRatio = 0;
  try
  {
    inputShapes(std::cin, shapes, count, scalePoint, scaleRatio);
  }
  catch (const std::exception & e)
  {
    std::cerr << "Error: " << e.what() << '\n';
    return 1;
  }

  if (count == 0)
  {
    std::cerr << "Nothing to scale\n";
    freeShapes(shapes, count);
    return 2;
  }

  outputShapes(std::cout, shapes, count);

  for (size_t i = 0; i < count; ++i)
  {
    scale(shapes[i], scalePoint, scaleRatio);
  }

  outputShapes(std::cout, shapes, count);

  freeShapes(shapes, count);
}

