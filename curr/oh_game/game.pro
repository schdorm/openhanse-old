SOURCES += main.cpp \
 widgets/mainwindow.cpp \
 widgets/mainmenu.cpp \
 widgets/mainview.cpp \
 widgets/servermenu.cpp \
 widgets/ipdialog.cpp \
 widgets/terminal.cpp \
 widgets/optionwindow.cpp \
 widgets/gamesettingsmenu.cpp \
 widgets/playerlist.cpp \
 widgets/ingamemenu.cpp \
#clientsocket.cpp \
clientgamedata.cpp \
datamanager.cpp \
debugqueue.cpp \
settings.cpp \
serverprocess.cpp


HEADERS += sound_pre.h \
 widgets/mainwindow.h \
 widgets/mainmenu.h \
 widgets/mainview.h \
 widgets/servermenu.h \
 widgets/ipdialog.h \
 widgets/terminal.h \
 widgets/optionwindow.h \
 widgets/gamesettingsmenu.h \
 widgets/playerlist.h \
 widgets/ingamemenu.h \
#clientsocket.h \
clientgamedata.h \
datamanager.h \
debugqueue.h \
settings.h \
serverprocess.h


TEMPLATE = app
CONFIG += warn_on \
	  thread \
          qt

TARGET = OpenHanse

QT += phonon \
network

LIBS += -L../common -loh_common \
	-L../gamedata -loh_gamedata \
	-L../networktools -loh_networktools
	
INCLUDEPATH +=	../common \
		../gamedata \
		../networktools

DESTDIR = ../bin

FORMS = widgets/ipdialog.ui \
widgets/servermenu.ui \
widgets/playerlist.ui \
widgets/gamesettingsmenu.ui \
widgets/optionwindow.ui

QMAKE_CXXFLAGS_RELEASE += -Wall
#; QMAKE_LFLAGS_RPATH += ../bin/libs/liboh_common.so.1
#; unix:QMAKE_LFLAGS_RPATH *= ../common/ 

ohlibs.path = /usr/lib/
ohlibs.files = ../common/liboh_common.so* ../gamedata/liboh_gamedata.so* ../networktools/liboh_networktools.so* 

INSTALLS += ohlibs

TRANSLATIONS += oh_de-ge.ts
