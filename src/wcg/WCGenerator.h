// WCGenerator.h: interface for the WCGenerator class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WCGENERATOR_H__720250A8_3F71_4C41_88BD_BB590C1E44A8__INCLUDED_)
#define AFX_WCGENERATOR_H__720250A8_3F71_4C41_88BD_BB590C1E44A8__INCLUDED_

#include <string>
using namespace std;

class WCGenerator  
{
public:
	int DoDeploy();
	void SetWSDD(string& sWsddfile);
	void SetWSLibrary(string& sLibfile);
	void SetWSDefinition(string& sHeaderfile);
	WCGenerator();
	virtual ~WCGenerator();

};

#endif // !defined(AFX_WCGENERATOR_H__720250A8_3F71_4C41_88BD_BB590C1E44A8__INCLUDED_)
