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

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "internal.h"
#include "spp.h"
#include "spp_converter.h"
#include "tag.h"


#define MALLOC(s) (ct->m_mem.mallocFcn((s)))
#define MEMMOVE(p1, p2, s) (ct->m_mem.memMoveFcn((p1), (p2), (s)))
#define REALLOC(p,s) (ct->m_mem.reallocFcn((p),(s)))
#define FREE(p) (ct->m_mem.freeFcn((p)))
#define MIN_BUFF_SZ 128    /* 0x10000 */
#define INIT_BUFFER_SIZE 128 /* keep INIT_BUFFER_SIZE <= MIN_BUFF_SZ */
#define protocolEncodingName (ct->m_protocolEncodingName)
#define initEncoding (ct->m_initEncoding)
#define encoding (ct->m_encoding)
#define ns (ct->m_ns)
#define tokState (ct->m_tokState)
#define state (ct->m_state)
#define numOfChars (ct->m_numOfChars)
#define dataCounter (ct->m_dataCounter)
#define namespaceSeparator (ct->m_namespaceSeparator)


int isDone = 0;

enum 
{
    PROLOG, CONTENT
};

/** Struct which represents the parser object. All the member variables of this parser
  * object are prefixed with m_ to represent them as parser memeber variables through
  * out the code*/
typedef struct SPPContext
{
    char *m_buff;/* Tokenized ptr data buffer*/
    char *m_utf8Buff;/* Utf8 tokenized ptr data buffer*/
    int m_buffSize;/* Tokenized ptr data buffer size*/
    int m_utf8BuffSize;/* Utf8 8 tokenized ptr data buffer size*/
    char *m_prevTokPoint;/* This points to the previous tokenizing point of the buffer.
                            This means that when the buffer to be tokenized is passed
                            to the xmltok_impl.c's tokenizeContent method this pointer keeps
                            pointing to the end of data so far tokenized. Only m_currentTokPoint
                            is increased inside the tokenizeContent method*/
    char *m_currentTokPoint;/* This points to the current tokenizing point of the buffer*/
    int m_numOfChars;/* Number of characters to be parsed in the buffer*/
    int m_state;
    int m_tokState;/* Tokenizing state. Holds prolog or content*/
    TokDataStruct m_data;/* Tokenized ptr data structure*/
    int m_dataCounter;
    const XML_Char *m_protocolEncodingName;/* Encoding name*/
    INIT_ENCODING m_initEncoding;/* Encoding structure*/
    const ENCODING *m_encoding;/* Encoding structure*/
    XML_Bool m_ns;
    const SppMemoryHandlingSuite m_mem;/* Memory handling suite*/
    XML_Char m_namespaceSeparator;
    
    int (*getBlock)(char *buff, int buffSize, int *numchars);

} SPPContext;


static enum SPP_Error
processXmlDecl(SPPParser* ct, int isGeneralTextEntity,
               const char *s, const char *currentTokPoint)
{
    /* const XML_Char *encodingName = NULL; */
    /* const XML_Char *storedEncName = NULL; */
    const char *version = NULL;
    const char *versionend;
    /* const XML_Char *storedversion = NULL; */
    int standalone = -1;

    if (!(XmlParseXmlDecl)(isGeneralTextEntity,
        /*Default encoding*/
        encoding,
        s,
        currentTokPoint,
        0,
        &version,
        &versionend,
        &protocolEncodingName,
        /*Encoding is taken from the xml file declaration*/
        &encoding,
        &standalone))

    return SPP_ERROR_SYNTAX;
    else
    {
        /* printf("version:%s\n", version); */
        /* printf("versionend:%s\n", versionend); */
	int kk = ct->m_currentTokPoint - protocolEncodingName -3;
	char* protEncNameEnd = protocolEncodingName + kk;
	protEncNameEnd = '\0';
        /**(protocolEncodingName + (ct->m_currentTokPoint - protocolEncodingName) - 3) = '\0';*/
    
        /*printf("encodingName:%s\n", protocolEncodingName);*/
        /* if(standalone) */
        /* printf("standalone:%s\n", standalone); */
        initializeEncoding(ct);
    }
}

int ret_status;
enum SPP_Error parseProlog(SPPParser* ct)
{
    ct->m_data.numOfPtrs = 0;
    ct->m_data.numOfPtrsUtf8 = 0;
    ct->m_prevTokPoint = ct->m_currentTokPoint;
    do 
    {
        ret_status = 0;    
        if(PROLOG == tokState)
        {
            initializeEncoding(ct);
            /* printf("numOfChars:%d\n", numOfChars); */
            /* XmlPrologTok is defined in spp_converter.h
             */
            ret_status = XmlPrologTok(&state, &ct->m_data, encoding, &numOfChars, 
                ct->m_prevTokPoint, &ct->m_currentTokPoint);
            if(SPP_ERROR_NONE == ret_status)
            {
                /* printf("ct->m_prevTokPoint:%s\n", ct->m_prevTokPoint); */
                /* printf("ct->m_currentTokPoint:%s\n", ct->m_currentTokPoint); */
                processXmlDecl(ct, 0, ct->m_prevTokPoint, ct->m_currentTokPoint);
                ct->m_prevTokPoint = ct->m_currentTokPoint;
            }
        }
        return SPP_ERROR_NONE;
    
    } while (loadBuffer(ct));

    return SPP_ERROR_PARSE_FAILED;
}

enum SPP_Error parseContent(SPPParser* ct)
{
    ct->m_data.numOfPtrs = 0;
    ct->m_data.numOfPtrsUtf8 = 0;
    /* Initialially m_preveTokPoint points to the currentTokPoint*/
    ct->m_prevTokPoint = ct->m_currentTokPoint;
    do
    {
        ret_status = 0;    
        if(PROLOG == tokState)
        {
            initializeEncoding(ct);
            /* printf("numOfChars:%d\n", numOfChars); */

            /* XmlPrologTok is defined in spp_converter.h. While method is executed
             * prevTokPoint is not changed. currentTokPoint moves forward*/
            ret_status = XmlPrologTok(&state, &ct->m_data, encoding, &numOfChars, 
            ct->m_prevTokPoint, &ct->m_currentTokPoint);
            if(SPP_ERROR_NONE == ret_status)
            {
                /* printf("ct->m_prevTokPoint:%s\n", ct->m_prevTokPoint); */
                /* printf("ct->m_currentTokPoint:%s\n", ct->m_currentTokPoint); */
                processXmlDecl(ct, 0, ct->m_prevTokPoint, ct->m_currentTokPoint);
                ct->m_prevTokPoint = ct->m_currentTokPoint;
            }
        }
        if(SPP_ERROR_NONE == ret_status)
        {
            tokState = CONTENT;
            /* printf("numOfChars:%d\n", numOfChars); */
            /* XmlContentTok is defined in spp_converter.h.*/

            
            /* XmlContentTok is defined in spp_converter.h. While method is executed
             * prevTokPoint is not changed. currentTokPoint moves forward 
             * until a valid tag element is completed*/
            ret_status = XmlContentTok(&state, &ct->m_data, encoding,
                &numOfChars, ct->m_prevTokPoint, &ct->m_currentTokPoint);
            /* printf("tempStatus:%d\n", tempStatus); */
            /* printf("ct->m_prevTokPoint:%s\n", ct->m_prevTokPoint); */
            /* printf("ct->m_currentTokPoint:%s\n", ct->m_currentTokPoint); */
            if(SPP_ERROR_NONE == ret_status)
            {
                return SPP_ERROR_NONE;
            }
        }    
    
    } while (loadBuffer(ct));

    return SPP_ERROR_PARSE_FAILED;
}

int loadBuffer(SPPParser *ct)
{
    if(isDone)
        return SPP_ERROR_NONE;
    /* Holds the size from the parser buffer beginning to the
     * end of used data. Simply said, this is the already
     * used data to make a tag, remaining in the buffer*/
    int usedData;
    /* Take the size of data that is remained from the previous parse
     * iteration failing to complete a tag element */
    int unusedData = (int)(ct->m_currentTokPoint - ct->m_prevTokPoint);

    int toBeFilledSize = ct->m_buffSize - ((int) (ct->m_currentTokPoint - ct->m_buff));
    /* We define MIN_BUFFER_SZ as the minimum value the toBeFilledSize
     * could assume.
     * If the toBeFilledSize is less than the MIN_BUFFER_SZ*/
    if(toBeFilledSize < MIN_BUFF_SZ)
    {
        /* We can get rid of used data and use used data size and vacant size
         * to fill the buffer again*/
         toBeFilledSize = ct->m_buffSize - unusedData;

        /* If the toBeFilledSize is less than the MIN_BUFFER_SZ,
         * buffer size is doubled for performance reasons */
        if (toBeFilledSize < MIN_BUFF_SZ)
        {
            int ii;
            ct->m_buffSize *= 2;/* Double the parser buffer size*/

            /* Now since the buffer size is increased the fill
             * size is also increased*/
            toBeFilledSize = ct->m_buffSize - unusedData;

            /* Move the used data to the beginning of the parser
             * buffer. Used data will be lost */
            MEMMOVE(ct->m_buff, ct->m_prevTokPoint, unusedData);
            ct->m_buff = REALLOC(ct->m_buff, ct->m_buffSize);
            usedData = (int)(ct->m_prevTokPoint - ct->m_buff);
            /*MEMMOVE(ct->m_buff, ct->m_prevTokPoint, unusedData);*/
            ct->m_prevTokPoint = ct->m_buff;
            ct->m_currentTokPoint = ct->m_prevTokPoint + unusedData;
            ii = 0;
            /* Move the already tokenized data pointers */
            while (ii < ct->m_data.numOfPtrs)
                ct->m_data.ptrBuff[ii++] -= usedData;
        }
        else /* Don't double the buffer size. But get rid of the used data*/
        {
            int ii;

            usedData = (int)(ct->m_prevTokPoint - ct->m_buff);
            MEMMOVE(ct->m_buff, ct->m_prevTokPoint, unusedData);
            ct->m_prevTokPoint = ct->m_buff;
            ct->m_currentTokPoint = ct->m_prevTokPoint + unusedData;
            ii = 0;
            while (ii < ct->m_data.numOfPtrs)
                ct->m_data.ptrBuff[ii++] -= usedData;
        }
    }

    if(!ct->getBlock(ct->m_currentTokPoint, toBeFilledSize, &numOfChars))
    {
        return SPP_ERROR_READ_BLOCK;
    }
    else
        return SPP_ERROR_NONE; 
}

int getBlock(char *buff, int toBeFilledSize, int* numchars)
{
    int len;
    int done;
    *numchars = 0;
    len = fread(buff, 1, toBeFilledSize, stdin);
    /*printf("len:%d\n", len);*/
    *numchars += len;
        if (ferror(stdin))
        {
            fprintf(stderr, "Read error\n");
            exit(-1);
        }
        done = feof(stdin);
    if(done) 
        isDone = 1;
    return SPP_ERROR_NONE;
}


SPPParser* parserCreate(const XML_Char *encodingName)
{
    return parserCreate_mh(encodingName, NULL, NULL);
}

SPPParser* parserCreate_mh(const XML_Char *encodingName, 
    const SppMemoryHandlingSuite *memsuite,
    XML_Char nsSep)
{
    return parserCreate_in(encodingName, memsuite, nsSep);
}

/** Create parser*/
static SPPParser* parserCreate_in(const XML_Char *encodingName,
    const SppMemoryHandlingSuite *memsuite,
    XML_Char nsSep)
{
    SPPParser* ct;
    /* If memory handling functions are externally provided*/
    if (memsuite) 
    {
        SppMemoryHandlingSuite *mtemp;
        ct = (SPPParser*) memsuite->mallocFcn(sizeof(struct SPPContext));
        if (ct != NULL) 
        {
            mtemp = (SppMemoryHandlingSuite *)&(ct->m_mem);
            mtemp->mallocFcn = memsuite->mallocFcn;
            mtemp->memMoveFcn = memsuite->memMoveFcn;
            mtemp->reallocFcn = memsuite->reallocFcn;
            mtemp->freeFcn = memsuite->freeFcn;
        }
    }
    else /* Use system memory handling functions*/
    {
        SppMemoryHandlingSuite *mtemp;
        ct = (SPPParser*) malloc(sizeof(struct SPPContext));
        if (ct != NULL) 
        {
            mtemp = (SppMemoryHandlingSuite *)&(ct->m_mem);
            mtemp->mallocFcn = malloc;
            mtemp->memMoveFcn = memmove;
            mtemp->reallocFcn = realloc;
            mtemp->freeFcn = free;
        }
    }

    ct->m_buffSize = INIT_BUFFER_SIZE;
    ct->m_utf8BuffSize = ct->m_buffSize;
    char* buff = (char*) malloc(ct->m_buffSize * sizeof(char));
    char* utf8Buff = (char*) malloc(ct->m_utf8BuffSize * sizeof(char));
    if(buff == NULL || utf8Buff == NULL)
        return NULL;
    ct->m_buff = buff;
    ct->m_utf8Buff = utf8Buff;
    
    namespaceSeparator = '!';
    ns = XML_FALSE;

    if(SPP_ERROR_NONE == parserInit(ct, encodingName))
        return ct;
    else
        return NULL;
}

/** Initialize parser*/
static int parserInit(SPPParser* ct, const XML_Char *encodingName)
{
    if(ct)
    {
        numOfChars = 0;
        ct->m_currentTokPoint = ct->m_buff;
        ct->m_prevTokPoint = ct->m_buff;
        state = S_0;
        tokState = PROLOG;
        ct->getBlock = getBlock;
        ct->m_data.ptrBuff = NULL;
        ct->m_data.utf8PtrBuff = NULL;
        ct->m_data.ptrBuffSize = 8;
        dataCounter = 0;
        protocolEncodingName = encodingName;

        return SPP_ERROR_NONE;
    }
    else
        return SPP_ERROR_PARSER_INIT_FAILED;
}

/** Initialize encoding*/
static int initializeEncoding(SPPParser* ct)
{
    const char *s;
    #ifdef XML_UNICODE
        char encodingBuf[128];
        if (!protocolEncodingName)
            s = NULL;
        else 
        {
            int i;
            for (i = 0; protocolEncodingName[i]; i++) 
            {
                if (i == sizeof(encodingBuf) - 1
                    || (protocolEncodingName[i] & ~0x7f) != 0) 
                {
                    encodingBuf[0] = '\0';
                    break;
                }
                encodingBuf[i] = (char)protocolEncodingName[i];
            }
            encodingBuf[i] = '\0';
            s = encodingBuf;
        }
    #else
    /* printf("protocolEncodingName:%s\n", protocolEncodingName); */
    s = protocolEncodingName;
    #endif
    if (XmlInitEncoding(&initEncoding,
        &encoding, s))
        return SPP_ERROR_NONE;
    /* return handleUnknownEncoding(parser, protocolEncodingName); */
}

void* parserFree(SPPParser* ct)
{
    free(ct);
}

TokDataStruct* next(SPPParser* ct)
{
    dataCounter = 0;
    if(SPP_ERROR_NONE == parseContent(ct))
    {
        return &ct->m_data;
    }
    else
        return NULL;    

}

int getNextElementAsInt(SPPParser* ct, int* parseError)
{
    int intTemp;
    int intCount = 0;
    int tempDiff;

    const char *rawNameEnd = &ct->m_data.ptrBuff[intCount + 1][1];
    const char *fromPtr = ct->m_data.ptrBuff[intCount];
    XML_Char* toPtr = (XML_Char *) ct->m_utf8Buff;    
    XML_Char* startPtr = (XML_Char *) ct->m_utf8Buff;
    XML_Char* endPtr = (XML_Char *) ct->m_utf8Buff;
    tempDiff = ct->m_data.ptrBuff[intCount+1] - ct->m_data.ptrBuff[intCount];
    if(tempDiff <= 1)
        return;
    SppUtf8Convert(encoding, &fromPtr, rawNameEnd,
        (ICHAR **)&toPtr, (ICHAR *)ct->m_utf8Buff + ct->m_utf8BuffSize);
    sscanf(ct->m_utf8Buff, "%d", &intTemp);
    *parseError = SPP_ERROR_NONE;    
    return intTemp;

}

