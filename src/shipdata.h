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
// #include "map.h"

class ShipData
{

public:


enum ShipTypes
	{
	Kraier,
	Kogge,
	Holk
	};

// QString m_schiffsname;



// quint16 ladekapazitaet;

// QString filename;
// int schifflange;	//entspricht SchiffsBildY
// int schiffbreite;	//entspricht SchiffsBildX


 int g_height, g_height2;	// graphicsitem - height -> laenge		|| Not needed ?? (Model-Data-concept)
 int g_width, g_width2;		// graphicsitem - width -> breite	||


ShipData(const QString &);
~ShipData();



// control: set - fct.


void set_ToSettedSails(double);
void set_SailDir(double);
void set_ToRudderDir(double);
void set_ToDir(double);
void setName(const QString &);

bool setCargo(const Warenstruct&);

void brake(const double &);

void setMouseControl(bool);
void setControlDifficulty(int);

// control: Return - fct.

QString name()		const	{	return m_name;		}

double v()		const	{	return m_v;		}
double settedSails()	const	{	return m_settedSails;	}
double toSettedSails()	const	{	return m_toSettedSails;	}
double sailDir()	const	{	return m_sailDir;	}
double dir()		const	{	return m_dir;		}
double toDir()		const	{	return m_toDir;		}
double rudderDir()	const	{	return m_rudderDir;	}
double toRudderDir()	const	{	return m_toRudderDir;	}

Warenstruct cargo()	const	{	return m_cargo;		}
PositioningStruct currentPosition() const {return m_currentPosition;			}

int mPosX()		const	{	return m_currentPosition.m_position.x();	}
int mPosY()		const	{	return m_currentPosition.m_position.y();	}

int condition()		const	{	return m_condition;	}

// void bewegungsbeschreibung() --> calculate movement-things ...
void calcMovement(int, const double &);

void calcPos();

void setPos(const PositioningStruct&);

private:
bool m_setPosAllowed;
int m_delayvar;
int m_ControlDifficulty;
bool m_MouseControl;

protected:

Warenstruct m_cargo;			//Ladung

int m_id;
ShipTypes m_type;

QString m_name;				// the ships name

double m_v;
double m_controlVelocity;		//describes, how fast a ship can turn; drops, if the ship is spoilt / damaged ..
double m_settedSails;
double m_toSettedSails;
bool m_hasMoved;

double m_dir;
double m_toDir;	// mouse-control
double m_rudderDir;	//keyboard-control
double m_toRudderDir;	// 	''

// control-difficulty +
double m_sailDir;
// double toSailDir;


PositioningStruct m_currentPosition;
// UI6L
int m_condition;
int m_controlcondition;		// Manoevrierzustand: wie gut kann das Schiff lenken, wie intakt sind die Segel
int m_seamen;			// Matrosen

};

#endif
