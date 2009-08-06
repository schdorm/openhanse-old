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
#ifndef _schiffsklasse_h
#define _schiffsklasse_h

#include "waren.h"

class schiffsklasse 
{

private:

enum schiffstypen
	{
	Kraier,
	Kogge,
	Holk
	};
/*struct Warenstruct{
quint32 taler;							//Geld auf dem Schiff
quint16 ware [30];						//Waren auf dem Schiff
quint16 gesamtladung;
};*/

struct desc
{
int xpos, xposm;
int ypos, yposm;
QString map;
QString stadt;
// int zielx, ziely;

////////////////Steuerung: ////////////////////////////
qint16 geschwindigkeit, sollgeschwindigkeit;		//aktuelle Geschwindigkeit -> Sollgeschwindigkeit bei Maussteuerung
float prozentgesetzteSegel, sollprozentgesetzteSegel;

qint16 steuergeschwindigkeit;

float segelausrichtung;
float ausrichtung, sollausrichtung;			//aktueller Winkel -> Sollwinkel bei Maussteuerung
float steuerruderausrichtung, sollsteuerruderausrichtung;				//aktueller Winkel des Ruders
// QPoint ecke_obenlinks, ecke_obenrechts, ecke_untenlinks, ecke_untenrechts;
};

public:
desc attribute;
Warenstruct Ladung;

QString schiffsname;
quint16 id;
schiffstypen schiffstyp;
quint8 zustand;
quint8 manvzustand;		//Manoevrierzustand: wie gut kann das Schiff lenken, wie intakt sind die Segel
int besatzung;
// quint16 ladekapazitaet;

QString filename;
int schifflange;	//entspricht SchiffsBildY
int schiffbreite;	//entspricht SchiffsBildX

void init()					///== RESET
{
	static int idzuweisung;
	id = idzuweisung;
	idzuweisung++;

	Ladung.taler = 5000;

	for(int i = 0; i<const_warenanzahl; i++)
	{
		Ladung.ware[i]=5;
	}
	Ladung.fuellung=0;

	zustand = 100;
	schiffstyp = Kogge;
	attribute.sollsteuerruderausrichtung=0;
	attribute.steuerruderausrichtung=0;
	attribute.sollausrichtung=0;
	attribute.ausrichtung=0;

	attribute.steuergeschwindigkeit = 1;

	attribute.geschwindigkeit=0;
	attribute.sollgeschwindigkeit=0;
	attribute.prozentgesetzteSegel=0;
	attribute.sollprozentgesetzteSegel=0;
	attribute.segelausrichtung=0;
	filename = ":img/schiffe/schiff_gerade_skaliert2.png";
	Ladung.kapazitaet = rand()%2001;
}


};

#endif
