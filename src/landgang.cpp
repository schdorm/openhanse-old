/***************************************************************************
 *   Copyright (C) 2009 by Christian Doerffel   *
 *   christian.doerffel@googlemail.com   *
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
activeship.attribute.geschwindigkeit = 0;
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
		landingstruct.landingstate = LandingProcess::AtLand;
		return;
	}
}
// if(directLanding)
// {
// }
// else
// {
landingstruct.landingstate = LandingProcess::WaitingForDestination;
// }
activeship.graphicsitem = testschiff;
testschiff = szene->addPixmap(QPixmap(":img/schiffe/sh08_braun.png"));
testschiff->setPos(activeship.graphicsitem->x() + (0.5 + ((cos(activeship.attribute.ausrichtung) + 1)/2 ))* activeship.graphicsitem->boundingRect().width(), activeship.graphicsitem->y() + (0.5 + (sin(activeship.attribute.ausrichtung) + 1)/2) 	* activeship.graphicsitem->boundingRect().height());
QTransform t = activeship.graphicsitem->transform();
testschiff->setTransform(t);
landingstruct.orientation = activeship.attribute.ausrichtung;
}

void hauptfenster::activeLanding()
{
centerOn(testschiff);
const int i = 1;		//Zufaelliger Einfluss .... 
if(!landingstruct.correctOrientation)
{
	if((landingstruct.orientation - landingstruct.l_orientation < 0.03 && landingstruct.orientation - landingstruct.l_orientation > -0.03) || (landingstruct.orientation - landingstruct.l_orientation - 2 * M_PI < 0.03 && landingstruct.orientation - landingstruct.l_orientation - 2 * M_PI > -0.03) || (landingstruct.orientation - landingstruct.l_orientation + 2 * M_PI < 0.03 && landingstruct.orientation - landingstruct.l_orientation + 2 * M_PI > -0.03) )
	{
		landingstruct.orientation = landingstruct.l_orientation;
		landingstruct.correctOrientation = true;
		 const int w = testschiff->boundingRect().width()/2;
		  const int h = testschiff->boundingRect().height()/2;
		  testschiff->resetTransform();
		QTransform t;
		t.translate( w, h );
		t.rotateRadians(-landingstruct.orientation);
		t.translate( -w, -h );
		testschiff->setTransform( t );
		return;
	}

	if(landingstruct.l_orientation - landingstruct.orientation < -M_PI || landingstruct.l_orientation - landingstruct.orientation > M_PI)
	{
	landingstruct.orientation -= 0.035;
// 	printf("--");
// 	qWarning() << landingstruct.orientation;
	}
	else
	{
	landingstruct.orientation += 0.035;
// 	printf("++");
// 	qWarning() << landingstruct.orientation;
	}
	
	if(landingstruct.orientation > (2 * M_PI) - 0.005)
	{
	landingstruct.orientation = 0;
	}
	
	if(landingstruct.orientation < (-2 * M_PI) + 0.005)
	{
	landingstruct.orientation = 0;
	}


 	const int w = testschiff->boundingRect().width()/2;
 	const int h = testschiff->boundingRect().height()/2;
	testschiff->resetTransform();
	QTransform t;
	t.translate( w, h );
	t.rotateRadians(-landingstruct.orientation);
	t.translate( -w, -h );
	testschiff->setTransform( t );


return;
}

//if ausrichtung -> drehen, return;
//else
// move um dy/length LE in Y und um dx/length EH in X-Richtung
else
{
		testschiff->moveBy(i * landingstruct.vx, i * landingstruct.vy);
}

}
