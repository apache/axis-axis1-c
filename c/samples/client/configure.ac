AC_INIT(FULL-PACKAGE-NAME, VERSION, BUG-REPORT-ADDRESS)
AM_INIT_AUTOMAKE(0.3)
AM_CONFIG_HEADER(config.h)
CFLAGS="-Wshadow -Wall -pedantic -ansi"
CPPFLAGS="-Wshadow -Wall -pedantic -ansi"
#if you are using expat parser
LDFLAGS="-s -L$AXISCPP_HOME/bin -laxiscpp_client -L$EXPAT_HOME/lib -lexpat -ldl -lstdc++"
#if you are using xercesc parser
#LDFLAGS="-s -L$AXISCPP_HOME/bin -laxiscpp_client -L$XERCESC_HOME/lib -lxerces-c -ldl -lstdc++"
AC_PROG_CC
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_LIBTOOL
AC_OUTPUT(Makefile interoptests/Makefile interoptests/base/Makefile interoptests/cbase/Makefile interoptests/groupB/Makefile interoptests/cgroupB/Makefile interoptests/doclitbase/Makefile interoptests/doclitgroupB/Makefile simple/Makefile)
