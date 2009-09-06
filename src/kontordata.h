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
private:
int kontorid;
public:

KontorData(){
static int idzaehler;
	kontorid=idzaehler;
	idzaehler++;


	for(int i=0; i< const_warenanzahl; i++)
	{
		storage.ware[i] = 0;
		production.ware[i] = 0;
	}

	storage.kapazitaet = 800;
	storage.fuellung = 0;
	storage.taler = 0;
	storage.mengenbilanz = 0;
	production.taler = 0;
	}


int getID()	const	{	return kontorid;	}
int getCityID()	const	{	return cityID;		}
// int cityid;
// QString stadt; --> inherited from BuildingClass --> cityname + cityID

Warenstruct storage;
Warenstruct production;
///
void productGoods();



void build(const QString &param_cityname, const int &param_cityid)
{
	cityname = param_cityname;
	cityID = param_cityid;
	tax_level = Tax::midhighLevel;
}

};


#endif