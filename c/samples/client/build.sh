sh autogen.sh
sh runconfig
make
make install
strip -g sslclient base cbase groupb cgroupb
