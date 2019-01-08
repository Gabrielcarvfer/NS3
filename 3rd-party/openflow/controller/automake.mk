bin_PROGRAMS += controller/controller
man_MANS += controller/controller.8
DISTCLEANFILES += controller/controller.8

controller_controller_SOURCES = controller/controller.c
controller_controller_LDADD = lib/libopenflow.a $(FAULT_LIBS) $(SSL_LIBS)
#MAH: start
controller_controller_LDFLAGS = `xml2-config --libs`
#MAH: end

EXTRA_DIST += controller/controller.8.in
