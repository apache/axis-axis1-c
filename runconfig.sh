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
# Following is the configure options with a brief description
# --prefix=path to your installation folder. default is /usr/ocal/axiscpp_deploy
# --enable-tspp    Whether tspp parser library should be built. by default this is not built
# --enable-axis3    build axis3 client transport library. default=no
# --enable-testcases    build test cases. default=no
# --enable-samples    build samples. default=yes
# --enable-axis3    build axis3 client transport library. default=no
# --with-apache2=PATH    path to apache2 installation. if not given apache2 module library is not built.
# --with-apache=PATH    path to apache1 installation. if not given apache1 module library is not built.
# --with-xercesc=PATH    path to xercesc installation. if not given xercesc parser library is not built.
# --with-cppunit=PATH      build cppunit tests. this option is valid only if --enable-testcases option is yes
# --with-axis2-ssl=PATH      build axis2 secure  transport channel library.
# --with-axis3-ssl=PATH      build axis3 secure transport channel library. this can be enabled only if --enable-axis3
#                            option is yes.
 

echo "run configure with the options"
echo     "--prefix=/usr/local/axiscpp_deploy"
echo     "--with-apache2=/usr/local/apache2"
echo     "--with-xercesc=/usr/local/xerces-c."
echo     "If you need to configure with different/more options modify/add before run" 
echo     ""
./configure --prefix=/usr/local/axiscpp_deploy \
    --with-apache2=/usr/local/apache2 \
    --with-xercesc=/usr/local/xerces-c

