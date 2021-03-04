AUTOMAKE_OPTIONS = subdir-objects

bin_PROGRAMS = xsltpeds

xsltpeds_SOURCES = \
	src/CollectionProcessor.hpp \
	src/exceptions.hpp \
	src/main.cpp \
	src/PedsXmlCollectionProcessor.cpp \
	src/PedsXmlCollectionProcessor.hpp \
	src/PedsXmlZipfileProcessor.cpp \
	src/PedsXmlZipfileProcessor.hpp \
	src/PedsXsltProcessor.cpp \
	src/PedsXsltProcessor.hpp \
	src/Proca.cpp \
	src/Proca.hpp \
	src/Procf.cpp \
	src/Procf.hpp \
	src/Proco.cpp \
	src/Proco.hpp \
	src/SystemXsltProcessor.cpp \
	src/SystemXsltProcessor.hpp \
	src/ZipArchive.cpp \
	src/ZipArchive.hpp \
	src/ZipfileExpander.cpp \
	src/ZipfileExpander.hpp \
	src/ZipfileProcessor.cpp \
	src/ZipfileProcessor.hpp

xsltpeds_CPPFLAGS = \
	-I/usr/include/libxml2

xsltpeds_LDFLAGS = \
	-lboost_filesystem \
	-lboost_program_options\
	-lzip \
	-lxslt \
	-lxml2

myprojdatadir = $(pkgdatadir)
dist_myprojdata_DATA = peds.xsl