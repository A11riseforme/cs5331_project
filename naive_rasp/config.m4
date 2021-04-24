dnl config.m4 for extension naive_rasp

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary.

dnl If your extension references something external, use 'with':

PHP_ARG_WITH([naive_rasp],
  [for naive_rasp support],
  [AS_HELP_STRING([--with-naive_rasp],
    [Include naive_rasp support])])

dnl Otherwise use 'enable':

PHP_ARG_ENABLE([naive_rasp],
  [whether to enable naive_rasp support],
  [AS_HELP_STRING([--enable-naive_rasp],
    [Enable naive_rasp support])],
  [no])

if test "$PHP_NAIVE_RASP" != "no"; then
  dnl Write more examples of tests here...

  dnl Remove this code block if the library does not support pkg-config.
  dnl PKG_CHECK_MODULES([LIBFOO], [foo])
  dnl PHP_EVAL_INCLINE($LIBFOO_CFLAGS)
  dnl PHP_EVAL_LIBLINE($LIBFOO_LIBS, NAIVE_RASP_SHARED_LIBADD)

  dnl If you need to check for a particular library version using PKG_CHECK_MODULES,
  dnl you can use comparison operators. For example:
  dnl PKG_CHECK_MODULES([LIBFOO], [foo >= 1.2.3])
  dnl PKG_CHECK_MODULES([LIBFOO], [foo < 3.4])
  dnl PKG_CHECK_MODULES([LIBFOO], [foo = 1.2.3])

  dnl Remove this code block if the library supports pkg-config.
  dnl --with-naive_rasp -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/naive_rasp.h"  # you most likely want to change this
  dnl if test -r $PHP_NAIVE_RASP/$SEARCH_FOR; then # path given as parameter
  dnl   NAIVE_RASP_DIR=$PHP_NAIVE_RASP
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for naive_rasp files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       NAIVE_RASP_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$NAIVE_RASP_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the naive_rasp distribution])
  dnl fi

  dnl Remove this code block if the library supports pkg-config.
  dnl --with-naive_rasp -> add include path
  dnl PHP_ADD_INCLUDE($NAIVE_RASP_DIR/include)

  dnl Remove this code block if the library supports pkg-config.
  dnl --with-naive_rasp -> check for lib and symbol presence
  dnl LIBNAME=NAIVE_RASP # you may want to change this
  dnl LIBSYMBOL=NAIVE_RASP # you most likely want to change this

  dnl If you need to check for a particular library function (e.g. a conditional
  dnl or version-dependent feature) and you are using pkg-config:
  dnl PHP_CHECK_LIBRARY($LIBNAME, $LIBSYMBOL,
  dnl [
  dnl   AC_DEFINE(HAVE_NAIVE_RASP_FEATURE, 1, [ ])
  dnl ],[
  dnl   AC_MSG_ERROR([FEATURE not supported by your naive_rasp library.])
  dnl ], [
  dnl   $LIBFOO_LIBS
  dnl ])

  dnl If you need to check for a particular library function (e.g. a conditional
  dnl or version-dependent feature) and you are not using pkg-config:
  dnl PHP_CHECK_LIBRARY($LIBNAME, $LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $NAIVE_RASP_DIR/$PHP_LIBDIR, NAIVE_RASP_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_NAIVE_RASP_FEATURE, 1, [ ])
  dnl ],[
  dnl   AC_MSG_ERROR([FEATURE not supported by your naive_rasp library.])
  dnl ],[
  dnl   -L$NAIVE_RASP_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(NAIVE_RASP_SHARED_LIBADD)

  dnl In case of no dependencies
  AC_DEFINE(HAVE_NAIVE_RASP, 1, [ Have naive_rasp support ])

  PHP_NEW_EXTENSION(naive_rasp, naive_rasp.c, $ext_shared)
fi
