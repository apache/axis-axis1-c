/***************************************************************************
 *
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
 *                                                                         
 ***************************************************************************/
#if !defined(_BUFFER_HPP__INCLUDED_)
#define _BUFFER_HPP__INCLUDED_

#include "XmlPullParserException.hpp"

template <class T>
class Buffer
{
protected:
	T *buffer;
	int size;
	
public:
	Buffer(int size);
	~Buffer();
	
	void grow();
	
	T *get()
	{
		return buffer;
	}	
	
	int getSize()
	{
		return size;
	}
};

template <class T>
Buffer<T>::Buffer(int size)
{
	this->size= size;
	buffer= (T *)malloc(sizeof(T)*size);
	if (!buffer)
		throw new XmlPullParserException();
}

template <class T>
Buffer<T>::~Buffer()
{
	free(buffer);
}

template <class T>
void Buffer<T>::grow()
{
	size <<= 1;
	T *p= (T *)realloc(buffer, sizeof(T)*size);
	if (p)
		buffer= p;
	else
		throw new XmlPullParserException();
}
#endif
