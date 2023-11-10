#include "getMinimumSum.hpp"
#include "minSumMgt.hpp"
#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[])
{
  using namespace spiridonov;
  if (argc != 4)
  {
    std::cerr << "Usage: ./lab num input output" << "\n";
    return 1;
  }

  long long num = 0;
  try
  {
    num = std::stoi(argv[1]);
  }
  catch (const std::exception & e)
  {
    std::cerr << "Error parsing first argument" << "\n";
    return 1;
  }

  if ((num < 1) || (num > 2))
  {
    std::cerr << "First argument must be 1 or 2" << "\n";
    return 1;
  }

  long long rows = 0, cols = 0;
  std::ifstream input(argv[2]);
  input >> rows >> cols;
  int* matrix = new int[rows * cols];

  if (!input)
  {
    std::cout << "Failed to open input file: " << argv[2] << "\n";
    return 2;
  }

  if (num == 1)
  {
    matrix = new int[rows * cols]();
    try
    {
      int* dynamic_matrix = new int[rows * cols]();
      matrix = dynamic_matrix;
    }
    catch (const std::logic_error & e)
    {
      std::cerr << e.what() << "\n";
      return 2;
    }
  }

  else if (num == 2)
  {
    try
    {
      matrix = new int[rows * cols];
    }
    catch (const std::logic_error & e)
    {
      std::cerr << "Failed to allocate memory for matrix: " << e.what() << "\n";
      return 2;
    }
  }
  else
  {
    std::cout << "Invalid value for num: " << num << "\n";
    return 1;
  }
  try
  {
    for (long long i = 0; i < rows * cols; i++)
    {
      input >> matrix[i];
    }
  }
  catch (const std::ifstream::failure & e)
  {
    std::cerr << "Failed to read input from file: " << e.what() << "\n";
    return 2;
  }

  spiridonov::readMatrix(input, matrix, rows * cols);
  input.close();
  std::ofstream output(argv[3]);

  if (!output)
  {
    std::cerr << "Failed to open output file: " << argv[3] << "\n";
    delete[] matrix;
    return 1;
  }
  if (rows == 0 || cols == 0)
  {
    delete[] matrix;
    output << 0 << "\n";
    output.close();
    return 0;
  }

  int min_sum = spiridonov::getMinimumSum(matrix, rows, cols);
  output << min_sum << "\n";
  output.close();
  delete[] matrix;
  return 0;
}
