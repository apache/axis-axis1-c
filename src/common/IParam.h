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
 * 4. The names "SOAP" and "Apache Software Foundation" must
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
 *
 *
 *
 *
 * @author Susantha Kumara (skumara@virtusa.com)
 *
 */
// IParam.h: interface for the IParam class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IPARAM_H__25C278BB_5875_49E6_A3EC_B6AD3E543D69__INCLUDED_)
#define AFX_IPARAM_H__25C278BB_5875_49E6_A3EC_B6AD3E543D69__INCLUDED_

#include "TypeMapping.h"
#include "IWrapperSoapDeSerializer.h"
#include "IWrapperSoapSerializer.h"

#include "TypeMapping.h"
#include "time.h"

#include <string>
using namespace std;

typedef int (* AXIS_DESERIALIZE_FUNCT)(void*, IWrapperSoapDeSerializer*);
//bArray is true if void* is a pointer to an array. Then nSize is the size of that array.
typedef void (* AXIS_OBJECT_DELETE_FUNCT)(void*, bool bArray=false, int nSize=0);
//bArray indicates that the object in void* is an element of an array (note that void* is not itself an array).
typedef int (* AXIS_SERIALIZE_FUNCT)(void*, IWrapperSoapSerializer&, bool bArray=false);
typedef int (* AXIS_OBJECT_SIZE_FUNCT)(void);

class ComplexObjectHandler
{
public:
	void* pObject;
	AXIS_SERIALIZE_FUNCT pSZFunct;
	AXIS_OBJECT_DELETE_FUNCT pDelFunct;
	AXIS_DESERIALIZE_FUNCT pDZFunct;
	AXIS_OBJECT_SIZE_FUNCT pSizeFunct;
	AxisString m_TypeName;
	AxisString m_URI;
public:
	ComplexObjectHandler();
	~ComplexObjectHandler();
	void Init();
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
    long lDuration;/* duration in seconds*/
    

	//all basic types should come here
	class ArrayBean* pArray; //this is used to hold arrays
	class IArrayBean* pIArray; //used by wrapper classes

//	class AccessBean* pBean; //this is used to hold user types
//	class IAccessBean* pIBean; //used by wrapper classes
	ComplexObjectHandler* pCplxObj;

	//following is used by the wrapper class to set return value in case of strings	
	const AxisChar* pStrValue; 
} uParamValue;

class IParam  
{
public:
	IParam(){};
	virtual ~IParam(){};
 
    virtual int GetInt() = 0;
    virtual unsigned int GetUnsignedInt() = 0;
    virtual short GetShort() = 0;
    virtual unsigned short GetUnsignedShort() = 0;
    virtual char GetByte() = 0;
    virtual unsigned char GetUnsignedByte() = 0;
    virtual long GetLong() = 0;
    virtual long GetInteger() = 0;
    virtual unsigned long GetUnsignedLong() = 0;
	virtual float GetFloat() = 0;
    virtual double GetDouble() = 0;
    virtual double GetDecimal() = 0;
	virtual const AxisString& GetString() = 0;
    virtual const AxisString& GetAnyURI() = 0;
    virtual const AxisString& GetQName() = 0;
	virtual const AxisString& GetHexString() = 0;
	virtual const AxisString& GetBase64String() = 0;
	virtual const AxisString& GetTypeName() = 0;
    /*return a tm struct which contain year-month-date-hour-
      minute-second*/
    virtual struct tm GetDateTime() = 0;
    virtual struct tm GetDate() = 0;
    virtual struct tm GetTime() = 0;
    /*return a tm struct which contain years-months-dates-hours-
      minutes-seconds which represents a duration*/
    virtual long GetDuration() = 0;

    virtual int GetArraySize()= 0;
	virtual int SetArrayElements(void* pElements)= 0;
	//virtual int SetUserType(IAccessBean* pObject)= 0;
	//virtual void SetName(const AxisChar* sName)= 0;
	/*virtual int GetInt()=0;
	virtual float GetFloat()=0;
	virtual const AxisString& GetString()=0;
	virtual const AxisString& GetHexString()=0;
	virtual const AxisString& GetBase64String()=0;
	virtual int GetArraySize()=0;
	virtual int SetArrayElements(void* pElements)=0;*/

	virtual int SetArrayElements(void* pObject, AXIS_DESERIALIZE_FUNCT pDZFunct, AXIS_OBJECT_DELETE_FUNCT pDelFunct, AXIS_OBJECT_SIZE_FUNCT pSizeFunct)=0;
//	virtual int SetUserType(IAccessBean* pObject)=0;
	virtual int SetUserType(void* pObject, AXIS_DESERIALIZE_FUNCT pDZFunct, AXIS_OBJECT_DELETE_FUNCT pDelFunct)=0;
	virtual void SetName(const AxisChar* sName)=0;

};

#endif // !defined(AFX_IPARAM_H__25C278BB_5875_49E6_A3EC_B6AD3E543D69__INCLUDED_)
