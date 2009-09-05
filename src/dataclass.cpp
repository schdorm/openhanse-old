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

DataClass::DataClass()
{
active_ship = new ShipData();
// active_ship->init();
active_city = new CityClass();
active_kontor = new KontorData();
active_char = new Person();

landingstruct.landingstate = LandingProcess::NotActive;
connect(&calc_data_timer, SIGNAL(timeout()), this, SLOT(calcData()));
}

DataClass::~DataClass()
{
delete active_ship;
delete active_city;
delete active_kontor;
delete active_char;

}

void DataClass::startTimer()
{
calc_data_timer.start(const_calc_data_delay);
}

void DataClass::calcData()
{

}


void DataClass::addBuilding(BuildingClass *param_building)
{
BuildingList << *param_building;
}

void DataClass::addShip(ShipData *param_ship)
{
ShipList << *param_ship;
}

void DataClass::addKontor(KontorData *param_kontor)
{
KontorList << *param_kontor;
}

void DataClass::addCity(CityClass *param_city)
{
CityList << *param_city;
}

void DataClass::addPerson(Person *param_person)
{
PersonList << *param_person;
}

void DataClass::setCurrentCity(CityClass *param_city)
{
active_city = param_city;
}

void DataClass::setCurrentCity(QString param_cityname)
{
	currentMap.cityname = param_cityname;
	currentMap.isCity = true;
	foreach(*active_city, CityList)
	{
		if(active_city->cityname == currentMap.cityname)
		{
			break;
		}
	}
}

QList<CityClass> DataClass::ret_CityList()
{
return CityList;
}
QList<ShipData> DataClass::ret_ShipList()
{
return ShipList;
}
QList<KontorData> DataClass::ret_KontorList()
{
return KontorList;
}



