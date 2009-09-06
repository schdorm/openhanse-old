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

#include "stadtklasse.h"
#include "kontordata.h"
#include "shipdata.h"
#include "wind.h"
#include "zeit.h"
#include "buildingclass.h"
#include "person.h"
#include "map.h"

class DataClass : public QThread
{
Q_OBJECT
public slots:
void calcData();
void startTimer();

void calcShipMovement();

signals:
void sig_newDay(int);

public:
DataClass();
~DataClass();

CityClass *active_city;
KontorData *active_kontor;
ShipData *active_ship;
Person *active_char;

zeit gametime;
Wind wind;
Map *currentMap;

QList <Map*> maplist;

void addBuilding(const BuildingClass &);		// add a Building .... to the Building .... List
void addShip(ShipData *);
void addKontor(const KontorData &);
void addCity(const CityClass &);
void addPerson(const Person &);

void setCurrentCity();
void setCurrentCity(CityClass *);

void pause();

bool anbord;

LandingProcess::landingstructure landingstruct;


QList<CityClass> ret_CityList() const;
QList<ShipData*> ret_ShipList() const;
QList<KontorData> ret_KontorList() const;


private:
QTimer calc_data_timer;
QTimer calc_ship_movement_timer;
int cycle;



protected:
// bool singleplayer;
void run();

int schwierigkeit;
QList <CityClass> CityList;
QList <ShipData *> ShipList;
QList <BuildingClass> BuildingList;
QList <KontorData> KontorList;
QList <Person> PersonList;
ShipData *shipiterator;		//pointer for iterating through lists
};

#endif
