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

#include <axis/AxisUserAPI.hpp>

AXIS_CPP_NAMESPACE_START 

/*
 * xsd_base64Binary, xsd_hexBinary and AnyType probably should own the 
 * storage that they address, in which case their destructors should free it
 * and their copy constructors should new storage. Also the = method would
 * need to be overloaded as well. Also their constructors would need to new
 * storage. The users of these classes would have to be checked to make sure
 * they don't new/delete the storage owned by these classes. Also methods
 * in SoapDeSerializer (for example) copy these classes around which would 
 * invoke these constructors excessively. So instead those methods should 
 * pass these classes around by reference instead. xsd_hexBinary and 
 * xsd__base64Binary are very similar and could share an implementation
 * which they both inherit from. Maybe these classes could have private data
 * and overload the [] operator and size() methods.
 */
xsd__base64Binary::xsd__base64Binary() { 
  __ptr = 0;
  __size = 0;
}

xsd__base64Binary::~xsd__base64Binary() { 
}

xsd__hexBinary::xsd__hexBinary() { 
  __ptr = 0;
  __size = 0;
}

xsd__hexBinary::~xsd__hexBinary() { 
}

AnyType::AnyType() { 
  _array = 0;
  _size = 0;
}

AnyType::~AnyType() { 
}

AXIS_CPP_NAMESPACE_END
