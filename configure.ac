#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([Xsltpeds], [0.1.0], [])
AC_CONFIG_SRCDIR([src/main.cpp])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])

# Checks for programs.
AC_PROG_CXX

# Checks for libraries.
AC_CHECK_LIB([boost_filesystem], [printf])
AC_CHECK_LIB([boost_program_options], [printf])
AC_CHECK_LIB([xml2], [xmlParseFile])
AC_CHECK_LIB([xslt], [xsltParseStylesheetFile])
AC_CHECK_LIB([zip], [zip_fread])

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL

# Checks for library functions.
AC_FUNC_ERROR_AT_LINE
AC_CHECK_FUNCS([strerror])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
