AC_INIT(FULL-PACKAGE-NAME, VERSION, BUG-REPORT-ADDRESS)
AM_INIT_AUTOMAKE(0.3)
AM_CONFIG_HEADER(config.h)
CFLAGS="-Wshadow -Wall -pedantic -ansi"
CPPFLAGS="-Wshadow -Wall -pedantic -ansi"
LDFLAGS="-s -L$AXISCPP_HOME/bin -laxiscpp_client -ldl -lstdc++"
AC_PROG_CC
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_LIBTOOL
AC_OUTPUT(Makefile client/Makefile client/stubTest/Makefile client/stubTest/stubBase/Makefile client/interop/Makefile client/interop/round1/Makefile client/threadSafe/Makefile client/fault_mapping/Makefile client/fault_mapping/gen_src/Makefile client/exceptionTest/Makefile client/exceptionTest/gen_src/Makefile)
