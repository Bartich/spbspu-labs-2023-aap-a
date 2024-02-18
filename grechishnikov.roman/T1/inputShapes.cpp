#include "inputShapes.hpp"
#include <stdexcept>
#include <cctype>
#include "rectangle.hpp"
#include "triangle.hpp"
#include "polygon.hpp"
#include "parametersLogic.hpp"

grechishnikov::Shape* grechishnikov::inputShape(const char* str)
{
  if (str == nullptr)
  {
    return nullptr;
  }
  const size_t legalNameCount = 3;
  const char* legalName[] = { "RECTANGLE\0", "TRIANGLE\0", "POLYGON\0" };
  Shape* (*correspondingFunctions[])(const grechishnikov::point_t* points, size_t size) = {
    grechishnikov::inputRectangle,
    grechishnikov::inputTriangle,
    grechishnikov::inputPolygon
  };

  const char* name = nullptr;
  const double* values = nullptr;
  const grechishnikov::point_t* points = nullptr;
  size_t size = 0;

  try
  {
    name = parseName(str);
    for (size_t i = 0; i < legalNameCount; i++)
    {
      if (isEqualStr(legalName[i], name))
      {
        size_t pos = 0;
        for (size_t i = 0; str[i] != ' '; i++)
        {
          pos++;
        }
        values = grechishnikov::parseValues(str + pos, size);
        points = grechishnikov::makePairs(values, size);

        Shape* returnShape = (*correspondingFunctions[i])(points, size / 2);

        delete[] name;
        delete[] values;
        delete[] points;
        return returnShape;
      }
    }
  }
  catch (const std::exception& e)
  {
    delete[] name;
    delete[] values;
    delete[] points;
    throw;
  }

  delete[] name;
  throw std::logic_error("Unknown name");
}

grechishnikov::Shape* grechishnikov::inputRectangle(const grechishnikov::point_t* points, size_t size)
{
  return new grechishnikov::Rectangle(points, size);
}

grechishnikov::Shape* grechishnikov::inputTriangle(const grechishnikov::point_t* points, size_t size)
{
  return new grechishnikov::Triangle(points, size);
}

grechishnikov::Shape* grechishnikov::inputPolygon(const grechishnikov::point_t* points, size_t size)
{
  return new grechishnikov::Polygon(points, size);
}

void grechishnikov::freeShapes(Shape* const* shapes, size_t size)
{
  for (size_t i = 0; i < size; i++)
  {
    delete shapes[i];
  }
}

const char* grechishnikov::parseName(const char* str)
{
  if (str == nullptr)
  {
    throw std::logic_error("No name was entered");
  }
  char* name = new char[20] { '0' };
  size_t i = 0;
  for (i = 0; str[i] != ' ' && str[i] != '\0'; i++)
  {
    if (std::isalpha(str[i]))
    {
      name[i] = str[i];
    }
    else
    {
      delete[] name;
      throw std::logic_error("Incorrect name input");
    }
  }
  name[i] = '\0';
  return name;
}

bool grechishnikov::isEqualStr(const char* fStr, const char* sStr)
{
  if (fStr == nullptr || sStr == nullptr)
  {
    return false;
  }
  bool check = 1;
  size_t i = 0;
  for (i = 0; fStr[i] != '\0' && sStr[i] != '\0'; i++)
  {
    if (fStr[i] != sStr[i])
    {
      check = 0;
    }
  }
  if (fStr[i] != sStr[i])
  {
    check = 0;
  }
  return check;
}
