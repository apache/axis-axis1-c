/*
 * Copyright 2003-2004 The Apache Software Foundation.

 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *		http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * This file was auto-generated by the Axis C++ Web Service Generator (WSDL2Ws)
 * This file contains functions to manipulate complex type intArrayType
 */

#include <axis/AxisWrapperAPI.hpp>
#include <axis/Axis.hpp>

#include "IntArrayType.hpp"

xsd__int_Array * intArrayType::getintItem()
{
	return intItem ; 
}

void intArrayType::setintItem(xsd__int_Array * pInValue)
{
	if(intItem == NULL)
	{
		intItem = new xsd__int_Array();
	}
	intItem->clone(*pInValue); 
}
/*
 * This static method serialize a intArrayType type of object
 */
int Axis_Serialize_intArrayType(intArrayType* param, IWrapperSoapSerializer* pSZ, bool bArray = false)
{
	if ( param == NULL )
	{
	 /* TODO : may need to check nillable value - Now done*/
		pSZ->serializeAsAttribute( "xsi:nil", 0, (void*)&(xsd_boolean_true), XSD_BOOLEAN);
		pSZ->serialize( ">", NULL);
		return AXIS_SUCCESS;
	}

	/* first serialize attributes if any*/
	pSZ->serialize( ">", 0);

	/* then serialize elements if any*/
	pSZ->serializeBasicArray(param->intItem, Axis_URI_intArrayType,XSD_INT, "intItem");
	return AXIS_SUCCESS;
}

/*
 * This static method deserialize a intArrayType type of object
 */
int Axis_DeSerialize_intArrayType(intArrayType* param, IWrapperSoapDeSerializer* pIWSDZ)
{
	Axis_Array * array;

	array = pIWSDZ->getBasicArray(XSD_INT, "intItem",0);
	if(param->intItem == NULL)
	{
		param->intItem = new xsd__int_Array();
	}
	param->intItem->clone( *array);
	Axis::AxisDelete((void*) array, XSD_ARRAY);

	return pIWSDZ->getStatus();
}
void* Axis_Create_intArrayType(intArrayType* pObj, bool bArray = false, int nSize=0)
{
	if (bArray && (nSize > 0))
	{
		if (pObj)
		{
			intArrayType* pNew = new intArrayType[nSize];
			size_t i = nSize/2;
			for (int ii=0; ii<i; ++ii)
			{
				pNew[ii] = pObj[ii];
				pObj[ii].reset();
			}
			delete [] pObj;
			return pNew;
		}
		else
		{
			return new intArrayType[nSize];
		}
	}
	else
		return new intArrayType;
}

/*
 * This static method delete a intArrayType type of object
 */
void Axis_Delete_intArrayType(intArrayType* param, bool bArray = false, int nSize=0)
{
	if (bArray)
	{
		delete [] param;
	}
	else
	{
		delete param;
	}
}
/*
 * This static method gives the size of intArrayType type of object
 */
int Axis_GetSize_intArrayType()
{
	return sizeof(intArrayType);
}

intArrayType::intArrayType()
{
	intItem = NULL;
	reset();
}

void intArrayType::reset()
{
	/*do not allocate memory to any pointer members here
	 because deserializer will allocate memory anyway. */
	if ( intItem != NULL)
	{
		intItem->clear();
	}
}

intArrayType::~intArrayType()
{
	/*delete any pointer and array members here*/
	if (intItem!= NULL)
		delete intItem;
}
