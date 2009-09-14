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
#ifndef _BUILDINGDATA_H
#define _BUILDINGDATA_H

#include "definitions.h"

class BuildingData		//Gebaudeklasse
{
public:
// QString name;

// void set_GraphicsItem(QGraphicsItem *);

protected:
int m_BuildingID;
// QString cityname;
// int cityID;
// int workers;
// Tax::levels tax_level;
// // QGraphicsItem *graphicsitem;
// ObjectType::object_types_def type;
// double state;

QString m_CityName;
int m_CityID;
int m_Workers;
Tax::levels m_TaxLevel;
QGraphicsItem *m_graphicsitem;
ObjectType::object_types_def m_Type;
double m_state;
};

#endif
