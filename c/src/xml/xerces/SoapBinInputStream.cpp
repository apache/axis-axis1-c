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

/* SoapBinInputStream.cpp: implementation of the SoapBinInputStream class. */


#include "SoapBinInputStream.h"

SoapBinInputStream::SoapBinInputStream(AxisIOStream* pInputStream)
{
    m_pInputStream = pInputStream;
    m_nByteCount = 0;
}

SoapBinInputStream::~SoapBinInputStream()
{

}

/*
 * I dont really understand the use of this function
 */
unsigned int SoapBinInputStream::curPos() const
{
    return m_nByteCount;
}

unsigned int SoapBinInputStream::readBytes(XMLByte* const pcToFill,
                                           const unsigned int iMaxToRead)
{
    int iRead = iMaxToRead;
	m_pInputStream->getBytes((char*)pcToFill, &iRead);
	m_nByteCount += iRead;
    return iRead;
}
