AC_INIT(FULL-PACKAGE-NAME, VERSION, BUG-REPORT-ADDRESS)
AM_INIT_AUTOMAKE(0.3)
AM_CONFIG_HEADER(config.h)

AC_MSG_CHECKING(whether to use apache2 as server transport)
AC_ARG_ENABLE(apache2, [  --enable-apache2        use apache2 as server transport.],
[ case "${enableval}" in
  no)
    AC_MSG_RESULT(no)
    APACHE2BUILD=""
    ;;
  *)
    AC_MSG_RESULT(yes)
    dnl find the apache2 include dir in /usr/local/apache2
    if test -d '/usr/local/apache2/include'; then
        apache2inc="-I/usr/local/apache2/include"
    dnl else find it in the APACHE2_HOME env variable
    elif test -d ${APACHE2_HOME}; then
        apache2inc="-I${APACHE2_HOME}/include"
    fi
    APACHE2BUILD="apache2"
    ;;
  esac ],
  AC_MSG_RESULT(no)
)

AC_MSG_CHECKING(whether to use apache as server transport)
AC_ARG_ENABLE(apache, [  --enable-apache        use apache as server transport.],
[ case "${enableval}" in
  no)
    AC_MSG_RESULT(no)
    APACHEBUILD=""
    ;;
  *)
    AC_MSG_RESULT(yes)
    dnl find the apache include dir in /usr/local/apache
    if test -d '/usr/local/apache/include'; then
        apacheinc="-I/usr/local/apache/include"
    dnl else find it in the APACHE_HOME env variable
    elif test -d ${APACHE_HOME}; then
        apacheinc="-I${APACHE_HOME}/include"
    fi
    APACHEBUILD="apache"
    ;;
  esac ],
  AC_MSG_RESULT(no)
)

AC_MSG_CHECKING(whether to build xercesc parser library)
AC_ARG_ENABLE(xercesc, [  --enable-xercesc    build xercesc parser library.],
[ case "${enableval}" in
  no)
    AC_MSG_RESULT(no)
    XERCESCBUILD=""
    ;;
  *)
    AC_MSG_RESULT(yes)
    dnl find the xercesc include dir in XERCESC_HOME
    if test -d ${XERCESC_HOME}; then
        xercescinc="-I${XERCESC_HOME}/include"
        xercesclib="-L${XERCESC_HOME}/lib"
    fi
    XERCESCBUILD="xerces"
    
    ;;
  esac ],
  AC_MSG_RESULT(no)
)

AC_MSG_CHECKING(whether to build expat parser library)
AC_ARG_ENABLE(expat, [  --enable-expat        build expat parser library.],
[ case "${enableval}" in
  no)
    AC_MSG_RESULT(no)
    EXPATBUILD=""
    ;;
  *)
    AC_MSG_RESULT(yes)
    dnl find the expat include dir in EXPAT_HOME
    if test -d ${EXPAT_HOME}; then
        expatinc="-I${EXPAT_HOME}/include"
        expatlib="-I${EXPAT_HOME}/lib"
    fi
    EXPATBUILD="expat"
    
    ;;
  esac ],
  AC_MSG_RESULT(no)
)

APACHE2INC=$apache2inc
APACHEINC=$apacheinc
XERCESCINC=$xercescinc
XERCESCLIB=$xercesclib
EXPATINC=$expatinc
EXPATLIB=$expatlib
LINKCLIENTLIB="-L${AXISCPP_DEPLOY}/lib -laxiscpp_client -ldl"
AC_SUBST(APACHE2INC)
AC_SUBST(APACHEINC)
AC_SUBST(XERCESCINC)
AC_SUBST(XERCESCLIB)
AC_SUBST(EXPATINC)
AC_SUBST(EXPATLIB)
AC_SUBST(XERCESCBUILD)
AC_SUBST(EXPATBUILD)
AC_SUBST(APACHE2BUILD)
AC_SUBST(APACHEBUILD)
AC_SUBST(LINKCLIENTLIB)

CFLAGS="-Wall -Wshadow -DENABLE_AXISTRACE"
CPPFLAGS="-Wall -Wshadow -DENABLE_AXISTRACE"
LDFLAGS="-s -lstdc++"
AC_PROG_CC
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_LIBTOOL

AC_OUTPUT(Makefile \
    src/Makefile \
    src/common/Makefile \
    src/soap/Makefile \
    src/wsdd/Makefile \
    src/xml/Makefile \
    src/transport/Makefile \
    src/transport/axis/Makefile \
    src/engine/Makefile \
    src/engine/server/Makefile \
    src/engine/client/Makefile  \
    src/server/Makefile \
    src/server/apache2/Makefile \
    src/server/apache/Makefile \
    src/server/simple_axis_server/Makefile \
    src/server/adminservice/Makefile \
    src/client/Makefile \
    src/client/adminclient/Makefile \
    src/xml/expat/Makefile \
    src/xml/xerces/Makefile \
    samples/Makefile \
    samples/server/Makefile \
    samples/server/interoptests/Makefile \
    samples/server/interoptests/base/Makefile \
    samples/server/interoptests/cbase/Makefile \
    samples/server/interoptests/groupB/Makefile \
    samples/server/interoptests/cgroupB/Makefile \
    samples/server/interoptests/doclitbase/Makefile \
    samples/server/interoptests/doclitgroupB/Makefile \
    samples/server/simple/Makefile \
    samples/server/rpcfault/Makefile \
    samples/server/doclitfault/Makefile \
    samples/server/echoStringHeaderHandler/Makefile \
    samples/client/Makefile \
    samples/client/interoptests/Makefile \
    samples/client/interoptests/base/Makefile \
    samples/client/interoptests/cbase/Makefile \
    samples/client/interoptests/groupB/Makefile \
    samples/client/interoptests/cgroupB/Makefile \
    samples/client/interoptests/doclitbase/Makefile \
    samples/client/interoptests/doclitgroupB/Makefile \
    samples/client/simple/Makefile \
    samples/client/rpcfault/Makefile \
    samples/client/doclitfault/Makefile \
    samples/client/testHandler/Makefile)
