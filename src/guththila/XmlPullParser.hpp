/* Guththila - Typed Pull Parser
 *  
 *  Authors: 
 *  Dasarath Weerathunga ( dasarath@cse.mrt.ac.lk,
 *                         dasarath@opensource .lk)
 *
 *  Dinesh Premalal ( premalwd@cse.mrt.ac.lk,
 *                    premalal@opensource.lk) */

#ifndef XMLPULLPARSER_HPP
#define XMLPULLPARSER_HPP
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "XmlPullParserException.hpp"
#include "FileInputStream.hpp"
#include "Array.hpp"
#include "unicode.hpp"
#include "Token.hpp"
#include "Namespace.hpp"
#include "Attribute.hpp"
#include "Depth.hpp"

/*! this variable useful when printing UTF-16 Buffer , normally it
 *  carries length of the UTF-16 Buffer */


class XmlPullParser
{
  InputStream *s;
  Buffer <char> *buffer;
  int offset;
  int last;
  int _next;
  int event;
  UTF8_char length;
  Array < token_t > *token;
  Array < namespace_t > *namespa;
  Array < attr_t > *attr;
  Array < depth_t > *depth;

  token_t *name;
  token_t *prefix;
  namespace_t *namesp;

  UTF8_char term;
  enum
    {
      S_0, S_1, S_2, S_3, S_4
    } state;

  int read ();
  void shift ();
  int nextCh (int eof = 0);
  /********/
  int isUtf8 ();
  int isUtf16 ();
  int fromUtf16 (int eof);
  /********/
  char *lastCh ();
  void reset (int del = 0);
  int tokenize ();

  void openToken ();
  void closeToken (int type);
  void relocateTokens (int offset);

  namespace_t *getNamespace (token_t * prefix);
  int addNamespace (token_t * uri);
  int addNamespace (token_t * prefix, token_t * uri);
  int addAttribute (token_t * prefix, token_t * name, token_t * value);
  void openElement ();
  void closeElement ();

  int isS (int c);
  int parseS (int c);
  int parseEq (int c);
  int parseNameToken (int c);
  int parseAttValueToken (int quote);
  int parseAttribute (int c);
  void parseXMLDecl ();
  void parseSTagOrEmptyElemTag (int c);
  void parseETag ();
  int parseCharData ();

public:
  enum
    {
      XMLDecl = 0, STag, EmptyElemTag, ETag, Content
    };

  XmlPullParser (InputStream * in);
  ~XmlPullParser ();

  int next ();

  char *getName ();
  char *getPrefix ();
  char *getNamespaceUri ();
  char *getValue ();

  int getDepth ();
  int getNamespaceCount (int i);
  char *getNamespacePrefix (int i);
  char *getNamespaceUri (int i);

  int getAttributeCount ();
  char *getAttributeName (int i);
  char *getAttributeValue (int i);
  char *getAttributePrefix (int i);
  char *getAttributeNamespaceUri (int i);
  char *getNamespaceForPrefix (char *prefix);
  char *getPrefixForNamespace (char *ns);
};

#endif
