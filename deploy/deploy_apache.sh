#!/bin/bash

rm /usr/local/apache/libexec/libaxiscpp_mod.so
rm webservices/libAdminService.so
rm libs/libserver_engine.so
rm libs/libaxis_transport.so
rm libs/libaxis_xmlparser.so
cp -f $AXISCPP_HOME/bin/libAdminService.so webservices/
cp -f $AXISCPP_HOME/bin/libserver_engine.so libs/
cp -f $AXISCPP_HOME/bin/libaxiscpp_mod.so /usr/local/apache/libexec/
cp -f $AXISCPP_HOME/bin/libaxis_transport.so libs/
cp -f $AXISCPP_HOME/bin/libaxis_expat.so libs/libaxis_xmlparser.so
/usr/local/apache/bin/apachectl stop
sleep 2
/usr/local/apache/bin/apachectl start
