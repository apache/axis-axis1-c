AC_INIT(axis-c-src, 1-3-beta-linux, BUG-REPORT-ADDRESS)
AM_INIT_AUTOMAKE(0.3)
AM_CONFIG_HEADER(config.h)
PACKAGE=axis-c-src
AC_MSG_CHECKING(whether to use apache2 as server transport)
AC_ARG_WITH(apache2,
[  --with-apache2[=PATH]      use apache2 as server transport.],
[ case "$withval" in
  no)
    AC_MSG_RESULT(no)
    APACHE2BUILD=""
    ;;
  *)
    AC_MSG_RESULT(yes)
    dnl Find apache2 include dir in the path pointed by APACHE2_HOME env variable
    if test -d $withval; then
        apache2inc="-I$withval/include"
    dnl else find the apache2 include dir in /usr/local/apache2
    elif test -d '/usr/local/apache2/include'; then
        apache2inc="-I/usr/local/apache2/include"
    else
        AC_MSG_ERROR(could not find apache2. stop)
    fi
    APACHE2BUILD="apache2"
    ;;
  esac ],
  AC_MSG_RESULT(no)
)

AC_MSG_CHECKING(whether to user apache as server transport.)
AC_ARG_WITH(apache,
[  --with-apache[=PATH]      use apache as server transport.],
[ case "$withval" in
  no)
    AC_MSG_RESULT(no)
    APACHEBUILD=""
    ;;
  *)
    AC_MSG_RESULT(yes)
    dnl Find apache include dir in the path pointed by APACHE_HOME env variable
    if test -d $withval; then
        apacheinc="-I$withval/include"
    dnl else find the apache include dir in /usr/local/apache
    elif test -d '/usr/local/apache/include'; then
        apacheinc="-I/usr/local/apache/include"
    else
        AC_MSG_ERROR(could not find apache. stop)
        exit
    fi
    APACHEBUILD="apache"
    ;;
  esac ],
  AC_MSG_RESULT(no)
)

AC_MSG_CHECKING(whether to build expat parser library.)
AC_ARG_WITH(expat,
[  --with-expat[=PATH]      build expat parser library.],
[ case "$withval" in
  no)
    AC_MSG_RESULT(no)
    EXPATBUILD=""
    ;;
  *)
    AC_MSG_RESULT(yes)
    dnl test for  expat directory
    if test -d $withval; then
        expatinc="-I$withval/include"
        expatlib="-L$withval/lib -lexpat -ldl"
    else
        AC_MSG_ERROR(could not find expat. stop)
    fi
    EXPATBUILD="expat"
  
  ;;
  esac ],
  AC_MSG_RESULT(no)
)

AC_MSG_CHECKING(whether to build xercesc parser library.)
AC_ARG_WITH(xercesc,
[  --with-xercesc[=PATH]      build xercesc parser library.],
[ case "$withval" in
  no)
    AC_MSG_RESULT(no)
    XERCESCBUILD=""
    ;;
  *)
    AC_MSG_RESULT(yes)
    dnl test for  xercesc directory
    if test -d $withval; then
        xercescinc="-I$withval/include"
        xercesclib="-L$withval/lib -lxerces-c -ldl"
    else
        AC_MSG_ERROR(could not find xercesc. stop)
    fi
    XERCESCBUILD="xerces"
  
  ;;
  esac ],
  AC_MSG_RESULT(no)
)

AC_MSG_CHECKING(whether to build tspp xml parser library)
AC_ARG_ENABLE(tspp, [  --enable-tspp    build tspp xml parser library.],
[ case "${enableval}" in
  no)
    AC_MSG_RESULT(no)
    TSPPBUILD=""
    ;;
  *)
    AC_MSG_RESULT(yes)
    TSPPBUILD="tspp"

    ;;
  esac ],
  AC_MSG_RESULT(no)
  TSPPBUILD="tspp"
)

AC_MSG_CHECKING(whether to build test cases)
AC_ARG_ENABLE(testcases, [  --enable-testcases    build test cases.],
[ case "${enableval}" in
  no)
    AC_MSG_RESULT(no)
    TESTCASESBUILD=""
    ;;
  *)
    AC_MSG_RESULT(yes)
    TESTCASESBUILD="tests"
    
    ;;
  esac ],
  AC_MSG_RESULT(no)
  TESTCASESBUILD="tests"
)

AC_MSG_CHECKING(whether to build samples)
AC_ARG_ENABLE(samples, [  --enable-samples    build samples.],
[ case "${enableval}" in
  no)
    AC_MSG_RESULT(no)
    SAMPLESBUILD=""
    ;;
  *)
    AC_MSG_RESULT(yes)
    SAMPLESBUILD="samples"
    
    ;;
  esac ],
  AC_MSG_RESULT(no)
  SAMPLESBUILD="samples"
)

AC_MSG_CHECKING(whether to build libwww client transport library)
AC_ARG_ENABLE(libwww, [  --enable-libwww    build libwww client transport library.],
[ case "${enableval}" in
  no)
    AC_MSG_RESULT(no)
    LIBWWWBUILD=""
    ;;
  *)
    AC_MSG_RESULT(yes)
    LIBWWWBUILD="libwww"
    
    ;;
  esac ],
  AC_MSG_RESULT(no)
  LIBWWWBUILD=""
)

AC_MSG_CHECKING(whether write to log)
AC_ARG_ENABLE(log, [  --enable-log    enable log facility.],
[ case "${enableval}" in
  no)
    AC_MSG_RESULT(no)
    ENABLELOGGING=""
    ;;
  *)
    AC_MSG_RESULT(yes)
    ENABLELOGGING="-DENABLE_AXISTRACE"
    
    ;;
  esac ],
  AC_MSG_RESULT(no)
  ENABLELOGGING="-DENABLE_AXISTRACE"
)

APACHE2INC=$apache2inc
APACHEINC=$apacheinc
XERCESCINC=$xercescinc
XERCESCLIB=$xercesclib
EXPATINC=$expatinc
EXPATLIB=$expatlib
LINKCLIENTLIB="-L${AXISCPP_HOME}/src/engine/client -laxiscpp_client -ldl"
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
AC_SUBST(TESTCASESBUILD)
AC_SUBST(SAMPLESBUILD)
AC_SUBST(LIBWWWBUILD)
AC_SUBST(TSPPBUILD)

CFLAGS="-Wall -Wshadow ${ENABLELOGGING}"
CPPFLAGS="-Wall -Wshadow ${ENABLELOGGING}"
LDFLAGS="-lstdc++"
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
    src/transport/axis2/Makefile \
    src/transport/axis2/ipv6/Makefile \
    src/transport/libwww/Makefile \
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
    src/xml/tspp/Makefile \
    samples/Makefile \
    samples/server/Makefile \
    samples/server/interoptests/Makefile \
    samples/server/interoptests/base/Makefile \
    samples/server/interoptests/groupB/Makefile \
    samples/server/interoptests/doclitbase/Makefile \
    samples/server/interoptests/doclitgroupB/Makefile \
    samples/server/simple/Makefile \
    samples/server/array/Makefile \
    samples/server/ref/Makefile \
    samples/server/rpcfault/Makefile \
    samples/server/doclitfault/Makefile \
    samples/server/echoStringHeaderHandler/Makefile \
    samples/client/Makefile \
    samples/client/interoptests/Makefile \
    samples/client/interoptests/base/Makefile \
    samples/client/interoptests/groupB/Makefile \
    samples/client/interoptests/doclitbase/Makefile \
    samples/client/interoptests/doclitgroupB/Makefile \
    samples/client/simple/Makefile \
    samples/client/array/Makefile \
    samples/client/ref/Makefile \
    samples/client/rpcfault/Makefile \
    samples/client/doclitfault/Makefile \
    samples/client/testHandler/Makefile \
    tests/Makefile \
    tests/client/Makefile \
    tests/client/stubTest/Makefile \
    tests/client/stubTest/stubBase/Makefile \
    tests/client/interop/Makefile \
    tests/client/interop/round1/Makefile \
    tests/client/interop/round1/gen_src/Makefile \
    tests/client/threadSafe/Makefile \
    tests/client/threadSafe/gen_src/Makefile
    tests/client/fault_mapping/Makefile \
    tests/client/fault_mapping/gen_src/Makefile \
    tests/client/exceptionTest/Makefile \
    tests/client/exceptionTest/gen_src/Makefile \
    tests/client/soapHeader/Makefile \
    tests/client/soapHeader/test1/Makefile \
    tests/client/soapHeader/test1/rpc/Makefile \
    tests/client/soapHeader/test2/Makefile \
    tests/client/soapHeader/test2/rpc/Makefile \
    tests/client/soapHeader/test3/Makefile \
    tests/client/soapHeader/test3/rpc/Makefile \
    tests/client/soapHeader/test4/Makefile \
    tests/client/soapHeader/test4/rpc/Makefile \
    tests/client/soapHeader/test6/Makefile \
    tests/client/soapHeader/test6/rpc/Makefile \
    tests/client/soapHeader/test8/Makefile \
    tests/client/soapHeader/test8/rpc/Makefile \
    tests/client/soapHeader/test9/Makefile \
    tests/client/soapHeader/test9/rpc/Makefile \
    tests/client/soapHeader/test10/Makefile \
    tests/client/soapHeader/test10/rpc/Makefile \
    tests/client/xsdAnyTest1/Makefile \
    tests/client/xsdAnyTest1/gen_src/Makefile \
    tests/client/httpHeader/Makefile \
    tests/client/httpHeader/test1/Makefile \
    tests/client/httpHeader/test1/rpc/Makefile \
    tests/client/httpHeader/test2/Makefile \
    tests/client/httpHeader/test2/rpc/Makefile \
    tests/client/httpHeader/test3/Makefile \
    tests/client/httpHeader/test3/rpc/Makefile \
    tests/client/httpHeader/test4/Makefile \
    tests/client/httpHeader/test4/rpc/Makefile \
    tests/client/httpHeader/test5/Makefile \
    tests/client/httpHeader/test5/rpc/Makefile \
    tests/client/httpHeader/test7/Makefile \
    tests/client/httpHeader/test7/rpc/Makefile \
    tests/client/httpHeader/test8/Makefile \
    tests/client/httpHeader/test8/rpc/Makefile \
    tests/server/Makefile \
    tests/server/exceptionTest/Makefile \
    tests/server/exceptionTest/gen_src/Makefile \
    tests/server/xsdAnyTest1/Makefile \
    tests/server/xsdAnyTest1/gen_src/Makefile)
