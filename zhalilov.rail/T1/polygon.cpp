#include "polygon.hpp"

#include <stdexcept>
#include <algorithm>

zhalilov::Polygon::Polygon(const point_t *points, const size_t size):
  m_points(nullptr),
  m_size(size)
{
  if (m_size < 3)
  {
    throw std::invalid_argument("not enough points to describe polygon");
  }
  for (size_t i = 0; i < size; i++)
  {
    for (size_t j = i + 1; j < size; j++)
    {
      if ((points[i].x == points[j].x) && (points[i].y == points[j].y))
      {
        throw std::invalid_argument("some points are equal");
      }
    }
  }

  m_points = new point_t[m_size];
  for (size_t i = 0; i < m_size; i++)
  {
    m_points[i] = points[i];
  }
}

zhalilov::Polygon::~Polygon()
{
  delete[] m_points;
}

double zhalilov::Polygon::getArea() const
{
  double square = 0.0;
  for (size_t i = 0; i < m_size - 1; i++)
  {
    square -= m_points[i].x * m_points[i + 1].y;
  }
  square -= m_points[m_size - 1].x * m_points[0].y;
  for (size_t i = 0; i < m_size - 1; i++)
  {
    square += m_points[i].y * m_points[i + 1].x;
  }
  square += m_points[m_size - 1].y * m_points[0].x;
  square *= 0.5;
  return square;
}

zhalilov::rectangle_t zhalilov::Polygon::getFrameRect() const
{
  point_t maxY = m_points[0], minY = m_points[0];
  point_t maxX = m_points[0], minX = m_points[0];

  for (size_t i = 1; i < m_size; i++)
  {
    if (m_points[i].x > maxX.x)
    {
      maxX = m_points[i];
    }
    if (m_points[i].x < minX.x)
    {
      minX = m_points[i];
    }
    if (m_points[i].y > maxY.y)
    {
      maxY = m_points[i];
    }
    if (m_points[i].y < minY.y)
    {
      minY = m_points[i];
    }
  }

  double width = maxX.x - minX.x;
  double height = maxY.y - minY.y;
  double posX = minX.x + width / 2.0;
  double posY = minY.y + height / 2.0;
  rectangle_t frameRect = { width, height, { posX, posY }};
  return frameRect;
}

zhalilov::point_t zhalilov::Polygon::getCenter()
{
  double posX = 0.0;
  double posY = 0.0;
  for (size_t i = 0; i < m_size; i++)
  {
    posX += m_points[i].x;
    posY += m_points[i].y;
  }
  posX = posX / m_size;
  posY = posY / m_size;
  return { posX, posY };
}

void zhalilov::Polygon::move(const point_t &point)
{
  point_t center = getCenter();
  move(point.x - center.x, point.y - center.y);
}

void zhalilov::Polygon::move(const double dx, const double dy)
{
  for (size_t i = 0; i < m_size; i++)
  {
    m_points[i].x += dx;
    m_points[i].y += dy;
  }
}

void zhalilov::Polygon::doScale(const double ratio)
{
  double deltaX = 0.0;
  double deltaY = 0.0;
  point_t center = getCenter();
  for (size_t i = 0; i < m_size; i++)
  {
    deltaX = m_points[i].x - center.x;
    deltaY = m_points[i].y - center.y;
    m_points[i].x = center.x + deltaX * ratio;
    m_points[i].y = center.y + deltaY * ratio;
  }
}
