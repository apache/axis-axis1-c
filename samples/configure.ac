AC_INIT(FULL-PACKAGE-NAME, VERSION, BUG-REPORT-ADDRESS)
AM_INIT_AUTOMAKE(0.3)
AM_CONFIG_HEADER(config.h)




LINKCLIENTLIB="-L${AXISCPP_DEPLOY}/lib -laxiscpp_client -ldl"

LDFLAGS="-lstdc++"
AC_PROG_CC
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_LIBTOOL

AC_OUTPUT(Makefile \
    server/Makefile \
    server/interoptests/Makefile \
    server/interoptests/base/Makefile \
    server/interoptests/cbase/Makefile \
    server/interoptests/groupB/Makefile \
    server/interoptests/cgroupB/Makefile \
    server/interoptests/doclitbase/Makefile \
    server/interoptests/doclitgroupB/Makefile \
    server/simple/Makefile \
    server/rpcfault/Makefile \
    server/doclitfault/Makefile \
    server/echoStringHeaderHandler/Makefile \
    client/Makefile \
    client/interoptests/Makefile \
    client/interoptests/base/Makefile \
    client/interoptests/cbase/Makefile \
    client/interoptests/groupB/Makefile \
    client/interoptests/cgroupB/Makefile \
    client/interoptests/doclitbase/Makefile \
    client/interoptests/doclitgroupB/Makefile \
    client/simple/Makefile \
    client/rpcfault/Makefile \
    client/doclitfault/Makefile \
    client/testHandler/Makefile)
