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

#if !defined(AXIS_HEXCODER_H____INCLUDED_)
#define AXIS_HEXCODER_H____INCLUDED_

int Hex_Encode(char * coded_dst, const unsigned char *plain_src,
               int len_plain_src);
int Hex_Decode(unsigned char * plain_dst, const char *coded_src);

#endif
