sh autogen.sh
sh runconfig
make
make install
strip -g sslclient cbase
