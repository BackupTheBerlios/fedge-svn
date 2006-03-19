## Makefile.am for fedge

# this has all of the subdirectories that make will recurse into.  if
# there are none, comment this out
SUBDIRS = . pics

# this is the program that gets installed.  it's name is used for all
# of the other Makefile.am variables
bin_PROGRAMS = fedge

# set the include path for X, qt and KDE
INCLUDES         = $(all_includes)

# the library search path. 
fedge_LDFLAGS = $(KDE_RPATH) $(all_libraries)

# the libraries to link against.
fedge_LDADD   = $(LIB_KFILE) -lkdeprint

# which sources should be compiled for fedge
fedge_SOURCES = main.cpp fedge.cpp message.cpp pop3fetcher.cpp kmailfetcher.cpp \
	fedgeballoon.cpp pop3deleter.cpp kmaildeleter.cpp deleter.cpp fetcher.cpp \
	fedgeconfig.kcfgc configgeneraloptions.ui

# these are the headers for your project
noinst_HEADERS = fedge.h message.h fetcher.h deleter.h opener.h pop3fetcher.h \
	kmailfetcher.h fedgeballoon.h pop3deleter.h kmaildeleter.h

# client stuff

# let automoc handle all of the meta source files (moc)
METASOURCES = AUTO

messages: rc.cpp
	$(XGETTEXT) *.cpp -o $(podir)/fedge.pot

KDE_ICON = fedge

# this is where the kdelnk file will go 
xdg_apps_data = fedge.desktop

# this is where the XML-GUI resource file goes
rcdir = $(kde_datadir)/fedge
rc_DATA = fedgeui.rc

#kconfigXT
kde_kcfg_DATA = fedge.kcfg

shelldesktopdir = $(kde_appsdir)/Network
shelldesktop_DATA = fedge.desktop
