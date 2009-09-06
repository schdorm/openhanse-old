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

#ifndef _MAPCLASS_H
#define _MAPCLASS_H


#include "definitions.h"
#include "mapobject.h"


class Map
{
public:

	Map();
	~Map();

	enum MapType
	{
		 sea,			// 001
		 coast,			// 010 || -> | -> 110
		 land,			// 011 || -> | -> 111
		 coast_city,			// 100
		 land_city
	};
	enum Orientations
	{
		null,
		North,
		East,
		South,
		West
	};

	QList <MapObject*> objectlist;
// QList <ShipClass *> ships;
	void loadStartMap(const QString &);

	bool loadMap(const Orientations &);


QPoint ret_Coordinate()		{	return coordinate;	}
QSize ret_Size()		{	return size;		}
QString ret_Cityname()		{	return cityname;	}
QString ret_Background()	{	return background;	}

QString ret_Mapnorth()		{	return mapnorth;	}
QString ret_Mapeast()		{	return mapeast;		}
QString ret_Mapsouth()		{	return mapsouth;	}
QString ret_Mapwest()		{	return mapwest;		}

MapType ret_Type()		{	return type;		}

private:
bool loadMap(QString);

QString m_mapdirectory;

protected:

QString filename;
QPoint coordinate;
QSize size;
bool isCity;
QString cityname;
QString background;
QString mapnorth;
QString mapeast;
QString mapsouth;
QString mapwest;
MapType type;

};

#endif
