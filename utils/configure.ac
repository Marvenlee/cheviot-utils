AC_INIT([utils],[1.0])
AM_INIT_AUTOMAKE([-Werror subdir-objects foreign])

AC_PROG_CC
AC_PROG_RANLIB
AM_PROG_AS

AS_VAR_IF(BOARD, [], AC_MSG_ERROR([Missing required variable: BOARD!]))
  
AM_CONDITIONAL([BOARD_RASPBERRY_PI_1], [test "$BOARD" = "raspberrypi1"])
AM_CONDITIONAL([BOARD_RASPBERRY_PI_4], [test "$BOARD" = "raspberrypi4"])

AC_CONFIG_FILES([
  Makefile
  say/Makefile
  setgpio/Makefile  
  top/Makefile
  shutdown/Makefile
  ])
  
AC_OUTPUT

