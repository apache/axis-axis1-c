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
 * @author Mark Whitlock
 */

#if !defined(CONTENTIDSET_H_INCLUDED_)
#define CONTENTIDSET_H_INCLUDED_

#include <list>
#include <string>
#include <axis/GDefine.hpp>

using namespace std;
AXIS_CPP_NAMESPACE_START

/**
 * ContentIdSet is the set of MIME Content-Ids for all attachments in a MIME message.
 * Each Content-Id must be unique within the MIME message. This class ensures uniqueness
 * by providing a registerId method which fails when the content id has already been 
 * registered. Content ids can be automatically generated by the generate method.
 *
 * The WS-I profile specifies the format of Content-Ids. This class should implement
 * those rules.
 */
class ContentIdSet
{
public:
	ContentIdSet();
	virtual ~ContentIdSet();
	void registerId(const char* id);
	const char *generateId();
	void clearAll();
private:	
	list<const char*> m_set;
	int m_maxId;
};

AXIS_CPP_NAMESPACE_END

#endif // !defined(CONTENTIDSET_H_INCLUDED_)
