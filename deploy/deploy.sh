rm ./libaxiscpp2_mod.so
rm ../Axis/webservices/libAdminService.so
rm ../Axis/libs/libserver_engine.so
cp -f $AXISCPP_HOME/bin/libAdminService.so ../Axis/webservices/
cp -f $AXISCPP_HOME/bin/libserver_engine.so ../Axis/libs/
cp -f $AXISCPP_HOME/bin/libaxiscpp_mod2.so ./
../bin/apachectl stop
sleep 2
../bin/apachectl start
