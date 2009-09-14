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

#ifndef _kontorklasse_h
#define _kontorklasse_h

#include "waren.h"
#include "buildingdata.h"

class KontorData : public BuildingData
{
public:

KontorData(){
static int idzaehler;
	m_kontorid = idzaehler;
	idzaehler++;


	for(int i=0; i< const_warenanzahl; i++)
	{
		m_storage.ware[i] = 0;
		m_production.ware[i] = 0;
	}

	m_storage.kapazitaet = 800;
	m_storage.fuellung = 0;
	m_storage.taler = 0;
	m_storage.mengenbilanz = 0;
	m_production.taler = 0;
	}


int getID()	const	{	return m_kontorid;	}
int getCityID()	const	{	return m_CityID;		}
// int cityid;
// QString stadt; --> inherited from BuildingClass --> cityname + cityID

const Warenstruct &storage ()	const	{	return m_storage;	}

///
void productGoods();
void setStorage(const Warenstruct &param_storage)
{
m_storage = param_storage;
}


void build(const QString &param_cityname, int param_cityid)
{
	m_CityName = param_cityname;
	m_CityID = param_cityid;
	m_TaxLevel = Tax::midhighLevel;
}

private:
Warenstruct m_storage;
Warenstruct m_production;
int m_kontorid;
};


#endif
