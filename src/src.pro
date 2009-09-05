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
 wind.cpp \
 shipdata.cpp \
 quests.cpp \
 buildings.cpp \
 dataclass.cpp \
 person.cpp \
 objectgraphicsitem.cpp

TEMPLATE = app
CONFIG += warn_on \
	  thread \
          qt

TARGET = OpenHanse

DESTDIR = ../bin

RESOURCES += img.qrc \
 maps.qrc \
 objekte.qrc

HEADERS += shipdata.h \
 hauptfenster.h \
 gesamtbild.h \
 stadtklasse.h \
 handelsfenster.h \
 waren.h \
 kontordata.h \
 tabpanel.h \
 konsole.h \
 zeit.h \
 wind.h \
 questclass.h \
 questhandler.h \
  definitions.h \
 dataclass.h \
 build_menu.h \
 buildingdata.h \
 map.h \
 person.h \
 objectgraphicsitem.h


QMAKE_CXXFLAGS_RELEASE += -Wall

