SOURCES += main.cpp \
 hauptfenster.cpp \
 gesamtbild.cpp \
 landgang.cpp \
 karteladen.cpp \
 handel.cpp \
 gb_spiel.cpp \
 sul.cpp \
 produktion.cpp \
 tabpanel.cpp \
 konsole.cpp \
 zeit.cpp \
 quests.cpp

TEMPLATE = app
CONFIG += warn_on \
	  thread \
          qt
TARGET = OpenHanse
DESTDIR = ../bin
RESOURCES += img.qrc \
 maps.qrc \
 objekte.qrc

HEADERS += schiff.h \
 hauptfenster.h \
 gesamtbild.h \
 stadtklasse.h \
 handelsfenster.h \
 waren.h \
 kontorklasse.h \
 tabpanel.h \
 konsole.h \
 zeit.h \
questclass.h \
questhandler.h


QMAKE_CXXFLAGS_RELEASE += -Wall

