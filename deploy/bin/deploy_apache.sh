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

rm /usr/local/apache/libexec/libaxiscpp_mod.so
rm ../lib/libaxis_xmlparser.so
cp -f ../lib/libaxiscpp_mod.so /usr/local/apache/libexec/
cp -f ../lib/libaxis_expat.so ../lib/libaxis_xmlparser.so
cp -f ../etc/server.wsdd_linux ../etc/server.wsdd
cp -f ../etc/client.wsdd_linux ../etc/client.wsdd
cp -f ../etc/axiscpp.conf_linux ../etc/axiscpp.conf
/usr/local/apache/bin/apachectl stop
sleep 2
/usr/local/apache/bin/apachectl start
