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
active_ship = new ShipClass();
// active_ship->init();
active_city = new CityClass();
active_kontor = new KontorClass();

landingstruct.landingstate = LandingProcess::NotActive;
}



void DataClass::addBuilding(BuildingClass *param_building)
{
BuildingList << *param_building;
}

void DataClass::addShip(ShipClass *param_ship)
{
ShipList << *param_ship;
}

void DataClass::addKontor(KontorClass *param_kontor)
{
KontorList << *param_kontor;
}

void DataClass::addCity(CityClass *param_city)
{
CityList << *param_city;
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
QList<ShipClass> DataClass::ret_ShipList()
{
return ShipList;
}
QList<KontorClass> DataClass::ret_KontorList()
{
return KontorList;
}



