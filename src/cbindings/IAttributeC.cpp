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

#include <axis/IAttribute.hpp>
AXIS_CPP_NAMESPACE_USE

extern "C" {
#include <axis/GDefine.h>
#include <axis/IAttribute.h>

AXISC_STORAGE_CLASS_INFO void axiscDestroyIAttribute(AXISCHANDLE attribute) {
	IAttribute *attr = (IAttribute*)attribute;
	delete attr;
}

AXISC_STORAGE_CLASS_INFO int axiscSetValueIAttribute(AXISCHANDLE attribute, const AxiscChar * value) {
	if(!value)
	{
		return AXIS_FAIL;
	}
	IAttribute *attr = (IAttribute*)attribute;
	attr->setValue(value);
	
	return AXIS_SUCCESS;
}

AXISC_STORAGE_CLASS_INFO int axiscSetUriIAttribute(AXISCHANDLE attribute, const AxiscChar * uri) {
	if(!uri)
	{
		return AXIS_FAIL;
	}
	IAttribute *attr = (IAttribute*)attribute;
	attr->setURI(uri);
	return AXIS_SUCCESS;
}


AXISC_STORAGE_CLASS_INFO int axiscSetPrefixIAttribute(AXISCHANDLE attribute, const AxiscChar * prefix) {
	if(!prefix)
	{
		return AXIS_FAIL;
	}
	
	IAttribute *attr = (IAttribute*)attribute;
	attr->setPrefix(prefix);
	return AXIS_SUCCESS;
}

AXISC_STORAGE_CLASS_INFO int axiscSetLocalNameIAttribute(AXISCHANDLE attribute, const AxiscChar * localname) {
	if(!localname)
	{
		return AXIS_FAIL;
	}
	IAttribute *attr = (IAttribute*)attribute;
	attr->setLocalName(localname);
	return AXIS_SUCCESS;
}

AXISC_STORAGE_CLASS_INFO const AxiscChar * axiscGetValueIAttribute(AXISCHANDLE attribute) {
	IAttribute *attr = (IAttribute*)attribute;
	return attr->getValue();
}

AXISC_STORAGE_CLASS_INFO const AxiscChar * axiscGetUri(AXISCHANDLE attribute) {
	IAttribute *attr = (IAttribute*)attribute;
	return attr->getURI();
}

AXISC_STORAGE_CLASS_INFO const AxiscChar * axiscGetPrefixIAttribute(AXISCHANDLE attribute) {
	IAttribute *attr = (IAttribute*)attribute;
	return attr->getPrefix();
}

AXISC_STORAGE_CLASS_INFO const AxiscChar * axiscGetLocalNameIAttribute(AXISCHANDLE attribute) {
	IAttribute *attr = (IAttribute*)attribute;
	return attr->getLocalName();
}

}
