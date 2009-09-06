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

#ifndef _OBJECT_GRAPHICS_ITEM_H
#define _OBJECT_GRAPHICS_ITEM_H

#include "waren.h"
#include "definitions.h"
#include <QtGui/QGraphicsItem>

#include "shipdata.h"
#include "buildingdata.h"
#include "kontordata.h"
// #include ""

class ObjectGraphicsItem : public QGraphicsPixmapItem 
{


public:
ObjectGraphicsItem(ShipData *);
~ObjectGraphicsItem();
enum ObjectTypes
{
	Citybuilding,
	Factory,
	Kontor,
	Ship
} ;

QList<QGraphicsPixmapItem *> GraphicsMembersList;


// void setGraphicsItem(QGraphicsPixmapItem*);

void addMemberItem(QGraphicsItem *, QPointF);

bool setShipPos();

void rotateItem();

ShipData *shipdata;
BuildingData *buildingdata;

private:

int g_height, g_height2;	// graphicsitem - height -> laenge
int g_width, g_width2;		// graphicsitem - width -> breite

ObjectTypes type;
QStringList filenamelist;

protected:
void mousePressEvent(QGraphicsSceneMouseEvent *event);

};

#endif
