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
#include "hauptfenster.h"

#include <QtCore/QtDebug>

#include <math.h>

void hauptfenster::landgang()
{
GAMEDATA->active_ship->brake(1);
emit SIGgeschwindigkeit(0);
GAMEDATA->anbord=false;
qWarning() << "angelegt";
}

 void hauptfenster::einschiffen()
{
qWarning() << "abgelegt";
GAMEDATA->anbord=true;
}


void hauptfenster::landing()
{
GAMEDATA->anbord = false;
// bool directLanding;
QGraphicsItem *it;
foreach(it, landobjektliste)
{
	if(schiffskollision(it))
	{
		GAMEDATA->landingstruct.landingstate = LandingProcess::AtLand;
// 		GAMEDATA->active_char->fillDownPixmapList(QImage(":img/sonstige/charset1.png"), QRect(85,6,21,40), 6);
// 		GAMEDATA->active_char->fillUpPixmapList(QImage(":img/sonstige/charset1.png"), QRect(13,344,21,40), 1);
// 		GAMEDATA->active_char->fillUpPixmapList(QImage(":img/sonstige/charset1.png"), QRect(84,344,21,40), 6);
// 		GAMEDATA->active_char->fillDownPixmapList(QImage(":img/sonstige/charset1_bearb_scal_2x.png"), QRect(137,0,20,40), 1);
// 		GAMEDATA->active_char->fillDownPixmapList(QImage(":img/sonstige/charset1_bearb_scal_2x.png"), QRect(0,0,20,40), 6);
///		GAMEDATA->active_char->fillUpPixmapList(QImage(":img/sonstige/charset1_bearb_scal_2x.png"), QRect(137,0,20,40), 1);
///		GAMEDATA->active_char->fillUpPixmapList(QImage(":img/sonstige/charset1_bearb_scal_2x.png"), QRect(0,0,20,40), 6);
		return;
		
		// Side: standing: 18 [139|40]; walking: 22[0|40]; Down: walking 20[0|0]; standing: 20 [137|0]
	}
}
// if(directLanding)
// {
// }
// else
// {
GAMEDATA->landingstruct.landingstate = LandingProcess::WaitingForDestination;
// }
// activeship.graphicsitem = GAMEDATA->landingstruct.landingShip_gi;
// GAMEDATA->landingstruct.landingShip_gi = szene->addPixmap(QPixmap(":img/schiffe/sh08_braun.png"));
GAMEDATA->landingstruct.landingShip_gi = scene()->addPixmap(QPixmap(":img/schiffe/beiboot_5_30x95.png"));

///GAMEDATA->landingstruct.landingShip_gi->setPos(GAMEDATA->active_ship->ret_CurrentPos.generic_position.x() + (0.5 + ((cos(GAMEDATA->active_ship->ret_Dir()) + 1)/2 ))* GAMEDATA->active_ship->graphicsitem->boundingRect().width(), GAMEDATA->active_ship->graphicsitem->y() + (0.5 + (sin(GAMEDATA->active_ship->ret_Dir()) + 1)/2) 	* GAMEDATA->active_ship->graphicsitem->boundingRect().height());

// GAMEDATA->landingstruct.landingShip_gi->setPos(GAMEDATA->active_ship->ret_MPos_X() + GAMEDATA->active_ship->graphicsitem->boundingRect().x(), GAMEDATA->active_ship->ret_MPos_Y() /*+ activeship.g_height2*/);
/*
QTransform t = GAMEDATA->active_ship->graphicsitem->transform();
GAMEDATA->landingstruct.landingShip_gi->setTransform(t);
GAMEDATA->landingstruct.landingShip_gi->setZValue(1);
GAMEDATA->landingstruct.orientation = GAMEDATA->active_ship->ret_Dir();*/
}

void hauptfenster::activeLanding()
{
const int const_landungstransparenz = 80;
centerOn(GAMEDATA->landingstruct.landingShip_gi);
const int i = 3;		//Zufaelliger Einfluss .... 
if(!GAMEDATA->landingstruct.correctOrientation)
{
	if((GAMEDATA->landingstruct.orientation - GAMEDATA->landingstruct.l_orientation < 0.03 && GAMEDATA->landingstruct.orientation - GAMEDATA->landingstruct.l_orientation > -0.03) || (GAMEDATA->landingstruct.orientation - GAMEDATA->landingstruct.l_orientation - 2 * M_PI < 0.03 && GAMEDATA->landingstruct.orientation - GAMEDATA->landingstruct.l_orientation - 2 * M_PI > -0.03) || (GAMEDATA->landingstruct.orientation - GAMEDATA->landingstruct.l_orientation + 2 * M_PI < 0.03 && GAMEDATA->landingstruct.orientation - GAMEDATA->landingstruct.l_orientation + 2 * M_PI > -0.03) )
	{
		GAMEDATA->landingstruct.orientation = GAMEDATA->landingstruct.l_orientation;
		GAMEDATA->landingstruct.correctOrientation = true;
		 const int w = GAMEDATA->landingstruct.landingShip_gi->boundingRect().width()/2;
		  const int h = GAMEDATA->landingstruct.landingShip_gi->boundingRect().height()/2;
		  GAMEDATA->landingstruct.landingShip_gi->resetTransform();
		QTransform t;
		t.translate( w, h );
		t.rotateRadians(-GAMEDATA->landingstruct.orientation);
		t.translate( -w, -h );
		GAMEDATA->landingstruct.landingShip_gi->setTransform( t );
		return;
	}

	if(GAMEDATA->landingstruct.l_orientation - GAMEDATA->landingstruct.orientation < -M_PI || GAMEDATA->landingstruct.l_orientation - GAMEDATA->landingstruct.orientation > M_PI)
	{
	GAMEDATA->landingstruct.orientation -= 0.035;
// 	printf("--");
// 	qWarning() << GAMEDATA->landingstruct.orientation;
	}
	else
	{
	GAMEDATA->landingstruct.orientation += 0.035;
// 	printf("++");
// 	qWarning() << GAMEDATA->landingstruct.orientation;
	}
	
	if(GAMEDATA->landingstruct.orientation > (2 * M_PI) - 0.005)
	{
	GAMEDATA->landingstruct.orientation = 0;
	}
	
	if(GAMEDATA->landingstruct.orientation < (-2 * M_PI) + 0.005)
	{
	GAMEDATA->landingstruct.orientation = 0;
	}


 	const int w = GAMEDATA->landingstruct.landingShip_gi->boundingRect().width()/2;
 	const int h = GAMEDATA->landingstruct.landingShip_gi->boundingRect().height()/2;
	GAMEDATA->landingstruct.landingShip_gi->resetTransform();
	QTransform t;
	t.translate( w, h );
	t.rotateRadians(-GAMEDATA->landingstruct.orientation);
	t.translate( -w, -h );
	GAMEDATA->landingstruct.landingShip_gi->setTransform( t );


return;
}

//if ausrichtung -> drehen, return;
//else
// move um dy/length LE in Y und um dx/length EH in X-Richtung
else
{
		GAMEDATA->landingstruct.landingShip_gi->moveBy(i * GAMEDATA->landingstruct.vx, i * GAMEDATA->landingstruct.vy);
		static int durchlauf;
		durchlauf ++;
		if(durchlauf%10 == 0)
		{
		
		QList <QGraphicsItem*>collList =  GAMEDATA->landingstruct.landingShip_gi->collidingItems();
		if(!collList.isEmpty())
		{
		qWarning() << "debug A";
			QGraphicsPixmapItem *giit;		//GraphicsItemITerator -> land
// 			activeship.attribute.xposm = GAMEDATA->landingstruct.landingShip_gi->x() + GAMEDATA->landingstruct.landingShip_gi->boundingRect().width()/2;
// 			activeship.attribute.yposm = GAMEDATA->landingstruct.landingShip_gi->y() + GAMEDATA->landingstruct.landingShip_gi->boundingRect().height()/2;
			foreach(giit, landobjektliste)
			{
				if(kollision(GAMEDATA->landingstruct.landingShip_gi,giit))
				{
				qWarning() << "Debug B";
				  int xms = GAMEDATA->landingstruct.landingShip_gi->x() - giit->x(),	// X Mitte Schiff
				  yms = GAMEDATA->landingstruct.landingShip_gi->y() - giit->y();	// Y ~
// 				  QImage colldimg = QImage((static_cast<QGraphicsPixmapItem*>(giit)).pixmap());
				  QImage colldimg = QImage(giit->pixmap().toImage());

				  if(xms > 0 && xms < colldimg.width() && yms >= 0 && yms < colldimg.height())
				    {
					float tempfloat = qAlpha(colldimg.pixel(xms, yms));
					qWarning() << tempfloat;

					if(tempfloat > const_landungstransparenz)
					{
// 						bremsfaktor = tempfloat;
						GAMEDATA->landingstruct.landingstate = LandingProcess::AtLand;
					}
				    }
				}
			}
		}
		}
}

}
