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

#include <stdlib.h>

#ifndef XPP_H_OF_AXIS_INCLUDED
#define XPP_H_OF_AXIS_INCLUDED
#ifdef XML_UNICODE     /* Information is UTF-16 encoded. */
#ifdef XML_UNICODE_WCHAR_T
typedef wchar_t XML_Char;
typedef wchar_t XML_LChar;
#else
typedef unsigned short XML_Char;
typedef char XML_LChar;
#endif /* XML_UNICODE_WCHAR_T */
#else                  /* Information is UTF-8 encoded. */
typedef char XML_Char;
typedef char XML_LChar;
#endif /* XML_UNICODE */

typedef unsigned char XML_Bool;
#define XML_TRUE   ((XML_Bool) 1)
#define XML_FALSE  ((XML_Bool) 0)


#ifdef XML_UNICODE

#ifdef XML_UNICODE_WCHAR_T
#define XML_T(x) (const wchar_t)x
#define XML_L(x) L ## x
#else
#define XML_T(x) (const unsigned short)x
#define XML_L(x) x
#endif

#else

#define XML_T(x) x
#define XML_L(x) x

#endif


#ifdef XML_UNICODE
#define XML_ENCODE_MAX XML_UTF16_ENCODE_MAX
#define XmlConvert XmlUtf16Convert
#define XmlGetInternalEncoding XmlGetUtf16InternalEncoding
#define XmlEncode XmlUtf16Encode
#define MUST_CONVERT(enc, s) (!(enc)->isUtf16 || (((unsigned long)s) & 1))
typedef unsigned short ICHAR;
#else
#define XML_ENCODE_MAX XML_UTF8_ENCODE_MAX
#define XmlConvert XmlUtf8Convert
#define XmlGetInternalEncoding XmlGetUtf8InternalEncoding
#define XmlEncode XmlUtf8Encode
#define MUST_CONVERT(enc, s) (!(enc)->isUtf8)
typedef char ICHAR;
#endif


/** Tokenizing states*/
enum 
{
    S_0, S_1, S_2, S_3, S_4, S_5, S_6, S_7,
    S_8, S_9, S_10, S_11, S_12, S_13, S_14
};        

/** Special characters*/
enum 
{
    START_TAG, END_TAG, EMPTY_ELEMENT_TAG, PCDATA
};

/** Error codes*/
enum SPP_Error 
{
    SPP_ERROR_NONE,
    SPP_ERROR_NO_MEMORY,
    SPP_ERROR_SYNTAX,
    SPP_ERROR_NO_ELEMENTS,
    SPP_ERROR_INVALID_TOKEN,
    SPP_ERROR_UNCLOSED_TOKEN,
    SPP_ERROR_TAG_MISMATCH,
    SPP_ERROR_DUPLICATE_ATTRIBUTE,
    SPP_ERROR_UNKNOWN_ENCODING,
    SPP_ERROR_INCORRECT_ENCODING,
    SPP_ERROR_NOT_STANDALONE,
    SPP_ERROR_UNEXPECTED_STATE,
    SPP_ERROR_TOKENIZER_FAILED,
    SPP_ERROR_UNEXPECTED_TOKEN_CONTENT,
    SPP_ERROR_PARSE_FAILED,
    SPP_ERROR_READ_BLOCK,
    SPP_ERROR_PARSER_INIT_FAILED,
    SPP_ERROR_UNKNOWN
};

/** Memeory handling structure*/
typedef struct mm 
{
    void *( *mallocFcn)(size_t size);
    void *( *memMoveFcn)(void *ptrto, void *ptrfrom, size_t size);
    void *( *reallocFcn)(void *ptr, size_t size);
    void ( *freeFcn)(void *ptr);
} SppMemoryHandlingSuite;

/** Struct to hold ptrs to tokenized data*/
typedef struct data
{
    int type;
    int ptrBuffSize;
    int numOfPtrs;
    int numOfPtrsUtf8;
    char **ptrBuff;
    char **utf8PtrBuff;
} TokDataStruct;

/* char *tn[] = {"START_TAG", "END_TAG", "EMPTY_ELEMENT_TAG", "PCDATA"}; */

struct SPPContext;

/** SPP parser structure*/
typedef struct SPPContext SPPParser;

/** Parser create with encoding*/
SPPParser* parserCreate(const XML_Char *encodingName);

/** Parser create with encoding, namspace*/
SPPParser* parserCreate_ns(const XML_Char *encodingName, XML_Char nsSep);

/** Parser create with encoding, external memory handling suite and namespace*/
SPPParser* parserCreate_mh(const XML_Char *encodingName, 
    const SppMemoryHandlingSuite *memsuite,
    XML_Char nsSep);
enum SPP_Error parseProlog(SPPParser* ct);

void* parserFree(SPPParser* ct);

/** Parse the next element tag*/
TokDataStruct* next(SPPParser* ct);

/** Get next element as integer*/
int getNextElementAsInt(SPPParser* ct, int* parseError);

/** Get next attribute as integer*/
int getNextAttributeAsInt(SPPParser* ct, int* parseError);

#endif

