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

#include "dataclass.h"
#include <QtDebug>

// #define _DEBUG_CALC_

DataClass::DataClass()
{
active_ship = new ShipData();
// active_ship->init();
active_city = new CityClass();
active_kontor = new KontorData();
active_char = new Person();

currentMap = 0;

landingstruct.landingstate = LandingProcess::NotActive;
connect(&calc_data_timer, SIGNAL(timeout()), this, SLOT(calcData()));
// singleplayer = true;
}

DataClass::~DataClass()
{
	delete active_ship;
	delete active_city;
	delete active_kontor;
	delete active_char;
	maplist << currentMap;
	foreach(currentMap, maplist)
	{
		delete currentMap;
	}
}

void DataClass::startTimer()
{
calc_data_timer.start(const_calc_data_delay);
// if(singleplayer)
{
start(QThread::HighestPriority);
}
}

void DataClass::calcData()
{
#ifdef _DEBUG_CALC_
qWarning() << "DataClass::calcData()";
#endif
cycle++;
if(gametime.refreshTime())			//returns true, when a new day starts ...
{
	qWarning() << "A new day is rising up ... :-)";
	emit sig_newDay(cycle);
	if(cycle > 2000000000)	// 2 000 000 000
	{
		cycle = 0;
	}
}
wind.refresh();
foreach(shipiterator, ShipList)
{
shipiterator->calcMovement(wind.v(), wind.dir());
}
}

void DataClass::pause()
{
qWarning() << "void DataClass::pause()";
calc_data_timer.stop();
// calc_ship_movement_timer.stop();
quit();
}

void DataClass::addBuilding(const BuildingClass &param_building)
{
BuildingList << param_building;
}

void DataClass::addShip(ShipData *param_ship)
{
ShipList << param_ship;
}

void DataClass::addKontor(const KontorData &param_kontor)
{
KontorList << param_kontor;
}

void DataClass::addCity(const CityClass &param_city)
{
CityList << param_city;
}

void DataClass::addPerson(const Person &param_person)
{
PersonList << param_person;
}

void DataClass::setCurrentCity(CityClass *param_city)
{
active_city = param_city;
}

void DataClass::setCurrentCity()
{
	foreach(*active_city, CityList)
	{
		if(active_city->cityname == currentMap->ret_Cityname())
		{
			break;
		}
	}
}

QList<CityClass> DataClass::ret_CityList() const
{
return CityList;
}
QList<ShipData*> DataClass::ret_ShipList() const
{
return ShipList;
}
QList<KontorData> DataClass::ret_KontorList() const
{
return KontorList;
}


void DataClass::run()
{
calc_ship_movement_timer.start(20);
connect(&calc_ship_movement_timer, SIGNAL(timeout()), this, SLOT(calcShipMovement()));
exec();
// setPriority(QThread::HighestPriority);
}

void DataClass::calcShipMovement()
{
#ifdef _DEBUG_CALC_
qWarning() << "void DataClass::calcShipMovement()";
#endif
foreach(shipiterator, ShipList)
{
shipiterator->calcPos();
}

}

