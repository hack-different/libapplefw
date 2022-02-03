AC_INIT([libdt], [0.1], [rickmark@outlook.com])

AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([src/])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])

AC_PROG_CC
AM_PROG_CC_C_O
LT_INIT


AC_C_CONST
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT8_T

AC_CHECK_LIB([lzfse], [lzfse_decode])


AC_CONFIG_FILES([Makefile include/Makefile src/Makefile tools/Makefile])


AC_OUTPUT
