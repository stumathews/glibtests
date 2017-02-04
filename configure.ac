 
AC_PREREQ([2.67])
AC_INIT([glibtest], [0.1], [fakeaddress@foo.net])
AM_INIT_AUTOMAKE([foreign]) 
AC_CONFIG_SRCDIR([])
AC_CONFIG_HEADERS([config.h])
 
# Checks for programs.
AC_PROG_CC
PKG_PROG_PKG_CONFIG([0.27])
PKG_CHECK_MODULES([GLIB], [glib-2.0 >= 2.26.0])
 
# Checks for libraries.
AC_SUBST([GLIB_CFLAGS])
AC_SUBST([GLIB_LIBS])
 
# Checks for header files.
 
# Checks for typedefs, structures, and compiler characteristics.
 
# Checks for library functions.
 
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
