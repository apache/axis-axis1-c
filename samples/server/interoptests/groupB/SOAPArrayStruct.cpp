/*
 * This file was auto-generated by the Axis C++ Web Service Generator (WSDL2Ws)
 * This file contains functions to manipulate complex type SOAPArrayStruct
 */

#include <malloc.h>
#include "SOAPArrayStruct.h"
#include <axis/AxisWrapperAPI.hpp>

/*
 * This static method serialize a SOAPArrayStruct type of object
 */
int Axis_Serialize_SOAPArrayStruct(SOAPArrayStruct* param, IWrapperSoapSerializer* pSZ, bool bArray = false)
{
	if (bArray)
	{
		pSZ->serialize("<", Axis_TypeName_SOAPArrayStruct, ">", NULL);
	}
	else
	{
		const AxisChar* sPrefix = pSZ->getNamespacePrefix(Axis_URI_SOAPArrayStruct);
		pSZ->serialize("<", Axis_TypeName_SOAPArrayStruct, " xsi:type=\"", sPrefix, ":",
			Axis_TypeName_SOAPArrayStruct, "\" xmlns:", sPrefix, "=\"",
			Axis_URI_SOAPArrayStruct, "\">", NULL);
	}

	pSZ->serializeAsElement("varString", (void*)&(param->varString), XSD_STRING);
	pSZ->serializeAsElement("varInt", (void*)&(param->varInt), XSD_INT);
	pSZ->serializeAsElement("varFloat", (void*)&(param->varFloat), XSD_FLOAT);
	pSZ->serializeBasicArray((Axis_Array*)(&param->varArray),XSD_STRING, "varArray");

	pSZ->serialize("</", Axis_TypeName_SOAPArrayStruct, ">", NULL);
	return AXIS_SUCCESS;
}

/*
 * This static method deserialize a SOAPArrayStruct type of object
 */
int Axis_DeSerialize_SOAPArrayStruct(SOAPArrayStruct* param, IWrapperSoapDeSerializer* pIWSDZ)
{
	param->varString = pIWSDZ->getElementAsString("varString",0);
	param->varInt = pIWSDZ->getElementAsInt("varInt",0);
	param->varFloat = pIWSDZ->getElementAsFloat("varFloat",0);
	param->varArray = (xsd__string_Array&)pIWSDZ->getBasicArray(XSD_STRING, "varArray",0);
	return pIWSDZ->getStatus();
}
void* Axis_Create_SOAPArrayStruct(SOAPArrayStruct* pObj, bool bArray = false, int nSize=0)
{
	if (bArray && (nSize > 0))
	{
		if (pObj)
		{
			SOAPArrayStruct* pNew = new SOAPArrayStruct[nSize];
			memcpy(pNew, pObj, sizeof(SOAPArrayStruct)*nSize/2);
			memset(pObj, 0, sizeof(SOAPArrayStruct)*nSize/2);
			delete [] pObj;
			return pNew;
		}
		else
		{
			return new SOAPArrayStruct[nSize];
		}
	}
	else
		return new SOAPArrayStruct;
}

/*
 * This static method delete a SOAPArrayStruct type of object
 */
void Axis_Delete_SOAPArrayStruct(SOAPArrayStruct* param, bool bArray = false, int nSize=0)
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
 * This static method gives the size of SOAPArrayStruct type of object
 */
int Axis_GetSize_SOAPArrayStruct()
{
	return sizeof(SOAPArrayStruct);
}

SOAPArrayStruct::SOAPArrayStruct()
{
	/*do not allocate memory to any pointer members here
	 because deserializer will allocate memory anyway. */
	varArray.m_Array = 0;
	varArray.m_Size = 0;
}

SOAPArrayStruct::~SOAPArrayStruct()
{
	/*delete any pointer and array members here*/
	delete [] ((xsd__string*)varArray.m_Array);
}
