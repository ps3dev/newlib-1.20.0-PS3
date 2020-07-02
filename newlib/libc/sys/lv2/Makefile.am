## Process this file with automake to generate Makefile.in

AUTOMAKE_OPTIONS = cygnus

INCLUDES = $(NEWLIB_CFLAGS) $(CROSS_CFLAGS) $(TARGET_CFLAGS)

AM_CCASFLAGS = $(INCLUDES)

noinst_LIBRARIES = lib.a

NET_SOURCES = poll.c select.c socket.c net/gethostbyaddr.c net/gethostbyname.c net/getservbyport.c net/inet_addr.c net/inet_aton.c net/inet_lnaof.c net/inet_makeaddr.c net/inet_netof.c net/inet_network.c net/inet_ntoa.c net/inet_ntop.c net/inet_pton.c net/net_init.c
lib_a_SOURCES = getreent.c lock.c lock_recursive.c lock_internal.c ${NET_SOURCES}
lib_a_CCASFLAGS = $(AM_CCASFLAGS)
lib_a_CFLAGS = $(AM_CFLAGS)

all-local: crt0.o

ACLOCAL_AMFLAGS = -I ../../.. -I ../../../..
CONFIG_STATUS_DEPENDENCIES = $(newlib_basedir)/configure.host
