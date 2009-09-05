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
#ifndef _SHIPDATA_H
#define _SHIPDATA_H

#include "definitions.h"

class ShipData
{

public:


enum ShipTypes
	{
	Kraier,
	Kogge,
	Holk
	};

Warenstruct cargo;			//Ladung
QString schiffsname;



// quint16 ladekapazitaet;

// QString filename;
// int schifflange;	//entspricht SchiffsBildY
// int schiffbreite;	//entspricht SchiffsBildX

int control_difficulty;
bool mouse_control;




ShipData()					///== RESET
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

	condition = 100;
	type = Kogge;
	v = 0;
	dir = 0;
	toDir = 0;
	sailDir = 0;
	rudderDir = 0;
	toRudderDir = 0;
	settedSails = 0;
	toSettedSails = 0;
	control_velocity = 1;
	
	control_difficulty = 0;
// 	filename = ":img/schiffe/schiff_gerade_skaliert2.png";
	cargo.kapazitaet = rand()%2001;
}
~ShipData()
{
}

int ret_Condition();

// control: set - fct.
void set_ToSettedSails(double);
void set_SailDir(double);
void set_ToRudderDir(double);
void set_ToDir(double);

void brake(double);

// control: Return - fct.
double ret_V();
double ret_SettedSails();
double ret_ToSettedSails();
double ret_SailDir();
// double ret_ToSailDir();
double ret_Dir();
double ret_ToDir();
double ret_RudderDir();
double ret_ToRudderDir();

PositioningStruct ret_CurrentPosition();
int ret_MPos_X();
int ret_MPos_Y();


// void bewegungsbeschreibung() --> calculate movement-things ...
void calcMovement(int, double);

protected:

int id;
ShipTypes type;


double v;
double control_velocity;		//describes, how fast a ship can turn; drops, if the ship is spoilt / damaged ..
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

// int g_height, g_height2;	// graphicsitem - height -> laenge		|| Not needed (Model-Data-concept)
// int g_width, g_width2;		// graphicsitem - width -> breite	||

PositioningStruct currentPosition;

int condition;
int controlcondition;		// Manoevrierzustand: wie gut kann das Schiff lenken, wie intakt sind die Segel
int seamen;			// Matrosen

};

#endif
