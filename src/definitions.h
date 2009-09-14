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

#ifndef _DEFINITIONS_H
#define _DEFINITIONS_H
#include "waren.h"
#include <QtCore/QLineF>
#include <QtCore/QPoint>
#include <QtGui/QGraphicsPixmapItem>

namespace ObjectType
{
	enum object_types_def
	{
		Townhall,
		Market,
		Church,
		Port,
		Kontor,
		Bank,
		Tavern,
		namespacexyz,
		Factories,			// Werkstaetten
		Building_lot			// Baustelle
	};
}

namespace Direction
{
	enum directions
	{
	Up,
	Down,
	Left,
	Right
	
	};
}


namespace Tax
{
	enum levels
	{
		lowLevel,
		midlowLevel,
		midLevel,
		midhighLevel,
		highLevel
	};
}



struct PositioningStruct
{
QPointF generic_position;
// int x_posm, y_posm;
// int x_pos, y_pos;
QPointF m_position;
QString mapname;
QPoint mapcoords;
};

const int AKTUALISIERUNGSINTERVALL = 30;
const int WENDEGESCHWINDIGKEIT = 10;
const int BESCHLEUNIGUNG = 50;
const int WINDVERAENDERUNG = 30;

const float const_max_rudder_deflection = 0.04;

const int const_calc_data_delay = 200;

const int _oh_version = 35;

#endif
