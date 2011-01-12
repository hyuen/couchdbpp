#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.61)

AC_INIT([couchdb++], [0.0.1], [tragicphantom@gmail.com])
AM_INIT_AUTOMAKE([foreign])

# Checks for programs.
AC_PROG_CXX
AC_PROG_LIBTOOL

# Checks for libraries.
m4_include([m4/ac_check_curl.m4])
AC_CHECK_CURL([7.15.5])

# Checks for header files.
m4_include([m4/ax_boost_base.m4])
AX_BOOST_BASE([1.31.0])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_TYPE_SIZE_T

# Checks for library functions.
AC_HEADER_STDC
AC_CHECK_FUNCS([setenv])

AC_CONFIG_HEADER([include/config.h])
AC_CONFIG_FILES([Makefile src/Makefile test/Makefile])
AC_OUTPUT
