#include "AccessBean.h"
#include "Param.h"
#include "../soap/SoapDeSerializer.h"
#include "BasicTypeSerializer.h"

AccessBean::AccessBean()
{
	m_TypeName = "";
}

//this is never called. just default method
int AccessBean::DeSerialize(SoapDeSerializer *pDZ)
{
	return SUCCESS;
}

//this is never called. just default method
string& AccessBean::Serialize()
{
	return m_TypeName; 
}

ArrayBean::ArrayBean()
{
	t = XSD_UNKNOWN;
	s = 0;
	m_ItemName = "";
	v.so = NULL;
}

ArrayBean::~ArrayBean()
{
	switch (t)
	{
	case XSD_INT:
		{
			int* a = (int*)v.so;
			delete [] a;
		}
		break;
	case XSD_FLOAT:
		{
			float* a = (float*)v.so;
			delete [] a;
		}
		break;
	case XSD_STRING:
		{
			string* a = (string*)v.so;
			delete [] a;
		}
		break;
		//continue this for all basic types
	case USER_TYPE: //array of user types
		{
			AccessBean** a = v.co;
			for (int ix=0;ix<s; ix++)
			{
				delete (*a);
				a++;
			}
			delete [] a;
		}
		break;
	default:;
	}	
}

int ArrayBean::DeSerialize(SoapDeSerializer *pDZ)
{
	Param* p;
	if ((XSD_UNKNOWN == t) ||(s<=0)||(!v.so)) return FAIL;
	switch (t)
	{
	case XSD_INT:
		{
			int* a = (int*)v.so;
			for (int ix=0;ix<s;ix++)
			{
				p = pDZ->GetParam();
				if (!p) return FAIL;
				a[ix] = p->GetInt();
			}
		}
		break;
	case XSD_FLOAT:
		{
			float* a = (float*)v.so;
			for (int ix=0;ix<s;ix++)
			{
				p = pDZ->GetParam();
				if (!p) return FAIL;
				a[ix] = p->GetFloat();
			}
		}
		break;
	case XSD_STRING:
		{
			string* a = (string*)v.so;
			for (int ix=0;ix<s;ix++)
			{
				p = pDZ->GetParam();
				if (!p) return FAIL;
				a[ix] = p->GetString();
			}
		}
		break;
		//continue this for all basic types
	case USER_TYPE: //array of user types
		{
			AccessBean** a = v.co;
			for (int ix=0;ix<s;ix++)
			{
				p = pDZ->GetParam();
			//	a->m_TypeName = p->m_sName;
				(*a)->DeSerialize(pDZ);
				a++;
			}
		}
		break;
	default:;
	}
}

string& ArrayBean::Serialize()
{	
	m_sSZ = "";
	if (t == USER_TYPE)
	{
		AccessBean** pType = v.co;
		for (int ix=0; ix<s; ix++)
		{
			m_sSZ += (*pType)->Serialize();
			pType++;
		}
	}
	else
	{
		switch (t)
		{
		case XSD_INT:
			{
				int* pInt = (int*)v.so;
				for (int ix=0; ix<s; ix++)
				{
					m_sSZ += BasicTypeSerializer::serialize(m_ItemName, *pInt);
					pInt++;
				}
			}
			break;
		case XSD_FLOAT:
			{
				float* pFloat = (float*)v.so;
				for (int ix=0; ix<s; ix++)
				{
					m_sSZ += BasicTypeSerializer::serialize(m_ItemName, *pFloat);
					pFloat++;
				}
			}
			break;
		case XSD_STRING:
			{
				string* pStr = (string*)v.so;
				for (int ix=0; ix<s; ix++)
				{
					m_sSZ += BasicTypeSerializer::serialize(m_ItemName, *pStr);
					pStr++;
				}
			}
			break;
		default:;
		}
	}
	return m_sSZ;
}
