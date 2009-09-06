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
 
#include "objectgraphicsitem.h"

ObjectGraphicsItem::ObjectGraphicsItem(ShipData *param_shipdata)
{/*
	shipdata = 0;
	buildingdata = 0;
	switch(type)
	{
		case Ship:
		{
			shipdata = new ShipData();
			break;
		}
		default:
			break;
	}*/
	shipdata = param_shipdata;
	type = Ship;
}

ObjectGraphicsItem::~ObjectGraphicsItem()
{
// delete shipdata;
// delete buildingdata;
}


void ObjectGraphicsItem::addMemberItem(QGraphicsItem *param_MemberItem, QPointF param_DestinationCoords)	// adds a graphicsItem to itself --> e.g. adds the body of the ship / the sails of the ship to the "Ship-Item"
{
param_MemberItem->setParentItem(this);
param_MemberItem->setPos(param_DestinationCoords);
if(type == Ship)
{
shipdata->g_width2 = boundingRect().width()/2;
shipdata->g_height2 = boundingRect().height()/2;
shipdata->g_width = boundingRect().width();
shipdata->g_height = boundingRect().height();

}
}

bool ObjectGraphicsItem::setShipPos()
{
rotateItem();
QPointF destinationpoint = shipdata->ret_CurrentPosition().generic_position;	// Position in the data-struct
if(destinationpoint != pos())				//if data-position != graphicsposition (this->pos())
{
setPos(destinationpoint);
return true;
}
else return false;
}

void ObjectGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

}

void ObjectGraphicsItem::rotateItem()
{
static float lastdir;
if(shipdata != 0 && lastdir != shipdata->ret_Dir())
{
lastdir = shipdata->ret_Dir();
		resetTransform();
		QTransform t;
		t.translate( boundingRect().width(), boundingRect().height() );
		t.rotateRadians(- lastdir);
		t.translate( - boundingRect().width(), - boundingRect().height() );
		setTransform( t );
}
}
