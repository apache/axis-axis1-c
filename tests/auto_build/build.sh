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

echo "----------------------------------"
echo "build server, client and samples"
echo "----------------------------------"
echo "run configure"
./configure --prefix=/usr/local/axiscpp_deploy \
    --with-apache2=/usr/local/apache2 \
    --with-apache=/usr/local/apache \
    --with-expat=/usr/local/expat1957 \
    --with-xercesc=/usr/local/xerces-c \
    --enable-libwww=no
echo "make"
make 2> build_errors

