#!/bin/bash

rm /usr/local/apache/libexec/libaxiscpp_mod.so
rm ../lib/libaxis_xmlparser.so
cp -f ../lib/libaxiscpp_mod.so /usr/local/apache/libexec/
cp -f ../lib/libaxis_expat.so ../lib/libaxis_xmlparser.so
if test -d ../log; then
    echo "check whether log folder exists"
else
    mkdir ../log
fi
chmod 777 ../log
/usr/local/apache/bin/apachectl stop
sleep 2
/usr/local/apache/bin/apachectl start
