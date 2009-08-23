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
gamedata->active_ship->brake(1);
emit SIGgeschwindigkeit(0);
anbord=false;
qWarning() << "angelegt";
}

 void hauptfenster::einschiffen()
{
qWarning() << "abgelegt";
anbord=true;
}


void hauptfenster::landing()
{
anbord = false;
// bool directLanding;
QGraphicsItem *it;
foreach(it, landobjektliste)
{
	if(schiffskollision(it))
	{
		gamedata->landingstruct.landingstate = LandingProcess::AtLand;
		return;
	}
}
// if(directLanding)
// {
// }
// else
// {
gamedata->landingstruct.landingstate = LandingProcess::WaitingForDestination;
// }
// activeship.graphicsitem = gamedata->landingstruct.landingShip_gi;
gamedata->landingstruct.landingShip_gi = szene->addPixmap(QPixmap(":img/schiffe/sh08_braun.png"));
gamedata->landingstruct.landingShip_gi->setPos(gamedata->active_ship->graphicsitem->x() + (0.5 + ((cos(gamedata->active_ship->ret_Dir()) + 1)/2 ))* gamedata->active_ship->graphicsitem->boundingRect().width(), gamedata->active_ship->graphicsitem->y() + (0.5 + (sin(gamedata->active_ship->ret_Dir()) + 1)/2) 	* gamedata->active_ship->graphicsitem->boundingRect().height());

// gamedata->landingstruct.landingShip_gi->setPos(gamedata->active_ship->ret_MPos_X() + gamedata->active_ship->graphicsitem->boundingRect().x(), gamedata->active_ship->ret_MPos_Y() /*+ activeship.g_height2*/);

QTransform t = gamedata->active_ship->graphicsitem->transform();
gamedata->landingstruct.landingShip_gi->setTransform(t);
gamedata->landingstruct.landingShip_gi->setZValue(1);
gamedata->landingstruct.orientation = gamedata->active_ship->ret_Dir();
}

void hauptfenster::activeLanding()
{
const int const_landungstransparenz = 80;
centerOn(gamedata->landingstruct.landingShip_gi);
const int i = 3;		//Zufaelliger Einfluss .... 
if(!gamedata->landingstruct.correctOrientation)
{
	if((gamedata->landingstruct.orientation - gamedata->landingstruct.l_orientation < 0.03 && gamedata->landingstruct.orientation - gamedata->landingstruct.l_orientation > -0.03) || (gamedata->landingstruct.orientation - gamedata->landingstruct.l_orientation - 2 * M_PI < 0.03 && gamedata->landingstruct.orientation - gamedata->landingstruct.l_orientation - 2 * M_PI > -0.03) || (gamedata->landingstruct.orientation - gamedata->landingstruct.l_orientation + 2 * M_PI < 0.03 && gamedata->landingstruct.orientation - gamedata->landingstruct.l_orientation + 2 * M_PI > -0.03) )
	{
		gamedata->landingstruct.orientation = gamedata->landingstruct.l_orientation;
		gamedata->landingstruct.correctOrientation = true;
		 const int w = gamedata->landingstruct.landingShip_gi->boundingRect().width()/2;
		  const int h = gamedata->landingstruct.landingShip_gi->boundingRect().height()/2;
		  gamedata->landingstruct.landingShip_gi->resetTransform();
		QTransform t;
		t.translate( w, h );
		t.rotateRadians(-gamedata->landingstruct.orientation);
		t.translate( -w, -h );
		gamedata->landingstruct.landingShip_gi->setTransform( t );
		return;
	}

	if(gamedata->landingstruct.l_orientation - gamedata->landingstruct.orientation < -M_PI || gamedata->landingstruct.l_orientation - gamedata->landingstruct.orientation > M_PI)
	{
	gamedata->landingstruct.orientation -= 0.035;
// 	printf("--");
// 	qWarning() << gamedata->landingstruct.orientation;
	}
	else
	{
	gamedata->landingstruct.orientation += 0.035;
// 	printf("++");
// 	qWarning() << gamedata->landingstruct.orientation;
	}
	
	if(gamedata->landingstruct.orientation > (2 * M_PI) - 0.005)
	{
	gamedata->landingstruct.orientation = 0;
	}
	
	if(gamedata->landingstruct.orientation < (-2 * M_PI) + 0.005)
	{
	gamedata->landingstruct.orientation = 0;
	}


 	const int w = gamedata->landingstruct.landingShip_gi->boundingRect().width()/2;
 	const int h = gamedata->landingstruct.landingShip_gi->boundingRect().height()/2;
	gamedata->landingstruct.landingShip_gi->resetTransform();
	QTransform t;
	t.translate( w, h );
	t.rotateRadians(-gamedata->landingstruct.orientation);
	t.translate( -w, -h );
	gamedata->landingstruct.landingShip_gi->setTransform( t );


return;
}

//if ausrichtung -> drehen, return;
//else
// move um dy/length LE in Y und um dx/length EH in X-Richtung
else
{
		gamedata->landingstruct.landingShip_gi->moveBy(i * gamedata->landingstruct.vx, i * gamedata->landingstruct.vy);
		static int durchlauf;
		durchlauf ++;
		if(durchlauf%10 == 0)
		{
		
		QList <QGraphicsItem*>collList =  gamedata->landingstruct.landingShip_gi->collidingItems();
		if(!collList.isEmpty())
		{
		qWarning() << "debug A";
			QGraphicsPixmapItem *giit;		//GraphicsItemITerator -> land
// 			activeship.attribute.xposm = gamedata->landingstruct.landingShip_gi->x() + gamedata->landingstruct.landingShip_gi->boundingRect().width()/2;
// 			activeship.attribute.yposm = gamedata->landingstruct.landingShip_gi->y() + gamedata->landingstruct.landingShip_gi->boundingRect().height()/2;
			foreach(giit, landobjektliste)
			{
				if(kollision(gamedata->landingstruct.landingShip_gi,giit))
				{
				qWarning() << "Debug B";
				  int xms = gamedata->landingstruct.landingShip_gi->x() - giit->x(),	// X Mitte Schiff
				  yms = gamedata->landingstruct.landingShip_gi->y() - giit->y();	// Y ~
// 				  QImage colldimg = QImage((static_cast<QGraphicsPixmapItem*>(giit)).pixmap());
				  QImage colldimg = QImage(giit->pixmap().toImage());

				  if(xms > 0 && xms < colldimg.width() && yms >= 0 && yms < colldimg.height())
				    {
					float tempfloat = qAlpha(colldimg.pixel(xms, yms));
					qWarning() << tempfloat;

					if(tempfloat > const_landungstransparenz)
					{
// 						bremsfaktor = tempfloat;
						gamedata->landingstruct.landingstate = LandingProcess::AtLand;
					}
				    }
				}
			}
		}
		}
}

}
