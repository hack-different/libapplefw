AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)

AM_CFLAGS = \
	$(GLOBAL_CFLAGS) 

bin_PROGRAMS = \
	dt \
	pmgr


dt_SOURCES = dt.c
dt_CFLAGS = $(AM_CFLAGS) 
dt_LDFLAGS = $(AM_LDFLAGS) 
dt_LDADD = $(top_builddir)/src/libapplefw.la

pmgr_SOURCES = pmgr.c
pmgr_CFLAGS = $(AM_CFLAGS) 
pmgr_LDFLAGS = $(AM_LDFLAGS) 
pmgr_LDADD = $(top_builddir)/src/libapplefw.la