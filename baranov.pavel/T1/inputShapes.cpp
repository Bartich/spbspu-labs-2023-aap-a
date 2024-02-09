#include "inputShapes.hpp"
#include "shape.hpp"
#include "rectangle.hpp"
#include "ring.hpp"
#include "ellipse.hpp"
#include <inputString.hpp>
#include <cstring>
#include <stdexcept>

baranov::Shape * baranov::parseRectangle(const char * string)
{
  double rectParameters[4]{};
  size_t pos = 0;
  string += 9;
  for (size_t i = 0; i < 4; ++i)
  {
    rectParameters[i] = std::stod(string, & pos);
    string += pos;
  }
  if (*string != '\0')
  {
    throw std::invalid_argument("Invalid rectangle parameters");
  }
  baranov::point_t ldCorner = { rectParameters[0], rectParameters[1] };
  baranov::point_t ruCorner = { rectParameters[2], rectParameters[3] };
  return new baranov::Rectangle(ldCorner, ruCorner);
}

baranov::Shape * baranov::parseRing(const char * string)
{
  double ringParameters[4]{};
  size_t pos = 0;
  string += 4;
  for (size_t i = 0; i < 4; ++i)
  {
    ringParameters[i] = std::stod(string, & pos);
    string += pos;
  }
  if (*string != '\0')
  {
    throw std::invalid_argument("Invalid ring parameters");
  }
  baranov::point_t center = { ringParameters[0], ringParameters[1] };
  return new baranov::Ring(center, ringParameters[2], ringParameters[3]);
}

baranov::Shape * baranov::parseEllipse(const char * string)
{
  double ellipseParameters[4]{};
  size_t pos = 0;
  string += 7;
  for (size_t i = 0; i < 4; ++i)
  {
    ellipseParameters[i] = std::stod(string, & pos);
    string += pos;
  }
  if (*string != '\0')
  {
    throw std::invalid_argument("Invalid ellipse parameters");
  }
  baranov::point_t center = { ellipseParameters[0], ellipseParameters[1] };
  return new baranov::Ellipse(center, ellipseParameters[2], ellipseParameters[3]);
}

void baranov::parseScale(const char * string, point_t & scalePoint, size_t & scaleRatio)
{
  double scaleParameters[3]{};
  size_t pos = 0;
  string += 5;
  for (size_t i = 0; i < 3; ++i)
  {
    try
    {
      scaleParameters[i] = std::stod(string, & pos);
    }
    catch (const std::exception &)
    {
      throw std::runtime_error("Invalid scale parameters");
    }
    string += pos;
  }
  if (*string != '\0' || scaleParameters[2] < 0)
  {
    throw std::runtime_error("Invalid scale parameters");
  }
  scalePoint = { scaleParameters[0], scaleParameters[1] };
  scaleRatio = scaleParameters[2];
}

baranov::Shape * baranov::parseShape(const char * string)
{
  const size_t shapeCount = 3;
  const char * shapeNames[] = {"RECTANGLE", "RING", "ELLIPSE"};
  for (size_t i = 0; i < shapeCount; ++i)
  {
    size_t nameSize = strlen(shapeNames[i]);
    if (std::strlen(string) <= nameSize)
    {
      continue;
    }
    if (strncmp(shapeNames[i], string, nameSize) == 0)
    {
      if (i == 0)
      {
        return baranov::parseRectangle(string);
      }
      else if (i == 1)
      {
        return baranov::parseRing(string);
      }
      else if (i == 2)
      {
        return baranov::parseEllipse(string);
      }
    }
  }
  throw std::invalid_argument("Invalid shape name");
}

void baranov::freeShapes(baranov::Shape ** shapes, size_t size)
{
  for (size_t i = 0; i < size; ++i)
  {
    delete shapes[i];
  }
}

void baranov::inputShapes(std::istream & input, Shape ** shapes, size_t & count, point_t & scalePoint, size_t & scaleRatio)
{
  char * string = nullptr;
  while (true)
  {
    try
    {
      string = baranov::inputString(input);
      if (strncmp(string, "SCALE", 5) == 0)
      {
        baranov::parseScale(string, scalePoint, scaleRatio);
        delete[] string;
        return;;
      }
      shapes[count] = baranov::parseShape(string);
      ++count;
      delete[] string;
    }
    catch (const std::invalid_argument & e)
    {
      std::cerr << e.what() << '\n';
      delete[] string;
    }
    catch (const std::logic_error &)
    {
    }
    catch (const std::range_error &)
    {
      freeShapes(shapes, count);
      throw;
    }
    catch (const std::exception &)
    {
      delete[] string;
      freeShapes(shapes, count);
      throw;
    }
  }
}

