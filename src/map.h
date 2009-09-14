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

// QList <ShipClass *> ships;
	void loadStartMap(const QString &);

	bool loadMap(Orientations);

const QList <MapObject*> &objectList() const	{return m_ObjectList;	}

const QPoint &coordinates()	const	{	return m_coordinate;	}
const QSize &size()		const	{	return m_size;		}
const QString &cityname()	const	{	return m_cityname;	}
const QString &background()	const	{	return m_background;	}

const QString &mapnorth()	const	{	return m_mapnorth;	}
const QString &mapeast()	const	{	return m_mapeast;	}
const QString &mapsouth()	const	{	return m_mapsouth;	}
const QString &mapwest()	const	{	return m_mapwest;	}

MapType type()		const	{	return m_type;		}

private:
bool loadMap(QString);

// QString m_mapdirectory;

protected:

QString m_filename;
QPoint m_coordinate;
QSize m_size;
bool m_isCity;
QString m_cityname;
QString m_background;
QString m_mapnorth;
QString m_mapeast;
QString m_mapsouth;
QString m_mapwest;
MapType m_type;

	QList <MapObject*> m_ObjectList;

};

#endif
