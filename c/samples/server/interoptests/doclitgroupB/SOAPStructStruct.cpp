///////////////////////////////////////////////////////////////////////////////////
//This file is automatically generated by the Axis C++ Wrapper Class Generator
//Web service wrapper class's implementation generated by Axis WCG
//Parameters and wrapper methos to manipulate SOAPStructStruct
////////////////////////////////////////////////////////////////////////////////////

#include "SOAPStructStruct.h"
#include <axis/server/AxisWrapperAPI.h>

extern int Axis_DeSerialize_SOAPStruct(SOAPStruct* param, IWrapperSoapDeSerializer *pDZ);
extern void* Axis_Create_SOAPStruct(void* pObj, bool bArray = false, int nSize=0);
extern void Axis_Delete_SOAPStruct(SOAPStruct* param, bool bArray = false, int nSize=0);
extern int Axis_Serialize_SOAPStruct(SOAPStruct* param, IWrapperSoapSerializer* pSZ, bool bArray = false);
extern int Axis_GetSize_SOAPStruct();

/////////////////////////////////////////////////////////////////////////////
// This static method serialize a SOAPStructStruct type of object
//////////////////////////////////////////////////////////////////////
int Axis_Serialize_SOAPStructStruct(SOAPStructStruct* param, IWrapperSoapSerializer* pSZ, bool bArray = false)
{
	pSZ->SerializeAsElement("varString", (void*)&(param->varString), XSD_STRING);
	pSZ->SerializeAsElement("varInt", (void*)&(param->varInt), XSD_INT);
	pSZ->SerializeAsElement("varFloat", (void*)&(param->varFloat), XSD_FLOAT);
	pSZ->Serialize("<varStruct>", 0);
	Axis_Serialize_SOAPStruct(param->varStruct, pSZ);
	pSZ->Serialize("</varStruct>", 0);
	return AXIS_SUCCESS;
}

/////////////////////////////////////////////////////////////////////////////
// This static method deserialize a SOAPStructStruct type of object
//////////////////////////////////////////////////////////////////////
int Axis_DeSerialize_SOAPStructStruct(SOAPStructStruct* param, IWrapperSoapDeSerializer *pIWSDZ)
{
	param->varString = pIWSDZ->GetElementAsString("varString",0);
	param->varInt = pIWSDZ->GetElementAsInt("varInt",0);
	param->varFloat = pIWSDZ->GetElementAsFloat("varFloat",0);
	param->varStruct = (SOAPStruct*)pIWSDZ->GetCmplxObject((void*)Axis_DeSerialize_SOAPStruct
		, (void*)Axis_Create_SOAPStruct, (void*)Axis_Delete_SOAPStruct
		, "varStruct", Axis_URI_SOAPStruct);
	return AXIS_SUCCESS;
}
void* Axis_Create_SOAPStructStruct(void* pObj, bool bArray = false, int nSize=0)
{
	if (bArray && (nSize > 0))
		return new SOAPStructStruct[nSize];
	else
		return new SOAPStructStruct;
}

SOAPStructStruct::SOAPStructStruct()
{
	varString = 0;
	varStruct = 0;
}

SOAPStructStruct::~SOAPStructStruct()
{
	free(varString);
	delete varStruct;
}
/////////////////////////////////////////////////////////////////////////////
// This static method delete a SOAPStructStruct type of object
//////////////////////////////////////////////////////////////////////
void Axis_Delete_SOAPStructStruct(SOAPStructStruct* param, bool bArray = false, int nSize=0)
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
/////////////////////////////////////////////////////////////////////////////
// This static method gives the size of SOAPStructStruct type of object
//////////////////////////////////////////////////////////////////////
int Axis_GetSize_SOAPStructStruct()
{
	return sizeof(SOAPStructStruct);
}
