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
 
#ifndef AXISINPUTSTREAM_HPP
#define AXISINPUTSTREAM_HPP

#include "InputStream.hpp"
#include "SOAPTransport.h"

AXIS_CPP_NAMESPACE_USE
/**
InputStream class that wraps the AxisIOStream object

@author Susantha Kumara
*/
class AxisInputStream : public InputStream
{
public:
    AxisInputStream(AxisIOStream* pInputStream);

    ~AxisInputStream();

    int read(char* buffer, int offset, int length);
private:
	AxisIOStream* m_pInputStream;
};

#endif
