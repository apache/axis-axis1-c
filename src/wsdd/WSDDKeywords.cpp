// WSDDKeywords.cpp: implementation of the WSDDKeywords class.
//
//////////////////////////////////////////////////////////////////////

#include "WSDDKeywords.h"
#include "../common/AxisUtils.h"

#define __TRC(X) AxisUtils::ToAxisXMLCh(X)

volatile bool WSDDKeywords::m_bInit = false;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define AX_DELETE(X) delete const_cast<AxisXMLCh*>(X)

const AxisXMLCh* kw_depl;
const AxisXMLCh* kw_srv;
const AxisXMLCh* kw_glconf;
const AxisXMLCh* kw_param; 
const AxisXMLCh* kw_hdl;
const AxisXMLCh* kw_chain;
const AxisXMLCh* kw_ns;
const AxisXMLCh* kw_prv;
const AxisXMLCh* kw_cn; //must be changed to libname or so
const AxisXMLCh* kw_am;
const AxisXMLCh* kw_ar;
const AxisXMLCh* kw_rqf;
const AxisXMLCh* kw_rsf;
const AxisXMLCh* kw_tr;
const AxisXMLCh* kw_name;
const AxisXMLCh* kw_value;
const AxisXMLCh* kw_type; //what about this ? change to libname ?
const AxisXMLCh* kw_scope;
const AxisXMLCh* kw_http;
const AxisXMLCh* kw_smtp;

WSDDKeywords::WSDDKeywords()
{
	Initialize();
}

WSDDKeywords::~WSDDKeywords()
{
	UnInitialize();
}

void WSDDKeywords::Initialize()
{
	if (!m_bInit)
	{
		kw_depl = __TRC("deployment");
		kw_srv = __TRC("service");
		kw_glconf = __TRC("globalConfiguration");
		kw_param = __TRC("parameter"); 
		kw_hdl = __TRC("handler");
		kw_chain = __TRC("chain");
		kw_ns = __TRC("namespace");
		kw_prv = __TRC("provider");
		kw_cn = __TRC("className"); //must be changed to libname or so
		kw_am = __TRC("allowedMethods");
		kw_ar = __TRC("allowedRoles");
		kw_rqf = __TRC("requestFlow");
		kw_rsf = __TRC("responseFlow");
		kw_tr = __TRC("transport");
		kw_name = __TRC("name");
		kw_value = __TRC("value");
		kw_type = __TRC("type"); //what about this ? change to libname ?
		kw_scope = __TRC("scope");
		kw_http = __TRC("http");
		kw_smtp = __TRC("smtp");
		m_bInit = true;
	}
}

void WSDDKeywords::UnInitialize()
{
	if (m_bInit)
	{
		AX_DELETE(kw_smtp);
		m_bInit = false;
	}
}
