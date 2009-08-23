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

const int _oh_version = 35;
namespace MapType
{
	enum mtyp
	{
		 sea,			// 001
		 coast,			// 010 || -> | -> 110
		 land,			// 011 || -> | -> 111
		 coast_city,			// 100
		 land_city
	};
}

namespace LandingProcess
{
	enum landing_process_states
	{
		NotActive,
		WaitingForDestination,
		ActiveLanding,
		AtLand
	};
	struct landingstructure{
		landing_process_states landingstate;
		QLineF landing_line;
		bool correctOrientation;
		double l_orientation;
		double orientation;
		double vx, vy;
		QGraphicsPixmapItem *landingShip_gi;
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

namespace ShipType
{
enum schiffstypen
	{
	Kraier,
	Kogge,
	Holk
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

const int const_grundpreis[const_warenanzahl] = {50, 95, 84, 67, 10000, 350, 950, 168, 270, 400, 107, 60, 130, 210, 30, 50, 300, 190, 3800, 5100, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30};


#endif
