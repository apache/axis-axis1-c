// WSDDKeywords.h: interface for the WSDDKeywords class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WSDDKEYWORDS_H__870A488E_084E_4EAB_8162_25A1DDF2CD74__INCLUDED_)
#define AFX_WSDDKEYWORDS_H__870A488E_084E_4EAB_8162_25A1DDF2CD74__INCLUDED_

#include "../common/GDefine.h"

//keywords used in the wsdd file
extern const AxisXMLCh* kw_depl;
extern const AxisXMLCh* kw_srv;
extern const AxisXMLCh* kw_glconf;
extern const AxisXMLCh* kw_param; 
extern const AxisXMLCh* kw_hdl;
extern const AxisXMLCh* kw_chain;
extern const AxisXMLCh* kw_ns;
extern const AxisXMLCh* kw_prv;
extern const AxisXMLCh* kw_cn; //must be changed to libname or so
extern const AxisXMLCh* kw_am;
extern const AxisXMLCh* kw_ar;
extern const AxisXMLCh* kw_rqf;
extern const AxisXMLCh* kw_rsf;
extern const AxisXMLCh* kw_tr;
extern const AxisXMLCh* kw_name;
extern const AxisXMLCh* kw_value;
extern const AxisXMLCh* kw_type; //what about this ? change to libname ?
extern const AxisXMLCh* kw_scope;
extern const AxisXMLCh* kw_http;
extern const AxisXMLCh* kw_smtp;

class WSDDKeywords  
{
public:
	static void Initialize();
	static void UnInitialize();
	WSDDKeywords();
	virtual ~WSDDKeywords();
private:
	static volatile bool m_bInit;
};

#endif // !defined(AFX_WSDDKEYWORDS_H__870A488E_084E_4EAB_8162_25A1DDF2CD74__INCLUDED_)
