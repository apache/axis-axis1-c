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
#define XmlGetInternalEncodingNS XmlGetUtf16InternalEncodingNS
#define XmlEncode XmlUtf16Encode
#define MUST_CONVERT(enc, s) (!(enc)->isUtf16 || (((unsigned long)s) & 1))
typedef unsigned short ICHAR;
#else
#define XML_ENCODE_MAX XML_UTF8_ENCODE_MAX
#define XmlConvert XmlUtf8Convert
#define XmlGetInternalEncoding XmlGetUtf8InternalEncoding
#define XmlGetInternalEncodingNS XmlGetUtf8InternalEncodingNS
#define XmlEncode XmlUtf8Encode
#define MUST_CONVERT(enc, s) (!(enc)->isUtf8)
typedef char ICHAR;
#endif



enum 
{
    S_0, S_1, S_2, S_3, S_4, S_5, S_6, S_7,
    S_8, S_9, S_10, S_11, S_12, S_13, S_14
};        

enum 
{
    START_TAG, END_TAG, EMPTY_ELEMENT_TAG, PCDATA
};


enum XML_Error 
{
    XML_ERROR_NONE,
    XML_ERROR_NO_MEMORY,
    XML_ERROR_SYNTAX,
    XML_ERROR_NO_ELEMENTS,
    XML_ERROR_INVALID_TOKEN,
    XML_ERROR_UNCLOSED_TOKEN,
    XML_ERROR_PARTIAL_CHAR,
    XML_ERROR_TAG_MISMATCH,
    XML_ERROR_DUPLICATE_ATTRIBUTE,
    XML_ERROR_JUNK_AFTER_DOC_ELEMENT,
    XML_ERROR_PARAM_ENTITY_REF,
    XML_ERROR_UNDEFINED_ENTITY,
    XML_ERROR_RECURSIVE_ENTITY_REF,
    XML_ERROR_ASYNC_ENTITY,
    XML_ERROR_BAD_CHAR_REF,
    XML_ERROR_BINARY_ENTITY_REF,
    XML_ERROR_ATTRIBUTE_EXTERNAL_ENTITY_REF,
    XML_ERROR_MISPLACED_XML_PI,
    XML_ERROR_UNKNOWN_ENCODING,
    XML_ERROR_INCORRECT_ENCODING,
    XML_ERROR_UNCLOSED_CDATA_SECTION,
    XML_ERROR_EXTERNAL_ENTITY_HANDLING,
    XML_ERROR_NOT_STANDALONE,
    XML_ERROR_UNEXPECTED_STATE,
    XML_ERROR_ENTITY_DECLARED_IN_PE,
    XML_ERROR_FEATURE_REQUIRES_XML_DTD,
    XML_ERROR_CANT_CHANGE_FEATURE_ONCE_PARSING,
    XML_ERROR_UNBOUND_PREFIX,
    XML_TEST_ERROR
};

typedef struct mm 
{
  void *( *malloc_fcn)(size_t size);
  void *( *memmove_fcn)(void *ptrto, void *ptrfrom, size_t size);
  void *( *realloc_fcn)(void *ptr, size_t size);
  void ( *free_fcn)(void *ptr);
} XML_Memory_Handling_Suite;

typedef struct data
{
        int type;
        int ptrs_sz;
        int num_ptrs;
    int num_ptrs_utf8;
        char **ptrs;
    char **utf8ptrs;
} data_t;

/* char *tn[] = {"START_TAG", "END_TAG", "EMPTY_ELEMENT_TAG", "PCDATA"}; */

struct xpp_context;

typedef struct xpp_context xpp_context_t;

xpp_context_t* parser_create(const XML_Char *encodingName);

xpp_context_t* parser_create_ns(const XML_Char *encodingName, XML_Char nsSep);

xpp_context_t* parser_create_mh(const XML_Char *encodingName, 
                                const XML_Memory_Handling_Suite *memsuite,
                                XML_Char nsSep);

void* parser_free(xpp_context_t* ct);

data_t* next(xpp_context_t* ct);

int get_next_element_as_int(xpp_context_t* ct, int* parse_error);

int get_next_attribute_as_int(xpp_context_t* ct, int* parse_error);

#endif

