lib_LTLIBRARIES = libaxis_LibWWWTransport.la
AM_CPPFLAGS = $(CPPFLAGS) -DHT_EXT_CONTINUE
libaxis_LibWWWTransport_la_SOURCES = LibWWWTransport.cpp
#libaxis_LibWWWTransport_la_LIBADD = "`libwww-config  --libs`"
libaxis_LibWWWTransport_la_LDFLAGS="-L`libwww-config  --prefix`/lib -lwwwinit -lwwwapp -lwwwhtml -lwwwtelnet -lwwwnews -lwwwhttp -lwwwmime -lwwwgopher -lwwwftp -lwwwfile -lwwwdir -lwwwcache -lwwwstream -lwwwmux -lwwwtrans -lwwwcore -lwwwutils -lmd5 -ldl"
#libaxis_LibWWWTransport_la_LDFLAGS = "`libwww-config  --libs`"
INCLUDES = -I$(AXISCPP_HOME)/include `libwww-config --cflags`

