sh autogen.sh
sh runconfig
make
make install
strip -g bin/*.so.*
