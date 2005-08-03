#ifndef FILEINPUTSTREAM_HPP
#define FILEINPUTSTREAM_HPP
#include <InputStream.hpp>
#include <XmlPullParserException.hpp>
class FileInputStream:public InputStream
{
  FILE *s;
public:
    FileInputStream (FILE * s);
   ~FileInputStream ();
  int read (char *buffer, int offset, int length);
};

#endif
