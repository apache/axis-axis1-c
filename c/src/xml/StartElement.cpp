// StartElement.cpp: implementation of the StartElement class.
//
//////////////////////////////////////////////////////////////////////

#include <axis/xml/StartElement.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace axisxml {

StartElement::StartElement()
{

}

StartElement::~StartElement()
{
	for (list<Attribute*>::iterator it = m_Attributes.begin(); it != m_Attributes.end(); it++)
	{
		delete *it;
	}
}

}

