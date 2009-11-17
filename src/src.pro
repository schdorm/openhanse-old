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
 objectgraphicsitem.cpp \
 settings.cpp \
 map.cpp \
datamanager.cpp \
 city.cpp \
 gameparameter.cpp \
 goods.cpp \
 mainscene.cpp \
 optionwindow.cpp \
 ingamemenu.cpp

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
 buildmenu.h \
 buildingdata.h \
 map.h \
 person.h \
 objectgraphicsitem.h \
 settings.h \
 mapobject.h \
datamanager.h \
 landing.h \
 gameparameter.h \
 mainscene.h \
 optionwindow.h \
 ingamemenu.h \


QMAKE_CXXFLAGS_RELEASE += -Wall

TRANSLATIONS += oh_de-ge.ts
