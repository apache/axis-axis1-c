/*
 * This file was auto-generated by the Axis C++ Web Service Generator (WSDL2Ws)
 * This file contains functions to manipulate complex type SOAPStruct
 */

#include <malloc.h>
#include "SOAPStruct.h"
#include <axis/server/AxisWrapperAPI.h>

/*
 * This static method serialize a SOAPStruct type of object
 */
int Axis_Serialize_SOAPStruct(SOAPStruct* param, IWrapperSoapSerializer* pSZ, bool bArray = false)
{
	if (bArray)
	{
		pSZ->serialize("<", Axis_TypeName_SOAPStruct, ">", NULL);
	}
	else
	{
		const AxisChar* sPrefix = pSZ->getNamespacePrefix(Axis_URI_SOAPStruct);
		pSZ->serialize("<", Axis_TypeName_SOAPStruct, " xsi:type=\"", sPrefix, ":",
			Axis_TypeName_SOAPStruct, "\" xmlns:", sPrefix, "=\"",
			Axis_URI_SOAPStruct, "\">", NULL);
	}

	pSZ->serializeAsElement("varInt", (void*)&(param->varInt), XSD_INT);
	pSZ->serializeAsElement("varString", (void*)&(param->varString), XSD_STRING);
	pSZ->serializeAsElement("varFloat", (void*)&(param->varFloat), XSD_FLOAT);

	pSZ->serialize("</", Axis_TypeName_SOAPStruct, ">", NULL);
	return AXIS_SUCCESS;
}

/*
 * This static method deserialize a SOAPStruct type of object
 */
int Axis_DeSerialize_SOAPStruct(SOAPStruct* param, IWrapperSoapDeSerializer* pIWSDZ)
{
	param->varInt = pIWSDZ->getElementAsInt("varInt",0);
	param->varString = pIWSDZ->getElementAsString("varString",0);
	param->varFloat = pIWSDZ->getElementAsFloat("varFloat",0);
	return pIWSDZ->getStatus();
}
void* Axis_Create_SOAPStruct(SOAPStruct* pObj, bool bArray = false, int nSize=0)
{
	if (bArray && (nSize > 0))
	{
		if (pObj)
		{
			SOAPStruct* pNew = new SOAPStruct[nSize];
			memcpy(pNew, pObj, sizeof(SOAPStruct)*nSize/2);
			memset(pObj, 0, sizeof(SOAPStruct)*nSize/2);
			delete [] pObj;
			return pNew;
		}
		else
		{
			return new SOAPStruct[nSize];
		}
	}
	else
		return new SOAPStruct;
}

/*
 * This static method delete a SOAPStruct type of object
 */
void Axis_Delete_SOAPStruct(SOAPStruct* param, bool bArray = false, int nSize=0)
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
 * This static method gives the size of SOAPStruct type of object
 */
int Axis_GetSize_SOAPStruct()
{
	return sizeof(SOAPStruct);
}

SOAPStruct::SOAPStruct()
{
	/*do not allocate memory to any pointer members here
	 because deserializer will allocate memory anyway. */
}

SOAPStruct::~SOAPStruct()
{
	/*delete any pointer and array members here*/
}
