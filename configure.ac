AC_INIT(FULL-PACKAGE-NAME, VERSION, BUG-REPORT-ADDRESS)
AM_INIT_AUTOMAKE(0.3)
AM_CONFIG_HEADER(config.h)
#if you use expat parser
CFLAGS="-Wall -Wshadow -DENABLE_AXIS_EXCEPTION -DENABLE_AXISTRACE"
CPPFLAGS="-Wall -Wshadow -DENABLE_AXIS_EXCEPTION -DENABLE_AXISTRACE"
LDFLAGS="-s -lstdc++"
AC_PROG_CC
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_LIBTOOL

#{apache2 block starts
#if you use apache2

#if you need to build both expat and xerces libraries

#AC_OUTPUT(Makefile src/Makefile src/common/Makefile src/soap/Makefile src/wsdd/Makefile src/xml/Makefile src/transport/Makefile src/transport/axis/Makefile src/engine/Makefile src/engine/server/Makefile src/engine/client/Makefile  src/server/Makefile src/server/apache2/Makefile src/server/simple_axis_server/Makefile src/server/adminservice/Makefile src/client/Makefile src/client/adminclient/Makefile src/xml/expat/Makefile src/xml/xerces/Makefile)

#if you need to build only expat

#AC_OUTPUT(Makefile src/Makefile src/common/Makefile src/soap/Makefile src/wsdd/Makefile src/xml/Makefile src/transport/Makefile src/transport/axis/Makefile src/engine/Makefile src/engine/server/Makefile src/engine/client/Makefile  src/server/Makefile src/server/apache2/Makefile src/server/simple_axis_server/Makefile src/server/adminservice/Makefile src/client/Makefile src/client/adminclient/Makefile src/xml/expat/Makefile)

#if you need to build only xerces

#AC_OUTPUT(Makefile src/Makefile src/common/Makefile src/soap/Makefile src/wsdd/Makefile src/xml/Makefile src/transport/Makefile src/transport/axis/Makefile src/engine/Makefile src/engine/server/Makefile src/engine/client/Makefile  src/server/Makefile src/server/apache2/Makefile src/server/simple_axis_server/Makefile src/server/adminservice/Makefile src/client/Makefile src/client/adminclient/Makefile src/xml/xerces/Makefile)

#}apache2 block ends

#{apache1.3 block starts
#if you use apache1.3

#if you need to build both expat and xerces libraries

AC_OUTPUT(Makefile src/Makefile src/common/Makefile src/soap/Makefile src/wsdd/Makefile src/xml/Makefile src/transport/Makefile src/transport/axis/Makefile src/engine/Makefile src/engine/server/Makefile src/engine/client/Makefile  src/server/Makefile src/server/apache/Makefile src/server/simple_axis_server/Makefile src/server/adminservice/Makefile src/client/Makefile src/client/adminclient/Makefile src/xml/expat/Makefile src/xml/xerces/Makefile)

#if you need to build only expat

#AC_OUTPUT(Makefile src/Makefile src/common/Makefile src/soap/Makefile src/wsdd/Makefile src/xml/Makefile src/transport/Makefile src/transport/axis/Makefile src/engine/Makefile src/engine/server/Makefile src/engine/client/Makefile  src/server/Makefile src/server/apache/Makefile src/server/simple_axis_server/Makefile src/server/adminservice/Makefile src/client/Makefile src/client/adminclient/Makefile src/xml/expat/Makefile)

#if you need to build only xerces

#AC_OUTPUT(Makefile src/Makefile src/common/Makefile src/soap/Makefile src/wsdd/Makefile src/xml/Makefile src/transport/Makefile src/transport/axis/Makefile src/engine/Makefile src/engine/server/Makefile src/engine/client/Makefile  src/server/Makefile src/server/apache/Makefile src/server/simple_axis_server/Makefile src/server/adminservice/Makefile src/client/Makefile src/client/adminclient/Makefile src/xml/xerces/Makefile)

#}apache1.3 block ends
