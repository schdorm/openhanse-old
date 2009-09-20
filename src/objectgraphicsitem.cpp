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
 
 #include "datamanager.h"
 #include "dataclass.h"
#include "objectgraphicsitem.h"
#include "shipdata.h"

#define _DEBUG_REFRESH_

#ifdef _DEBUG_REFRESH_
#include <QtDebug>
#endif
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
	m_shipdata = param_shipdata;
	m_type = ShipGraphics;
}

ObjectGraphicsItem::~ObjectGraphicsItem()
{
// delete shipdata;
// delete buildingdata;
}


void ObjectGraphicsItem::addMemberItem(QGraphicsItem *param_MemberItem, const QPointF &param_DestinationCoords)	// adds a graphicsItem to itself --> e.g. adds the body of the ship / the sails of the ship to the "Ship-Item"
{
// ->setParentItem(this);
addToGroup(param_MemberItem);
param_MemberItem->setPos(param_DestinationCoords);
if(m_type == ShipGraphics)
{
m_shipdata->g_width2 = boundingRect().width()/2;
m_shipdata->g_height2 = boundingRect().height()/2;
m_shipdata->g_width = boundingRect().width();
m_shipdata->g_height = boundingRect().height();

}
}

bool ObjectGraphicsItem::setShipPos()
{
#ifdef _DEBUG_REFRESH_
// qWarning() << "bool ObjectGraphicsItem::setShipPos()";
#endif
rotateItem();
QPointF destinationpoint = m_shipdata->currentPosition().generic_position;	// Position in the data-struct
if(destinationpoint != pos())				//if data-position != graphicsposition (this->pos())
{
setPos(destinationpoint);
return true;
}
else return false;
}

void ObjectGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
#ifdef _DEBUG_REFRESH_
qWarning() << "void ObjectGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event)";
#endif
	switch(m_type)
	{
		case ShipGraphics:
		{
			if(GAMEDATA->landingState().status() == Landing::OnBoard)
			{
			
			}
			else if(GAMEDATA->landingState().status() == Landing::AtLand)
			{
 				GAMEDATA->castOff(m_shipdata);
				qWarning() << "Onbord = true";
				GAMEDATA->landingProcess()->setStatus(Landing::OnBoard);
			}
			break;
		}
		default:
		break;
	}
}

void ObjectGraphicsItem::rotateItem()
{
//   static float lastdir;
	if(m_shipdata != 0 && m_lastdir != m_shipdata->dir())
	{
		m_lastdir = m_shipdata->dir();
		resetTransform();
		QTransform t;
		t.translate( boundingRect().width(), boundingRect().height() );
		t.rotateRadians(- m_lastdir);
		t.translate( - boundingRect().width(), - boundingRect().height() );
		setTransform( t );
	}
}
