/*
 *	@author sanjaya singharage (sanjayas@opensource.lk)
 */

// SoapInputSource.h: interface for the SoapInputSource class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOAPINPUTSOURCE_H__CB5BD78C_76E6_4246_8EB8_D011ED7505FA__INCLUDED_)
#define AFX_SOAPINPUTSOURCE_H__CB5BD78C_76E6_4246_8EB8_D011ED7505FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <xercesc/sax/InputSource.hpp>
#include "SoapBinInputStream.h"

XERCES_CPP_NAMESPACE_USE

class SoapInputSource : public InputSource  
{
private:
	SoapBinInputStream* m_pInputStream;
public:
	SoapInputSource(AXIS_MODULE_CALLBACK_GET_MESSAGE_BYTES pReadFunct, const void* pContext);
	virtual ~SoapInputSource();
	BinInputStream* makeStream() const;
};

#endif // !defined(AFX_SOAPINPUTSOURCE_H__CB5BD78C_76E6_4246_8EB8_D011ED7505FA__INCLUDED_)
