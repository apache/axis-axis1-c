/*
 *This file is automatically generated by the Axis C++ Wrapper Class Generator
 *Web service wrapper class's implementation generated by Axis WCG
 *Parameters and wrapper methos to manipulate SOAPStruct
 */

#include <malloc.h>
#include "SOAPStruct.h"
#include <axis/common/AxisWrapperAPI.h>

/**
 * This static method serialize a SOAPStruct type of object
 */
int Axis_Serialize_SOAPStruct(SOAPStruct* param, IWrapperSoapSerializer* pSZ, bool bArray)
{
	const AxisChar* sPrefix;
	if (bArray)
	{
		pSZ->_functions->SerializeStartElementOfType(pSZ->_object, Axis_TypeName_SOAPStruct, 0, 0);
	}
	else
	{
		sPrefix = pSZ->_functions->GetNamespacePrefix(pSZ->_object, Axis_URI_SOAPStruct);
		pSZ->_functions->SerializeStartElementOfType(pSZ->_object, Axis_TypeName_SOAPStruct, Axis_URI_SOAPStruct, sPrefix);
	}

	pSZ->_functions->SerializeAsElement(pSZ->_object, "varString", (void*)&(param->varString), XSD_STRING);
	pSZ->_functions->SerializeAsElement(pSZ->_object, "varInt", (void*)&(param->varInt), XSD_INT);
	pSZ->_functions->SerializeAsElement(pSZ->_object, "varFloat", (void*)&(param->varFloat), XSD_FLOAT);

	pSZ->_functions->SerializeEndElementOfType(pSZ->_object, Axis_TypeName_SOAPStruct);
	return AXIS_SUCCESS;
}

/**
 * This static method deserialize a SOAPStruct type of object
 */
int Axis_DeSerialize_SOAPStruct(SOAPStruct* param, IWrapperSoapDeSerializer *pDZ)
{
	param->varString = pDZ->_functions->GetElementAsString(pDZ->_object,0,0);
	param->varInt = pDZ->_functions->GetElementAsInt(pDZ->_object,0,0);
	param->varFloat = pDZ->_functions->GetElementAsFloat(pDZ->_object,0,0);
	return pDZ->_functions->GetStatus(pDZ->_object);
}
void* Axis_Create_SOAPStruct(SOAPStruct* pObj, bool bArray, int nSize)
{
	if (bArray && (nSize > 0))
	{
		pObj = malloc(sizeof(SOAPStruct)*nSize);
		memset(pObj, 0, sizeof(SOAPStruct)*nSize);
	}
	else
	{
		pObj = malloc(sizeof(SOAPStruct));
		memset(pObj, 0, sizeof(SOAPStruct));
	}
	return pObj;
}
/**
 * This static method to deallocate a SOAPStruct type of object
 */
void Axis_Delete_SOAPStruct(SOAPStruct* param, bool bArray, int nSize)
{
	int x;
	SOAPStruct* pTemp;
	if (bArray)
	{
		/*delete any pointer members or array members of this struct here*/
		pTemp = param;
		for (x=0; x<nSize; x++)
		{
			if(pTemp->varString) free(pTemp->varString);
			pTemp++;
		}
		free(param);
	}
	else
	{
		/*delete any pointer members or array members of this struct here*/
		if(param->varString) free(param->varString);
		free(param);
	}
}
/**
 * This static method gives the size of SOAPStruct type of object
 */
int Axis_GetSize_SOAPStruct()
{
	return sizeof(SOAPStruct);
}
