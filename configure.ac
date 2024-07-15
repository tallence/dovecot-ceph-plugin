#
# Copyright (c) 2017-2018 Tallence AG and the authors
#
# This is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License version 2.1, as published by the Free Software
# Foundation.  See file COPYING.

AC_PREREQ([2.59])


AC_INIT([dovecot-ceph-plugin], [1.0.1], [https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/new], ,[https://github.com/ceph-dovecot/dovecot-ceph-plugin])


AC_CONFIG_AUX_DIR([.])
AC_CONFIG_SRCDIR([src])
AC_CONFIG_MACRO_DIR([m4])

AX_IS_RELEASE(always)
AX_CHECK_ENABLE_DEBUG()

AM_INIT_AUTOMAKE([no-define foreign tar-ustar subdir-objects])
LT_INIT([shared disable-static pic-only])

AM_MAINTAINER_MODE
PKG_PROG_PKG_CONFIG

# TEST_WITH(name, value, [plugin])
AC_DEFUN([TEST_WITH], [
  want=want_`echo $1|sed s/-/_/g`
  if test $2 = yes || test $2 = no || test $2 = auto; then
    eval $want=$2
  elif test $2 = plugin; then
    if test "$3" = plugin; then
      eval $want=plugin
    else
      AC_ERROR([--with-$1=plugin not supported])
    fi
  elif `echo $2|grep '^/' >/dev/null`; then
    AC_ERROR([--with-$1=path not supported. You may want to use instead:
CPPFLAGS=-I$2/include LDFLAGS=-L$2/lib ./configure --with-$1])
  else
    AC_ERROR([--with-$1: Unknown value: $2])
  fi
])

# Look for librados
have_librados=no
AC_CHECK_HEADER([rados/librados.h], [
  have_librados=yes
  AC_DEFINE([HAVE_LIBRADOS], [1], [Define if you have the RADOS library])
  LIBS="$LIBS -lrados"
], [AC_MSG_ERROR([cannot build without RADOS support: librados.h not found])])

AC_CHECK_FUNC(rados_read_op_omap_get_vals2, AC_DEFINE(HAVE_OMAP_GET_VALS2, 1, [Define if you have the `rados_read_op_omap_get_vals2' function]))
AC_CHECK_FUNC(rados_set_alloc_hint2, AC_DEFINE(HAVE_ALLOC_HINT_2, 1, [Define if you have the `set_alloc_hint2' function]))
AC_CHECK_FUNC(rados_read_op_omap_get_keys2, AC_DEFINE(HAVE_OMAP_GET_KEYS_2, 1, [Define if you have the `omap_get_keys2' function]))

# Evaluate with options
AC_ARG_WITH(dict,
AS_HELP_STRING([--with-dict[=ARG]], [Build with [ARG=yes] or without [ARG=no] RADOS dictionary plugin (yes)]),
  TEST_WITH(dict, $withval),
  want_dict=yes)
AM_CONDITIONAL(BUILD_DICT_RADOS, test "$want_dict" = "yes")

AC_ARG_WITH(storage,
AS_HELP_STRING([--with-storage[=ARG]], [Build with [ARG=yes] or without [ARG=no] RADOS storage plugin (yes)]),
  TEST_WITH(storage, $withval),
  want_storage=yes)
AM_CONDITIONAL(BUILD_STORAGE_RBOX, test "$want_storage" = "yes")

AC_ARG_WITH(tests,
AS_HELP_STRING([--with-tests[=ARG]], [Build with [ARG=yes] or without [ARG=no] RADOS librmb tests (yes)]),
  TEST_WITH(tests, $withval),
  want_tests=yes)
AM_CONDITIONAL(BUILD_TESTS, test "$want_tests" = "yes")

AC_ARG_WITH(integration-tests,
AS_HELP_STRING([--with-integration-tests[=ARG]], [Build with [ARG=yes] or without [ARG=no] integration tests (no)]),
  TEST_WITH(integration-tests, $withval),
  want_integration_tests=no)
AM_CONDITIONAL(BUILD_INTEGRATION_TESTS, test "$want_integration_tests" = "yes")

AX_CODE_COVERAGE()


AX_VALGRIND_DFLT([helgrind], [off])
AX_VALGRIND_DFLT([drd], [off])
AX_VALGRIND_DFLT([sgcheck], [off])
AX_VALGRIND_CHECK()

AC_PROG_CC_C99
AC_PROG_CXX
AC_PROG_CPP
AC_PROG_LIBTOOL
AC_PROG_GREP
AC_PROG_INSTALL

AC_ENABLE_SHARED
AC_DISABLE_STATIC

AX_CXX_COMPILE_STDCXX([11])

# warnings disabled because of strange Dovecot header files
AX_COMPILER_FLAGS_CXXFLAGS(,,,[-Wno-undef -Wno-redundant-decls])
AX_COMPILER_FLAGS_CFLAGS(,,,[-Wno-declaration-after-statement])
AX_COMPILER_FLAGS()

AC_ISC_POSIX
AC_C_INLINE


# Couple Dovecot config
DC_DOVECOT
DC_DOVECOT_MODULEDIR

LIBS+=" $DOVECOT_LIBS"
LIBDOVECOT_INCLUDE="$LIBDOVECOT_INCLUDE $LIBDOVECOT_STORAGE_INCLUDE"

BINARY_CFLAGS="$DOVECOT_BINARY_CFLAGS"
BINARY_LDFLAGS="$DOVECOT_BINARY_LDFLAGS"

CFLAGS+=" $WARN_CFLAGS $DOVECOT_CFLAGS $EXTRA_CFLAGS -I\$(top_srcdir) $LIBDOVECOT_INCLUDE"
CXXFLAGS+=" $WARN_CXXFLAGS -fpermissive -std=c++11 $lt_cv_prog_compiler_pic_CXX"

AC_SUBST(BINARY_CFLAGS)
AC_SUBST(BINARY_LDFLAGS)
AC_SUBST(LIBDOVECOT_INCLUDE)

AC_DEFINE([PACKAGE_VERSION_MAJOR], regexp(AC_PACKAGE_VERSION, [^\([0-9]+\)\.\([0-9]+\)], [\1]), [Dovecot Ceph plugins major version])
AC_DEFINE([PACKAGE_VERSION_MINOR], regexp(AC_PACKAGE_VERSION, [^\([0-9]+\)\.\([0-9]+\)], [\2]), [Dovecot Ceph plugins minor version])

# Checks for libraries with pkg-config support.
PKG_CHECK_MODULES([JANSSON], [jansson])
AC_SUBST(JANSSON_CFLAGS)
AC_SUBST(JANSSON_LIBS)

AC_MSG_CHECKING([for dict_vfuncs.switch_ioloop])
AS_IF([$GREP switch_ioloop $dovecot_pkgincludedir/dict-private.h], [AC_MSG_RESULT(yes) AC_DEFINE([HAVE_DICT_SWITCH_IOLOOP],,[dict_vfuncs.switch_ioloop supported])],[AC_MSG_RESULT(no)])

AC_MSG_CHECKING([for dict_vfuncs.set_timestamp])
AS_IF([$GREP -q set_timestamp $dovecot_pkgincludedir/dict-private.h], [AC_MSG_RESULT(yes) AC_DEFINE([HAVE_DICT_SET_TIMESTAMP],,[dict_vfuncs.set_timestamp supported])],[AC_MSG_RESULT(no)])

AC_MSG_CHECKING([for index-pop3-uidl.h])
AS_IF([test -f $dovecot_pkgincludedir/index-pop3-uidl.h], [AC_MSG_RESULT(yes) AC_DEFINE([HAVE_INDEX_POP3_UIDL_H],,[index-pop3-uidl.h found])],[AC_MSG_RESULT(no)])

AC_MSG_CHECKING([for mail_vfuncs.index_mail_set_cache_corrupted_reason])
AS_IF([$GREP -q index_mail_set_cache_corrupted_reason $dovecot_pkgincludedir/index-mail.h], [AC_MSG_RESULT(yes) AC_DEFINE([HAVE_INDEX_MAIL_SET_CACHE_CORRUPTED_REASON],,[mail_vfuncs.index_mail_set_cache_corrupted_reason supported])],[AC_MSG_RESULT(no)])

AC_MSG_CHECKING([for dict_lookup_result.values])
AS_IF([$GREP -q values_reason $dovecot_pkgincludedir/dict.h], [AC_MSG_RESULT(yes) AC_DEFINE([HAVE_DICT_LOOKUP_RESULT_VALUES],,[dict_lookup_result.values supported])],[AC_MSG_RESULT(no)])

AC_MSG_CHECKING([for mail_save_context.copy_src_mail])
AS_IF([$GREP -q copy_src_mail $dovecot_pkgincludedir/mail-storage-private.h ], [AC_MSG_RESULT(yes) AC_DEFINE([HAVE_MAIL_SAVE_CONTEXT_COPY_SRC_MAIL],,[mail_save_context.copy_src_mail supported])],[AC_MSG_RESULT(no)])

AC_MSG_CHECKING([for MAIL_INDEX_HDR_FLAG_FSCKD])
AS_IF([$GREP -q MAIL_INDEX_HDR_FLAG_FSCKD $dovecot_pkgincludedir/mail-index.h], [AC_MSG_RESULT(yes) AC_DEFINE([HAVE_MAIL_INDEX_HDR_FLAG_FSCKD],,[MAIL_INDEX_HDR_FLAG_FSCKD supported])],[AC_MSG_RESULT(no)])

AC_CHECK_MEMBER([struct mail_storage_vfuncs.list_index_corrupted],
  [AC_DEFINE(HAVE_LIST_INDEX_CORRUPTED, 1, [Define if you have the `struct mail_storage_vfuncs.list_index_corrupted' member])], [],
                          [[
                          #include "config.h"
                          #include "lib.h"
                          #include "mail-storage-private.h"
                          ]])

AC_CHECK_MEMBER([struct mail_save_context.save_from_lf_src],
  [AC_DEFINE(HAVE_SAVE_FROM_LF_SRC, 1, [Define if you have the `mail_save_context.save_from_lf_src' member])], [],
                          [[
                          #include "config.h"
                          #include "lib.h"
                          #include "mail-storage-private.h"
                          ]])

AC_MSG_CHECKING([for HAVE_MAIL_STORAGE_TRANSACTION_OLD_SIGNATURE])
AS_IF([$GREP -A 1 'mailbox_transaction_begin(struct mailbox \*box' $dovecot_pkgincludedir/mail-storage.h | grep 'enum mailbox_transaction_flags flags);'], [AC_MSG_RESULT(yes) AC_DEFINE([HAVE_MAIL_STORAGE_TRANSACTION_OLD_SIGNATURE],,[HAVE_MAIL_STORAGE_TRANSACTION_OLD_SIGNATURE supported])],[AC_MSG_RESULT(no)])


AC_MSG_CHECKING([for HAVE_ITER_FROM_INDEX_DIR])
AS_IF([$GREP -A 1 'bool iter_from_index_dir;' $dovecot_pkgincludedir/mailbox-list.h | grep 'bool iter_from_index_dir;'], [AC_MSG_RESULT(yes) AC_DEFINE([HAVE_ITER_FROM_INDEX_DIR],,[HAVE_ITER_FROM_INDEX_DIR supported])],[AC_MSG_RESULT(no)])

AC_MSG_CHECKING([for HAVE_INDEX_MAIL_INIT_OLD_SIGNATURE])
AS_IF([$GREP -A 3 'index_mail_init(struct index_mail \*mail' $dovecot_pkgincludedir/index-mail.h | $GREP -q 'struct mailbox_header_lookup_ctx \*_wanted_headers);'],
      [AC_MSG_RESULT(yes) AC_DEFINE([HAVE_INDEX_MAIL_INIT_OLD_SIGNATURE],,[HAVE_INDEX_MAIL_INIT_OLD_SIGNATURE supported])],
      [AC_MSG_RESULT(no)])

AC_CONFIG_HEADERS([config-local.h])
AX_PREFIX_CONFIG_H([$PACKAGE-config.h], [$PACKAGE], [config-local.h])

if test "$enable_debug" = yes; then
  AC_DEFINE([DEBUG],[],[Debug Mode])
else
  AC_DEFINE([NDEBUG],[],[Release Mode])
fi

if test "x$want_tests" = "xyes"; then
  # Configure pthreads.
  ACX_PTHREAD([have_pthread=yes])

  # Define gtest variables
  GTEST_VERSION="1.8.0"

  if test "x$have_pthread" = "xyes"; then
    GTEST_CPPFLAGS="-DGTEST_HAS_PTHREAD=1"
    GTEST_CXXFLAGS="$PTHREAD_CFLAGS -fpermissive -std=c++11 -Wmissing-declarations"
    #GTEST_CXXFLAGS="$PTHREAD_CFLAGS -fpermissive -shared-libgcc -std=c++11 -Wmissing-declarations"
    GTEST_LDFLAGS="-module -avoid-version"
    GTEST_LIBS="$PTHREAD_LIBS"
  else
    GTEST_CPPFLAGS="-DGTEST_HAS_PTHREAD=0"
    GTEST_CXXFLAGS=
    GTEST_LDFLAGS=
    GTEST_LIBS=
  fi

  AC_SUBST([GTEST_VERSION])
  AC_SUBST([GTEST_CPPFLAGS])
  AC_SUBST([GTEST_CXXFLAGS])
  AC_SUBST([GTEST_LDFLAGS])
  AC_SUBST([GTEST_LIBS])
fi

# finish

AC_CONFIG_FILES([
Makefile
src/Makefile
src/librmb/Makefile
src/dict-rados/Makefile
src/storage-rbox/Makefile
src/librmb/tools/Makefile
src/librmb/tools/rmb/Makefile
src/tests/Makefile
])

AC_OUTPUT

echo
AC_MSG_NOTICE([DEBUG is enabled .............. : $enable_debug])
AC_MSG_NOTICE([Install prefix ................ : $prefix])
AC_MSG_NOTICE([Dovecot directory ............. : $dovecotdir])
AC_MSG_NOTICE([With dictionary ............... : $want_dict])
AC_MSG_NOTICE([With storage .................. : $want_storage])
AC_MSG_NOTICE([With tests .................... : $want_tests])
AC_MSG_NOTICE([With integration tests ........ : $want_integration_tests])

if test "x$want_tests" = "xyes"; then
AC_MSG_NOTICE([

minimal-gtest-autotools $VERSION is now configured
Configure Information:
  C Compiler        : $CC
    DEFS            :   $DEFS
    CPPFLAGS        :   $CPPFLAGS
    CFLAGS          :   $CFLAGS

  C++ Compiler      : $CXX
    DEFS            :   $DEFS
    CPPFLAGS        :   $CPPFLAGS
    CXXFLAGS        :   $CXXFLAGS

  Linker            : $LD
    LDFLAGS         :   $LDFLAGS
    LIBS            :   $LIBS

  Google Test
    GTEST_CPPFLAGS  : $GTEST_CPPFLAGS
    GTEST_CXXFLAGS  : $GTEST_CXXFLAGS
    GTEST_LDFLAGS   : $GTEST_LDFLAGS
    GTEST_LIBS      : $GTEST_LIBS
])
fi
