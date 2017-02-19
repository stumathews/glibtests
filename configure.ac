AC_PREREQ([2.67])
AC_INIT([glib_test], [0.1], [fakeaddress@foo.net])
AM_INIT_AUTOMAKE([foreign]) 
AC_CONFIG_SRCDIR([])
AC_CONFIG_HEADERS([config.h])
 
# Checks for programs.
AC_PROG_CC
PKG_PROG_PKG_CONFIG([0.27])
PKG_CHECK_MODULES([GLIB], [glib-2.0 >= 2.26.0])
PKG_CHECK_MODULES([SDL2], [sdl2 >= 2.0])
 
# Checks for libraries.
AC_SUBST([GLIB_CFLAGS])
AC_SUBST([GLIB_LIBS])
AC_SUBST([SDL2_CFLAGS])
AC_SUBST([SDL2_LIBS])

AC_SUBST([LIBSTU_CLAGS], ["-I /c/Users/Stuart/git/stulibc/src/includes"])
AC_SUBST([LIBSTU_LIBS],["-L/usr/local/lib -lstu"])
 
# Checks for header files.
 
# Checks for typedefs, structures, and compiler characteristics.
 
# Checks for library functions.
 
AM_INIT_AUTOMAKE([subdir-objects])
AC_OUTPUT(Makefile game/Makefile)
