#include "createarray.h"

bool gladyshev::checkVowel(char arrayelem)
{
  const char vowarr[11] = "AEIOUaeiou";
  for (size_t i = 0; i < 10; ++i)
  {
    if (arrayelem == vowarr[i])
    {
      return false;
    }
  }
  return true;
}

char * gladyshev::createFinalArray(char * start)
{
  size_t nummain = 0;
  size_t numsup = 0;
  while (start[nummain] != '\0')
  {
    if (checkVowel(start[nummain]))
    {
      start[numsup] = start[nummain];
      ++numsup;
    }
    ++nummain;
  }
  for (size_t i = numsup; i < nummain; ++i)
  {
    start[i] = 0;
  }
  start[numsup] = '\0';
  return start;
}
