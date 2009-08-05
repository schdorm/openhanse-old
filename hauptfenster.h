/***************************************************************************
 *   Copyright (C) 2009 by Christian Doerffel   *
 *   schdorm@googlemail.com   *
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

#include <QtGui/QGraphicsView>

#include <QtGui/QGraphicsItem>
#include <QtGui/QGraphicsPixmapItem>

#include <QtGui/QImage>

 #include <QtGui/QLabel>

#include <QtGui/QCheckBox>

#include "schiff.h"
// #include "gebaude.h"
// #include "stadtklasse.h"

// #include <math.h>

// const int const_mhiscale = 5;
const int _oh_version = 33;
namespace MapType
	{
	enum mtyp
		{
		 sea,			// 001
		 coast,			// 010 || -> | -> 110
		 land,			// 011 || -> | -> 111
		 city			// 100
		};
	}
class hauptfenster : public QGraphicsView
{
Q_OBJECT
public:
	hauptfenster();

	void karteladen(QString);

	void starttimer();
	void windsetzen();
	void bewegungsbeschreibung();
	bool schiffskollision(QGraphicsItem *);

	void keyEventWeiterleitung(QKeyEvent *event);


schiffsklasse activeship;		//Schiff, auf dem man gerade aktiv ist
int schwierigkeit;
bool tastatur;

bool anlegbar;
bool anbord;
// bool uhra;

bool uhr;
float minute;
int stunde;
int tag;
int jahr;

int tageslaenge;			//Menge an Aktualisierungen fuer einen Spieltag

int windgeschwindigkeit;
float windrichtung;

quint32 durchlauf;

// QRgb schiffbar, nschiffbar, anlegestelle, strand_weich ,strand_hart;

// struct mapfarbdefstruct
// {
// int id;
// QRgb farbe;
// };


// enum mtyp{
// land,
// coast,
// sea
// };

enum object_types_def
{
object_type_townhall,
object_type_market,
object_type_church,
object_type_port,
object_type_office,
object_type_bank,
object_type_tavern,
object_type_namespacexyz
};




QList <QGraphicsPixmapItem*> landobjektliste;
// QList <mapfarbdefstruct> farbdefliste;
struct schuss{
QGraphicsPixmapItem *kugel;
int w;				// Weg
int h;				// Hoehe
float dir;			// Richtung
};

struct mapproperties_struct{
QString mapname;
QString dir;
QString stadtname;
QString hintergrund;
QString handlingimg;
quint16 hoehe;
quint16 breite;
QString mapnord;
QString mapost;
QString mapsued;
QString mapwest;
// MapType::mtyp maptyp;
int maptyp;
}mapprops;

QGraphicsPixmapItem *testschiff ;
QImage collimg[3];
// QList <QGraphicsItem *> hafenobjliste;

public slots:


	
	void aktualisieren();
	void schuss();
	
	void landgang();
	void ablegen();

	void slotpause();
	void endePause();
	void startPause();
	
	void segelsetzen(int);


private:

QImage maphandlingimg;

// qint8 aszene;
// Gebaude *gebaude[50];
// QGraphicsScene *szene[2];
QGraphicsScene *szene;


// QGraphicsPixmapItem *background;
QList <QGraphicsPixmapItem*> wolkenliste;
QGraphicsPixmapItem *wolke;
// QGraphicsItem *wolken[15];
// QGraphicsItem *objekte;

// QImage *img;
// QPixmap bgpixmap;
// QBrush bgbrush;			//Hintergrundbrushzeugs
// bool kartegeladen;

QTimer *bewegung;		//regelt neusetzen

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
void kannanlegen(bool);
// void nichtmehranlegen();
void handel();
void Aktualisierung(int);
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
