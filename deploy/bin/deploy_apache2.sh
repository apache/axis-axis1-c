#!/bin/bash

rm /usr/local/apache2/modules/libaxiscpp_mod2.so
rm ../lib/libaxis_xmlparser.so
cp -f ../lib/libaxiscpp_mod2.so /usr/local/apache2/modules/
cp -f ../lib/libaxis_expat.so ../lib/libaxis_xmlparser.so
if test -d ../log; then
    echo "Checking log folder..."
else
    mkdir ../log
fi
chmod 777 ../log
cp -f ../etc/server.wsdd_linux ../etc/server.wsdd
cp -f ../etc/client.wsdd_linux ../etc/client.wsdd
cp -f ../etc/axiscpp.conf_linux ../etc/axiscpp.conf
/usr/local/apache2/bin/apachectl stop
sleep 2
/usr/local/apache2/bin/apachectl start
