AC_INIT(FULL-PACKAGE-NAME, VERSION, BUG-REPORT-ADDRESS)
AM_INIT_AUTOMAKE(0.3)
AM_CONFIG_HEADER(config.h)
#if you use expat parser
CFLAGS="-Wall -Wshadow -DENABLE_AXIS_EXCEPTION -D__AXISTRACE__"
CPPFLAGS="-Wall -Wshadow -DENABLE_AXIS_EXCEPTION -D__AXISTRACE__"
LDFLAGS="-s -L$EXPAT_HOME/lib -lexpat -lstdc++"
AC_PROG_CC
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_LIBTOOL

#if you use apache2

#AC_OUTPUT(Makefile src/Makefile src/common/Makefile src/soap/Makefile src/wsdd/Makefile src/xml/Makefile src/transport/Makefile src/transport/axis/Makefile src/engine/Makefile src/engine/server/Makefile src/engine/client/Makefile  src/server/Makefile src/server/apache2/Makefile src/server/simple_axis_server/Makefile src/server/adminservice/Makefile src/client/Makefile src/client/adminclient/Makefile src/xml/expat/Makefile src/xml/xerces/Makefile)

#if you use apache1.3

AC_OUTPUT(Makefile src/Makefile src/common/Makefile src/soap/Makefile src/wsdd/Makefile src/xml/Makefile src/transport/Makefile src/transport/axis/Makefile src/engine/Makefile src/engine/server/Makefile src/engine/client/Makefile  src/server/Makefile src/server/apache/Makefile src/server/simple_axis_server/Makefile src/server/adminservice/Makefile src/client/Makefile src/client/adminclient/Makefile src/xml/expat/Makefile src/xml/xerces/Makefile)

