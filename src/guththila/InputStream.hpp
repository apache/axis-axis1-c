#ifndef INPUTSTREAM_HPP
#define INPUTSTREAM_HPP
#include <stdio.h>

class InputStream
{
public:
  virtual int read (char *buffer, int offset, int length) = 0;
};
#endif
