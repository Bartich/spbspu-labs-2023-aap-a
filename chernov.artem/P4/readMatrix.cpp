#include "readMatrix.hpp"

#include <cstddef>
#include <fstream>
#include <stdexcept>

void chernov::readMatrix(std::ifstream& input, int* matrix, size_t rows, size_t cols)
{
  for (size_t i = 0; i < rows * cols; ++i)
  {
    input >> matrix[i];
    if (!input)
    {
      throw std::invalid_argument("Input error");
    }
  }
}
