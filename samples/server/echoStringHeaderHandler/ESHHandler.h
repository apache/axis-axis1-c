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
 * @author Roshan Weerasuriya (roshan@jkcs.slt.lk, roshan@opensource.lk)
 *
 */

/*
 * Revision 1.1  2004/06/14 roshan
 * Removed the declarations of getOption(const string& sArg) and 
 *  setOptionList(const map<string, string>* OptionList), because these methods
 *  are not needed to be implemented by the users. These are generic methods.
 *  Added the implementations of these methods to the Handler base class.
 */

#if !defined(_ESHHANDLER_H____OF_AXIS_INCLUDED_)
#define _ESHHANDLER_H____OF_AXIS_INCLUDED_

#include <axis/server/Handler.hpp>

AXIS_CPP_NAMESPACE_USE

class ESHHandler : public Handler
{
public:
	int AXISCALL fini();
	int AXISCALL init();
	void AXISCALL onFault(void* pvIMsg);
	int AXISCALL invoke(void* pvIMsg);
	ESHHandler();
	virtual ~ESHHandler();    
};

#endif // !defined(_ESHHANDLER_H____OF_AXIS_INCLUDED_)
