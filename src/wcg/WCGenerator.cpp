// WCGenerator.cpp: implementation of the WCGenerator class.
//
//////////////////////////////////////////////////////////////////////
#pragma warning (disable : 4786)

#include "WCGenerator.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#include "WSClass.h"
#include "TranslationUnit.h"

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