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
#ifndef _schiffsklasse_h
#define _schiffsklasse_h

// #include "waren.h"
#include "definitions.h"
#include <QtGui/QGraphicsItem>

class ShipClass 
{

private:
int v;
int control_velocity;
double settedSails;
double toSettedSails;
bool hasMoved;

double dir;
double toDir;	// mouse-control
double rudderDir;	//keyboard-control
double toRudderDir;	// 	''

// control-difficulty +
double sailDir;
// double toSailDir;

int g_height, g_height2;	// graphicsitem - height -> laenge
int g_width, g_width2;		// graphicsitem - width -> breite

PositioningStruct currentPosition;



/*struct desc
{
int xpos, xposm;
int ypos, yposm;
QString map;
QString stadt;

////////////////Steuerung: ////////////////////////////
qint16 geschwindigkeit, sollgeschwindigkeit;		//aktuelle Geschwindigkeit -> Sollgeschwindigkeit bei Maussteuerung
float prozentgesetzteSegel, sollprozentgesetzteSegel;

qint16 steuergeschwindigkeit;

float segelausrichtung;
float ausrichtung, sollausrichtung;			//aktueller Winkel -> Sollwinkel bei Maussteuerung
float steuerruderausrichtung, sollsteuerruderausrichtung;				//aktueller Winkel des Ruders
// QPoint ecke_obenlinks, ecke_obenrechts, ecke_untenlinks, ecke_untenrechts;
};*/

public:
QGraphicsPixmapItem *graphicsitem;

// desc attribute;
Warenstruct cargo;			//Ladung

QString schiffsname;
int id;
ShipType::schiffstypen type;
int zustand;
int manvzustand;		//Manoevrierzustand: wie gut kann das Schiff lenken, wie intakt sind die Segel
int besatzung;
// quint16 ladekapazitaet;

QString filename;
int schifflange;	//entspricht SchiffsBildY
int schiffbreite;	//entspricht SchiffsBildX

int control_difficulty;
bool mouse_control;

void init()					///== RESET
{
	static int idzuweisung;
	id = idzuweisung;
	idzuweisung++;

	cargo.taler = 5000;

	for(int i = 0; i<const_warenanzahl; i++)
	{
		cargo.ware[i]=5;
	}
	cargo.fuellung=0;

	zustand = 100;
	type = ShipType::Kogge;/*
	attribute.sollsteuerruderausrichtung=0;
	attribute.steuerruderausrichtung=0;
	attribute.sollausrichtung=0;
	attribute.ausrichtung=0;

	attribute.steuergeschwindigkeit = 1;

	attribute.geschwindigkeit=0;
	attribute.sollgeschwindigkeit=0;
	attribute.prozentgesetzteSegel=0;
	attribute.sollprozentgesetzteSegel=0;
	attribute.segelausrichtung=0;*/
	filename = ":img/schiffe/schiff_gerade_skaliert2.png";
	cargo.kapazitaet = rand()%2001;
}

void setGraphicsItem(QGraphicsPixmapItem*);

// control: set - fct.
void set_ToSettedSails(double);
void set_SailDir(double);
void set_ToRudderDir(double);
void set_ToDir(double);

void brake(double);

// control: Return - fct.
int ret_V();
double ret_SettedSails();
double ret_ToSettedSails();
double ret_SailDir();
// double ret_ToSailDir();
double ret_Dir();
double ret_ToDir();
double ret_RudderDir();
double ret_ToRudderDir();

PositioningStruct ret_currentPosition();
int ret_MPos_X();
int ret_MPos_Y();


// void bewegungsbeschreibung();
void calcMovement(int, double);
bool moveGraphics();

void rotateGraphics();

};

#endif
