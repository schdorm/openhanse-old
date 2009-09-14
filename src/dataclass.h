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

#ifndef _DATA_CLASS_H
#define _DATA_CLASS_H

#include <QtCore/QObject>
#include <QtCore/QThread>
#include <QtCore/QTimer>

// #include "stadtklasse.h"
// #include "kontordata.h"
// #include "shipdata.h"
#include "wind.h"
#include "zeit.h"
#include "buildingclass.h"
// #include "person.h"
#include "map.h"
 #include "landing.h"
 
 
class CityClass;
class KontorData;
class ShipData;
class Person;
class BuildingClass;
// class Map;

class DataClass : public QThread
{
Q_OBJECT
public:
DataClass();
~DataClass();


void addBuilding(const BuildingClass &);		// add a Building .... to the Building .... List
void addShip(const ShipData &);
void addKontor(const KontorData &);
void addCity(const CityClass &);
void addPerson(const Person &);
void addMap(const Map &);

void setCurrentCity();
void setCurrentCity(CityClass *);


void pause();



// QList<CityClass> ret_CityList() const;
// QList<ShipData> ret_ShipList() const;
// QList<KontorData> ret_KontorList() const;

void manageMapReading(const Map::Orientations &orientation);

const QList <ShipData> * shipList ()	const	{	return &m_ShipList;	}
const QList <Person> * personList ()	const	{	return &m_PersonList;	}
const QList <CityClass> * cityList()	const	{	return &m_CityList;	}
const QList <KontorData> * kontorList()	const	{	return &m_KontorList;	}
const QList <BuildingClass> * buildingList() const{	return &m_BuildingList;	}

const QList <Map> * MapList()		const	{	return &m_MapList;	}

#ifdef _RELEASE_
const zeit & gametime()		const	{	return m_gametime;	}
const Wind & wind()		const	{	return m_wind;		}
#else
zeit & gametime()			{	return m_gametime;	}
Wind & wind()				{	return m_wind;		}
#endif

CityClass *activeCity	()		{	return m_ActiveCity;	}
KontorData *activeKontor()		{	return m_ActiveKontor;	}
ShipData *activeShip	()		{	return m_ActiveShip;	}
Person *activeChar	()		{	return m_ActiveChar;	}

Map *currentMap		()		{	return m_CurrentMap;	}

bool anbord		() const 		{	return m_anbord;	}

// LandingProcess::landingstructure *landingstruct() {	return &m_landingstructure;	}

// const LandingProcess::landingstructure *landingstruct() const {	return &m_landingstructure;	}

const Landing &landingState	() const	{	return m_landingprocess;	}
Landing *landingProcess		()		{	return &m_landingprocess;	}


public slots:
void calcData();
void startTimer();

void calcShipMovement();

signals:
void sig_newDay(int);

private:
QTimer calc_data_timer;
QTimer calc_ship_movement_timer;
int cycle;

void produktion(int);


protected:
// bool singleplayer;
void run();

bool m_anbord;

int m_schwierigkeit;

zeit m_gametime;
Wind m_wind;

QList <CityClass> m_CityList;
QList <ShipData> m_ShipList;
QList <BuildingClass> m_BuildingList;
QList <KontorData> m_KontorList;
QList <Person> m_PersonList;

QList <Map> m_MapList;			// used only if cache maps is enabled

// ShipData *shipiterator;		//pointer for iterating through lists
// LandingProcess::landingstructure m_landingstructure;
Landing m_landingprocess;

CityClass *m_ActiveCity;
KontorData *m_ActiveKontor;
ShipData *m_ActiveShip;
Person *m_ActiveChar;

Map *m_CurrentMap;

};

#endif
