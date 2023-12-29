#include "output.hpp"
namespace piyavkin
{
  void output(std::ostream& out, size_t shapeCount, Shape ** shapes)
  {
    double sum = 0;
    for (size_t i = 0; i < shapeCount; ++i)
    {
      sum += shapes[i]->getArea();
    }
    out << sum << " ";
    for (size_t i = 0; i < shapeCount; ++i)
    {
     out << shapes[i]->getFrameRect().pos.x - shapes[i]->getFrameRect().width / 2 << " " << shapes[i]->getFrameRect().pos.y - shapes[i]->getFrameRect().heigth / 2 << " ";
     out << shapes[i]->getFrameRect().pos.x + shapes[i]->getFrameRect().width / 2 << " " << shapes[i]->getFrameRect().pos.y + shapes[i]->getFrameRect().heigth / 2 << " ";
    }
    out << "\n";
  }
}
