/*
 *   Copyright 2003-2004 The Apache Software Foundation.
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 */

const ENCODING *
NS(XmlGetUtf8InternalEncoding)(void)
{
  return &ns(internal_utf8_encoding).enc;
}

const ENCODING *
NS(XmlGetUtf16InternalEncoding)(void)
{
#if BYTEORDER == 1234
  return &ns(internal_little2_encoding).enc;
#elif BYTEORDER == 4321
  return &ns(internal_big2_encoding).enc;
#else
  const short n = 1;
  return (*(const char *)&n
          ? &ns(internal_little2_encoding).enc
          : &ns(internal_big2_encoding).enc);
#endif
}

static const ENCODING *NS(encodings)[] = 
{
  &ns(latin1_encoding).enc,
  &ns(ascii_encoding).enc,
  &ns(utf8_encoding).enc,
  &ns(big2_encoding).enc,
  &ns(big2_encoding).enc,
  &ns(little2_encoding).enc,
  &ns(utf8_encoding).enc /* NO_ENC */
};

static int PTRCALL
NS(initScanProlog)(int* parser_state, data_t* data,const ENCODING *enc, 
                   int* num_chars, char *end,
                   const char **nextTokPtr)
{
  /* printf("XML_PROLOG_STATE:%d\n", XML_PROLOG_STATE); */
  return initScan(parser_state, data, NS(encodings),(const INIT_ENCODING *)enc,
                  XML_PROLOG_STATE, num_chars, end, nextTokPtr);
}

static int PTRCALL
NS(initScanContent)(int* parser_state, data_t* data,const ENCODING *enc, 
                    int* num_chars, char *end,
                    const char **nextTokPtr)
{
  /* printf("XML_CONTENT_STATE:%d\n", XML_PROLOG_STATE); */
  return initScan(parser_state, data, NS(encodings),(const INIT_ENCODING *)enc,
                  XML_CONTENT_STATE, num_chars, end, nextTokPtr);
}

int
NS(XmlInitEncoding)(INIT_ENCODING *p, const ENCODING **encPtr,
                    const char *name)
{
  int i = getEncodingIndex(name);
  if (i == UNKNOWN_ENC)
    return 0;
  SET_INIT_ENC_INDEX(p, i);
  p->initEnc.scanners[XML_PROLOG_STATE] = NS(initScanProlog);
  p->initEnc.scanners[XML_CONTENT_STATE] = NS(initScanContent);
  p->initEnc.updatePosition = initUpdatePosition;
  p->encPtr = encPtr;
  *encPtr = &(p->initEnc);
  initEncTable(encPtr); /* this is temporary solution by damitha */
  return 1;
}

static const ENCODING *
NS(findEncoding)(const ENCODING *enc, const char *ptr, const char *end)
{
#define ENCODING_MAX 128
  char buf[ENCODING_MAX];
  char *p = buf;
  int i;
  XmlUtf8Convert(enc, &ptr, end, &p, p + ENCODING_MAX - 1);
  if (ptr != end)
    return 0;
  *p = 0;
  if (streqci(buf, KW_UTF_16) && enc->minBytesPerChar == 2)
    return enc;
  i = getEncodingIndex(buf);
  if (i == UNKNOWN_ENC)
    return 0;
  return NS(encodings)[i];
}

int
NS(XmlParseXmlDecl)(int isGeneralTextEntity,
                    const ENCODING *enc,
                    const char *ptr,
                    const char *end,
                    const char **badPtr,
                    const char **versionPtr,
                    const char **versionEndPtr,
                    const char **encodingName,
                    const ENCODING **encoding,
                    int *standalone)
{
  return doParseXmlDecl(NS(findEncoding),
                        isGeneralTextEntity,
                        enc,
                        ptr,
                        end,
                        badPtr,
                        versionPtr,
                        versionEndPtr,
                        encodingName,
                        encoding,
                        standalone);
}

int NS(XmlDamConvert)(const ENCODING *enc, const char **fromPtr,
                      const char *rawNameEnd,
    const char **toPtr, const char *bufEnd)
{
    /* printf("fromPtr:%s\n", *fromPtr); */
    /* printf("rawNameEnd:%s\n", rawNameEnd); */
                    XmlUtf8Convert(enc,
                               fromPtr, rawNameEnd,
                               toPtr, bufEnd);
}

