#include "AccessBean.h"

AccessBean::AccessBean()
{
}

//this is never called. just default method
int AccessBean::DeSerialize(ISoapDeSerializer *pDZ)
{
	return SUCCESS;
}

//this is never called. just default method
int AccessBean::Serialize(IWrapperSoapSerializer& pSZ)
{
	return SUCCESS;
}

int AccessBean::GetSize()
{
	return sizeof(AccessBean);
}
