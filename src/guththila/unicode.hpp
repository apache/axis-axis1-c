/* Guththila - Typed Pull Parser
 *  
 *  Authors: 
 *  
 *  Dinesh Premalal ( premalwd@cse.mrt.ac.lk,
 *                    premalal@opensource.lk) */

#ifndef UNICODE_H
#define UNICODE_H

typedef unsigned char UTF8_char;
typedef unsigned short UTF16_char;
typedef unsigned int UTF32_char;


/*! These are the values of UTF-16 Document
 * After , BOM (Byter Oreder Mark) was determined unicodeState
 * variable will set to one of the following values
 * None = Normally treated as Utf-8 Document
 * LE = Little Endian UTF-16 Document
 * BE = Big Endian UTF-16 Document
 * For the time being Endianess make no effect to the parsing  */
enum UTF16_endianess {None=1, LE, BE};

/*!This static variable will will track the Document type  */
static unsigned int unicodeState = 0;

static UTF8_char  unicodeLength = 0;

#ifdef UNICODE_OUT
#define strlen(x) strlenUnicode(x) 
#define strndup(x, y) strdupUnicode(x, y)

UTF8_char strlenUnicode (char *);

char * strdupUnicode (char *);

char * strdupUnicode (char *, int);

#endif


#endif /* TSPP_H */
