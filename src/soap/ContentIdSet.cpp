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

// !!! This include file must be first thing in file !!!
#include "../platforms/PlatformAutoSense.hpp"

#include <list>

#include "ContentIdSet.hpp"
#include "AxisSoapException.h"

#include "../common/AxisTrace.h"

using namespace std;
AXIS_CPP_NAMESPACE_START

ContentIdSet::ContentIdSet()
{
	m_maxId = 0;
}

ContentIdSet::~ContentIdSet()
{
	clearAll();
}

void ContentIdSet::registerId(const char* id)
{
	for (list<const char*>::iterator it = m_set.begin(); it != m_set.end(); it++)
	{
		if ((*it) && 0==strcmp(id,*it)) throw AxisSoapException(CLIENT_MIME_CONTENT_ID_NOT_UNIQUE);
	}
	char *copy = new char[strlen(id)+1];
	strcpy(copy,id);
	m_set.push_back(const_cast<const char *>(copy));
}

const char *ContentIdSet::generateId()
{
	m_maxId++;
	char pszId[8];
	sprintf(pszId,"%u",m_maxId);
	bool found = true;
	while (found)
	{
		found = false;
		for (list<const char*>::iterator it = m_set.begin(); it != m_set.end(); it++)
		{
			if ((*it) && 0==strcmp(*it,pszId))
			{
				m_maxId++;
				sprintf(pszId,"%u",m_maxId);
				found = true;
				break;
			}
		}
	}

	char *copy = new char[strlen(pszId)+1];
	strcpy(copy,pszId);
	m_set.push_back(const_cast<const char *>(copy));
	return const_cast<const char *>(copy);
}

void ContentIdSet::clearAll()
{
	for (list<const char*>::iterator it = m_set.begin(); it != m_set.end(); it++)
	{
		char *id = const_cast<char*>(*it);
		delete [] id;
	}
	m_set.clear();
	m_maxId = 0;
}


AXIS_CPP_NAMESPACE_END


