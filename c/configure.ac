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
    dnl Find apache2 include dir in the path pointed by APACHE2_HOME env variable
    if test -d ${APACHE2_HOME}; then
        apache2inc="-I${APACHE2_HOME}/include"
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

AC_MSG_CHECKING(whether to use apache as server transport)
AC_ARG_ENABLE(apache, [  --enable-apache        use apache as server transport.],
[ case "${enableval}" in
  no)
    AC_MSG_RESULT(no)
    APACHEBUILD=""
    ;;
  *)
    AC_MSG_RESULT(yes)
    dnl Find apache include dir in the path pointed by APACHE_HOME env variable
    if test -d ${APACHE_HOME}; then
        apacheinc="-I${APACHE_HOME}/include"
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
    else
        AC_MSG_ERROR(could not find xercesc. stop)
	exit
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
    else
        AC_MSG_ERROR(could not find expat. stop)
	exit
    fi
    EXPATBUILD="expat"
    
    ;;
  esac ],
  AC_MSG_RESULT(no)
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
)

if test -d "$prefix/conf"; then
cp deploy/axiscpp.conf_linux $prefix/conf/axiscpp.conf
else
mkdir $prefix/conf
cp deploy/conf/server.wsdd_linux $prefix/conf/server.wsdd
cp deploy/axiscpp.conf_linux $prefix/axiscpp.conf
cp deploy/deploy_apache2.sh $prefix
cp deploy/deploy_apache.sh $prefix
fi

if test -d "$prefix/log"; then
chmod 777 $prefix/log
else
mkdir $prefix/log
chmod 777 $prefix/log
fi

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
AC_SUBST(TESTCASESBUILD)
AC_SUBST(SAMPLESBUILD)

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
