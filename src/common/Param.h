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

#ifdef WIN32
#pragma warning (disable : 4786)
#endif

#if !defined(_PARAM_H____OF_AXIS_INCLUDED_)
#define _PARAM_H____OF_AXIS_INCLUDED_

#include <axis/server/IParam.hpp>

AXIS_CPP_NAMESPACE_START

class ArrayBean;

class ParamValue
{
public:
    int nValue;
    unsigned int unValue;
    short sValue;
    unsigned short usValue;
    long lValue;
    unsigned ulValue;
//FJP v Added
#ifdef WIN32
    __int64 llValue;
#else
    long long llValue;
#endif
//FJP ^ Added
    char cValue;
    unsigned char ucValue;
    float fValue;
    double dValue;
    struct tm tValue;/* this will hold the c type tm struct*/
    xsd__hexBinary hbValue;
    xsd__base64Binary b64bValue;
    long lDuration;/* duration in seconds*/
    union {
        class ArrayBean* pArray; /* this is used to hold arrays */
        class IArrayBean* pIArray; /* used by wrapper classes */
    };
    ComplexObjectHandler* pCplxObj;
    const AxisChar* pStrValue;
    AnyType* pAnyObject; /* used to hold AnyType struct for xsd:any */
};

/*
 *  @class Param
 *  @brief interface for the Param class.
 *
 *
 *  @author Susantha Kumara (skumara@virtusa.com)
 */
class Param : public IParam
{
    friend class SoapSerializer;
    friend class SoapFault;
public:
    Param(){ m_Type = USER_TYPE;}; 
    /* if there is no attribute that says the type */
    virtual ~Param();

private:
    ParamValue m_Value;
    AxisString m_sName; /* Name of the parameter */
    XSDTYPE m_Type; /* Type of the parameter */
    AxisString m_strPrefix; /* needed in serialization only */
    AxisString m_strUri; /* needed in serialization only */

public: 
    int setValue(XSDTYPE nType, ParamValue Value);
    int serialize(SoapSerializer& pSZ);
    void setPrefix(const AxisChar* prefix);
    void setUri(const AxisChar* uri);
    int setArrayElements(void* pElements);
    int setArrayElements(void* pObject, AXIS_DESERIALIZE_FUNCT pDZFunct, 
        AXIS_OBJECT_DELETE_FUNCT pDelFunct, AXIS_OBJECT_SIZE_FUNCT pSizeFunct);
    int setUserType(void* pObject, AXIS_DESERIALIZE_FUNCT pDZFunct, 
        AXIS_OBJECT_DELETE_FUNCT pDelFunct);
    void setName(const AxisChar* sName);
};

AXIS_CPP_NAMESPACE_END

#endif 


