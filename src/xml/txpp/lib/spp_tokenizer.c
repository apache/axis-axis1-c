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

#include "spp.h"
#ifndef PREFIX
#define PREFIX(ident) ident
#endif

static int PTRCALL PREFIX(add_ptr)(char *ptr, TokDataStruct *data)
{
    if (data->numOfPtrs == data->ptrBuffSize
        || !data->ptrBuff) 
    {
        int sz = data->ptrBuffSize << 1;
        char **ptrBuff = (char **)malloc(sz << 2);
        if (!ptrBuff)
            return SPP_ERROR_NO_MEMORY;
        if (data->ptrBuff) 
        {
            memmove(ptrBuff, data->ptrBuff, data->numOfPtrs << 2);
            free(data->ptrBuff);
        }
        data->ptrBuff = ptrBuff;
        data->ptrBuffSize = sz;
        /* printf("sz:%d\n", sz); */
    }

    data->ptrBuff[data->numOfPtrs++] = ptr;
    
    return SPP_ERROR_NONE;
}

static int PTRCALL
PREFIX(is_letter)(int byteType)
{
    if(BT_NMSTRT == byteType || BT_HEX == byteType)
        return -1;
    else 
        return 0;
    
}

static int PTRCALL
PREFIX(is_name_start_char)(int byteType)
{
    if(PREFIX(is_letter)(byteType) || BT_COLON == byteType)
        return -1;
    else
        return 0;
}

static int PTRCALL
PREFIX(is_name_char)(int byteType)
{
    if(PREFIX(is_letter)(byteType) || BT_DIGIT == byteType || 
        BT_COLON == byteType || BT_MINUS == byteType ||
         BT_NAME == byteType)
        return -1;
    else return 0;
}

static int PTRCALL
PREFIX(doHomeWork)(TokDataStruct* data, int* parserState, char** ptr, int* numOfChars)
{
    numOfChars -= MINBPC(enc);
    *ptr += MINBPC(enc);    
    data->numOfPtrs = 0;
    *parserState = S_0;
    return SPP_ERROR_NONE;
}

static int PTRCALL
PREFIX(tokenizeProlog)(int* parserState, TokDataStruct* data, const ENCODING *enc,
                       int *numOfChars, char* end, const char **ptr)
{ 
    /* printf("*numOfChars:%d\n", *numOfChars); */
    int byteType;
    while(*numOfChars >= MINBPC(enc))
    {
        byteType = BYTE_TYPE(enc, *ptr);
        /* printf("*ptr:%s\n", *ptr); */
        /* printf("byteType:%d\n", byteType); */
        /* printf("*parserState:%d\n", *parserState); */
        switch (*parserState) 
        {
            case S_0:
                if(BT_LT == byteType) 
                {
                    *parserState = S_13;
                }
                else
                    data->type = PCDATA;
                
                break;
        
            case S_1:
                if(BT_QUEST == byteType)
                {
                    data->type = END_TAG;
                    *parserState = S_10;
                }
                else if (PREFIX(is_name_start_char)(byteType)) 
                {
                    data->type = START_TAG;
                    *parserState = S_2;
                }
                else
                    *parserState = S_14;
                
                break;
        
            case S_2:
                if (BT_GT == byteType) 
                {
                    
                    *parserState = S_0;
                }
                else if (BT_QUEST == byteType) 
                {
                    *parserState = S_9;
                }
                else if (BT_S == byteType) 
                {
                    *parserState = S_3;
                }    
                else if (!PREFIX(is_name_char)(byteType))
                    *parserState = S_14;
                break;
        
            case S_3:
                if (BT_GT == byteType) 
                {
                        PREFIX(doHomeWork)(data, parserState, ptr, numOfChars);
                        return SPP_ERROR_NONE;
                    
                }
                else if (BT_QUEST == byteType)
                    *parserState = S_9;
                else if (PREFIX(is_name_start_char)(byteType)) 
                {
                    *parserState = S_4;
                }    
                else if (BT_S != byteType)
                    *parserState = S_14;
                break;
            
            case S_4:
                if (BT_EQUALS == byteType) 
                {
                    *parserState = S_6;
                }
                else if (BT_S == byteType) 
                {
                    *parserState = S_5;
                }
                else if (!PREFIX(is_name_char)(byteType))
                    *parserState = S_14;
                break;
        
            case S_5:
                if (BT_EQUALS == byteType)
                    *parserState = S_6;
                else if (BT_S != byteType)
                    *parserState = S_14;
                break;
        
            case S_6:
                if (BT_APOS == byteType) 
                {
                    *parserState = S_8;
                }
                else if (BT_QUOT == byteType) 
                {
                    *parserState = S_7;
                }
                else if (BT_S != byteType)
                    *parserState = S_14;
                break;
        
            case S_7:
                if (BT_QUOT == byteType) 
                {
                    *parserState = S_3;
                }
                else if(BT_LT == byteType || BT_AMP == byteType)
                {                    
                    *parserState = S_14;
                    /* some problem exists. fix! */
                }
                break;
            
            case S_8:
                if (BT_APOS == byteType) 
                {
                    *parserState = S_3;
                }
                else if (BT_LT == byteType || BT_AMP == byteType)
                    *parserState = S_14;
                break;
            
            case S_9:
                data->type = EMPTY_ELEMENT_TAG;
                
                if (BT_GT == byteType) 
                {
                    PREFIX(doHomeWork)(data, parserState, ptr, numOfChars);
                    return SPP_ERROR_NONE;    
                }
                else
                    *parserState = S_14;
                break;
        
            case S_10:
                if (PREFIX(is_name_start_char)(byteType)) 
                {
                    *parserState = S_11;
                }
                else
                    *parserState = S_14;
                break;
        
            case S_11:
                if (BT_GT == byteType) 
                {
                    *parserState = S_0;
                }
                else if (BT_S == byteType) 
                {
                    *parserState = S_12;
                }
                else if (!PREFIX(is_name_char)(byteType))
                    *parserState = S_14;
                break;
        
            case S_12:
                if (BT_GT == byteType) 
                {
                    *parserState = S_0;
                }
                else if (BT_S != byteType)
                    *parserState = S_14;
                break;
        
            case S_13:
                if(BT_QUEST == byteType)
                    *parserState = S_1;
                else
                    *parserState = S_14;
                break;

            case S_14:
                printf("some problem exists. fix it!\n");
    
            default:
                
                return -(*parserState);
            }

            *numOfChars -= MINBPC(enc);
            *ptr += MINBPC(enc);
        }

        return SPP_ERROR_TOKENIZER_FAILED;

}

static int PTRCALL
PREFIX(tokenizeContent)(int* parserState, TokDataStruct* data, const ENCODING *enc,
                        int *numOfChars, char* end, const char **ptr)
{ 
    /* printf("*numOfChars:%d\n", *numOfChars); */
    int byteType;
    while(*numOfChars >= MINBPC(enc))
    {
        byteType = BYTE_TYPE(enc, *ptr);
        /*printf("*ptr:%s\n", *ptr);*/
        /* printf("byteType:%d\n", byteType); */
        /* printf("*parserState:%d\n", *parserState); */
        switch (*parserState) 
        {
            case S_0:
                /* if ('<' == ch) { */
                if(BT_LT == byteType) 
                {
                    if (data->numOfPtrs) 
                    {
                        PREFIX(add_ptr)(*ptr - 1, data);
                        return SPP_ERROR_NONE;
                    }
                    
                    *parserState = S_1;
                }
                else
                if (!data->numOfPtrs) 
                {
                    data->type = PCDATA;
                    PREFIX(add_ptr)(*ptr, data); 
                }
                
                break;
        
            case S_1:
                /* if ('/' == ch) { */
                if(BT_SOL == byteType)
                {
                    data->type = END_TAG;
                    
                    *parserState = S_10;
                }
                else if (PREFIX(is_name_start_char)(byteType)) 
                {
                    data->type = START_TAG;
                    PREFIX(add_ptr)(*ptr, data);
                    
                    *parserState = S_2;
                }
                else
                    *parserState = S_13;
                
                break;
        
            case S_2:
                if (BT_GT == byteType) 
                {
                    if (data->numOfPtrs) 
                    {
                        PREFIX(add_ptr)(*ptr - 1, data);
                        return SPP_ERROR_NONE;
                    }
                    
                    *parserState = S_0;
                }
                else if (BT_SOL == byteType) 
                {
                    PREFIX(add_ptr)(*ptr - 1, data);
                    
                    *parserState = S_9;
                }
                /* else if (is_white_space(ch)) { */
                else if (BT_S == byteType) 
                {
                    PREFIX(add_ptr)(*ptr - 1, data);
                    
                    *parserState = S_3;
                }    
                /* else if (!is_name_char(ch)) */
                else if (!PREFIX(is_name_char)(byteType))
                    *parserState = S_13;
                break;
        
            case S_3:
                if (BT_GT == byteType) 
                {
                    if (data->numOfPtrs)
                        return SPP_ERROR_NONE;
                    
                    *parserState = S_0;
                }
                /* else if ('/' == ch) */
                else if (BT_SOL == byteType)
                    *parserState = S_9;
                else if (PREFIX(is_name_start_char)(byteType)) 
                {
                    PREFIX(add_ptr)(*ptr, data);
                    
                    *parserState = S_4;
                }    
                else if (BT_S != byteType)
                    *parserState = S_13;
                break;
            
            case S_4:
                /* if ('=' == ch) { */
                if (BT_EQUALS == byteType) 
                {
                    PREFIX(add_ptr)(*ptr - 1, data);
                    
                    *parserState = S_6;
                }
                else if (BT_S == byteType) 
                {
                    PREFIX(add_ptr)(*ptr - 1, data);
                    
                    *parserState = S_5;
                }
                else if (!PREFIX(is_name_char)(byteType))
                    *parserState = S_13;
                break;
        
            case S_5:
                /* if ('=' == ch) */
                if (BT_EQUALS == byteType)
                    *parserState = S_6;
                else if (BT_S != byteType)
                    *parserState = S_13;
                break;
        
            case S_6:
                /* if ('\'' == ch) { */
                if (BT_APOS == byteType) 
                {
                    PREFIX(add_ptr)(*ptr, data);
                    
                    *parserState = S_8;
                }
                /* else if ('"' == ch) { */
                else if (BT_QUOT == byteType) 
                {
                    PREFIX(add_ptr)(*ptr, data);
                    
                    *parserState = S_7;
                }
                else if (BT_S != byteType)
                    *parserState = S_13;
                break;
        
            case S_7:
                /* if ('"' == ch) { */
                if (BT_QUOT == byteType) 
                {
                    PREFIX(add_ptr)(*ptr, data);
                    
                    *parserState = S_3;
                }
                /* else if ('<' == ch || '&' == ch) */
                else if (BT_LT == byteType || BT_AMP == byteType)
                    *parserState = S_13;
                /* some problem exists. fix it!. */
                break;
            
            case S_8:
                /* if ('\'' == byteType) { */
                if (BT_APOS == byteType) 
                {
                    PREFIX(add_ptr)(*ptr, data);
                
                    *parserState = S_3;
                }
                /* else if ('<' == ch || '&' == ch) */
                else if (BT_LT == byteType || BT_AMP == byteType)
                    *parserState = S_13;
                break;
            
            case S_9:
                data->type = EMPTY_ELEMENT_TAG;
                
                /* if ('>' == ch) { */
                if (BT_GT == byteType) 
                {
                    if (data->numOfPtrs)
                        return SPP_ERROR_NONE;
                    
                    *parserState = S_0;
                }
                else
                    *parserState = S_13;
                break;
        
            case S_10:
                if (PREFIX(is_name_start_char)(byteType)) 
                {
                    PREFIX(add_ptr)(*ptr, data);
                    
                    *parserState = S_11;
                }
                else
                    *parserState = S_13;
                break;
        
            case S_11:
                /* if ('>' == ch) { */
                if (BT_GT == byteType) 
                {
                    if (data->numOfPtrs) 
                    {
                        PREFIX(add_ptr)(*ptr - 1, data);
                        return SPP_ERROR_NONE;
                    }
                    
                    *parserState = S_0;
                }
                else if (BT_S == byteType) 
                {
                    PREFIX(add_ptr)(*ptr - 1, data);
                    
                    *parserState = S_12;
                }
                else if (!PREFIX(is_name_char)(byteType))
                    *parserState = S_13;
                break;
        
            case S_12:
                /* if ('>' == ch) { */
                if (BT_GT == byteType) 
                {
                    if (data->numOfPtrs)
                        return SPP_ERROR_NONE;
                    
                    *parserState = S_0;
                }
                else if (BT_S != byteType)
                    *parserState = S_13;
                break;
        
            case S_13:
                /* some problem exists. fix it!. */
    
            default:
                
                return -(*parserState);
            }

            *numOfChars -= MINBPC(enc);
            *ptr += MINBPC(enc);
        }

        return SPP_ERROR_TOKENIZER_FAILED;

}

static int PTRCALL
PREFIX(nameMatchesAscii)(const ENCODING *enc, const char *ptr1,
                         const char *end1, const char *ptr2)
{
  for (; *ptr2; ptr1 += MINBPC(enc), ptr2++) 
  {
    if (ptr1 == end1)
      return 0;
    if (!CHAR_MATCHES(enc, ptr1, *ptr2))
      return 0;
  }
  return ptr1 == end1;
}
            
