AC_INIT(FULL-PACKAGE-NAME, VERSION, BUG-REPORT-ADDRESS)
AM_INIT_AUTOMAKE(0.3)
AM_CONFIG_HEADER(config.h)
CFLAGS="-Wshadow -Wall -pedantic -ansi"
CPPFLAGS="-Wshadow -Wall -pedantic -ansi"
LDFLAGS="-s -L$AXISCPP_HOME/lib/expat -lexpat -lltdl -lstdc++"
AC_PROG_CC
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_LIBTOOL
AC_OUTPUT(Makefile interoptests/Makefile interoptests/base/Makefile interoptests/cbase/Makefile interoptests/groupB/Makefile interoptests/cgroupB/Makefile interoptests/doclitbase/Makefile interoptests/doclitgroupB/Makefile)
