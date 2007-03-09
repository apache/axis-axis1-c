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

#include <axis/AxisUserAPI.hpp>
#include "../engine/AxisEngine.h"
#include "Param.h"
#include "ArrayBean.h"
#include "BasicTypeSerializer.h"
#include "AxisUtils.h"
#include "AxisTrace.h"
#include "../soap/SoapAttachmentReference.hpp"
#include <stdlib.h>
#include <stdio.h>

AXIS_CPP_NAMESPACE_START

int AxisEngine::m_bServer;


Param::~Param ()
{
    if (m_AnySimpleType)
    {
        delete m_AnySimpleType;
        m_AnySimpleType = NULL;
    }
    
    switch (m_Type)
    {
        case XSD_ARRAY:
            if (m_Value.pArray)
                delete m_Value.pArray;
            break;
        case USER_TYPE:
            delete m_Value.pCplxObj;
            break;
        case XSD_ANY:
            // Do not delete the m_Value.pAnyObject here because it is the
            // application's storage. The AnyObject has never been cloned.
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
                return AXIS_FAIL;
                
            if (RPC_ENCODED == pSZ.getStyle ())
            {
                pSZ.serialize ("<", NULL);
                if (!m_strPrefix.empty ())
                {
                    pSZ.serialize (m_strPrefix.c_str (), ":", m_sName.c_str (),
                         " xmlns:", m_strPrefix.c_str (), "=\"",
                        m_strUri.c_str (), "\"", NULL);
                }
                else
                    pSZ.serialize (m_sName.c_str (), NULL);

                // get a prefix from Serializer
                ATprefix = pSZ.getNamespacePrefix (m_Value.pArray->m_URI.c_str ());

                if (m_Value.pArray->m_value.cta==NULL || 
                  m_Value.pArray->m_value.cta->pObject==NULL)
                {
                  // ======================================================================
                  // If null input, serialize as nil element.
                  // ======================================================================

	                pSZ.serializeAsAttribute( "xsi:nil", 0, (void*)&(xsd_boolean_true), XSD_BOOLEAN);
	                pSZ.serialize( ">", NULL);
                }
                else
                {
                  pSZ.serialize (" xmlns:enc", NULL);
                  pSZ.serialize ("=\"http://www.w3.org/2001/06/soap-encoding\" ", NULL);
                  
                  if (m_Value.pArray->m_type == USER_TYPE &&
                    !m_Value.pArray->m_URI.empty())
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
                }
                pSZ.serialize ("</", NULL);
                if (!m_strPrefix.empty ())
                    pSZ.serialize (m_strPrefix.c_str (), ":", m_sName.c_str (), NULL);
                else
                    pSZ.serialize (m_sName.c_str (), NULL);

                pSZ.removeNamespacePrefix (m_Value.pArray->m_URI.c_str ());
                pSZ.serialize (">\n", NULL);
            }
            else 
            {
                /* no wrapper element in doc/lit style. So directly call Array Serializer */
                
                if (!m_strUri.empty())
                    pSZ.setNamespace(m_strUri.c_str());

                m_Value.pArray->Serialize (pSZ); /* Only serializes the inner items */ 
                if (!m_strUri.empty())
                    pSZ.setNamespace(NULL);
            }
            break;
        
        case USER_TYPE:
            if (RPC_ENCODED == pSZ.getStyle ())
            {
                TRACE_SERIALIZE_FUNCT_ENTRY(m_Value.pCplxObj->pSZFunct, m_Value.pCplxObj->pObject, &pSZ, false);
                int stat = AXIS_FAIL;
                stat = m_Value.pCplxObj->pSZFunct (m_Value.pCplxObj->pObject, &pSZ, false);
                TRACE_SERIALIZE_FUNCT_EXIT(m_Value.pCplxObj->pSZFunct, stat);
            }
            else
            {
                pSZ.serialize ("<", m_sName.c_str (), NULL); 
                /* note : ">" is not serialized to enable the type's serializer
                 * to add attributes 
                 */
                TRACE_SERIALIZE_FUNCT_ENTRY(m_Value.pCplxObj->pSZFunct, m_Value.pCplxObj->pObject, &pSZ, false);
                int stat = AXIS_FAIL;
                stat = m_Value.pCplxObj->pSZFunct (m_Value.pCplxObj->pObject, &pSZ, false);
                TRACE_SERIALIZE_FUNCT_EXIT(m_Value.pCplxObj->pSZFunct, stat);

                pSZ.serialize ("</", m_sName.c_str (), ">\n", NULL);
            }
            break;
        case XSD_ANY:
             pSZ.serializeAnyObject(m_Value.pAnyObject);
             break;
        case ATTACHMENT:
            m_Value.pAttachmentRef->serialize(pSZ,m_sName.c_str());
            break;
        default:
            pSZ.serializeAsElement((AxisChar*) m_sName.c_str (), (IAnySimpleType*) m_AnySimpleType);
            break;
    }
    
    return AXIS_SUCCESS;
}

void Param::setValue(XSDTYPE nType, 
                     IAnySimpleType* value)
{
    m_Type = nType;
    m_AnySimpleType = value;
}

void Param::setPrefix (const AxisChar* prefix)
{
    m_strPrefix = prefix;
}

void Param::setURI (const AxisChar* uri)
{
    m_strUri = uri;
}

int Param::setUserType (void* pObject, 
                        AXIS_DESERIALIZE_FUNCT pDZFunct,
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
            return AXIS_FAIL;
    }
    
    return AXIS_FAIL;
}

// following function is called to set array of user types.
int Param::setArrayElements (void* pObject, 
                             AXIS_DESERIALIZE_FUNCT pDZFunct,
                             AXIS_OBJECT_DELETE_FUNCT pDelFunct)
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
            m_Value.pArray->m_value.cta->pObject = pObject;
            return AXIS_SUCCESS;
        }
        else                  //unexpected situation
            return AXIS_FAIL;
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
        {
            TRACE_OBJECT_DELETE_FUNCT_ENTRY(pDelFunct, pObject, 0);
            pDelFunct(pObject, 0);
            TRACE_OBJECT_DELETE_FUNCT_EXIT(pDelFunct);
        }
    }
}

void ComplexObjectHandler::init ()
{
    pObject = NULL;
    pSZFunct = NULL;
    pDelFunct = NULL;
    pDZFunct = NULL;
    m_TypeName = "";
    m_URI = "";
}

AXIS_CPP_NAMESPACE_END
