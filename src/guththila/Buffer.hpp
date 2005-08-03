#ifndef BUFFER_HPP
#define BUFFER_HPP
#include <stdlib.h>

template < class T > class Buffer
{
protected:
  T * buffer;
  int size;

public:
  Buffer (int size);
  ~Buffer ();

  void grow ();

  int 
  getSize ()
  {
    return size;
  }


  T *
  get ()
  {
    return buffer;
  }
};

template < class T > Buffer < T >::Buffer (int size)
{
  this->size = size;
  buffer = (T *) malloc (sizeof (T) * size);
  if (!buffer)
    throw new XmlPullParserException ();
}


template < class T > Buffer < T >::~Buffer ()
{
  free (buffer);
}


template < class T > void Buffer < T >::grow ()
{
  size <<= 1;
  T *p = (T *) realloc (buffer, sizeof (T) * size);
  if (p)
    buffer = p;
  else
    throw new XmlPullParserException ();
}

#endif
