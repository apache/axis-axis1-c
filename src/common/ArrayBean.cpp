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
					TRACE_OBJECT_DELETE_FUNCT_ENTRY(m_value.cta->pDelFunct, m_value.cta->pObject, true, m_nSize);
                    m_value.cta->pDelFunct(m_value.cta->pObject, true, m_nSize);
					TRACE_OBJECT_DELETE_FUNCT_EXIT(m_value.cta->pDelFunct);
                }
                // make sure that the ComplexObjectHandler's destructor does 
                // not try to delete the objects again 
                m_value.cta->pObject = NULL;
            }
            delete m_value.cta;
			m_value.cta = NULL;
        }
    }
    else if (AxisEngine::m_bServer && m_value.sta)
    {
        if (m_nSize > 0)
        {
            for (int count = 0 ; count < m_nSize ; count++)
            {
                if ( ((void **) m_value.sta)[count] != NULL)
                {
                    switch (m_type)
                    {
                        case XSD_DURATION:
                        {
                            delete ((xsd__duration**) m_value.sta)[count];
                          break;
                        }
                        case XSD_DATETIME:
                        {
                            delete ((xsd__dateTime**) m_value.sta)[count];
                            break;
                        }
                        case XSD_TIME:
                        {
                            delete ((xsd__time**) m_value.sta)[count];
                            break;
                        }
                        case XSD_DATE:
                        {
                            delete ((xsd__date**) m_value.sta)[count];
                            break;
                        }
                        case XSD_GYEARMONTH:
                        {
                            delete ((xsd__gYearMonth**) m_value.sta)[count];
                            break;
                        }
                        case XSD_GYEAR:
                        {
                            delete ((xsd__gYear**) m_value.sta)[count];
                            break;
                        }
                        case XSD_GMONTHDAY:
                        {
                            delete ((xsd__gMonthDay**) m_value.sta)[count];
                            break;
                        }
                        case XSD_GDAY:
                        {
                            delete ((xsd__gDay**) m_value.sta)[count];
                            break;
                        }
                        case XSD_GMONTH:
                        {
                            delete ((xsd__gMonth**) m_value.sta)[count];
                            break;
                        }
                        case XSD_STRING:
                        {
                            delete []((xsd__string*) m_value.sta)[count];
                            break;
                        }
                        case XSD_NORMALIZEDSTRING:
                        {
                            delete []((xsd__normalizedString*) m_value.sta)[count];
                            break;
                        }
                        case XSD_TOKEN:
                        {
                            delete []((xsd__token*) m_value.sta)[count];
                            break;
                        }
                        case XSD_LANGUAGE:
                        {
                            delete []((xsd__language*) m_value.sta)[count];
                            break;
                        }
                        case XSD_NAME:
                        {
                            delete []((xsd__Name*) m_value.sta)[count];
                            break;
                        }
                        case XSD_NCNAME:
                        {
                            delete []((xsd__NCName*) m_value.sta)[count];
                            break;
                        }
                        case XSD_ID:
                        {
                            delete []((xsd__ID*) m_value.sta)[count];
                            break;
                        }
                        case XSD_IDREF:
                        {
                            delete []((xsd__IDREF*) m_value.sta)[count];
                            break;
                        }
                        case XSD_IDREFS:
                        {
                            delete []((xsd__IDREFS*) m_value.sta)[count];
                            break;
                        }
                        case XSD_ENTITY:
                        {
                            delete []((xsd__ENTITY*) m_value.sta)[count];
                            break;
                        }
                        case XSD_ENTITIES:
                        {
                            delete []((xsd__ENTITIES*) m_value.sta)[count];
                            break;
                        }
                        case XSD_NMTOKEN:
                        {
                            delete []((xsd__NMTOKEN*) m_value.sta)[count];
                            break;
                        }
                        case XSD_NMTOKENS:
                        {
                            delete []((xsd__NMTOKENS*) m_value.sta)[count];
                            break;
                        }
                        case XSD_BOOLEAN:
                        {
                            delete ((xsd__boolean**) m_value.sta)[count];
                            break;
                        }
                        case XSD_BASE64BINARY:
                        {
                            delete ((xsd__base64Binary**) m_value.sta)[count];
                            break;
                        }
                        case XSD_HEXBINARY:
                        {
                            delete ((xsd__hexBinary**) m_value.sta)[count];
                            break;
                        }
                        case XSD_FLOAT:
                        {
                            delete ((xsd__float**) m_value.sta)[count];
                            break;
                        }
                        case XSD_DECIMAL:
                        {
                            delete ((xsd__decimal**) m_value.sta)[count];
                            break;
                        }
                        case XSD_INTEGER:
                        {
                            delete ((xsd__integer**) m_value.sta)[count];
                            break;
                        }
                        case XSD_NONPOSITIVEINTEGER:
                        {
                            delete ((xsd__nonPositiveInteger**) m_value.sta)[count];
                            break;
                        }
                        case XSD_NEGATIVEINTEGER:
                        {
                            delete ((xsd__negativeInteger**) m_value.sta)[count];
                            break;
                        }
                        case XSD_LONG:
                        {
                            delete ((xsd__long**) m_value.sta)[count];
                            break;
                        }
                        case XSD_INT:
                        {
                            delete ((xsd__int**) m_value.sta)[count];
                            break;
                        }
                        case XSD_SHORT:
                        {
                            delete ((xsd__short**) m_value.sta)[count];
                            break;
                        }
                        case XSD_BYTE:
                        {
                            delete ((xsd__byte**) m_value.sta)[count];
                            break;
                        }
                        case XSD_NONNEGATIVEINTEGER:
                        {
                            delete ((xsd__nonNegativeInteger**) m_value.sta)[count];
                            break;
                        }
                        case XSD_UNSIGNEDLONG:
                        {
                            delete ((xsd__unsignedLong**) m_value.sta)[count];
                            break;
                        }
                        case XSD_UNSIGNEDINT:
                        {
                            delete ((xsd__unsignedInt**) m_value.sta)[count];
                            break;
                        }
                        case XSD_UNSIGNEDSHORT:
                        {
                            delete ((xsd__unsignedShort**) m_value.sta)[count];
                            break;
                        }
                        case XSD_UNSIGNEDBYTE:
                        {
                            delete ((xsd__unsignedByte**) m_value.sta)[count];
                            break;
                        }
                        case XSD_POSITIVEINTEGER:
                        {
                            delete ((xsd__positiveInteger**) m_value.sta)[count];
                            break;
                        }
                        case XSD_DOUBLE:
                        {
                            delete ((xsd__double**) m_value.sta)[count];
                            break;
                        }
                        case XSD_ANYURI:
                        {
                            delete []((xsd__anyURI*) m_value.sta)[count];
                            break;
                        }
                        case XSD_QNAME:
                        {
                            delete []((xsd__QName*) m_value.sta)[count];
                            break;
                        }
                        case XSD_NOTATION:
                        {
                            delete []((xsd__NOTATION*) m_value.sta)[count];
                            break;
                        }
                        case XSD_ARRAY:
                        {
                            delete ((Axis_Array**) m_value.sta)[count];
                            break;
                        }
                        default:
                            break;
                    }
                }
            }
            m_nSize = 0;
        }
        delete [] m_value.sta;
        m_value.sta = NULL;
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

		TRACE_OBJECT_SIZE_FUNCT_ENTRY(m_value.cta->pSizeFunct);
        int itemsize = m_value.cta->pSizeFunct();
		TRACE_OBJECT_SIZE_FUNCT_EXIT(m_value.cta->pSizeFunct, itemsize);

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
