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

/* WCGenerator.h: interface for the WCGenerator class. */


#if !defined(AXIS_WCGENERATOR_H__OF_AXIS_INCLUDED_)
#define AXIS_WCGENERATOR_H__OF_AXIS_INCLUDED_

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

#endif
