#include <iomanip>

#include "inputarray.h"
#include "allocatememory.h"
#include "createarray.h"

int main()
{
  using namespace gladyshev;
  char * endArray = nullptr;
  try
  {
    endArray = inputArray(std::cin);
  }
  catch (const std::bad_alloc& e)
  {
    std::cerr << "Cannot allocate memory" << "\n";
    delete[] endArray;
    return 1;
  }
  catch (const std::runtime_error& e)
  {
    std::cerr << "Error: " << e.what() << "\n";
    delete[] endArray;
    return 1;
  }
  endArray = createFinalArray(endArray);
  std::cout << endArray << "\n";
  delete[] endArray;
  return 0;
}
