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

/*
 *    @author Dasarath Weerathunga
 */

#if !defined(_ARRAY_HPP__INCLUDED_)
#define _ARRAY_HPP__INCLUDED_

 #include "Buffer.hpp"
 #include "XmlPullParserException.hpp"
 
 template <class T>
class Array: public Buffer<T>
{
	int last;
	
public:
	Array(int iSize): Buffer<T>(iSize)
	{
		last= -1;
	}
	
	T& operator[](int i)
	{
		if (i > last)
			throw new XmlPullParserException();
		return buffer[i];
	}

	int count()
	{
		return last+1;
	}

	T& getLast()
	{
		if (last < 0)
			throw new XmlPullParserException();
		return buffer[last];
	}

	T& append()
	{
		if (++last == size)
			grow();
		return buffer[last];
	}

	int trunc(int iSize)
	{
		if ((iSize > 0 && last < iSize) || iSize < 0)
			throw new XmlPullParserException();
		else
			return last= iSize-1;
	}

	int chip()
	{
		if (last < 0)
			throw new XmlPullParserException();
		else
			return last--; // included return as there was an error occuring
	}
};

#endif
