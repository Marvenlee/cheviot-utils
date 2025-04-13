
sbin_PROGRAMS = getty

getty_SOURCES = \
  main.c \
  init.c \
  subr.c
  
getty_LDADD = -lc -ldb -lutil -lterminfo

AM_CFLAGS = -O0 -std=c99 -g2
AM_CPPFLAGS = -I$(srcdir)

