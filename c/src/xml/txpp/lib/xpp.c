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
#include "xpp.h"
#include "xmltok.h"
#include "xmlrole.h"
#ifdef HAVE_XPP_CONFIG_H
#include "../xpp_config.h"
#endif
#include "tag.h"


#define MALLOC(s) (ct->m_mem.malloc_fcn((s)))
#define MEMMOVE(p1, p2, s) (ct->m_mem.memmove_fcn((p1), (p2), (s)))
#define REALLOC(p,s) (ct->m_mem.realloc_fcn((p),(s)))
#define FREE(p) (ct->m_mem.free_fcn((p)))
#define    MIN_BUFF_SZ    512    /* 0x10000 */
#define INIT_BUFFER_SIZE 512 /* keep INIT_BUFFER_SIZE <= MIN_BUFF_SZ */
#define protocolEncodingName (ct->m_protocolEncodingName)
#define initEncoding (ct->m_initEncoding)
#define encoding (ct->m_encoding)
#define ns (ct->m_ns)
#define tok_state (ct->m_tok_state)
#define state (ct->m_state)
#define num_chars (ct->m_num_chars)
#define XmlParseXmlDeclNS XmlParseXmlDecl
#define eventPtr (ct->m_eventPtr)
#define eventEndPtr (ct->m_eventEndPtr)
#define XmlConvert XmlUtf8Convert
#define data_counter (ct->m_data_counter)
#define namespaceSeparator (ct->m_namespaceSeparator)


int isDone = 0;

enum 
{
        PROLOG, CONTENT
};

typedef struct xpp_context
{
    char *buff;
    char *utf8buff;
    int buff_sz;
    int utf8buff_sz;
    char *dirty;
    char *next;
    int m_num_chars;
    int m_state;
    int m_tok_state;
    data_t data;
    int m_data_counter;
    const XML_Char *m_protocolEncodingName;
    INIT_ENCODING m_initEncoding;
    const ENCODING *m_encoding;
    XML_Bool m_ns;
      const char *m_eventPtr;
      const char *m_eventEndPtr;
    const XML_Memory_Handling_Suite m_mem;
    XML_Char m_namespaceSeparator;
    
    int (*get_block)(char *buff, int buff_sz, int *numchars);

} xpp_context;


static enum XML_Error
processXmlDecl(xpp_context_t* ct, int isGeneralTextEntity,
               const char *s, const char *next)
{
  /* const XML_Char *encodingName = NULL; */
  /* const XML_Char *storedEncName = NULL; */
  const ENCODING *newEncoding = NULL;
  const char *version = NULL;
  const char *versionend;
  /* const XML_Char *storedversion = NULL; */
  int standalone = -1;

  if (!(ns
        ? XmlParseXmlDeclNS
        : XmlParseXmlDecl)(isGeneralTextEntity,
                           encoding,
                           s,
                           next,
                           &eventPtr,
                           &version,
                           &versionend,
                           &protocolEncodingName,
                           &newEncoding,
                           &standalone))

    return XML_ERROR_SYNTAX;
  else
  {
    /* printf("version:%s\n", version); */
    /* printf("versionend:%s\n", versionend); */
    *(protocolEncodingName + (ct->next - protocolEncodingName) - 3) = '\0';
    
    printf("encodingName:%s\n", protocolEncodingName);
    /* if(standalone) */
        /* printf("standalone:%s\n", standalone); */
    initialize_encoding(ct);
    
  }
   
}

int ret_status;

int parse(xpp_context_t *ct)
{
    ct->data.num_ptrs = 0;
    ct->data.num_ptrs_utf8 = 0;
    ct->dirty = ct->next;
    do {
        ret_status = 0;    
        if(PROLOG == tok_state)
        {
            initialize_encoding(ct);
            /* printf("num_chars:%d\n", num_chars); */
            ret_status = XmlPrologTok(&state, &ct->data, encoding, &num_chars, 
                ct->dirty, &ct->next);
            if(XML_ERROR_NONE == ret_status)
            {
                /* printf("ct->dirty:%s\n", ct->dirty); */
                /* printf("ct->next:%s\n", ct->next); */
                processXmlDecl(ct, 0, ct->dirty, ct->next);
                ct->dirty = ct->next;
            }
        }
        if(XML_ERROR_NONE == ret_status)
        {
            tok_state = CONTENT;
            /* printf("num_chars:%d\n", num_chars); */
            ret_status = XmlContentTok(&state, &ct->data, encoding,
                &num_chars, ct->dirty, &ct->next);
        /* printf("tempStatus:%d\n", tempStatus); */
        /* printf("ct->dirty:%s\n", ct->dirty); */
        /* printf("ct->next:%s\n", ct->next); */
            if(XML_ERROR_NONE == ret_status)
            {
                return XML_ERROR_NONE;
            }
        }    
    
    } while (load_buffer(ct));

    return XML_TEST_ERROR;
}

    
int load_buffer(xpp_context_t *ct)
{
    if(isDone)
        return XML_ERROR_NONE;
    int sz = ct->buff_sz - (int)(ct->next - ct->buff);
    if (sz < MIN_BUFF_SZ) 
    {
        int ii, n, m;
        n = (int)(ct->next - ct->dirty);
        ct->buff_sz *= 2;
        sz = ct->buff_sz - n;
        ct->buff = REALLOC(ct->buff, ct->buff_sz);

        m = (int)(ct->dirty - ct->buff);
        MEMMOVE(ct->buff, ct->dirty, n);
        ct->dirty = ct->buff;
        ct->next = ct->dirty + n;
        ii = 0;
        while (ii < ct->data.num_ptrs)
            ct->data.ptrs[ii++] -= m;
    }
    
    /* printf("ct->buff_sz:%d\n", ct->buff_sz); */
    if(!ct->get_block(ct->next, sz, &num_chars)) 
    {
        return XML_TEST_ERROR;
    }
    else
        return XML_ERROR_NONE;
}

int get_block(char *buff, int buff_sz, int* numchars)
{
    int len;
    int done;
    *numchars = 0;
    len = fread(buff, 1, buff_sz, stdin);
    printf("len:%d\n", len);
    *numchars += len;
        if (ferror(stdin))
        {
            fprintf(stderr, "Read error\n");
                exit(-1);
        }
        done = feof(stdin);
    if(done) 
        isDone = 1;

    return XML_ERROR_NONE;
}


xpp_context_t* parser_create(const XML_Char *encodingName)
{
    return parser_create_mh(encodingName, NULL, NULL);
}

xpp_context_t* parser_create_ns(const XML_Char *encodingName, XML_Char nsSep)
{
    XML_Char tmp[2];
    *tmp = nsSep;
    return parser_create_mh(encodingName, NULL, tmp);
}

xpp_context_t* parser_create_mh(const XML_Char *encodingName, 
                                const XML_Memory_Handling_Suite *memsuite,
                                XML_Char nsSep)
{
    return parser_create_in(encodingName, memsuite, nsSep);
}

static xpp_context_t* parser_create_in(const XML_Char *encodingName,
                                       const XML_Memory_Handling_Suite *memsuite,
                                       XML_Char nsSep)
{
    xpp_context_t* ct;

    if (memsuite) 
    {
            XML_Memory_Handling_Suite *mtemp;
        ct = (xpp_context_t*) memsuite->malloc_fcn(sizeof(struct xpp_context));
            if (ct != NULL) 
            {
                  mtemp = (XML_Memory_Handling_Suite *)&(ct->m_mem);
                  mtemp->malloc_fcn = memsuite->malloc_fcn;
                  mtemp->memmove_fcn = memsuite->memmove_fcn;
                  mtemp->realloc_fcn = memsuite->realloc_fcn;
                  mtemp->free_fcn = memsuite->free_fcn;
            }
      }
      else 
      {
            XML_Memory_Handling_Suite *mtemp;
            ct = (xpp_context_t*) malloc(sizeof(struct xpp_context));
            if (ct != NULL) 
            {
                  mtemp = (XML_Memory_Handling_Suite *)&(ct->m_mem);
                  mtemp->malloc_fcn = malloc;
                  mtemp->memmove_fcn = memmove;
                  mtemp->realloc_fcn = realloc;
                  mtemp->free_fcn = free;
            }
      }

    ct->buff_sz = INIT_BUFFER_SIZE;
    ct->utf8buff_sz = ct->buff_sz;
        char* buff = (char*) malloc(ct->buff_sz * sizeof(char));
        char* utf8buff = (char*) malloc(ct->utf8buff_sz * sizeof(char));
    if(buff == NULL || utf8buff == NULL)
        return NULL;
        ct->buff = buff;
    ct->utf8buff = utf8buff;
    

    namespaceSeparator = '!';
      ns = XML_FALSE;


    if(XML_ERROR_NONE == parser_init(ct, encodingName))
        return ct;
    else
        return NULL;
}

static int parser_init(xpp_context_t* ct, const XML_Char *encodingName)
{
    if(ct)
    {
            num_chars = 0;
            ct->next = ct->buff;
            ct->dirty = ct->buff;
            state = S_0;
        tok_state = PROLOG;
            ct->get_block = get_block;
            ct->data.ptrs = NULL;
            ct->data.utf8ptrs = NULL;
            ct->data.ptrs_sz = 8;
        data_counter = 0;
        eventPtr = NULL;
          eventEndPtr = NULL;
        protocolEncodingName = encodingName;


        return XML_ERROR_NONE;
    }
    else
        return XML_TEST_ERROR;
}

static int initialize_encoding(xpp_context_t* ct)
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
        if ((ns ? XmlInitEncodingNS : XmlInitEncoding)(&initEncoding,
            &encoding, s))
        return XML_ERROR_NONE;
        /* return handleUnknownEncoding(parser, protocolEncodingName); */
}

void* parser_free(xpp_context_t* ct)
{
    free(ct);
}

data_t* next(xpp_context_t* ct)
{
    data_counter = 0;
    if(!parse(ct))    
    {
        process_data(ct, encoding);
        return &ct->data;
    }
    else
        return NULL;    

}

static int add_utf8_ptr(char *ptr, data_t *data)
{
        if (data->num_ptrs_utf8 == data->ptrs_sz
                || !data->utf8ptrs) 
        {
                int sz = data->ptrs_sz << 1;
                char **ptrs = (char **)malloc(sz << 2);
                if (!ptrs)
                        return XML_TEST_ERROR;
                if (data->utf8ptrs) 
                {
                       memmove(ptrs, data->utf8ptrs, data->num_ptrs_utf8 << 2);
                       free(data->utf8ptrs);
                }
                data->utf8ptrs = ptrs;
                data->ptrs_sz = sz;
        }

        data->utf8ptrs[data->num_ptrs_utf8++] = ptr;

        return XML_ERROR_NONE;
}


static void process_data(xpp_context_t* ct)
{
    int intCount = 0;
    char holder;
        int bufSize;
        int totLen = 0;
    int wordLen = 0;
    int tempDiff;
    XML_Char* toPtr = (XML_Char *) ct->utf8buff;    
    XML_Char* startPtr = (XML_Char *) ct->utf8buff;
    XML_Char* endPtr = (XML_Char *) ct->utf8buff;
    while(intCount < ct->data.num_ptrs)
    {
        const char *rawNameEnd = &ct->data.ptrs[intCount + 1][1];
        const char *fromPtr = ct->data.ptrs[intCount];
        tempDiff = ct->data.ptrs[intCount+1] - ct->data.ptrs[intCount];
        if(tempDiff <= 1)
            return;
        startPtr += wordLen;
        /* printf("fromPtr:\n\n%s\n\n", fromPtr); */
        /* printf("rawNameEnd:\n\n%s\n\n", rawNameEnd); */
        
            if(ct->utf8buff_sz < ct->buff_sz)
            {
            ct->utf8buff_sz = 2 * ct->buff_sz;
            /* printf("utf8buff_sz:%d\n", ct->utf8buff_sz); */
                char *temp = (char *)REALLOC(ct->utf8buff, ct->utf8buff_sz);
                      if (temp == NULL)
                        return XML_ERROR_NO_MEMORY;
                      ct->utf8buff = temp;
            }
            XmlDamConvert(encoding, &fromPtr, rawNameEnd,
                (ICHAR **)&toPtr, (ICHAR *)ct->utf8buff + ct->utf8buff_sz);
        /* printf("startPtr:\n%s\n", startPtr); */
        /* printf("toPtr:\n%s\n", toPtr); */
        wordLen = toPtr - startPtr;
        /* printf("wordLen:%d\n", wordLen); */
            totLen += wordLen;
            
        endPtr = toPtr - 1;
        add_utf8_ptr(startPtr, &ct->data);
        add_utf8_ptr(endPtr, &ct->data);
        intCount += 2;
    }

    return;
        
}

int get_next_element_as_int(xpp_context_t* ct, int* parse_error)
{
    int intTemp;
    char* temp;

    data_counter = 0;
        temp = ct->data.utf8ptrs[data_counter +  1][1];
        ct->data.utf8ptrs[data_counter + 1][1] = XML_T('\0');
    /* printf("ct->data.ptrs[0]:%s\n", ct->data.ptrs[0]); */
        sscanf(ct->data.utf8ptrs[data_counter], "%d", &intTemp);
        ct->data.utf8ptrs[data_counter + 1][1] = temp;
                        
    *parse_error = XML_ERROR_NONE;    
    return intTemp;

}

/*
 *   Prier to call this method state should be START_TAG
 */
int get_next_attribute_as_int(xpp_context_t* ct, int* parse_error)
{
    int intTemp;
    char* temp;
    data_t* data;

    if (2 >= ct->data.num_ptrs_utf8) 
    {
        *parse_error = XML_TEST_ERROR;
        return 0;
    }


    data_counter += 2;
        temp = ct->data.ptrs[data_counter + 1][1];
        ct->data.utf8ptrs[data_counter+1][1] = '\0';
        /* printf("ct->data.ptrs[data_counter]:%s\n", 
         * ct->data.ptrs[data_counter]); 
         */
        sscanf(ct->data.utf8ptrs[data_counter], "%d", &intTemp);
        ct->data.utf8ptrs[data_counter+1][1] = temp;
                        
        
    *parse_error = XML_ERROR_NONE;
    return intTemp;

}

