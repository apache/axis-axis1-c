/*
 * This file was auto-generated by the Axis C++ Web Service Generator (WSDL2Ws)
 * This file contains functions to manipulate complex type DivByZeroStruct
 */

#include <axis/AxisWrapperAPI.hpp>

#include "DivByZeroStruct.hpp"
/*
 * This static method serialize a DivByZeroStruct type of object
 */
int Axis_Serialize_DivByZeroStruct(DivByZeroStruct* param, IWrapperSoapSerializer* pSZ, bool bArray = false)
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
	pSZ->serializeAsElement("varString", Axis_URI_DivByZeroStruct, (void*)&(param->varString), XSD_STRING);
	pSZ->serializeAsElement("varInt", Axis_URI_DivByZeroStruct, (void*)&(param->varInt), XSD_INT);
	pSZ->serializeAsElement("varFloat", Axis_URI_DivByZeroStruct, (void*)&(param->varFloat), XSD_FLOAT);
	return AXIS_SUCCESS;
}

/*
 * This static method deserialize a DivByZeroStruct type of object
 */
int Axis_DeSerialize_DivByZeroStruct(DivByZeroStruct* param, IWrapperSoapDeSerializer* pIWSDZ)
{
	param->varString = pIWSDZ->getElementAsString( "varString",0);
	param->varInt = pIWSDZ->getElementAsInt( "varInt",0);
	param->varFloat = pIWSDZ->getElementAsFloat( "varFloat",0);
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
	memset( &varString, 0, sizeof( xsd__string));
	memset( &varInt, 0, sizeof( xsd__int));
	memset( &varFloat, 0, sizeof( xsd__float));
}

DivByZeroStruct::~DivByZeroStruct()
{
	/*delete any pointer and array members here*/
}
