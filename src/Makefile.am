lib_LTLIBRARIES = libcouchdb++.la
libcouchdb___la_SOURCES  = Attachment.cpp Communication.cpp Connection.cpp Database.cpp Document.cpp Exception.cpp Revision.cpp
libcouchdb___la_CXXFLAGS = -Wall -I$(srcdir)/../include $(CURL_CFLAGS) $(BOOST_CPPFLAGS)
libcouchdb___la_LDFLAGS  = $(CURL_LIBS)

nobase_include_HEADERS = $(srcdir)/../include/couchdb/Attachment.hpp $(srcdir)/../include/couchdb/Communication.hpp $(srcdir)/../include/couchdb/Connection.hpp $(srcdir)/../include/couchdb/CouchDB.hpp $(srcdir)/../include/couchdb/Database.hpp $(srcdir)/../include/couchdb/Document.hpp $(srcdir)/../include/couchdb/Exception.hpp $(srcdir)/../include/couchdb/Revision.hpp
