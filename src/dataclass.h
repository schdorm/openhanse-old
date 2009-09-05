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
#include <QtCore/QTimer>

#include "stadtklasse.h"
#include "kontordata.h"
#include "shipdata.h"
#include "wind.h"
#include "zeit.h"
#include "buildingclass.h"
#include "person.h"
#include "map.h"

class DataClass : public QObject
{
Q_OBJECT
public slots:
void calcData();
void startTimer();

public:
DataClass();
~DataClass();

CityClass *active_city;
KontorData *active_kontor;
ShipData *active_ship;
Person *active_char;

zeit gametime;
windclass wind;
MapClass currentMap;

void addBuilding(BuildingClass *);		// add a Building .... to the Building .... List
void addShip(ShipData *);
void addKontor(KontorData *);
void addCity(CityClass *);
void addPerson(Person *);

void setCurrentCity(QString);
void setCurrentCity(CityClass *);
bool anbord;

LandingProcess::landingstructure landingstruct;


QList<CityClass> ret_CityList();
QList<ShipData> ret_ShipList();
QList<KontorData> ret_KontorList();

private:
QTimer calc_data_timer;
int schwierigkeit;


QList <CityClass> CityList;
QList <ShipData> ShipList;
QList <BuildingClass> BuildingList;
QList <KontorData> KontorList;
QList <Person> PersonList;



};

#endif
