/* -*- C++ -*- */

/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 2002 The Apache Software Foundation.  All rights
 * reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. The end-user documentation included with the redistribution,
 *    if any, must include the following acknowledgment:
 *       "This product includes software developed by the
 *        Apache Software Foundation (http://www.apache.org/)."
 *    Alternately, this acknowledgment may appear in the software itself,
 *    if and wherever such third-party acknowledgments normally appear.
 *
 * 4. The names "Axis" and "Apache Software Foundation" must
 *    not be used to endorse or promote products derived from this
 *    software without prior written permission. For written
 *    permission, please contact apache@apache.org.
 *
 * 5. Products derived from this software may not be called "Apache",
 *    nor may "Apache" appear in their name, without prior written
 *    permission of the Apache Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE APACHE SOFTWARE FOUNDATION OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * ====================================================================
 *
 * This software consists of voluntary contributions made by many
 * individuals on behalf of the Apache Software Foundation.  For more
 * information on the Apache Software Foundation, please see
 * <http://www.apache.org/>.
 */
/*
 *
 *
 * @author Lilantha Darshana (lilantha@virtusa.com)
 * @author Damitha Kumarage (damitha@jkcsworld.com, damitha@opensource.lk)
 *
 */

#include <client/transport/axis/Platform.hpp>
#include <client/transport/axis/Receiver.hpp>
#include <client/transport/axis/HttpTransport.hpp>
#include <iostream>


Receiver::~Receiver()
{

}

const char* Receiver::Recv() throw (AxisException)
{
  int bodyLength;
  int isHttpHeader;
	const char* pToReturn = NULL;
  isHttpHeader = m_pTrChannel->getIsHttpHeader();
  bodyLength = m_pTrChannel->getBodyLength();
  //printf("bodyLength:%d\n", bodyLength);
  //printf("isHttpHeader:%d\n", isHttpHeader);
  if(isHttpHeader == 1 && bodyLength == 0)
    return NULL;
	if (0 == m_BytesRead)
	{
		try
		{
            //printf("try\n");
			*m_pTrChannel >> (&m_pMsg);
            if(m_pMsg == NULL)
                return NULL;
            
			m_MsgSize = strlen(m_pMsg);        
		}
		catch(AxisException& ex)
		{
      printf("catch\n");
			// Get the fault message.
			*m_pTrChannel >> (&m_pMsg);
			m_MsgSize = strlen(m_pMsg);
			#ifdef _DEBUG
			//	std::cerr << ex.GetErrorMsg() << std::endl;
			#endif
		}
		catch(...)
		{
      printf("catch(...)\n");
			throw AxisException(RECEPTION_ERROR);
		}
	}
    //printf("m_MsgSize:%d\n", m_MsgSize);
	if (m_MsgSize > 0)
	{
    bodyLength = m_pTrChannel->getBodyLength();
    //printf("m_MsgSize:%d\n", m_MsgSize);
    //printf("bodyLength:%d\n", bodyLength);
    bodyLength -= m_MsgSize;
    m_pTrChannel->setBodyLength(bodyLength);    
		pToReturn = m_pMsg;
		m_BytesRead = m_MsgSize;
        //printf("m_BytesRead:%d\n", m_BytesRead);
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

