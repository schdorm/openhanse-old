/***************************************************************************
 *   Copyright (C) 2009 by Christian Doerffel                              *
 *   schdorm@googlemail.com                                                *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef _hauptfenster_h
#define _hauptfenster_h

#include <QtCore/QObject>
#include <QtCore/QTimer>

#include <QtGui/QGraphicsView>

#include <QtGui/QGraphicsItem>
#include <QtGui/QGraphicsPixmapItem>

#include <QtGui/QImage>

 #include <QtGui/QLabel>

#include <QtGui/QCheckBox>

// #include "konsole.h"


#include "datamanager.h"

#include "definitions.h"

// #include "settings.h"
// #include "dataclass.h"
// #include "shipdata.h"
#include "map.h"

#include "objectgraphicsitem.h"

// #include "gebaude.h"
// #include "stadtklasse.h"

// #include <math.h>

// const int const_mhiscale = 5;

// class konsole;

class hauptfenster : public QGraphicsView
{
Q_OBJECT
public:
	hauptfenster(/*DataClass *, Settings **/);
	~hauptfenster();

	void karteladen(Map::Orientations);

	void starttimer(int);
	bool schiffskollision(QGraphicsItem *);
	bool kollision(QGraphicsItem*, QGraphicsItem*);
	bool isLand( QGraphicsItem *) const;
	
	void landing();
	void activeLanding();

	void keyEventWeiterleitung(QKeyEvent *event);
	void rotateItem(QGraphicsItem *, double);
// 	void questHandler(QString);

// schiffsklasse activeship;		//Schiff, auf dem man gerade aktiv ist

// DataClass *gamedata;
// Settings *currentSettings;

int schwierigkeit;
bool tastatur;

bool anlegbar;

bool uhr;

bool cacheMaps;

// int tageslaenge;			//Menge an Aktualisierungen fuer einen Spieltag


quint32 durchlauf;

// QRgb schiffbar, nschiffbar, anlegestelle, strand_weich ,strand_hart;




// QList <mapfarbdefstruct> farbdefliste;
struct schuss{
QGraphicsPixmapItem *kugel;
int w;				// Weg
int h;				// Hoehe
float dir;			// Richtung
};


// struct mapproperties_struct{
// QString mapname;
// QString dir;
// QString stadtname;
// QString hintergrund;
// QString handlingimg;
// quint16 hoehe;
// quint16 breite;
// QString mapnord;
// QString mapost;
// QString mapsued;
// QString mapwest;
// // MapType::mtyp maptyp;
// int maptyp;
// }mapprops;


// QGraphicsPixmapItem *testschiff ;
QImage collimg[3];
// QList<QGraphicsPixmapItem*> schi
// QList <QGraphicsItem *> hafenobjliste;
QList <QGraphicsPixmapItem*> landobjektliste;

// konsole *konsolenwidget;

public slots:


	
	void aktualisieren();
	void schuss();
	
	void landgang();
// 	void einschiffen();

	void slotpause();
	void endePause();
	void startPause();
	
	void segelsetzen(int);


private:


ObjectGraphicsItem *activeship_model;
QList <ObjectGraphicsItem *> modellist;


int zoomlvl;

// QGraphicsScene *szene;
// QGraphicsScene m_scene;

QGraphicsItem *graphicsitem_it;
QList <QGraphicsPixmapItem*> wolkenliste;
QGraphicsPixmapItem *wolke;
// QGraphicsItem *objekte;

// QImage *img;
// QPixmap bgpixmap;
// QBrush bgbrush;			//Hintergrundbrushzeugs
// bool kartegeladen;

QTimer refreshGraphicsTimer;		//regelt neusetzen
int graphics_refresh_delay;		// time in ms, until the graphics are moved ...

#ifndef _RELEASE_
QLabel *knoten;
QLabel *sollknoten;
QLabel *sollsegel;
QLabel *segel;
QLabel *segeldir;
QLabel *solldir;		//dir=direction = Richtung
QLabel *dir;			
QLabel *steuerdir;
QLabel *sollsteuerdir;
QLabel *winddir;
QLabel *windv;
QLabel *acclabel;
// QLabel *eol;
// QLabel *eor;
// QLabel *eul;
// QLabel *eur;

QCheckBox *fokussieren;
#endif

bool pause;


// const static double pi = 3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628;
		//PI eben


signals:
void enterBuilding(int);
void sig_anlegbar(bool);
// void nichtmehranlegen();
void handel();

void SIGgeschwindigkeit(int);
void zeitsig();
void savesig();
void menusig();

void sig_konsole();

protected:
	void keyPressEvent(QKeyEvent *event);
	void mousePressEvent(QMouseEvent *event);

};

#endif
