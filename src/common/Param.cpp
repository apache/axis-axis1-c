/* -*- C++ -*- */
/*
 *   Copyright 2003-2004 The Apache Software Foundation.
// (c) Copyright IBM Corp. 2004, 2005 All Rights Reserved
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
 *
 * @author Susantha Kumara (skumara@virtusa.com)
 *
 */

#include "../engine/AxisEngine.h"
#include "Param.h"
#include "ArrayBean.h"
#include "BasicTypeSerializer.h"
#include <stdlib.h>
#include <stdio.h>
#include "AxisUtils.h"
#include <axis/AxisUserAPI.hpp>

AXIS_CPP_NAMESPACE_START

int AxisEngine::m_bServer;


Param::~Param ()
{
    int i;
    XML_String pStr = 0;
    AnyType* pAny = 0;
    switch (m_Type)
    {
        case XSD_ARRAY:
            if (m_Value.pArray)
                delete m_Value.pArray;
            break;
        case USER_TYPE:
            delete m_Value.pCplxObj;
            break;
        case XSD_STRING:
        case XSD_ANYURI:
        case XSD_QNAME:
        case XSD_NOTATION:
            if (AxisEngine::m_bServer)
            {
                delete [] const_cast<char*>(m_Value.pStrValue);
            }
            break;
        /*case XSD_BASE64BINARY:
            if (AxisEngine::m_bServer)
            {
                delete [] m_Value.b64bValue->__ptr;
            }
            break;
        case XSD_HEXBINARY:
            if (AxisEngine::m_bServer)
            {
                delete [] m_Value.hbValue->__ptr;
            }
            break;
            */
        case XSD_ANY:
            pAny = (AnyType*)m_Value.pAnyObject;
            for (i=0; i<pAny->_size; i++)
            {
                pStr = pAny->_array[i];
                if (pStr) delete [] pStr;
            }
            delete [] pAny;
            break;

        case XSD_INT:
        case XSD_BOOLEAN:
            delete m_Value.nValue;
            break; 

        case XSD_UNSIGNEDINT:
            delete m_Value.unValue;
            break;

        case XSD_SHORT:
            delete m_Value.sValue;
            break; 

        case XSD_UNSIGNEDSHORT:
            delete m_Value.usValue;
            break;         

        case XSD_BYTE:
            delete m_Value.cValue;
            break; 

        case XSD_UNSIGNEDBYTE:
            delete m_Value.ucValue;
            break;

        case XSD_LONG:
            delete m_Value.llValue;
            break;

        case XSD_INTEGER:
            delete m_Value.llValue;
            break;        

        case XSD_DURATION:
            delete m_Value.lDuration;
            break;        

        case XSD_UNSIGNEDLONG:
            delete m_Value.ulValue;
            break;

        case XSD_FLOAT:
            delete m_Value.fValue;
            break;

        case XSD_DOUBLE:
        case XSD_DECIMAL:
            delete m_Value.dValue;
            break;              

        case XSD_HEXBINARY:
            //delete [] m_Value.hbValue->__ptr;
            //delete m_Value.hbValue;
            break;

        case XSD_BASE64BINARY:
            //delete [] m_Value.b64bValue->__ptr;
            //delete m_Value.b64bValue;
            break;

        case XSD_DATETIME:
        case XSD_DATE:
        case XSD_TIME:
            delete m_Value.tValue;
            break;

        default:;
    }
}


int Param::serialize (SoapSerializer &pSZ)
{
    AxisString ATprefix;
    switch (m_Type)
    {
        case XSD_ARRAY:
            /* pSZ.serialize("<abc:ArrayOfPhoneNumbers 
	     * xmlns:abc="http://example.org/2001/06/numbers"
	     * xmlns:enc="http://www.w3.org/2001/06/soap-encoding" 
	     * enc:arrayType="abc:phoneNumberType[2]" >";
	     */
	    if (!m_Value.pArray)
                return AXIS_FAIL; // error condition
            if (RPC_ENCODED == pSZ.getStyle ())
            {
                pSZ.serialize ("<", NULL);
                if (!m_strPrefix.empty ())
                {
                    pSZ.serialize (m_strPrefix.c_str (), ":", m_sName.c_str (),
                        "Array", " xmlns:", m_strPrefix.c_str (), "=\"",
                        m_strUri.c_str (), "\"", NULL);
                }
                else
                {
                    pSZ.serialize (m_sName.c_str (), "Array", NULL);
                }
                // get a prefix from Serializer
                ATprefix =
                    pSZ.getNamespacePrefix (m_Value.pArray->m_URI.c_str ());

                pSZ.serialize (" xmlns:enc", NULL);
                pSZ.serialize
                    ("=\"http://www.w3.org/2001/06/soap-encoding\" ", NULL);
                if (m_Value.pArray->m_type == USER_TYPE)
                {
                    pSZ.serialize ("xmlns:", ATprefix.c_str (), "=\"",
                        m_Value.pArray->m_URI.c_str (), "\" ", NULL);
                }
                pSZ.serialize ("enc:arrayType=\"", NULL);
                if (m_Value.pArray->m_type == USER_TYPE)
                {
                    pSZ.serialize (ATprefix.c_str (), ":",
                        m_Value.pArray->m_TypeName.c_str (), NULL);
                }
                else //basic type array
                {
                    pSZ.serialize ("xsd:", BasicTypeSerializer::
                        basicTypeStr (m_Value.pArray->m_type), NULL);
                }
                {
                    char Buf[10]; //maximum array dimension is 99999999
                    sprintf (Buf, "[%d]", m_Value.pArray->m_nSize);
                    pSZ.serialize (Buf, NULL);
                }

                pSZ.serialize ("\">\n", NULL);
                m_Value.pArray->Serialize (pSZ); //Only serializes the inner items
                pSZ.serialize ("</", NULL);
                if (!m_strPrefix.empty ())
                {
                    pSZ.serialize (m_strPrefix.c_str (), ":", m_sName.c_str (),
                        "Array", NULL);
                }
                else
                {
                    pSZ.serialize (m_sName.c_str (), "Array", NULL);
                }
                pSZ.removeNamespacePrefix (m_Value.pArray->m_URI.c_str ());
                pSZ.serialize (">\n", NULL);
            }
            else /* no wrapper element in doc/lit style. 
		  * So directly call Array Serializer 
		  */
            {
				if (!m_strUri.empty())
					pSZ.setNamespace(m_strUri.c_str());

                m_Value.pArray->Serialize (pSZ); /* Only serializes the inner 
						  * items
						  */ 
				if (!m_strUri.empty())
					pSZ.setNamespace(NULL);

            }
            break;
        
	case USER_TYPE:
            if (RPC_ENCODED == pSZ.getStyle ())
            {
                m_Value.pCplxObj->pSZFunct (m_Value.pCplxObj->pObject, &pSZ, false);
            }
            else
            {
                pSZ.serialize ("<", m_sName.c_str (), NULL); 
                /* note : ">" is not serialized to enable the type's serializer
                 * to add attributes 
                 */
                m_Value.pCplxObj->pSZFunct (m_Value.pCplxObj->pObject, &pSZ, false);
                pSZ.serialize ("</", m_sName.c_str (), ">\n", NULL);
            }
            break;
      case XSD_ANY:
             pSZ.serializeAnyObject(m_Value.pAnyObject);
             break;
	case XSD_INT:
      case XSD_BOOLEAN:
            pSZ.serializeAsElement(m_sName.c_str (), m_Value.nValue, m_Type);
            break;
	case XSD_UNSIGNEDINT:
            pSZ.serializeAsElement(m_sName.c_str (), m_Value.unValue, m_Type);
            break;
	case XSD_SHORT:
            pSZ.serializeAsElement(m_sName.c_str (), m_Value.sValue, m_Type);
            break;
	case XSD_UNSIGNEDSHORT:
            pSZ.serializeAsElement(m_sName.c_str (), m_Value.usValue, m_Type);
            break;
	case XSD_BYTE:
            pSZ.serializeAsElement(m_sName.c_str (), m_Value.cValue, m_Type);
            break;
	case XSD_UNSIGNEDBYTE:
            pSZ.serializeAsElement(m_sName.c_str (), m_Value.ucValue, m_Type);
            break;
	case XSD_LONG:
            pSZ.serializeAsElement(m_sName.c_str (), m_Value.llValue, m_Type);
            break;
	case XSD_INTEGER:
            pSZ.serializeAsElement(m_sName.c_str (), m_Value.llValue, m_Type);
            break;
	case XSD_UNSIGNEDLONG:
            pSZ.serializeAsElement(m_sName.c_str (), m_Value.ulValue, m_Type);
            break;
	case XSD_FLOAT:
            pSZ.serializeAsElement(m_sName.c_str (), m_Value.fValue, m_Type);
            break;
	case XSD_DOUBLE:
	case XSD_DECIMAL:
            pSZ.serializeAsElement(m_sName.c_str (), m_Value.dValue, m_Type);
            break;
      case XSD_STRING:
      case XSD_ANYURI:
      case XSD_QNAME:
      case XSD_NOTATION:
            pSZ.serializeAsElement(m_sName.c_str (), (void *) m_Value.pStrValue, m_Type);
            break;
	case XSD_HEXBINARY:
            pSZ.serializeAsElement(m_sName.c_str (), m_Value.hbValue, m_Type);
            break;
	case XSD_BASE64BINARY:
            pSZ.serializeAsElement(m_sName.c_str (), m_Value.b64bValue, m_Type);
            break;
	case XSD_DURATION:
            pSZ.serializeAsElement(m_sName.c_str (), m_Value.lDuration, m_Type);
            break;
      case XSD_DATETIME:
      case XSD_DATE:
      case XSD_TIME:
            pSZ.serializeAsElement(m_sName.c_str (), m_Value.tValue, m_Type);
            break;
      default:
            return AXIS_FAIL; //this is an unexpected situation
    }
    return AXIS_SUCCESS;
}

int Param::setValue (XSDTYPE nType, ParamValue Value)
{
    m_Type = nType;
    switch (m_Type)
    {
        case XSD_INT:
        case XSD_BOOLEAN:
            m_Value.nValue = Value.nValue;
            break;
        case XSD_UNSIGNEDINT:
            m_Value.unValue = Value.unValue;
            break;
        case XSD_SHORT:
            m_Value.sValue = Value.sValue;
            break;
        case XSD_UNSIGNEDSHORT:
            m_Value.usValue = Value.usValue;
            break;
        case XSD_BYTE:
            m_Value.cValue = Value.cValue;
            break;
        case XSD_UNSIGNEDBYTE:
            m_Value.ucValue = Value.ucValue;
            break;
        case XSD_LONG:
            m_Value.llValue = Value.llValue;
            break;
        case XSD_INTEGER:
            m_Value.llValue = Value.llValue;
            break;
        case XSD_UNSIGNEDLONG:
            m_Value.ulValue = Value.ulValue;
            break;
        case XSD_FLOAT:
            m_Value.fValue = Value.fValue;
            break;
        case XSD_DOUBLE:
        case XSD_DECIMAL:
            m_Value.dValue = Value.dValue;
            break;
        case XSD_STRING:
        case XSD_ANYURI:
        case XSD_QNAME:
        case XSD_NOTATION:
            m_Value.pStrValue = Value.pStrValue;
            break;
        case XSD_HEXBINARY:
            m_Value.hbValue = Value.hbValue;
            break;
        case XSD_BASE64BINARY:
            m_Value.b64bValue = Value.b64bValue;
            break;
        case XSD_DURATION:
            m_Value.lDuration = Value.lDuration;
        case XSD_DATETIME:
        case XSD_DATE:
        case XSD_TIME:
            m_Value.tValue = Value.tValue;
            /* m_uAxisTime.setValue(nType, m_Value);
             * Continue this for all basic types
	     */ 
        case XSD_ARRAY:
            m_Value.pArray = Value.pArray;
            break;
        case USER_TYPE:
            m_Value.pCplxObj = Value.pCplxObj;
            break;
        default:
            return AXIS_FAIL; //this is an unexpected situation
    }
    return AXIS_SUCCESS;
}

void Param::setPrefix (const AxisChar* prefix)
{
    m_strPrefix = prefix;
}

void Param::setURI (const AxisChar* uri)
{
    m_strUri = uri;
}

int Param::setUserType (void* pObject, AXIS_DESERIALIZE_FUNCT pDZFunct,
    AXIS_OBJECT_DELETE_FUNCT pDelFunct)
{
    if (m_Type != USER_TYPE)
        return AXIS_FAIL;
    m_Value.pCplxObj = new ComplexObjectHandler;
    m_Value.pCplxObj->pObject = pObject;
    m_Value.pCplxObj->pDZFunct = pDZFunct;
    m_Value.pCplxObj->pDelFunct = pDelFunct;
    return AXIS_SUCCESS;
}

int Param::setArrayElements (void* pElements)
{
    if (m_Type != XSD_ARRAY)
        return AXIS_FAIL;
    if (m_Value.pArray)
    {
        if (m_Value.pArray->m_type != USER_TYPE)
        {
            m_Value.pArray->m_value.sta = pElements;
            return AXIS_SUCCESS;
        }
        else // unexpected situation
        {
            return AXIS_FAIL;
        }
    }
    return AXIS_FAIL;
}

// following function is called to set array of user types.
int Param::setArrayElements (void* pObject, AXIS_DESERIALIZE_FUNCT pDZFunct,
    AXIS_OBJECT_DELETE_FUNCT pDelFunct, AXIS_OBJECT_SIZE_FUNCT pSizeFunct)
{
    if (m_Type != XSD_ARRAY)
        return AXIS_FAIL;
    if (m_Value.pArray)
    {
        if (m_Value.pArray->m_type == USER_TYPE)
        {
            m_Value.pArray->m_value.cta = new ComplexObjectHandler;
            m_Value.pArray->m_value.cta->pDZFunct = pDZFunct;
            m_Value.pArray->m_value.cta->pDelFunct = pDelFunct;
            m_Value.pArray->m_value.cta->pSizeFunct = pSizeFunct;
            m_Value.pArray->m_value.cta->pObject = pObject;
            return AXIS_SUCCESS;
        }
        else                  //unexpected situation
        {
            return AXIS_FAIL;
        }
    }
    return AXIS_FAIL;
}

void Param::setName (const AxisChar* sName)
{
    m_sName = sName;
}

// ComplexObjectHandler functions
ComplexObjectHandler::ComplexObjectHandler ()
{
    init ();
}

ComplexObjectHandler::~ComplexObjectHandler ()
{
    /* At client side we do not delete either output or return objects */
    if (AxisEngine::m_bServer)
    {
        if (pObject && pDelFunct)
            pDelFunct (pObject, false, 0);
    }
}

void ComplexObjectHandler::init ()
{
    pObject = NULL;
    pSZFunct = NULL;
    pDelFunct = NULL;
    pDZFunct = NULL;
    pSizeFunct = NULL;
    m_TypeName = "";
    m_URI = "";
}

AXIS_CPP_NAMESPACE_END
