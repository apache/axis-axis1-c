rm /usr/local/apache2/modules/libaxiscpp_mod2.so
rm webservices/libAdminService.so
rm libs/libserver_engine.so
cp -f $AXISCPP_HOME/bin/libAdminService.so webservices/
cp -f $AXISCPP_HOME/bin/libserver_engine.so libs/
cp -f $AXISCPP_HOME/bin/libaxiscpp_mod2.so /usr/local/apache2/modules/
/usr/local/apache2/bin/apachectl stop
sleep 2
/usr/local/apache2/bin/apachectl start
