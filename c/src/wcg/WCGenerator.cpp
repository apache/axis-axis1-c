/*
 *   Copyright 2003-2004 The Apache Software Foundation.
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 */

/* WCGenerator.cpp: implementation of the WCGenerator class. */

#ifdef WIN32
#pragma warning (disable : 4786)
#endif

#include <axis/wcg/WCGenerator.h>

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
