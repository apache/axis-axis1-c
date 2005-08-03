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
 * @author Dasarath Weerathunga (dasarath@opensource.lk)
 *
 */

#include "FileInputStream.hpp"

FileInputStream::FileInputStream (FILE * s)
{
  this->s = s;
  if (!s)
    throw new XmlPullParserException ();
}



FileInputStream::~FileInputStream ()
{
  fclose (s);
}


int
FileInputStream::read (char *buffer, int offset, int length)
{
  return fread (buffer + offset, 1, length, s);
}
