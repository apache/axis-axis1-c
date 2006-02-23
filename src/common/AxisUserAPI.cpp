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
 * @author Mark Whitlock
 */

#include <axis/AxisUserAPI.hpp>
#include <axis/AxisUserAPIArrays.hpp>

AXIS_CPP_NAMESPACE_START 

/*
 * xsd_base64Binary, xsd_hexBinary and AnyType probably should own the 
 * storage that they address, in which case their destructors should free it
 * and their copy constructors should new storage. Also the = method would
 * need to be overloaded as well. Also their constructors would need to new
 * storage. The users of these classes would have to be checked to make sure
 * they don't new/delete the storage owned by these classes. Also methods
 * in SoapDeSerializer (for example) copy these classes around which would 
 * invoke these constructors excessively. So instead those methods should 
 * pass these classes around by reference instead. xsd_hexBinary and 
 * xsd__base64Binary are very similar and could share an implementation
 * which they both inherit from. Maybe these classes could have private data
 * and overload the [] operator and size() methods.
 */
xsd__base64Binary::xsd__base64Binary()
{ 
  __ptr = NULL;
  __size = 0;
}

xsd__base64Binary::xsd__base64Binary(const xsd__base64Binary & original)
{
	__ptr = NULL;
	__size = 0;
	*this = original;
}

void xsd__base64Binary::set(xsd__unsignedByte * data, int size)
{
	if (__ptr != NULL)
	{
		delete [] __ptr;
	}
	if (size > 0)
	{
		__ptr = new xsd__unsignedByte[size + 1];
		memcpy(__ptr, data, size * sizeof(xsd__unsignedByte));
		__ptr[size] = '\0';
	}
	else
	{
		__ptr = NULL;
	}
	__size = size;
}

xsd__int xsd__base64Binary::getSize() const
{
	return __size;
}

xsd__unsignedByte * xsd__base64Binary::get(xsd__int & size) const
{
	size = __size;
    return __ptr;
}

xsd__base64Binary & xsd__base64Binary::operator=(const xsd__base64Binary & original)
{
	this->set(original.__ptr, original.__size);
    return *this;
}

xsd__base64Binary::~xsd__base64Binary()
{
    if (__ptr != NULL)
    {
        delete [] __ptr;
    }
    __ptr = NULL;
    __size = 0;
}

xsd__hexBinary::xsd__hexBinary()
{ 
    __ptr = NULL;
    __size = 0;
}

xsd__hexBinary::xsd__hexBinary(const xsd__hexBinary & original)
{
    __ptr = NULL;
    __size = 0;
    *this = original;
}

void xsd__hexBinary::set(xsd__unsignedByte * data, int size)
{
    if (__ptr != NULL)
    {
        delete [] __ptr;
    }
    if (size > 0)
    {
        __ptr = new xsd__unsignedByte[size + 1];
        memcpy(__ptr, data, size * sizeof(xsd__unsignedByte));
		__ptr[size] = '\0';
    }
    else
    {
        __ptr = NULL;
    }
    __size = size;
}

xsd__int xsd__hexBinary::getSize() const
{
    return __size;
}

xsd__unsignedByte * xsd__hexBinary::get(xsd__int & size) const
{
    size = __size;
    return __ptr;
}

xsd__hexBinary & xsd__hexBinary::operator=(const xsd__hexBinary & original)
{
    this->set(original.__ptr, original.__size);
    return *this;
}

xsd__hexBinary::~xsd__hexBinary()
{
    if (__ptr != NULL)
    {
        delete [] __ptr;
    }
    __ptr = NULL;
    __size = 0;
}

AnyType::AnyType() { 
  _array = 0;
  _size = 0;
}

AnyType::~AnyType() { 
}

Axis_Array::Axis_Array()
{
    m_Array = NULL;
    m_Size = 0;
    m_Type = XSD_UNKNOWN;
    m_belongsToAxisEngine = true;
}

Axis_Array::Axis_Array(const Axis_Array & original)
{
    m_Array = NULL;
    m_Size = 0;
    m_Type = XSD_UNKNOWN;
    m_belongsToAxisEngine = true;
    clone(original);
}

void Axis_Array::clone(const Axis_Array & original)
{
    set(original.m_Array, original.m_Size, original.m_Type);
}

Axis_Array * Axis_Array::clone() const
{
    return new Axis_Array(*this);
}
 
void Axis_Array::set(void** array, int size, XSDTYPE type)
{
    clear();
    m_Size = size;
    m_Type = type;
    m_belongsToAxisEngine = true;
    
    if (size == 0)
    {
        m_Array = NULL;
    }
    else
    {
        m_Array = new void*[m_Size];
    
        for (int count = 0 ; count < m_Size ; count++)
        {
            if ( array[count] == NULL)
            {
                m_Array[count] = NULL;
            }
            else
            {
                switch (m_Type)
                {
                    case XSD_DURATION:
                    {
                        ((xsd__duration**) m_Array)[count] = new xsd__duration();
                        *((xsd__duration**)m_Array)[count] = *((xsd__duration**) array)[count];
                        break;
                    }
                    case XSD_DATETIME:
                    {
                        ((xsd__dateTime**) m_Array)[count] = new xsd__dateTime();
                        *((xsd__dateTime**)m_Array)[count] = *((xsd__dateTime**) array)[count];
                        break;
                    }
                    case XSD_TIME:
                    {
                        ((xsd__time**) m_Array)[count] = new xsd__time();
                        *((xsd__time**)m_Array)[count] = *((xsd__time**) array)[count];
                        break;
                    }
                    case XSD_DATE:
                    {
                        ((xsd__date**) m_Array)[count] = new xsd__date();
                        *((xsd__date**)m_Array)[count] = *((xsd__date**) array)[count];
                        break;
                    }
                    case XSD_GYEARMONTH:
                    {
                        ((xsd__gYearMonth**) m_Array)[count] = new xsd__gYearMonth();
                        *((xsd__gYearMonth**)m_Array)[count] = *((xsd__gYearMonth**) array)[count];
                        break;
                    }           
                    case XSD_GYEAR:
                    {
                        ((xsd__gYear**) m_Array)[count] = new xsd__gYear();
                        *((xsd__gYear**)m_Array)[count] = *((xsd__gYear**) array)[count];
                        break;
                    }
                    case XSD_GMONTHDAY:
                    {
                        ((xsd__gMonthDay**) m_Array)[count] = new xsd__gMonthDay();
                        *((xsd__gMonthDay**)m_Array)[count] = *((xsd__gMonthDay**) array)[count];
                        break;
                    }
                    case XSD_GDAY:
                    {
                        ((xsd__gDay**) m_Array)[count] = new xsd__gDay();
                        *((xsd__gDay**)m_Array)[count] = *((xsd__gDay**) array)[count];
                        break;
                    }
                    case XSD_GMONTH:
                    {
                        ((xsd__gMonth**) m_Array)[count] = new xsd__gMonth();
                        *((xsd__gMonth**)m_Array)[count] = *((xsd__gMonth**) array)[count];
                        break;
                    }
                    case XSD_STRING:
                    {
                        ((xsd__string*) m_Array)[count] = new char[strlen(((xsd__string*) array)[count])+1];
                        strcpy(((xsd__string*) m_Array)[count], ((xsd__string*) array)[count]);
                        break;
                    }
                    case XSD_NORMALIZEDSTRING:
                    {
                        ((xsd__normalizedString*) m_Array)[count] = new char[strlen(((xsd__normalizedString*) array)[count])+1];
                        strcpy(((xsd__normalizedString*) m_Array)[count], ((xsd__normalizedString*) array)[count]);
                        break;
                    }
                    case XSD_TOKEN:
                    {
                        ((xsd__token*) m_Array)[count] = new char[strlen(((xsd__token*) array)[count])+1];
                        strcpy(((xsd__token*) m_Array)[count], ((xsd__token*) array)[count]);
                        break;
                    }
                    case XSD_LANGUAGE:
                    {
                        ((xsd__language*) m_Array)[count] = new char[strlen(((xsd__language*) array)[count])+1];
                        strcpy(((xsd__language*) m_Array)[count], ((xsd__language*) array)[count]);
                        break;
                    }
                    case XSD_NAME:
                    {
                        ((xsd__Name*) m_Array)[count] = new char[strlen(((xsd__Name*) array)[count])+1];
                        strcpy(((xsd__Name*) m_Array)[count], ((xsd__Name*) array)[count]);
                        break;
                    }
                    case XSD_NCNAME:
                    {
                        ((xsd__NCName*) m_Array)[count] = new char[strlen(((xsd__NCName*) array)[count])+1];
                        strcpy(((xsd__NCName*) m_Array)[count], ((xsd__NCName*) array)[count]);
                        break;
                    }
                    case XSD_ID:
                    {
                        ((xsd__ID*) m_Array)[count] = new char[strlen(((xsd__ID*) array)[count])+1];
                        strcpy(((xsd__ID*) m_Array)[count], ((xsd__ID*) array)[count]);
                        break;
                    }
                    case XSD_IDREF:
                    {
                        ((xsd__IDREF*) m_Array)[count] = new char[strlen(((xsd__IDREF*) array)[count])+1];
                        strcpy(((xsd__IDREF*) m_Array)[count], ((xsd__IDREF*) array)[count]);
                        break;
                    }
                    case XSD_IDREFS:
                    {
                        ((xsd__IDREFS*) m_Array)[count] = new char[strlen(((xsd__IDREFS*) array)[count])+1];
                        strcpy(((xsd__IDREFS*) m_Array)[count], ((xsd__IDREFS*) array)[count]);
                        break;
                    }
                    case XSD_ENTITY:
                    {
                        ((xsd__ENTITY*) m_Array)[count] = new char[strlen(((xsd__ENTITY*) array)[count])+1];
                        strcpy(((xsd__ENTITY*) m_Array)[count], ((xsd__ENTITY*) array)[count]);
                        break;
                    }
                    case XSD_ENTITIES:
                    {
                        ((xsd__ENTITIES*) m_Array)[count] = new char[strlen(((xsd__ENTITIES*) array)[count])+1];
                        strcpy(((xsd__ENTITIES*) m_Array)[count], ((xsd__ENTITIES*) array)[count]);
                        break;
                    }
                    case XSD_NMTOKEN:
                    {
                        ((xsd__NMTOKEN*) m_Array)[count] = new char[strlen(((xsd__NMTOKEN*) array)[count])+1];
                        strcpy(((xsd__NMTOKEN*) m_Array)[count], ((xsd__NMTOKEN*) array)[count]);
                        break;
                    }
                    case XSD_NMTOKENS:
                    {
                        ((xsd__NMTOKENS*) m_Array)[count] = new char[strlen(((xsd__NMTOKENS*) array)[count])+1];
                        strcpy(((xsd__NMTOKENS*) m_Array)[count], ((xsd__NMTOKENS*) array)[count]);
                        break;
                    }
                    case XSD_BOOLEAN:
                    {
                        ((xsd__boolean**) m_Array)[count] = new xsd__boolean();
                        *((xsd__boolean**)m_Array)[count] = *((xsd__boolean**) array)[count];
                        break;
                    }
                    case XSD_BASE64BINARY:
                    {
						((xsd__base64Binary**) m_Array)[count] = new xsd__base64Binary();
						*((xsd__base64Binary**)m_Array)[count] = *((xsd__base64Binary**) array)[count];
                        break;
                    }
                    case XSD_HEXBINARY:
                    {
						((xsd__hexBinary**) m_Array)[count] = new xsd__hexBinary();
						*((xsd__hexBinary**)m_Array)[count] = *((xsd__hexBinary**) array)[count];
                        break;
                    }
                    case XSD_FLOAT:
                    {
                        ((xsd__float**) m_Array)[count] = new xsd__float();
                        *((xsd__float**)m_Array)[count] = *((xsd__float**) array)[count];
                        break;
                    }
                    case XSD_DECIMAL:
                    {
                        ((xsd__decimal**) m_Array)[count] = new xsd__decimal();
                        *((xsd__decimal**)m_Array)[count] = *((xsd__decimal**) array)[count];
                        break;
                    }
                    case XSD_INTEGER:
                    {
                        ((xsd__integer**) m_Array)[count] = new xsd__integer();
                        *((xsd__integer**)m_Array)[count] = *((xsd__integer**) array)[count];
                        break;
                    }
                    case XSD_NONPOSITIVEINTEGER:
                    {
                        ((xsd__nonPositiveInteger**) m_Array)[count] = new xsd__nonPositiveInteger();
                        *((xsd__nonPositiveInteger**)m_Array)[count] = *((xsd__nonPositiveInteger**) array)[count];
                        break;
                    }
                    case XSD_NEGATIVEINTEGER:
                    {
                        ((xsd__negativeInteger**) m_Array)[count] = new xsd__negativeInteger();
                        *((xsd__negativeInteger**)m_Array)[count] = *((xsd__negativeInteger**) array)[count];
                        break;
                    }
                    case XSD_LONG:
                    {
                        ((xsd__long**) m_Array)[count] = new xsd__long();
                        *((xsd__long**)m_Array)[count] = *((xsd__long**) array)[count];
                        break;
                    }
                    case XSD_INT:
                    {
                        ((xsd__int**) m_Array)[count] = new xsd__int();
                        *((xsd__int**)m_Array)[count] = *((xsd__int**) array)[count];
                        break;
                    }
                    case XSD_SHORT:
                    {
                        ((xsd__short**) m_Array)[count] = new xsd__short();
                        *((xsd__short**)m_Array)[count] = *((xsd__short**) array)[count];
                        break;
                    }
                    case XSD_BYTE:
                    {
                        ((xsd__byte**) m_Array)[count] = new xsd__byte();
                        *((xsd__byte**)m_Array)[count] = *((xsd__byte**) array)[count];
                        break;
                    }
                    case XSD_NONNEGATIVEINTEGER:
                    {
                        ((xsd__nonNegativeInteger**) m_Array)[count] = new xsd__nonNegativeInteger();
                        *((xsd__nonNegativeInteger**)m_Array)[count] = *((xsd__nonNegativeInteger**) array)[count];
                        break;
                    }
                    case XSD_UNSIGNEDLONG:
                    {
                        ((xsd__unsignedLong**) m_Array)[count] = new xsd__unsignedLong();
                        *((xsd__unsignedLong**)m_Array)[count] = *((xsd__unsignedLong**) array)[count];
                        break;
                    }
                    case XSD_UNSIGNEDINT:
                    {
                        ((xsd__unsignedInt**) m_Array)[count] = new xsd__unsignedInt();
                        *((xsd__unsignedInt**)m_Array)[count] = *((xsd__unsignedInt**) array)[count];
                        break;
                    }
                    case XSD_UNSIGNEDSHORT:
                    {
                        ((xsd__unsignedShort**) m_Array)[count] = new xsd__unsignedShort();
                        *((xsd__unsignedShort**)m_Array)[count] = *((xsd__unsignedShort**) array)[count];
                        break;
                    }
                    case XSD_UNSIGNEDBYTE:
                    {
                        ((xsd__unsignedByte**) m_Array)[count] = new xsd__unsignedByte();
                        *((xsd__unsignedByte**)m_Array)[count] = *((xsd__unsignedByte**) array)[count];
                        break;
                    }
                    case XSD_POSITIVEINTEGER:
                    {
                        ((xsd__positiveInteger**) m_Array)[count] = new xsd__positiveInteger();
                        *((xsd__positiveInteger**)m_Array)[count] = *((xsd__positiveInteger**) array)[count];
                        break;
                    }
                    case XSD_DOUBLE:
                    {
                        ((xsd__double**) m_Array)[count] = new xsd__double();
                        *((xsd__double**)m_Array)[count] = *((xsd__double**) array)[count];
                        break;
                    }
                    case XSD_ANYURI:
                    {
                        ((xsd__anyURI*) m_Array)[count] = new char[strlen(((xsd__anyURI*) array)[count])+1];
                        strcpy(((xsd__anyURI*) m_Array)[count], ((xsd__anyURI*) array)[count]);
                        break;
                    }
                    case XSD_QNAME:
                    {
                        ((xsd__QName*) m_Array)[count] = new char[strlen(((xsd__QName*) array)[count])+1];
                        strcpy(((xsd__QName*) m_Array)[count], ((xsd__QName*) array)[count]);
                        break;
                    }
                    case XSD_NOTATION:
                    {
                        ((xsd__NOTATION*) m_Array)[count] = new char[strlen(((xsd__NOTATION*) array)[count])+1];
                        strcpy(((xsd__NOTATION*) m_Array)[count], ((xsd__NOTATION*) array)[count]);
                        break;
                    }
                    case XSD_ARRAY:
                    {
                        ((Axis_Array**) m_Array)[count] = new Axis_Array(*((Axis_Array**) array)[count]);
                    }
                    case USER_TYPE:
                    {
                        ((int*) m_Array)[count] = ((int*) array)[count];
                    }
                    case XSD_UNKNOWN:
                    case XSD_ANY:
                    case ATTACHMENT:
                    default:
                        break;
                }
            }
        }
    }
}

void** Axis_Array::get(int& size, XSDTYPE& type) const
{
    size = m_Size;
    type = m_Type;
    return m_Array;
}


void Axis_Array::addElement(void* element)
{
    void** temp = new void*[m_Size+1];
    for (int count = 0 ; count < m_Size ; count++ )
    {
        temp[count] = m_Array[count];
    }
    if (m_Array != NULL)
    {
        delete [] m_Array;
    }
    m_Array = temp;
    m_belongsToAxisEngine = true;
 
    if ( element == NULL)
    {
        m_Array[m_Size] = NULL;
    }
    else
    {
        switch (m_Type)
        {
            case XSD_DURATION:
            {
                ((xsd__duration**) m_Array)[m_Size] = new xsd__duration();
                *((xsd__duration**)m_Array)[m_Size] = *(xsd__duration*) element;
                break;
            }
            case XSD_DATETIME:
            {
                ((xsd__dateTime**) m_Array)[m_Size] = new xsd__dateTime();
                *((xsd__dateTime**)m_Array)[m_Size] = *(xsd__dateTime*) element;
                break;
            }
            case XSD_TIME:
            {
                ((xsd__time**) m_Array)[m_Size] = new xsd__time();
                *((xsd__time**)m_Array)[m_Size] = *(xsd__time*) element;
                break;
            }
            case XSD_DATE:
            {
                ((xsd__date**) m_Array)[m_Size] = new xsd__date();
                *((xsd__date**)m_Array)[m_Size] = *(xsd__date*) element;
                break;
            }
            case XSD_GYEARMONTH:
            {
                ((xsd__gYearMonth**) m_Array)[m_Size] = new xsd__gYearMonth();
                *((xsd__gYearMonth**)m_Array)[m_Size] = *(xsd__gYearMonth*) element;
                break;
            }           
            case XSD_GYEAR:
            {
                ((xsd__gYear**) m_Array)[m_Size] = new xsd__gYear();
                *((xsd__gYear**)m_Array)[m_Size] = *(xsd__gYear*) element;
                break;
            }
            case XSD_GMONTHDAY:
            {
                ((xsd__gMonthDay**) m_Array)[m_Size] = new xsd__gMonthDay();
                *((xsd__gMonthDay**)m_Array)[m_Size] = *(xsd__gMonthDay*) element;
                break;
            }
            case XSD_GDAY:
            {
                ((xsd__gDay**) m_Array)[m_Size] = new xsd__gDay();
                *((xsd__gDay**)m_Array)[m_Size] = *(xsd__gDay*) element;
                break;
            }
            case XSD_GMONTH:
            {
                ((xsd__gMonth**) m_Array)[m_Size] = new xsd__gMonth();
                *((xsd__gMonth**)m_Array)[m_Size] = *(xsd__gMonth*) element;
                break;
            }
            case XSD_STRING:
            {
                ((xsd__string*) m_Array)[m_Size] = new char[strlen((xsd__string) element)+1];
                strcpy(((xsd__string*) m_Array)[m_Size], (xsd__string) element);
                break;
            }
            case XSD_NORMALIZEDSTRING:
            {
                ((xsd__normalizedString*) m_Array)[m_Size] = new char[strlen((xsd__normalizedString) element)+1];
                strcpy(((xsd__normalizedString*) m_Array)[m_Size], (xsd__normalizedString) element);
                break;
            }
            case XSD_TOKEN:
            {
                ((xsd__token*) m_Array)[m_Size] = new char[strlen((xsd__token) element)+1];
                strcpy(((xsd__token*) m_Array)[m_Size], (xsd__token) element);
                break;
            }
            case XSD_LANGUAGE:
            {
                ((xsd__language*) m_Array)[m_Size] = new char[strlen((xsd__language) element)+1];
                strcpy(((xsd__language*) m_Array)[m_Size], (xsd__language) element);
                break;
            }
            case XSD_NAME:
            {
                ((xsd__Name*) m_Array)[m_Size] = new char[strlen((xsd__Name) element)+1];
                strcpy(((xsd__Name*) m_Array)[m_Size], (xsd__Name) element);
                break;
            }
            case XSD_NCNAME:
            {
                ((xsd__NCName*) m_Array)[m_Size] = new char[strlen((xsd__NCName) element)+1];
                strcpy(((xsd__NCName*) m_Array)[m_Size], (xsd__NCName) element);
                break;
            }
            case XSD_ID:
            {
                ((xsd__ID*) m_Array)[m_Size] = new char[strlen((xsd__ID) element)+1];
                strcpy(((xsd__ID*) m_Array)[m_Size], (xsd__ID) element);
                break;
            }
            case XSD_IDREF:
            {
                ((xsd__IDREF*) m_Array)[m_Size] = new char[strlen((xsd__IDREF) element)+1];
                strcpy(((xsd__IDREF*) m_Array)[m_Size], (xsd__IDREF) element);
                break;
            }
            case XSD_IDREFS:
            {
                ((xsd__IDREFS*) m_Array)[m_Size] = new char[strlen((xsd__IDREFS) element)+1];
                strcpy(((xsd__IDREFS*) m_Array)[m_Size], (xsd__IDREFS) element);
                break;
            }
            case XSD_ENTITY:
            {
                ((xsd__ENTITY*) m_Array)[m_Size] = new char[strlen((xsd__ENTITY) element)+1];
                strcpy(((xsd__ENTITY*) m_Array)[m_Size], (xsd__ENTITY) element);
                break;
            }
            case XSD_ENTITIES:
            {
                ((xsd__ENTITIES*) m_Array)[m_Size] = new char[strlen((xsd__ENTITIES) element)+1];
                strcpy(((xsd__ENTITIES*) m_Array)[m_Size], (xsd__ENTITIES) element);
                break;
            }
            case XSD_NMTOKEN:
            {
                ((xsd__NMTOKEN*) m_Array)[m_Size] = new char[strlen((xsd__NMTOKEN) element)+1];
                strcpy(((xsd__NMTOKEN*) m_Array)[m_Size], (xsd__NMTOKEN) element);
                break;
            }
            case XSD_NMTOKENS:
            {
                ((xsd__NMTOKENS*) m_Array)[m_Size] = new char[strlen((xsd__NMTOKENS) element)+1];
                strcpy(((xsd__NMTOKENS*) m_Array)[m_Size], (xsd__NMTOKENS) element);
                break;
            }
            case XSD_BOOLEAN:
            {
                ((xsd__boolean**) m_Array)[m_Size] = new xsd__boolean();
                *((xsd__boolean**)m_Array)[m_Size] = *(xsd__boolean*) element;
                break;
            }
            case XSD_BASE64BINARY:
            {
				((xsd__base64Binary**) m_Array)[m_Size] = new xsd__base64Binary();
				*((xsd__base64Binary**)m_Array)[m_Size] = *(xsd__base64Binary*) element;
                break;
            }
            case XSD_HEXBINARY:
            {
				((xsd__hexBinary**) m_Array)[m_Size] = new xsd__hexBinary();
				*((xsd__hexBinary**)m_Array)[m_Size] = *(xsd__hexBinary*) element;
                break;
            }
            case XSD_FLOAT:
            {
                ((xsd__float**) m_Array)[m_Size] = new xsd__float();
                *((xsd__float**)m_Array)[m_Size] = *(xsd__float*) element;
                break;
            }
            case XSD_DECIMAL:
            {
                ((xsd__decimal**) m_Array)[m_Size] = new xsd__decimal();
                *((xsd__decimal**)m_Array)[m_Size] = *(xsd__decimal*) element;
                break;
            }
            case XSD_INTEGER:
            {
                ((xsd__integer**) m_Array)[m_Size] = new xsd__integer();
                *((xsd__integer**)m_Array)[m_Size] = *(xsd__integer*) element;
                break;
            }
            case XSD_NONPOSITIVEINTEGER:
            {
                ((xsd__nonPositiveInteger**) m_Array)[m_Size] = new xsd__nonPositiveInteger();
                *((xsd__nonPositiveInteger**)m_Array)[m_Size] = *(xsd__nonPositiveInteger*) element;
                break;
            }
            case XSD_NEGATIVEINTEGER:
            {
                ((xsd__negativeInteger**) m_Array)[m_Size] = new xsd__negativeInteger();
                *((xsd__negativeInteger**)m_Array)[m_Size] = *(xsd__negativeInteger*) element;
                break;
            }
            case XSD_LONG:
            {
                ((xsd__long**) m_Array)[m_Size] = new xsd__long();
                *((xsd__long**)m_Array)[m_Size] = *(xsd__long*) element;
                break;
            }
            case XSD_INT:
            {
                ((xsd__int**) m_Array)[m_Size] = new xsd__int();
                *((xsd__int**)m_Array)[m_Size] = *(xsd__int*) element;
                break;
            }
            case XSD_SHORT:
            {
                ((xsd__short**) m_Array)[m_Size] = new xsd__short();
                *((xsd__short**)m_Array)[m_Size] = *(xsd__short*) element;
                break;
            }
            case XSD_BYTE:
            {
                ((xsd__byte**) m_Array)[m_Size] = new xsd__byte();
                *((xsd__byte**)m_Array)[m_Size] = *(xsd__byte*) element;
                break;
            }
            case XSD_NONNEGATIVEINTEGER:
            {
                ((xsd__nonNegativeInteger**) m_Array)[m_Size] = new xsd__nonNegativeInteger();
                *((xsd__nonNegativeInteger**)m_Array)[m_Size] = *(xsd__nonNegativeInteger*) element;
                break;
            }
            case XSD_UNSIGNEDLONG:
            {
                ((xsd__unsignedLong**) m_Array)[m_Size] = new xsd__unsignedLong();
                *((xsd__unsignedLong**)m_Array)[m_Size] = *(xsd__unsignedLong*) element;
                break;
            }
            case XSD_UNSIGNEDINT:
            {
                ((xsd__unsignedInt**) m_Array)[m_Size] = new xsd__unsignedInt();
                *((xsd__unsignedInt**)m_Array)[m_Size] = *(xsd__unsignedInt*) element;
                break;
            }
            case XSD_UNSIGNEDSHORT:
            {
                ((xsd__unsignedShort**) m_Array)[m_Size] = new xsd__unsignedShort();
                *((xsd__unsignedShort**)m_Array)[m_Size] = *(xsd__unsignedShort*) element;
                break;
            }
            case XSD_UNSIGNEDBYTE:
            {
                ((xsd__unsignedByte**) m_Array)[m_Size] = new xsd__unsignedByte();
                *((xsd__unsignedByte**)m_Array)[m_Size] = *(xsd__unsignedByte*) element;
                break;
            }
            case XSD_POSITIVEINTEGER:
            {
                ((xsd__positiveInteger**) m_Array)[m_Size] = new xsd__positiveInteger();
                *((xsd__positiveInteger**)m_Array)[m_Size] = *(xsd__positiveInteger*) element;
                break;
            }
            case XSD_DOUBLE:
            {
                ((xsd__double**) m_Array)[m_Size] = new xsd__double();
                *((xsd__double**)m_Array)[m_Size] = *(xsd__double*) element;
                break;
            }
            case XSD_ANYURI:
            {
                ((xsd__anyURI*) m_Array)[m_Size] = new char[strlen((xsd__anyURI) element)+1];
                strcpy(((xsd__anyURI*) m_Array)[m_Size], (xsd__anyURI) element);
                break;
            }
            case XSD_QNAME:
            {
                ((xsd__QName*) m_Array)[m_Size] = new char[strlen((xsd__QName) element)+1];
                strcpy(((xsd__QName*) m_Array)[m_Size], (xsd__QName) element);
                break;
            }
            case XSD_NOTATION:
            {
                ((xsd__NOTATION*) m_Array)[m_Size] = new char[strlen((xsd__NOTATION) element)+1];
                strcpy(((xsd__NOTATION*) m_Array)[m_Size], (xsd__NOTATION) element);
                break;
            }
            case XSD_ARRAY:
            {
                ((Axis_Array**) m_Array)[m_Size] = new Axis_Array(*(Axis_Array*) element);
            }
            case USER_TYPE:
            {
                m_Array[m_Size] = element;
            }
            case XSD_UNKNOWN:
            case XSD_ANY:
            case ATTACHMENT:
            default:
                break;
        }
    }
    m_Size++;
}

Axis_Array::~Axis_Array()
{
    clear();
}

void Axis_Array::clear()
{ 
    if (m_Array != NULL)
    {
        if (m_Size > 0)
        {
            for (int count = 0 ; count < m_Size ; count++)
            {
                if (m_Array[count] != NULL)
                {
                    switch (m_Type)
                    {
                        case XSD_DURATION:
                        {
                            delete ((xsd__duration**) m_Array)[count];
        					break;
                        }
                        case XSD_DATETIME:
                        {
                            delete ((xsd__dateTime**) m_Array)[count];
                            break;
                        }
                        case XSD_TIME:
                        {
                            delete ((xsd__time**) m_Array)[count];
                            break;
                        }
                        case XSD_DATE:
                        {
                            delete ((xsd__date**) m_Array)[count];
                            break;
                        }
                        case XSD_GYEARMONTH:
                        {
                            delete ((xsd__gYearMonth**) m_Array)[count];
                            break;
                        }
                        case XSD_GYEAR:
                        {
                            delete ((xsd__gYear**) m_Array)[count];
                            break;
                        }
                        case XSD_GMONTHDAY:
                        {
                            delete ((xsd__gMonthDay**) m_Array)[count];
                            break;
                        }
                        case XSD_GDAY:
                        {
                            delete ((xsd__gDay**) m_Array)[count];
                            break;
                        }
                        case XSD_GMONTH:
                        {
                            delete ((xsd__gMonth**) m_Array)[count];
                            break;
                        }
                        case XSD_STRING:
                        {
                            delete []((xsd__string*) m_Array)[count];
                            break;
                        }
                        case XSD_NORMALIZEDSTRING:
                        {
                            delete []((xsd__normalizedString*) m_Array)[count];
                            break;
                        }
                        case XSD_TOKEN:
                        {
                            delete []((xsd__token*) m_Array)[count];
                            break;
                        }
                        case XSD_LANGUAGE:
                        {
                            delete []((xsd__language*) m_Array)[count];
                            break;
                        }
                        case XSD_NAME:
                        {
                            delete []((xsd__Name*) m_Array)[count];
                            break;
                        }
                        case XSD_NCNAME:
                        {
                            delete []((xsd__NCName*) m_Array)[count];
                            break;
                        }
                        case XSD_ID:
                        {
                            delete []((xsd__ID*) m_Array)[count];
                            break;
                        }
                        case XSD_IDREF:
                        {
                            delete []((xsd__IDREF*) m_Array)[count];
                            break;
                        }
                        case XSD_IDREFS:
                        {
                            delete []((xsd__IDREFS*) m_Array)[count];
                            break;
                        }
                        case XSD_ENTITY:
                        {
                            delete []((xsd__ENTITY*) m_Array)[count];
                            break;
                        }
                        case XSD_ENTITIES:
                        {
                            delete []((xsd__ENTITIES*) m_Array)[count];
                            break;
                        }
                        case XSD_NMTOKEN:
                        {
                            delete []((xsd__NMTOKEN*) m_Array)[count];
                            break;
                        }
                        case XSD_NMTOKENS:
                        {
                            delete []((xsd__NMTOKENS*) m_Array)[count];
                            break;
                        }
                        case XSD_BOOLEAN:
                        {
                            delete ((xsd__boolean**) m_Array)[count];
                            break;
                        }
                        case XSD_BASE64BINARY:
                        {
                            delete ((xsd__base64Binary**) m_Array)[count];
                            break;
                        }
                        case XSD_HEXBINARY:
                        {
                            delete ((xsd__hexBinary**) m_Array)[count];
                            break;
                        }
                        case XSD_FLOAT:
                        {
                            delete ((xsd__float**) m_Array)[count];
                            break;
                        }
                        case XSD_DECIMAL:
                        {
                            delete ((xsd__decimal**) m_Array)[count];
                            break;
                        }
                        case XSD_INTEGER:
                        {
                            delete ((xsd__integer**) m_Array)[count];
                            break;
                        }
                        case XSD_NONPOSITIVEINTEGER:
                        {
                            delete ((xsd__nonPositiveInteger**) m_Array)[count];
                            break;
                        }
                        case XSD_NEGATIVEINTEGER:
                        {
                            delete ((xsd__negativeInteger**) m_Array)[count];
                            break;
                        }
                        case XSD_LONG:
                        {
                            delete ((xsd__long**) m_Array)[count];
                            break;
                        }
                        case XSD_INT:
                        {
                            delete ((xsd__int**) m_Array)[count];
                            break;
                        }
                        case XSD_SHORT:
                        {
                            delete ((xsd__short**) m_Array)[count];
                            break;
                        }
                        case XSD_BYTE:
                        {
                            delete ((xsd__byte**) m_Array)[count];
                            break;
                        }
                        case XSD_NONNEGATIVEINTEGER:
                        {
                            delete ((xsd__nonNegativeInteger**) m_Array)[count];
                            break;
                        }
                        case XSD_UNSIGNEDLONG:
                        {
                            delete ((xsd__unsignedLong**) m_Array)[count];
                            break;
                        }
                        case XSD_UNSIGNEDINT:
                        {
                            delete ((xsd__unsignedInt**) m_Array)[count];
                            break;
                        }
                        case XSD_UNSIGNEDSHORT:
                        {
                            delete ((xsd__unsignedShort**) m_Array)[count];
                            break;
                        }
                        case XSD_UNSIGNEDBYTE:
                        {
                            delete ((xsd__unsignedByte**) m_Array)[count];
                            break;
                        }
                        case XSD_POSITIVEINTEGER:
                        {
                            delete ((xsd__positiveInteger**) m_Array)[count];
                            break;
                        }
                        case XSD_DOUBLE:
                        {
                            delete ((xsd__double**) m_Array)[count];
                            break;
                        }
                        case XSD_ANYURI:
                        {
                            delete []((xsd__anyURI*) m_Array)[count];
                            break;
                        }
                        case XSD_QNAME:
                        {
                            delete []((xsd__QName*) m_Array)[count];
                            break;
                        }
                        case XSD_NOTATION:
                        {
                            delete []((xsd__NOTATION*) m_Array)[count];
                            break;
                        }
                        case XSD_ARRAY:
                        {
                            delete ((Axis_Array**) m_Array)[count];
                            break;
                        }
                        case USER_TYPE:
                        case XSD_ANY:
                        case ATTACHMENT:
                        case XSD_UNKNOWN:
        				default:
                            break;
                    }
                }
			}
            m_Size = 0;
        }
        if (m_belongsToAxisEngine == true)
        {
            delete [] m_Array;
        }
        else
        {   // Warning!!  This could introduce memory leaks if used incorrectly!!!
            m_Array = NULL;
            m_belongsToAxisEngine = true;
        }
    }
}

xsd__duration_Array::xsd__duration_Array()
{
    m_Type = XSD_DURATION;
}

xsd__duration_Array::xsd__duration_Array(const xsd__duration_Array & original)
{
    if (original.m_Type == XSD_DURATION)
    {
        clone(original);
    }
}

xsd__duration_Array::~xsd__duration_Array()
{
    // Parent Axis_Array will carry out full clear up
}

void xsd__duration_Array::set(xsd__duration** array, int size)
{
	Axis_Array::set((void**)array, size, XSD_DURATION);
}

const xsd__duration** xsd__duration_Array::get(int& size) const
{
	XSDTYPE type;
    return (const xsd__duration**) Axis_Array::get(size, type);
}

xsd__dateTime_Array::xsd__dateTime_Array()
{
    m_Type = XSD_DATETIME;
}

xsd__dateTime_Array::xsd__dateTime_Array(const xsd__dateTime_Array & original)
{
    if (original.m_Type == XSD_DATETIME)
    {
        clone(original);
    }
}

xsd__dateTime_Array::~xsd__dateTime_Array()
{
    // Parent Axis_Array will carry out full clear up
}

void xsd__dateTime_Array::set(xsd__dateTime** array, int size)
{
   Axis_Array::set((void**)array, size, XSD_DATETIME);
}

const xsd__dateTime** xsd__dateTime_Array::get(int& size) const
{
  XSDTYPE type;
    return (const xsd__dateTime**) Axis_Array::get(size, type);
}

xsd__time_Array::xsd__time_Array()
{
    m_Type = XSD_TIME;
}

xsd__time_Array::xsd__time_Array(const xsd__time_Array & original)
{
    if (original.m_Type == XSD_TIME)
    {
        clone(original);
    }
}

xsd__time_Array::~xsd__time_Array()
{
    // Parent Axis_Array will carry out full clear up
}

void xsd__time_Array::set(xsd__time** array, int size)
{
   Axis_Array::set((void**)array, size, XSD_TIME);
}

const xsd__time** xsd__time_Array::get(int& size) const
{
  XSDTYPE type;
    return (const xsd__time**) Axis_Array::get(size, type);
}

xsd__date_Array::xsd__date_Array()
{
    m_Type = XSD_DATE;
}

xsd__date_Array::xsd__date_Array(const xsd__date_Array & original)
{
    if (original.m_Type == XSD_DATE)
    {
        clone(original);
    }
}

xsd__date_Array::~xsd__date_Array()
{
    // Parent Axis_Array will carry out full clear up
}

void xsd__date_Array::set(xsd__date** array, int size)
{
   Axis_Array::set((void**)array, size, XSD_DATE);
}

const xsd__date** xsd__date_Array::get(int& size) const
{
  XSDTYPE type;
    return (const xsd__date**) Axis_Array::get(size, type);
}

xsd__gYearMonth_Array::xsd__gYearMonth_Array()
{
    m_Type = XSD_GYEARMONTH;
}

xsd__gYearMonth_Array::xsd__gYearMonth_Array(const xsd__gYearMonth_Array & original)
{
    if (original.m_Type == XSD_GYEARMONTH)
    {
        clone(original);
    }
}

xsd__gYearMonth_Array::~xsd__gYearMonth_Array()
{
    // Parent Axis_Array will carry out full clear up
}

void xsd__gYearMonth_Array::set(xsd__gYearMonth** array, int size)
{
   Axis_Array::set((void**)array, size, XSD_GYEARMONTH);
}

const xsd__gYearMonth** xsd__gYearMonth_Array::get(int& size) const
{
  XSDTYPE type;
    return (const xsd__gYearMonth**) Axis_Array::get(size, type);
}

xsd__gYear_Array::xsd__gYear_Array()
{
    m_Type = XSD_GYEAR;
}

xsd__gYear_Array::xsd__gYear_Array(const xsd__gYear_Array & original)
{
    if (original.m_Type == XSD_GYEAR)
    {
        clone(original);
    }
}

xsd__gYear_Array::~xsd__gYear_Array()
{
    // Parent Axis_Array will carry out full clear up
}

void xsd__gYear_Array::set(xsd__gYear** array, int size)
{
   Axis_Array::set((void**)array, size, XSD_GYEAR);
}

const xsd__gYear** xsd__gYear_Array::get(int& size) const
{
  XSDTYPE type;
    return (const xsd__gYear**) Axis_Array::get(size, type);
}

xsd__gMonthDay_Array::xsd__gMonthDay_Array()
{
    m_Type = XSD_GMONTHDAY;
}

xsd__gMonthDay_Array::xsd__gMonthDay_Array(const xsd__gMonthDay_Array & original)
{
    if (original.m_Type == XSD_GMONTHDAY)
    {
        clone(original);
    }
}

xsd__gMonthDay_Array::~xsd__gMonthDay_Array()
{
    // Parent Axis_Array will carry out full clear up
}

void xsd__gMonthDay_Array::set(xsd__gMonthDay** array, int size)
{
   Axis_Array::set((void**)array, size, XSD_GMONTHDAY);
}

const xsd__gMonthDay** xsd__gMonthDay_Array::get(int& size) const
{
  XSDTYPE type;
    return (const xsd__gMonthDay**) Axis_Array::get(size, type);
}

xsd__gMonth_Array::xsd__gMonth_Array()
{
    m_Type = XSD_GMONTH;
}

xsd__gMonth_Array::xsd__gMonth_Array(const xsd__gMonth_Array & original)
{
    if (original.m_Type == XSD_GMONTH)
    {
        clone(original);
    }
}

xsd__gMonth_Array::~xsd__gMonth_Array()
{
    // Parent Axis_Array will carry out full clear up
}

void xsd__gMonth_Array::set(xsd__gMonth** array, int size)
{
   Axis_Array::set((void**)array, size, XSD_GMONTH);
}

const xsd__gMonth** xsd__gMonth_Array::get(int& size) const
{
  XSDTYPE type;
    return (const xsd__gMonth**) Axis_Array::get(size, type);
}

xsd__gDay_Array::xsd__gDay_Array()
{
    m_Type = XSD_GDAY;
}

xsd__gDay_Array::xsd__gDay_Array(const xsd__gDay_Array & original)
{
    if (original.m_Type == XSD_GDAY)
    {
        clone(original);
    }
}

xsd__gDay_Array::~xsd__gDay_Array()
{
    // Parent Axis_Array will carry out full clear up
}

void xsd__gDay_Array::set(xsd__gDay** array, int size)
{
   Axis_Array::set((void**)array, size, XSD_GDAY);
}

const xsd__gDay** xsd__gDay_Array::get(int& size) const
{
  XSDTYPE type;
    return (const xsd__gDay**) Axis_Array::get(size, type);
}

xsd__string_Array::xsd__string_Array()
{
    m_Type = XSD_STRING;
}

xsd__string_Array::xsd__string_Array(const xsd__string_Array & original)
{
    if (original.m_Type == XSD_STRING)
    {
        clone(original);
    }
}

xsd__string_Array::~xsd__string_Array()
{
    // Parent Axis_Array will carry out full clear up
}

void xsd__string_Array::set(xsd__string* array, int size)
{
 Axis_Array::set((void**)array, size, XSD_STRING);
}

const xsd__string* xsd__string_Array::get(int& size) const
{
    XSDTYPE type;
    return (const xsd__string*) Axis_Array::get(size, type);
}

xsd__normalizedString_Array::xsd__normalizedString_Array()
{
    m_Type = XSD_NORMALIZEDSTRING;
}

xsd__normalizedString_Array::xsd__normalizedString_Array(const xsd__normalizedString_Array & original)
{
    if (original.m_Type == XSD_NORMALIZEDSTRING)
    {
        clone(original);
    }
}

xsd__normalizedString_Array::~xsd__normalizedString_Array()
{
    // Parent Axis_Array will carry out full clear up
}

void xsd__normalizedString_Array::set(xsd__normalizedString* array, int size)
{
 Axis_Array::set((void**)array, size, XSD_NORMALIZEDSTRING);
}

const xsd__normalizedString* xsd__normalizedString_Array::get(int& size) const
{
    XSDTYPE type;
    return (const xsd__normalizedString*) Axis_Array::get(size, type);
}

xsd__token_Array::xsd__token_Array()
{
    m_Type = XSD_TOKEN;
}

xsd__token_Array::xsd__token_Array(const xsd__token_Array & original)
{
    if (original.m_Type == XSD_TOKEN)
    {
        clone(original);
    }
}

xsd__token_Array::~xsd__token_Array()
{
    // Parent Axis_Array will carry out full clear up
}

void xsd__token_Array::set(xsd__token* array, int size)
{
 Axis_Array::set((void**)array, size, XSD_TOKEN);
}

const xsd__token* xsd__token_Array::get(int& size) const
{
    XSDTYPE type;
    return (const xsd__token*) Axis_Array::get(size, type);
}

xsd__language_Array::xsd__language_Array()
{
    m_Type = XSD_LANGUAGE;
}

xsd__language_Array::xsd__language_Array(const xsd__language_Array & original)
{
    if (original.m_Type == XSD_LANGUAGE)
    {
        clone(original);
    }
}

xsd__language_Array::~xsd__language_Array()
{
    // Parent Axis_Array will carry out full clear up
}

void xsd__language_Array::set(xsd__language* array, int size)
{
 Axis_Array::set((void**)array, size, XSD_LANGUAGE);
}

const xsd__language* xsd__language_Array::get(int& size) const
{
    XSDTYPE type;
    return (const xsd__language*) Axis_Array::get(size, type);
}

xsd__Name_Array::xsd__Name_Array()
{
    m_Type = XSD_NAME;
}

xsd__Name_Array::xsd__Name_Array(const xsd__Name_Array & original)
{
    if (original.m_Type == XSD_NAME)
    {
        clone(original);
    }
}

xsd__Name_Array::~xsd__Name_Array()
{
    // Parent Axis_Array will carry out full clear up
}

void xsd__Name_Array::set(xsd__Name* array, int size)
{
 Axis_Array::set((void**)array, size, XSD_NAME);
}

const xsd__Name* xsd__Name_Array::get(int& size) const
{
    XSDTYPE type;
    return (const xsd__Name*) Axis_Array::get(size, type);
}

xsd__NCName_Array::xsd__NCName_Array()
{
    m_Type = XSD_NCNAME;
}

xsd__NCName_Array::xsd__NCName_Array(const xsd__NCName_Array & original)
{
    if (original.m_Type == XSD_NCNAME)
    {
        clone(original);
    }
}

xsd__NCName_Array::~xsd__NCName_Array()
{
    // Parent Axis_Array will carry out full clear up
}

void xsd__NCName_Array::set(xsd__NCName* array, int size)
{
 Axis_Array::set((void**)array, size, XSD_NCNAME);
}

const xsd__NCName* xsd__NCName_Array::get(int& size) const
{
    XSDTYPE type;
    return (const xsd__NCName*) Axis_Array::get(size, type);
}

xsd__ID_Array::xsd__ID_Array()
{
    m_Type = XSD_ID;
}

xsd__ID_Array::xsd__ID_Array(const xsd__ID_Array & original)
{
    if (original.m_Type == XSD_ID)
    {
        clone(original);
    }
}

xsd__ID_Array::~xsd__ID_Array()
{
    // Parent Axis_Array will carry out full clear up
}

void xsd__ID_Array::set(xsd__ID* array, int size)
{
 Axis_Array::set((void**)array, size, XSD_ID);
}

const xsd__ID* xsd__ID_Array::get(int& size) const
{
    XSDTYPE type;
    return (const xsd__ID*) Axis_Array::get(size, type);
}

xsd__IDREF_Array::xsd__IDREF_Array()
{
    m_Type = XSD_IDREF;
}

xsd__IDREF_Array::xsd__IDREF_Array(const xsd__IDREF_Array & original)
{
    if (original.m_Type == XSD_IDREF)
    {
        clone(original);
    }
}

xsd__IDREF_Array::~xsd__IDREF_Array()
{
    // Parent Axis_Array will carry out full clear up
}

void xsd__IDREF_Array::set(xsd__IDREF* array, int size)
{
 Axis_Array::set((void**)array, size, XSD_IDREF);
}

const xsd__IDREF* xsd__IDREF_Array::get(int& size) const
{
    XSDTYPE type;
    return (const xsd__IDREF*) Axis_Array::get(size, type);
}

xsd__IDREFS_Array::xsd__IDREFS_Array()
{
    m_Type = XSD_IDREFS;
}

xsd__IDREFS_Array::xsd__IDREFS_Array(const xsd__IDREFS_Array & original)
{
    if (original.m_Type == XSD_IDREFS)
    {
        clone(original);
    }
}

xsd__IDREFS_Array::~xsd__IDREFS_Array()
{
    // Parent Axis_Array will carry out full clear up
}

void xsd__IDREFS_Array::set(xsd__IDREFS* array, int size)
{
 Axis_Array::set((void**)array, size, XSD_IDREFS);
}

const xsd__IDREFS* xsd__IDREFS_Array::get(int& size) const
{
    XSDTYPE type;
    return (const xsd__IDREFS*) Axis_Array::get(size, type);
}

xsd__ENTITY_Array::xsd__ENTITY_Array()
{
    m_Type = XSD_ENTITY;
}

xsd__ENTITY_Array::xsd__ENTITY_Array(const xsd__ENTITY_Array & original)
{
    if (original.m_Type == XSD_ENTITY)
    {
        clone(original);
    }
}

xsd__ENTITY_Array::~xsd__ENTITY_Array()
{
    // Parent Axis_Array will carry out full clear up
}

void xsd__ENTITY_Array::set(xsd__ENTITY* array, int size)
{
 Axis_Array::set((void**)array, size, XSD_ENTITY);
}

const xsd__ENTITY* xsd__ENTITY_Array::get(int& size) const
{
    XSDTYPE type;
    return (const xsd__ENTITY*) Axis_Array::get(size, type);
}

xsd__ENTITIES_Array::xsd__ENTITIES_Array()
{
    m_Type = XSD_ENTITIES;
}

xsd__ENTITIES_Array::xsd__ENTITIES_Array(const xsd__ENTITIES_Array & original)
{
    if (original.m_Type == XSD_ENTITIES)
    {
        clone(original);
    }
}

xsd__ENTITIES_Array::~xsd__ENTITIES_Array()
{
    // Parent Axis_Array will carry out full clear up
}

void xsd__ENTITIES_Array::set(xsd__ENTITIES* array, int size)
{
 Axis_Array::set((void**)array, size, XSD_ENTITIES);
}

const xsd__ENTITIES* xsd__ENTITIES_Array::get(int& size) const
{
    XSDTYPE type;
    return (const xsd__ENTITIES*) Axis_Array::get(size, type);
}

xsd__NMTOKEN_Array::xsd__NMTOKEN_Array()
{
    m_Type = XSD_NMTOKEN;
}

xsd__NMTOKEN_Array::xsd__NMTOKEN_Array(const xsd__NMTOKEN_Array & original)
{
    if (original.m_Type == XSD_NMTOKEN)
    {
        clone(original);
    }
}

xsd__NMTOKEN_Array::~xsd__NMTOKEN_Array()
{
    // Parent Axis_Array will carry out full clear up
}

void xsd__NMTOKEN_Array::set(xsd__NMTOKEN* array, int size)
{
 Axis_Array::set((void**)array, size, XSD_NMTOKEN);
}

const xsd__NMTOKEN* xsd__NMTOKEN_Array::get(int& size) const
{
    XSDTYPE type;
    return (const xsd__NMTOKEN*) Axis_Array::get(size, type);
}

xsd__NMTOKENS_Array::xsd__NMTOKENS_Array()
{
    m_Type = XSD_NMTOKEN;
}

xsd__NMTOKENS_Array::xsd__NMTOKENS_Array(const xsd__NMTOKENS_Array & original)
{
    if (original.m_Type == XSD_NMTOKEN)
    {
        clone(original);
    }
}

xsd__NMTOKENS_Array::~xsd__NMTOKENS_Array()
{
    // Parent Axis_Array will carry out full clear up
}

void xsd__NMTOKENS_Array::set(xsd__NMTOKENS* array, int size)
{
 Axis_Array::set((void**)array, size, XSD_NMTOKEN);
}

const xsd__NMTOKENS* xsd__NMTOKENS_Array::get(int& size) const
{
    XSDTYPE type;
    return (const xsd__NMTOKENS*) Axis_Array::get(size, type);
}

xsd__boolean_Array::xsd__boolean_Array()
{
    m_Type = XSD_BOOLEAN;
}

xsd__boolean_Array::xsd__boolean_Array(const xsd__boolean_Array & original)
{
    if (original.m_Type == XSD_BOOLEAN)
    {
        clone(original);
    }
}

xsd__boolean_Array::~xsd__boolean_Array()
{
    // Parent Axis_Array will carry out full clear up
}

void xsd__boolean_Array::set(xsd__boolean** array, int size)
{
	Axis_Array::set((void**)array, size, XSD_BOOLEAN);
}

const xsd__boolean** xsd__boolean_Array::get(int& size) const
{
	XSDTYPE type;
    return (const xsd__boolean**) Axis_Array::get(size, type);
}

xsd__base64Binary_Array::xsd__base64Binary_Array()
{
    m_Type = XSD_BASE64BINARY;
}

xsd__base64Binary_Array::xsd__base64Binary_Array(const xsd__base64Binary_Array & original)
{
    if (original.m_Type == XSD_BASE64BINARY)
    {
        clone(original);
    }
}

xsd__base64Binary_Array::~xsd__base64Binary_Array()
{
    // Parent Axis_Array will carry out full clear up
}

void xsd__base64Binary_Array::set(xsd__base64Binary** array, int size)
{
	Axis_Array::set((void**)array, size, XSD_BASE64BINARY);
}

const xsd__base64Binary** xsd__base64Binary_Array::get(int& size) const
{
	XSDTYPE type;
    return (const xsd__base64Binary**) Axis_Array::get(size, type);
}

xsd__hexBinary_Array::xsd__hexBinary_Array()
{
    m_Type = XSD_HEXBINARY;
}

xsd__hexBinary_Array::xsd__hexBinary_Array(const xsd__hexBinary_Array & original)
{
    if (original.m_Type == XSD_HEXBINARY)
    {
        clone(original);
    }
}

xsd__hexBinary_Array::~xsd__hexBinary_Array()
{
    // Parent Axis_Array will carry out full clear up
}

void xsd__hexBinary_Array::set(xsd__hexBinary** array, int size)
{
	Axis_Array::set((void**)array, size, XSD_HEXBINARY);
}

const xsd__hexBinary** xsd__hexBinary_Array::get(int& size) const
{
	XSDTYPE type;
    return (const xsd__hexBinary**) Axis_Array::get(size, type);
}

xsd__float_Array::xsd__float_Array()
{
    m_Type = XSD_FLOAT;
}

xsd__float_Array::xsd__float_Array(const xsd__float_Array & original)
{
    if (original.m_Type == XSD_FLOAT)
    {
        clone(original);
    }
}

xsd__float_Array::~xsd__float_Array()
{
    // Parent Axis_Array will carry out full clear up
}

void xsd__float_Array::set(xsd__float** array, int size)
{
	Axis_Array::set((void**)array, size, XSD_FLOAT);
}

const xsd__float** xsd__float_Array::get(int& size) const
{
	XSDTYPE type;
    return (const xsd__float**) Axis_Array::get(size, type);
}

xsd__decimal_Array::xsd__decimal_Array()
{
    m_Type = XSD_DECIMAL;
}

xsd__decimal_Array::xsd__decimal_Array(const xsd__decimal_Array & original)
{
    if (original.m_Type == XSD_DECIMAL)
    {
        clone(original);
    }
}

xsd__decimal_Array::~xsd__decimal_Array()
{
    // Parent Axis_Array will carry out full clear up
}

void xsd__decimal_Array::set(xsd__decimal** array, int size)
{
	Axis_Array::set((void**)array, size, XSD_DECIMAL);
}

const xsd__decimal** xsd__decimal_Array::get(int& size) const
{
	XSDTYPE type;
    return (const xsd__decimal**) Axis_Array::get(size, type);
}

xsd__integer_Array::xsd__integer_Array()
{
    m_Type = XSD_INTEGER;
}

xsd__integer_Array::xsd__integer_Array(const xsd__integer_Array & original)
{
    if (original.m_Type == XSD_INTEGER)
    {
        clone(original);
    }
}

xsd__integer_Array::~xsd__integer_Array()
{
    // Parent Axis_Array will carry out full clear up
}

void xsd__integer_Array::set(xsd__integer** array, int size)
{
	Axis_Array::set((void**)array, size, XSD_INTEGER);
}

const xsd__integer** xsd__integer_Array::get(int& size) const
{
	XSDTYPE type;
    return (const xsd__integer**) Axis_Array::get(size, type);
}

xsd__nonPositiveInteger_Array::xsd__nonPositiveInteger_Array()
{
    m_Type = XSD_NONPOSITIVEINTEGER;
}

xsd__nonPositiveInteger_Array::xsd__nonPositiveInteger_Array(const xsd__nonPositiveInteger_Array & original)
{
    if (original.m_Type == XSD_NONPOSITIVEINTEGER)
    {
        clone(original);
    }
}

xsd__nonPositiveInteger_Array::~xsd__nonPositiveInteger_Array()
{
    // Parent Axis_Array will carry out full clear up
}

void xsd__nonPositiveInteger_Array::set(xsd__nonPositiveInteger** array, int size)
{
	Axis_Array::set((void**)array, size, XSD_NONPOSITIVEINTEGER);
}

const xsd__nonPositiveInteger** xsd__nonPositiveInteger_Array::get(int& size) const
{
	XSDTYPE type;
    return (const xsd__nonPositiveInteger**) Axis_Array::get(size, type);
}

xsd__negativeInteger_Array::xsd__negativeInteger_Array()
{
    m_Type = XSD_NEGATIVEINTEGER;
}

xsd__negativeInteger_Array::xsd__negativeInteger_Array(const xsd__negativeInteger_Array & original)
{
    if (original.m_Type == XSD_NEGATIVEINTEGER)
    {
        clone(original);
    }
}

xsd__negativeInteger_Array::~xsd__negativeInteger_Array()
{
    // Parent Axis_Array will carry out full clear up
}

void xsd__negativeInteger_Array::set(xsd__negativeInteger** array, int size)
{
	Axis_Array::set((void**)array, size, XSD_NEGATIVEINTEGER);
}

const xsd__negativeInteger** xsd__negativeInteger_Array::get(int& size) const
{
	XSDTYPE type;
    return (const xsd__negativeInteger**) Axis_Array::get(size, type);
}

xsd__long_Array::xsd__long_Array()
{
    m_Type = XSD_LONG;
}

xsd__long_Array::xsd__long_Array(const xsd__long_Array & original)
{
    if (original.m_Type == XSD_LONG)
    {
        clone(original);
    }
}

xsd__long_Array::~xsd__long_Array()
{
    // Parent Axis_Array will carry out full clear up
}

void xsd__long_Array::set(xsd__long** array, int size)
{
	Axis_Array::set((void**)array, size, XSD_LONG);
}

const xsd__long** xsd__long_Array::get(int& size) const
{
	XSDTYPE type;
    return (const xsd__long**) Axis_Array::get(size, type);
}

xsd__int_Array::xsd__int_Array()
{
    m_Type = XSD_INT;
}

xsd__int_Array::xsd__int_Array(const xsd__int_Array & original)
{
    if (original.m_Type == XSD_INT)
    {
        clone(original);
    }
}

xsd__int_Array::~xsd__int_Array()
{
    // Parent Axis_Array will carry out full clear up
}

void xsd__int_Array::set(xsd__int** array, int size)
{
	Axis_Array::set((void**)array, size, XSD_INT);
}

const xsd__int** xsd__int_Array::get(int& size) const
{
	XSDTYPE type;
    return (const xsd__int**) Axis_Array::get(size, type);
}

xsd__short_Array::xsd__short_Array()
{
    m_Type = XSD_SHORT;
}

xsd__short_Array::xsd__short_Array(const xsd__short_Array & original)
{
    if (original.m_Type == XSD_SHORT)
    {
        clone(original);
    }
}

xsd__short_Array::~xsd__short_Array()
{
    // Parent Axis_Array will carry out full clear up
}

void xsd__short_Array::set(xsd__short** array, int size)
{
	Axis_Array::set((void**)array, size, XSD_SHORT);
}

const xsd__short** xsd__short_Array::get(int& size) const
{
	XSDTYPE type;
    return (const xsd__short**) Axis_Array::get(size, type);
}

xsd__byte_Array::xsd__byte_Array()
{
    m_Type = XSD_BYTE;
}

xsd__byte_Array::xsd__byte_Array(const xsd__byte_Array & original)
{
    if (original.m_Type == XSD_BYTE)
    {
        clone(original);
    }
}

xsd__byte_Array::~xsd__byte_Array()
{
    // Parent Axis_Array will carry out full clear up
}

void xsd__byte_Array::set(xsd__byte** array, int size)
{
	Axis_Array::set((void**)array, size, XSD_BYTE);
}

const xsd__byte** xsd__byte_Array::get(int& size) const
{
	XSDTYPE type;
    return (const xsd__byte**) Axis_Array::get(size, type);
}

xsd__nonNegativeInteger_Array::xsd__nonNegativeInteger_Array()
{
    m_Type = XSD_NONNEGATIVEINTEGER;
}

xsd__nonNegativeInteger_Array::xsd__nonNegativeInteger_Array(const xsd__nonNegativeInteger_Array & original)
{
    if (original.m_Type == XSD_NONNEGATIVEINTEGER)
    {
        clone(original);
    }
}

xsd__nonNegativeInteger_Array::~xsd__nonNegativeInteger_Array()
{
    // Parent Axis_Array will carry out full clear up
}

void xsd__nonNegativeInteger_Array::set(xsd__nonNegativeInteger** array, int size)
{
	Axis_Array::set((void**)array, size, XSD_NONNEGATIVEINTEGER);
}

const xsd__nonNegativeInteger** xsd__nonNegativeInteger_Array::get(int& size) const
{
	XSDTYPE type;
    return (const xsd__nonNegativeInteger**) Axis_Array::get(size, type);
}

xsd__unsignedLong_Array::xsd__unsignedLong_Array()
{
    m_Type = XSD_UNSIGNEDLONG;
}

xsd__unsignedLong_Array::xsd__unsignedLong_Array(const xsd__unsignedLong_Array & original)
{
    if (original.m_Type == XSD_UNSIGNEDLONG)
    {
        clone(original);
    }
}

xsd__unsignedLong_Array::~xsd__unsignedLong_Array()
{
    // Parent Axis_Array will carry out full clear up
}

void xsd__unsignedLong_Array::set(xsd__unsignedLong** array, int size)
{
	Axis_Array::set((void**)array, size, XSD_UNSIGNEDLONG);
}

const xsd__unsignedLong** xsd__unsignedLong_Array::get(int& size) const
{
	XSDTYPE type;
    return (const xsd__unsignedLong**) Axis_Array::get(size, type);
}

xsd__unsignedInt_Array::xsd__unsignedInt_Array()
{
    m_Type = XSD_UNSIGNEDINT;
}

xsd__unsignedInt_Array::xsd__unsignedInt_Array(const xsd__unsignedInt_Array & original)
{
    if (original.m_Type == XSD_UNSIGNEDINT)
    {
        clone(original);
    }
}

xsd__unsignedInt_Array::~xsd__unsignedInt_Array()
{
    // Parent Axis_Array will carry out full clear up
}

void xsd__unsignedInt_Array::set(xsd__unsignedInt** array, int size)
{
	Axis_Array::set((void**)array, size, XSD_UNSIGNEDINT);
}

const xsd__unsignedInt** xsd__unsignedInt_Array::get(int& size) const
{
	XSDTYPE type;
    return (const xsd__unsignedInt**) Axis_Array::get(size, type);
}

xsd__unsignedShort_Array::xsd__unsignedShort_Array()
{
    m_Type = XSD_UNSIGNEDSHORT;
}

xsd__unsignedShort_Array::xsd__unsignedShort_Array(const xsd__unsignedShort_Array & original)
{
    if (original.m_Type == XSD_UNSIGNEDSHORT)
    {
        clone(original);
    }
}

xsd__unsignedShort_Array::~xsd__unsignedShort_Array()
{
    // Parent Axis_Array will carry out full clear up
}

void xsd__unsignedShort_Array::set(xsd__unsignedShort** array, int size)
{
	Axis_Array::set((void**)array, size, XSD_UNSIGNEDSHORT);
}

const xsd__unsignedShort** xsd__unsignedShort_Array::get(int& size) const
{
	XSDTYPE type;
    return (const xsd__unsignedShort**) Axis_Array::get(size, type);
}

xsd__unsignedByte_Array::xsd__unsignedByte_Array()
{
    m_Type = XSD_UNSIGNEDBYTE;
}

xsd__unsignedByte_Array::xsd__unsignedByte_Array(const xsd__unsignedByte_Array & original)
{
    if (original.m_Type == XSD_UNSIGNEDBYTE)
    {
        clone(original);
    }
}

xsd__unsignedByte_Array::~xsd__unsignedByte_Array()
{
    // Parent Axis_Array will carry out full clear up
}

void xsd__unsignedByte_Array::set(xsd__unsignedByte** array, int size)
{
	Axis_Array::set((void**)array, size, XSD_UNSIGNEDBYTE);
}

const xsd__unsignedByte** xsd__unsignedByte_Array::get(int& size) const
{
	XSDTYPE type;
    return (const xsd__unsignedByte**) Axis_Array::get(size, type);
}

xsd__positiveInteger_Array::xsd__positiveInteger_Array()
{
    m_Type = XSD_POSITIVEINTEGER;
}

xsd__positiveInteger_Array::xsd__positiveInteger_Array(const xsd__positiveInteger_Array & original)
{
    if (original.m_Type == XSD_POSITIVEINTEGER)
    {
        clone(original);
    }
}

xsd__positiveInteger_Array::~xsd__positiveInteger_Array()
{
    // Parent Axis_Array will carry out full clear up
}

void xsd__positiveInteger_Array::set(xsd__positiveInteger** array, int size)
{
	Axis_Array::set((void**)array, size, XSD_POSITIVEINTEGER);
}

const xsd__positiveInteger** xsd__positiveInteger_Array::get(int& size) const
{
	XSDTYPE type;
    return (const xsd__positiveInteger**) Axis_Array::get(size, type);
}

xsd__double_Array::xsd__double_Array()
{
    m_Type = XSD_DOUBLE;
}

xsd__double_Array::xsd__double_Array(const xsd__double_Array & original)
{
    if (original.m_Type == XSD_DOUBLE)
    {
        clone(original);
    }
}

xsd__double_Array::~xsd__double_Array()
{
    // Parent Axis_Array will carry out full clear up
}

void xsd__double_Array::set(xsd__double** array, int size)
{
	Axis_Array::set((void**)array, size, XSD_DOUBLE);
}

const xsd__double** xsd__double_Array::get(int& size) const
{
	XSDTYPE type;
    return (const xsd__double**) Axis_Array::get(size, type);
}

xsd__anyURI_Array::xsd__anyURI_Array()
{
    m_Type = XSD_ANYURI;
}

xsd__anyURI_Array::xsd__anyURI_Array(const xsd__anyURI_Array & original)
{
    if (original.m_Type == XSD_ANYURI)
    {
        clone(original);
    }
}

xsd__anyURI_Array::~xsd__anyURI_Array()
{
    // Parent Axis_Array will carry out full clear up
}

void xsd__anyURI_Array::set(xsd__anyURI* array, int size)
{
    Axis_Array::set((void**)array, size, XSD_ANYURI);
}

const xsd__anyURI* xsd__anyURI_Array::get(int& size) const
{
    XSDTYPE type;
    return (const xsd__anyURI*) Axis_Array::get(size, type);
}

xsd__QName_Array::xsd__QName_Array()
{
    m_Type = XSD_QNAME;
}

xsd__QName_Array::xsd__QName_Array(const xsd__QName_Array & original)
{
    if (original.m_Type == XSD_QNAME)
    {
        clone(original);
    }
}

xsd__QName_Array::~xsd__QName_Array()
{
    // Parent Axis_Array will carry out full clear up
}

void xsd__QName_Array::set(xsd__QName* array, int size)
{
    Axis_Array::set((void**)array, size, XSD_QNAME);
}

const xsd__QName* xsd__QName_Array::get(int& size) const
{
    XSDTYPE type;
    return (const xsd__QName*) Axis_Array::get(size, type);
}

xsd__NOTATION_Array::xsd__NOTATION_Array()
{
    m_Type = XSD_NOTATION;
}

xsd__NOTATION_Array::xsd__NOTATION_Array(const xsd__NOTATION_Array & original)
{
    if (original.m_Type == XSD_NOTATION)
    {
        clone(original);
    }
}

xsd__NOTATION_Array::~xsd__NOTATION_Array()
{
    // Parent Axis_Array will carry out full clear up
}

void xsd__NOTATION_Array::set(xsd__NOTATION* array, int size)
{
    Axis_Array::set((void**)array, size, XSD_NOTATION);
}

const xsd__NOTATION* xsd__NOTATION_Array::get(int& size) const
{
    XSDTYPE type;
    return (const xsd__NOTATION*) Axis_Array::get(size, type);
}

AXIS_CPP_NAMESPACE_END
