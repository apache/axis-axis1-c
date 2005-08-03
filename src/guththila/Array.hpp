#ifndef ARRAY_HPP
#define ARRAY_HPP
#include <Buffer.hpp>


template < class T >class Array:public Buffer < T >
{
  int _last;

public:
  Array (int size):Buffer < T > (size)
  {
    _last = -1;
  }

  T *
  get (int i = 0)
  {
    if (i > _last || _last == -1)
      throw new XmlPullParserException ();
    return &buffer[i];
  }

  /*! This method Will use in converstion Functions, This is a newly
    added function  */
  T 
  getElement(int i)
  {
    if (i > _last || _last == -1)
      throw new XmlPullParserException ();
    return buffer[i];
  }
  
  int 
  count ()
  {
    return _last + 1;
  }

  T *
  last ()
  {
    if (_last < 0)
      throw new XmlPullParserException ();
    return &buffer[_last];
  }

  T *
  append ()
  {
    if (++_last == size)
      grow ();
    return &buffer[_last];
  }

  /*! This method also use in conversion functions, This one also
    newly added one */
  void 
  append (T c)
  {
    if (++_last == size)
      grow ();
    buffer[_last] = c;
  }

  int 
  trunc (int size)
  {
    if ((size > 0 && _last < size) || size < 0)
      throw new XmlPullParserException ();
    else
      return _last = size - 1;
  }

  int 
  chip ()
  {
    if (_last < 0)
      throw new XmlPullParserException ();
    else
      return _last--;
  }
};

#endif
