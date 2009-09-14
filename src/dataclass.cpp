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
#include "stadtklasse.h"
#include "kontordata.h"
#include "shipdata.h"
// #include "wind.h"
// #include "zeit.h"
#include "buildingclass.h"
#include "person.h"
#include "map.h"
#include "landing.h"

#include "dataclass.h"
#include "datamanager.h"
#include "settings.h"

#include <QtDebug>

// #define _DEBUG_CALC_

DataClass::DataClass()
{
m_ActiveShip = new ShipData(QString());
// m_ActiveShip->init();
m_ActiveCity = 0;
m_ActiveKontor = new KontorData();
m_ActiveChar = new Person();

m_CurrentMap = new Map();

m_landingprocess.setStatus(Landing::NotActive);
connect(&calc_data_timer, SIGNAL(timeout()), this, SLOT(calcData()));
// singleplayer = true;
m_anbord = true;
}

DataClass::~DataClass()
{
	delete m_ActiveShip;
	delete m_ActiveCity;
	delete m_ActiveKontor;
	delete m_ActiveChar;
//  	m_MapList << *currentMap;
// 	foreach(*currentMap, m_MapList)
// 	{
 		delete m_CurrentMap;
// 	}
// 	m_MapList.clear();
// 	m_CityList.clear();
// 	m_KontorList.clear();
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
	if(m_gametime.refreshTime())			//returns true, when a new day starts ...
	{
		qWarning() << "A new day is rising up ... :-)";
// 		emit sig_newDay(cycle);
		produktion(cycle);
		if(cycle > 2000000000)	// 2 000 000 000
		{
			cycle = 0;
		}
	}
	m_wind.refresh();
	for(QList<ShipData>::iterator it = m_ShipList.begin(); it != m_ShipList.end(); ++it)
// 	foreach(shipiterator, ShipList)
	{
		it->calcMovement(m_wind.v(), m_wind.dir());
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
m_BuildingList << param_building;
}

void DataClass::addShip(const ShipData &param_ship)
{
m_ShipList << param_ship;
}

void DataClass::addKontor(const KontorData &param_kontor)
{
m_KontorList << param_kontor;
}

void DataClass::addCity(const CityClass &param_city)
{
m_CityList << param_city;
}

void DataClass::addPerson(const Person &param_person)
{
m_PersonList << param_person;
}

void DataClass::addMap(const Map &param_map)
{
m_MapList << param_map;
}

void DataClass::setCurrentCity(CityClass *param_city)
{
m_ActiveCity = param_city;
}

void DataClass::setCurrentCity()
{
	for(QList<CityClass>::iterator it = m_CityList.begin(); it != m_CityList.end(); ++it)
// 	foreach(*m_ActiveCity, CityList)
	{
		if(it->cityname() == m_CurrentMap->cityname())
		{
			m_ActiveCity = &*it;
			break;
		}
	}
}


// QList<CityClass> DataClass::ret_CityList() const
// {
// 	return m_CityList;
// }
// QList<ShipData> DataClass::ret_ShipList() const
// {
// 	return m_ShipList;
// }
// QList<KontorData> DataClass::ret_KontorList() const
// {
// 	return m_KontorList;
// }


void DataClass::manageMapReading(const Map::Orientations &orientation)
{

	delete m_CurrentMap;

	m_CurrentMap = new Map();
	
	m_CurrentMap->loadMap(orientation);
	
	if(SETTINGS->cacheMaps())
	{
		addMap(*m_CurrentMap);
	}
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
// foreach(shipiterator, ShipList)

	for(QList<ShipData>::iterator it = m_ShipList.begin(); it != m_ShipList.end(); ++it)
	{
		it->calcPos();
	}

}

