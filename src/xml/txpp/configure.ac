AC_INIT(FULL-PACKAGE-NAME, VERSION, BUG-REPORT-ADDRESS)
AM_INIT_AUTOMAKE(0.3)
AM_CONFIG_HEADER(config.h)
CFLAGS="-g -Wshadow -Wall -pedantic -ansi"
LDFLAGS="-ldl"
AC_PROG_CC
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_LIBTOOL
AC_MSG_CHECKING(whether to build testcases)
AC_ARG_ENABLE(testcases, [  --enable-testcases    build testcases.],
[ case "${enableval}" in
  no)
    AC_MSG_RESULT(no)
    TESTS=""
    ;;
  *)
    AC_MSG_RESULT(yes)
    echo "tests"
    TESTS="tests"
    ;;
  esac ],
  AC_MSG_RESULT(no)
)
LINKTXPPLIB="-L$prefix/lib -ltxpp"
AC_SUBST(TESTS)
AC_SUBST(LINKTXPPLIB)
AC_OUTPUT(Makefile \
          src/Makefile \
          tests/Makefile \
          tests/test1/Makefile \
          tests/test2/Makefile)
