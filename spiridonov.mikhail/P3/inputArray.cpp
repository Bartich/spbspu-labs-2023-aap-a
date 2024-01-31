#include "inputArray.hpp"
#include <iostream>

char* spiridonov::inputArray(std::istream& input, size_t& sizeOfStr)
{
  const size_t chunkSize = 10;
  char* currentArray = nullptr;

  try
  {
    currentArray = new char[chunkSize]();
    size_t capacity = chunkSize;

    char character = 0;
    size_t i = 0;

    input >> std::noskipws;

    while (input >> character && character != '\n')
    {
      if (i >= capacity)
      {
        capacity += chunkSize;
        char* newArray = new char[capacity]();
        std::copy(currentArray, currentArray + i, newArray);
        delete[] currentArray;
        currentArray = newArray;
      }

      currentArray[i] = character;
      i++;
    }

    char* finalArray = new char[i + 1]();
    std::copy(currentArray, currentArray + i, finalArray);
    finalArray[i] = '\0';

    delete[] currentArray;

    sizeOfStr = i;

    return finalArray;
  }

  catch (const std::bad_alloc&)
  {
    delete[] currentArray;
    throw;
  }
}
