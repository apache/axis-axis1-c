/*
 *This file is automatically generated by the Axis C++ Wrapper Class Generator
 *Web service wrapper class's implementation generated by Axis WCG
 *Parameters and wrapper methos to manipulate DivByZeroStruct
 */

#include <malloc.h>
#include "DivByZeroStruct.h"
#include <axis/server/AxisWrapperAPI.h>

/*
 * This static method serialize a DivByZeroStruct type of object
 */
int Axis_Serialize_DivByZeroStruct(DivByZeroStruct* param, IWrapperSoapSerializer* pSZ, bool bArray = false)
{
	if (bArray)
	{
		pSZ->serialize("<", Axis_TypeName_DivByZeroStruct, ">", NULL);
	}
	else
	{
		const AxisChar* sPrefix = pSZ->getNamespacePrefix(Axis_URI_DivByZeroStruct);
		pSZ->serialize("<", Axis_TypeName_DivByZeroStruct, " xsi:type=\"", sPrefix, ":",
			Axis_TypeName_DivByZeroStruct, "\" xmlns:", sPrefix, "=\"",
			Axis_URI_DivByZeroStruct, "\">", NULL);
	}

	pSZ->serializeAsElement("varString", (void*)&(param->varString), XSD_STRING);
	pSZ->serializeAsElement("varInt", (void*)&(param->varInt), XSD_INT);
	pSZ->serializeAsElement("varFloat", (void*)&(param->varFloat), XSD_FLOAT);

	pSZ->serialize("</", Axis_TypeName_DivByZeroStruct, ">", NULL);
	return AXIS_SUCCESS;
}

/*
 * This static method deserialize a DivByZeroStruct type of object
 */
int Axis_DeSerialize_DivByZeroStruct(DivByZeroStruct* param, IWrapperSoapDeSerializer *pIWSDZ)
{
	param->varString = pIWSDZ->getElementAsString("varString",0);
	param->varInt = pIWSDZ->getElementAsInt("varInt",0);
	param->varFloat = pIWSDZ->getElementAsFloat("varFloat",0);
	return pIWSDZ->getStatus();
}
void* Axis_Create_DivByZeroStruct(DivByZeroStruct* pObj, bool bArray = false, int nSize=0)
{
	if (bArray && (nSize > 0))
	{
		if (pObj)
		{
			DivByZeroStruct* pNew = new DivByZeroStruct[nSize];
			memcpy(pNew, pObj, sizeof(DivByZeroStruct)*nSize/2);
			memset(pObj, 0, sizeof(DivByZeroStruct)*nSize/2);
			delete [] pObj;
			return pNew;
		}
		else
		{
			return new DivByZeroStruct[nSize];
		}
	}
	else
		return new DivByZeroStruct;
}

/*
 * This static method delete a DivByZeroStruct type of object
 */
void Axis_Delete_DivByZeroStruct(DivByZeroStruct* param, bool bArray = false, int nSize=0)
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
 * This static method gives the size of DivByZeroStruct type of object
 */
int Axis_GetSize_DivByZeroStruct()
{
	return sizeof(DivByZeroStruct);
}

DivByZeroStruct::DivByZeroStruct()
{
	/*do not allocate memory to any pointer members here
	 because deserializer will allocate memory anyway. */
}

DivByZeroStruct::~DivByZeroStruct()
{
	/*delete any pointer and array members here*/
}