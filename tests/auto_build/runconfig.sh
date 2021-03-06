#!/bin/bash
#
#   Copyright 2003-2004 The Apache Software Foundation.
#
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#       http://www.apache.org/licenses/LICENSE-2.0
#
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an "AS IS" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.
#
#
#   @author Damitha Kumarage (damitha@opensource.lk, damitha@jkcsworld.com)
#

echo "run configure with the options"
echo     "--prefix=/usr/local/axiscpp_deploy"
echo     "--with-apache2=/usr/local/apache2"
echo     "--with-xercesc=/usr/local/xerces-c."
echo     "If you need to configure with different/more options modify/add before run" 
echo     ""
./configure --prefix=/home/damitha/programs/axiscpp_deploy \
    --with-apache2=/home/damitha/programs/apache2 \
    --with-xercesc=/usr/local/xerces-c

