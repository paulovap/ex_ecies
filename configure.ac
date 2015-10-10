#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.


AC_PREREQ([2.68])
AC_INIT([ex_ecies], [0.0.2], [paulovap@gmail.com])
AC_CANONICAL_TARGET
AC_CANONICAL_HOST
AC_CANONICAL_SYSTEM

AM_INIT_AUTOMAKE

AC_CONFIG_SRCDIR([c_src/lib_elixir_ecies.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC
AC_ERLANG_NEED_ERLC
AC_ERLANG_PATH_ERLC

# Checks for libraries.
AC_CHECK_LIB([ssl], [SSL_library_init])
AC_CHECK_LIB([ssl], [SSL_library_init])
AC_ERLANG_SUBST_ROOT_DIR
AC_ERLANG_SUBST_LIB_DIR
AC_ERLANG_SUBST_ERTS_VER

# Checks for header files.
#AC_CHECK_HEADER([erl_nif.h])
AC_CHECK_HEADERS([openssl/crypto.h openssl/x509.h openssl/pem.h openssl/ssl.h openssl/err.h],[],[AC_MSG_ERROR([OpenSSL headers required])])


# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_ERLANG_CHECK_LIB(erts, , ERLANG_UNAVAILABLE_LIBS="$ERLANG_UNAVAILABLE_LIBS erts")
AC_CHECK_LIB([crypto],[CRYPTO_new_ex_data], [], [AC_MSG_ERROR([OpenSSL libraries required])])


case "$target_os" in
    *linux-gnu)
     AC_DEFINE(GNU_LINUX,1,[This is a GNU/Linux system])
     AC_DEFINE_UNQUOTED(GNU_LINUX,1,[This is a GNU/Linux system])
     AM_CONDITIONAL(HAVE_GNU_LD, true)
     AM_CONDITIONAL(SOMEBSD, false)
     AM_CONDITIONAL(WINDOWS, false)
     XTRA_CPPLIBS=-lstdc++
     CFLAGS="-fPIC $CFLAGS"
     LIBEXT=.so
     AC_SUBST(LIBEXT)
     ;;
 darwin* )
     AC_DEFINE_UNQUOTED(DARWIN,1,[This is a Darwin system])
     AM_CONDITIONAL(HAVE_GNU_LD, false)
     AM_CONDITIONAL(SOMEBSD, false)
     AM_CONDITIONAL(WINDOWS, false)
     CFLAGS="-fno-common $CFLAGS"
     LDFLAGS="-dynamiclib -undefined dynamic_lookup"
     LIBEXT=.so
     AC_SUBST(LIBEXT)
     ;;
esac

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
