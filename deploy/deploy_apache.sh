#!/bin/bash

rm /usr/local/apache/libexec/libaxiscpp_mod.so
rm lib/libaxis_xmlparser.so
cp -f lib/libaxiscpp_mod.so /usr/local/apache/libexec/
cp -f lib/libaxis_expat.so lib/libaxis_xmlparser.so
/usr/local/apache/bin/apachectl stop
sleep 2
/usr/local/apache/bin/apachectl start
