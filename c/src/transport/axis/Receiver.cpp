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

/*
 * @author Lilantha Darshana (lilantha@virtusa.com)
 * @author Damitha Kumarage (damitha@jkcsworld.com, damitha@opensource.lk)
 *
 */

#include "Platform.hpp"
#include "Receiver.hpp"
#include "HttpTransport.hpp"
#include <iostream>
#include <stdio.h>


Receiver::~Receiver()
{

}

const char* Receiver::Recv()
{
      int bodyLength;
      int isHttpHeader;
    const char* pToReturn = NULL;
      isHttpHeader = m_pTrChannel->getIsHttpHeader();
      bodyLength = m_pTrChannel->getBodyLength();
      /* printf("bodyLength:%d\n", bodyLength); */
      /* printf("isHttpHeader:%d\n", isHttpHeader); */
      if(isHttpHeader == 1 && bodyLength == 0)
            return NULL;
    if (0 == m_BytesRead)
    {
        AXISC_TRY
#ifdef _DEBUG
                    printf("try\n");
#endif
            *m_pTrChannel >> (&m_pMsg);
                    if(m_pMsg == NULL)
            {
                printf("m_pMsg==NULL\n");
                        return NULL;
            }
            m_MsgSize = strlen(m_pMsg);        
        AXISC_CATCH(AxisException& ex)
                  printf("catch\n");
            /* Get the fault message. */
            *m_pTrChannel >> (&m_pMsg);
            m_MsgSize = strlen(m_pMsg);
            #ifdef _DEBUG
            /*    std::cerr << ex.GetErrorMsg() << std::endl; */
            #endif
        AXISC_CATCH(...)
            AXISTRACE1("SERVER_TRANSPORT_RECEPTION_EXCEPTION", CRITICAL);
            throw THROW_AXIS_TRANSPORT_EXCEPTION(SERVER_TRANSPORT_RECEPTION_EXCEPTION);
        AXISC_ENDCATCH
    }
        /* printf("m_MsgSize:%d\n", m_MsgSize); */
    if (m_MsgSize > 0)
    {
        bodyLength = m_pTrChannel->getBodyLength();
#ifdef _DEBUG
        printf("m_MsgSize:%d\n", m_MsgSize);
        printf("bodyLength:%d\n", bodyLength);
#endif
        bodyLength -= m_MsgSize;
        m_pTrChannel->setBodyLength(bodyLength);    
        pToReturn = m_pMsg;
        m_BytesRead = m_MsgSize;
        m_MsgSize -= m_BytesRead;
        m_pMsg += m_BytesRead;
            m_BytesRead = 0;
    
        return pToReturn;        
    }
    else
    {
            printf("m_MsgSize == 0, so return NULL\n");
        return NULL;
    }
}

int Receiver::getBytesRead()
{
  return m_BytesRead;
}

