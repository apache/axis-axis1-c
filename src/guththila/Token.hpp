#ifndef TOKEN_HPP
#define TOKEN_HPP

struct token_t
{
  int type;
  char *start, *end;

  enum
    {
      Unknown, Name, AttValue, Prefix, CharData
    };

  void 
  relocate (int offset)
  {
    start -= offset;
    end -= offset;
  }

  int 
  isOfType (int type)
  {
    return this->type == type;

  }

  int 
  length ()
  {
    if (end)
      return end - start + 1;
    else
      throw new XmlPullParserException ();
  }


#ifndef UNICODE_OUT /* To Obtain UTF-8 Output */

  /*!added two toString methods, Because according to output format
   * converstion function will be vary
   * Here memcpy was used instead of strcpy 
   * strcpy can't survive with UTF-16 string because , it ( UTF-16
   * string) has null characters middle of string  */

  char*
  toString (unsigned int unicodeState)
  {
    int len = length ();
    char *p = (char *)malloc (len + 1);
    memcpy (p, start, len);
    p[len] = 0;
    unicodeLength = len;
    switch (unicodeState)
      {
      case None:
	return p;
	break;
      case LE:
      case BE:
	return (char *)convertUtf16toUtf8 (p, unicodeLength);
	break;
      };
  }
#endif


#ifdef UNICODE_OUT /*! To Obtain UTF-16 Output  */


  char*
  toString (unsigned int unicodeState)
  {
    int len = length ();
    char *p = (char *)malloc (len + 1);
    memcpy (p, start, len);
    p[len] = 0;
    unicodeLength = len;
    switch (unicodeState)
      {
      case None:
	return (char *)convertUtf8toUtf16 (p, unicodeLength);
	break;
      case LE:
      case BE:
	return p;
	break;
      };
  }
#endif


  /*! To Determine length of Given UTF-8 character  */

  UTF8_char 
  lengthUtf8Char (char nextChar)
  {
    UTF8_char length;

    if ((nextChar & 0x80) == 0x00)
      length = 1;
    else if ((nextChar & 0xe0) == 0xc0)
      length = 2;
    else if ((nextChar & 0xf0) == 0xe0)
      length = 3;
    else if ((nextChar & 0xf1) == 0xf0)
      length = 4;
    else if ((nextChar & 0xfc) == 0xf1)
      length = 5;
    else
      length = 6;

    return length;
  }


  /*!mask will use to retrieve bits from Multibyte character  */
  UTF8_char 
  maskUtf8Char (UTF8_char length)
  {
    UTF8_char mask;
    
    switch (length)
      {
      case 1:
	mask = 0x7f;
	break;
      case 2:
	mask = 0x1f;
      case 3:
	mask = 0x0f;
	break;
      case 4:
	mask = 0x07;
	break;
      case 5:
	mask = 0x03;
	break;
      case 6:
	mask = 0x01;
	break;
      };

    return mask;
  }


  /*! This one will Convert UTF-8 buffer to UTF-16 Buffer
   * we have to give char pointer to utf-8 buffer and length of
   *that buffer , Then it will return pointer to UTF-16 Buffer*/

  UTF16_char *
  convertUtf8toUtf16 (char *p, int len)
  {
    char *s;
    s = p;
    Array < UTF16_char > *outBuffer;
    outBuffer = new Array < UTF16_char > (len);
    char mask;
    char utf8Buffer[6] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
    UTF32_char result;
    for (int i = 0; i < len; )
      {
	UTF8_char length = lengthUtf8Char (p[i]);
	mask = maskUtf8Char (length);
	for (int j = 0; j < length; j++)
	  utf8Buffer[j] = p[i++];

	result = utf8Buffer[0] & mask;
	for (int k = 1; k < length; k++)
	  {
	    if ((utf8Buffer[k] & 0xc0) != 0x80)
	      {
		throw XmlPullParserException ();
		break;
	      }
	    result <<= 6;
	    result |= (utf8Buffer[k] & 0x3f);
	  }
	outBuffer->append ((UTF16_char) result);
      }
    free (s);
    UTF8_char size = outBuffer->count ();
    unicodeLength = size * sizeof (unsigned short);
    UTF16_char *out = (UTF16_char *)malloc ((size+1) * sizeof (unsigned short));
    for (int l = 0; l < size; l++)
      out[l] = outBuffer->getElement (l);
    out[size] = 0x0;
    delete outBuffer;
    return out;
  }


  /*! This function use to determine, length of UTF-8 character of
   *  Given UTF-16 character  */
  int 
  lengthUtf16Char (UTF32_char utf16Char)
  {
    int utf16CharLength;

    if (0x80 > utf16Char)
      utf16CharLength = 1;
    else if (0x800 > utf16Char)
      utf16CharLength = 2;
    else if (0x10000 > utf16Char)
      utf16CharLength = 3;
    else if (0x200000 > utf16Char)
      utf16CharLength = 4;
    else if (0x4000000 > utf16Char)
      utf16CharLength = 5;
    else
      utf16CharLength = 6;

    return utf16CharLength;
  }


  /*! after Giveing UTF-16 Character and its equivalent UTf-8 length
   *this function will create UTF-8 character and stores it into
   *dest[8] buffer  */

  void 
  buildUtf8String (UTF32_char utf16Char, int len, UTF8_char dest[8])
  {
    UTF8_char mask;
    
    for (int x = 0; x < 8; x++)
      {
	dest[x] = 0x0;
      }

    if (len == 1)
      dest[0] = utf16Char;
    else
      {
	switch (len)
	  {
	  case 1:
	    break;
	  case 2:
	    mask = 0xc0;
	    break;
	  case 3:
	    mask = 0xe0;
	    break;
	  case 4:
	    mask = 0xf0;
	    break;
	  case 5:
	    mask = 0xf8;
	    break;
	  case 6:
	    mask = 0xfc;
	    break;
	  };

	for (int i = len - 1; i > 0; i--)
	  {
	    dest[i] = (utf16Char & 0x3f) | 0x80;
	    utf16Char >>= 6;
	  }

	dest[0] = utf16Char | mask;
	dest[len] = 0;
      }
  }


  /*! This function will convert UTF-16 Buffer to UTF-8 Buffer and
    returns pointer to UTF-8 buffer */
  
  UTF8_char *
  convertUtf16toUtf8 (char *p, int len)
  {
    char *s;
    int length;
    int bufferLength;
    s = p;
    UTF8_char dest[8];
    UTF32_char utf16Char = 0;
    UTF8_char i = 0;
    UTF8_char j = 0;
    Array < UTF8_char > *out;
    out = new Array < UTF8_char > (len);
    
    while (i < len)
      {
	utf16Char = *((UTF16_char *) & s[i]);
	i += 2;
	length = lengthUtf16Char (utf16Char);
	buildUtf8String (utf16Char, length, dest);
	j = 0;
	while (dest[j])
	  out->append (dest[j++]);
      }
    free (s);
    j = out->count ();
    UTF8_char *utf8Buffer = (UTF8_char *)calloc (j+1, 1);
    for (int i = 0; i < j; i++)
      utf8Buffer[i] = out->getElement (i);
    utf8Buffer[j] = 0x0;
    delete out;
    return utf8Buffer;
  }


  /*! Basically this function is use to compare "xmlns" with given
   * UTF-16 string, Otherwise it will compare "xmlns" with only first
   * characters and process Namespaces as attributes,
   *In oreder to FIX that this function defined */

  char *
  convertUtf16toUtf8Comp (char *p, int len)
  {
    int x = len/2;
    char buffer[x];
    int m ;
    int n;
    for (m = 0, n = 0; n<x; m +=2,n++)
      buffer[n] = p[m];
    char* s = buffer;
    return s;
  }


  /*!Basically use for compare "xmlns" with given char buffer  */
  int 
  compare (const char *s, int n)
  {
    UTF8_char *tmp;
    char *k;
    int x;
    if (unicodeState == None)
      return strncmp (start, s, n);
    else 
      {
	k = (char *)malloc (n*2);
	memcpy (k, start, n*2);
	tmp = convertUtf16toUtf8 (k, n*2);
	x = strncmp ((char *)tmp, s, n);
	free (tmp);
	return x;
      }
  }

};

#endif
