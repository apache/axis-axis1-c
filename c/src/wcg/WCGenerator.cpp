// WCGenerator.cpp: implementation of the WCGenerator class.
//
//////////////////////////////////////////////////////////////////////
#ifdef WIN32
#pragma warning (disable : 4786)
#endif

#include <axis/wcg/WCGenerator.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#include <axis/wcg/WSClass.h>
#include <axis/wcg/TranslationUnit.h>

WCGenerator::WCGenerator()
{

}

WCGenerator::~WCGenerator()
{

}

void WCGenerator::SetWSDefinition(string &sHeaderfile)
{

}

void WCGenerator::SetWSLibrary(string &sLibfile)
{

}

void WCGenerator::SetWSDD(string &sWsddfile)
{

}

int WCGenerator::DoDeploy()
{
	return 0;
}
/*
int main(int argc, char*argv[])
{
	WSClass* pCl = new WSClass();
	pCl->SetClassName(string("Test"));
	HeaderFile hf;
	hf.SetWSClass(pCl);
	hf.GenerateWrapperClassDef();
	return 0;
}
*/
