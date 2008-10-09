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
 *
 * @author Susantha Kumara (skumara@virtusa.com)
 *
 */

#include "axis/Axis.hpp"

#include "Param.h"
#include "ArrayBean.h"
#include "BasicTypeSerializer.h"
#include "../engine/AxisEngine.h"
#include "AxisTrace.h"

AXIS_CPP_NAMESPACE_START

ArrayBean::ArrayBean()
{
    m_type = XSD_UNKNOWN;
    m_ItemName = "";
    m_value.sta = NULL;
}

ArrayBean::~ArrayBean()
{
    if (USER_TYPE == m_type)
    {
        if (m_value.cta)
        {
            if (m_value.cta->pObject)
            {
                if (AxisEngine::m_bServer)
                {
					TRACE_OBJECT_DELETE_FUNCT_ENTRY(m_value.cta->pDelFunct, m_value.cta->pObject,  m_nSize);
                    m_value.cta->pDelFunct(m_value.cta->pObject, m_nSize);
					TRACE_OBJECT_DELETE_FUNCT_EXIT(m_value.cta->pDelFunct);
                }
                // make sure that the ComplexObjectHandler's destructor does 
                // not try to delete the objects again 
                m_value.cta->pObject = NULL;
            }
            delete m_value.cta;
        }
    }
    else if (AxisEngine::m_bServer && m_value.sta)
    {
    	// TODO - Why do we only do this for server? I think we need to do for client also.
        if (m_nSize > 0)
        {
            for (int count = 0 ; count < m_nSize ; count++)
            	if (((void **) m_value.sta)[count] != NULL)
            		Axis::AxisDelete(((void **) m_value.sta)[count], m_type);
        }
        delete [] m_value.sta;
    }
}

int ArrayBean::GetArraySize()
{	
    return m_nSize;
}

int ArrayBean::Serialize(SoapSerializer& pSZ)
{	
    if (USER_TYPE == m_type)
    {
        void* pItem;
        AXIS_BINDING_STYLE nStyle = pSZ.getStyle();

        void** ptrval = (void**) m_value.cta->pObject;
        if (DOC_LITERAL == nStyle) 
        {
            // Serialize functions for doc/lit services do not know the instance 
            // name and will not serialize outer element for the type 
      
            for (int x=0; x<m_nSize; x++)
            {
                pItem = ptrval[x];

				// try to find the prefix - array prefix overrides the
				// serializer prefix
            	const AxisChar* pNamespace = pSZ.getNamespace();
				const AxisChar* pPrefix = NULL;
                bool blnIsNewPrefix = false;
				if (NULL != pNamespace)
					if (strlen(pNamespace) > 0)
            	        pPrefix = pSZ.getNamespacePrefix(pNamespace, blnIsNewPrefix);

            	if (pPrefix != NULL)
                {
	                pSZ.serialize("<", pPrefix, ":", m_ItemName.c_str(), NULL); 
                    if (blnIsNewPrefix)
                    {
                        pSZ.serialize(" xmlns:", pPrefix, "=\"", pNamespace, "\"", NULL);
                    }
                }
	            else
	                pSZ.serialize("<", m_ItemName.c_str(), NULL); 
				
                // note : ">" is not serialized to enable the type's serializer
                // to add attributes 

				TRACE_SERIALIZE_FUNCT_ENTRY(m_value.cta->pSZFunct, pItem, &pSZ, true);
                int stat = AXIS_FAIL;
                stat = m_value.cta->pSZFunct(pItem, &pSZ, true); 
				TRACE_SERIALIZE_FUNCT_EXIT(m_value.cta->pSZFunct, stat);

                // no matter true or false is passed
            	if (pPrefix != NULL)
                	pSZ.serialize("</", pPrefix, ":", m_ItemName.c_str(), ">", NULL);
	            else
                	pSZ.serialize("</", m_ItemName.c_str(), ">", NULL);
                  
                if (blnIsNewPrefix)
                {
                    pSZ.removeNamespacePrefix(pNamespace);
                }
            }
        }
        else 
        {          
            // Serialize functions for RPC-encoded services will serialize 
            // outer element for the type. Also the type information is not 
            // added to the outer element as this object is part of an array 
            // (serialize function knows that when the 3rd parameter is 'true'. 
            for( int x = 0; x < m_nSize; x++)
            {
                pItem = ptrval[x];

				TRACE_SERIALIZE_FUNCT_ENTRY(m_value.cta->pSZFunct, pItem, &pSZ, true);
                int stat = AXIS_FAIL;
                stat = m_value.cta->pSZFunct(pItem, &pSZ, true); 
				TRACE_SERIALIZE_FUNCT_EXIT(m_value.cta->pSZFunct, stat);
            }
        }
    }
    else
    {
        AXIS_BINDING_STYLE nStyle = pSZ.getStyle();
        
        // this is to prevent serializing type information for basic array elements 
 
	   	const AxisChar* pNamespace = pSZ.getNamespace();
       	        
       	if (RPC_ENCODED == nStyle) pSZ.setStyle(RPC_LITERAL); 

        void ** p = (void **) m_value.sta;
        for (int ix = 0 ; ix < m_nSize ; ix++ )
        {
            pSZ.serializeAsElement(m_ItemName.c_str(), pNamespace, p[ix], m_type);
        }

    	// restore Serializer's style after array serialization is finished
    	if (RPC_ENCODED == nStyle) pSZ.setStyle(RPC_ENCODED);
    }
    return AXIS_SUCCESS;
}

void ArrayBean::SetDimension(int nDim)
{
    m_nSize = nDim;
}

void ArrayBean::SetItemName(const AxisChar* sName)
{
    m_ItemName = sName;
}

void ArrayBean::SetTypeName(const AxisChar* sName)
{
    m_TypeName = sName;
}

void ArrayBean::SetUri(const AxisChar* sURI)
{
    if (sURI)
        m_URI = sURI;
}

/**
 * Used to remove the pointer to the object array. Mostly to avoid deletion
 * by the destructor.
 */

void ArrayBean::RemoveArrayPointer()
{
    if (USER_TYPE == m_type)
    {
        if (m_value.cta)
        {
            m_value.cta->pObject = NULL;	
        }
    }
    else
    {
        m_value.sta = NULL;
    }
}

AXIS_CPP_NAMESPACE_END
