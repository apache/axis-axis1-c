#!/bin/bash

rm /usr/local/apache2/modules/libaxiscpp_mod2.so
rm lib/libaxis_xmlparser.so
cp -f lib/libaxiscpp_mod2.so /usr/local/apache2/modules/
cp -f lib/libaxis_expat.so lib/libaxis_xmlparser.so
/usr/local/apache2/bin/apachectl stop
sleep 2
/usr/local/apache2/bin/apachectl start
