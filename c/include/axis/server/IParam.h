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

#if !defined(_IPARAM_H____OF_AXIS_INCLUDED_)
#define _IPARAM_H____OF_AXIS_INCLUDED_

#include "AxisUserAPI.h"
#include "AxisWrapperAPI.h"
#include "TypeMapping.h"
#include "time.h"

#include <string>
using namespace std;
/**
    @class ComplexObjectHandler
    @brief

    @author Susantha Kumara (skumara@virtusa.com)
*/
class ComplexObjectHandler
{
public:
	void* pObject;
	AXIS_SERIALIZE_FUNCT pSZFunct;
	AXIS_OBJECT_CREATE_FUNCT pCreFunct;
	AXIS_OBJECT_DELETE_FUNCT pDelFunct;
	AXIS_DESERIALIZE_FUNCT pDZFunct;
	AXIS_OBJECT_SIZE_FUNCT pSizeFunct;
	AxisString m_TypeName;
	AxisString m_URI;
public:
	ComplexObjectHandler();
	~ComplexObjectHandler();
	void init();
};

typedef union uParamValue
{
	int nValue;
    unsigned int unValue;
    short sValue;
    unsigned short usValue;
    long lValue;
    unsigned ulValue;
    char cValue;
    unsigned char ucValue;
	float fValue;
	double dValue;
    struct tm tValue;/* this will hold the c type tm struct*/
	xsd__hexBinary hbValue;
	xsd__base64Binary b64bValue;
    long lDuration;/* duration in seconds*/
	class ArrayBean* pArray; //this is used to hold arrays
	class IArrayBean* pIArray; //used by wrapper classes
	ComplexObjectHandler* pCplxObj;
	const AxisChar* pStrValue; 
} uParamValue;

class IParam  
{
public:
	IParam(){};
	virtual ~IParam(){};
	virtual int setArrayElements(void* pElements)= 0;
	virtual int setArrayElements(void* pObject, AXIS_DESERIALIZE_FUNCT pDZFunct, AXIS_OBJECT_DELETE_FUNCT pDelFunct, AXIS_OBJECT_SIZE_FUNCT pSizeFunct)=0;
	virtual int setUserType(void* pObject, AXIS_DESERIALIZE_FUNCT pDZFunct, AXIS_OBJECT_DELETE_FUNCT pDelFunct)=0;
	virtual void setName(const AxisChar* sName)=0;
};

#endif // !defined(_IPARAM_H____OF_AXIS_INCLUDED_)
