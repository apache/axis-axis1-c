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

AXISC_STORAGE_CLASS_INFO void axiscSetValueIAttribute(AXISCHANDLE attribute, const AxiscChar * value) {
	IAttribute *attr = (IAttribute*)attribute;
	attr->setValue(value);
}

AXISC_STORAGE_CLASS_INFO void axiscSetUriIAttribute(AXISCHANDLE attribute, const AxiscChar * uri) {
	IAttribute *attr = (IAttribute*)attribute;
	attr->setURI(uri);
}

AXISC_STORAGE_CLASS_INFO void axiscSetPrefixIAttribute(AXISCHANDLE attribute, const AxiscChar * prefix) {
	IAttribute *attr = (IAttribute*)attribute;
	attr->setPrefix(prefix);
}

AXISC_STORAGE_CLASS_INFO void axiscSetLocalNameIAttribute(AXISCHANDLE attribute, const AxiscChar * localname) {
	IAttribute *attr = (IAttribute*)attribute;
	attr->setLocalName(localname);
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
