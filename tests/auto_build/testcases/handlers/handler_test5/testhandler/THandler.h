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
 *
 *
 * @author Andrew Perry (perryan@uk.ibm.com)
 *
 *****************************************************************************
 * Test Logic.
 * Set a property in the request flow and get it in the response flow and 
 * make sure they are the same.
 *
 * Test success is measured by comparing the actual response with an expected
 * response. So on failure just write anything to stdout and the test will 
 * fail.
 *****************************************************************************
 *
 */

#if !defined(_THANDLER_H____OF_AXIS_INCLUDED_)
#define _THANDLER_H____OF_AXIS_INCLUDED_

#include <axis/Handler.hpp>

AXIS_CPP_NAMESPACE_USE

class THandler : public Handler
{
public:
	int AXISCALL fini();
	int AXISCALL init();
	void AXISCALL onFault(void* pvIMsg);
	int AXISCALL invoke(void* pvIMsg);
	void setOptionList(const map<string, string>* OptionList);
	const string& getOption(const string& sArg);
	THandler();
	virtual ~THandler();

protected:
    string m_sEmpty;   

};

#endif // !defined(_THANDLER_H____OF_AXIS_INCLUDED_)
