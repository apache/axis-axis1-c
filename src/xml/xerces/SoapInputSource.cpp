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

/* SoapInputSource.cpp: implementation of the SoapInputSource class. */

#include "SoapInputSource.h"

SoapInputSource::SoapInputSource(AxisIOStream* pInputStream)
{
    m_pInputStream = new SoapBinInputStream(pInputStream);
}

SoapInputSource::~SoapInputSource()
{
	/* do not delete the m_pInputStream. See Xerces documentation */
}

BinInputStream* SoapInputSource::makeStream() const
{
    return m_pInputStream;
}
