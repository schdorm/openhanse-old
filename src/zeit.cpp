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

#include "zeit.h"

// zeit::zeit()
// {
// existingClock = false;
// day_length = 2000;
// year = 1350;
// month = 4;
// day = 1;
// hour = 12;
// minute = 0;
// }

void zeit::init()
{
existingClock = false;
day_length = 2000;
year = 1350;
month = 4;
day = 1;
hour = 12;
minute = 0;
}

double zeit::retMinute()
{
	return minute;
}

int zeit::retHour()
{
	return hour;
}

int zeit::retDay()
{
	return day;
}

int zeit::retMonth()
{
	return month;
}

int zeit::retYear()
{
	return year;
}

int zeit::retDayLength()
{
return day_length;
}


void zeit::setDayLength(int dlparam)
{
	day_length = dlparam;
}

void zeit::setMinute(double min)
{
	minute = min;
}

void zeit::setHour(int hr_param)
{
	hour = hr_param;
}

void zeit::setDay(int dayparam)
{
	day = dayparam;
}

void zeit::setMonth(int monthparam)
{
	month = monthparam;
}

void zeit::setYear(int yearparam)
{
	year = yearparam;
}

bool zeit::refreshTime()		//bool -> new Day ?
{

if(existingClock)
{
	refreshClock();
}

minute += day_length/1440;
if(minute>=60)
{
	minute = 0;
	hour ++;
	if(hour >=24)
	{
		day++;
		hour = 0;
		
		if((day > 31 && (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)) ||
		(day > 30 && ( month == 4 || month == 6 || month == 9 || month == 11)) ||
		(month == 2 && ((day > 28 && (year%4 != 0 || year%100 == 0)) || (day > 29 && year%4 == 0))))
		{
			day = 1;
			month++;
		}
		
		return true;		//new day is rising
	}
}

return false;				// still the old day ...
}

void zeit::refreshClock()
{

// {
// stunde += tageslaenge/24;
// QList <QGraphicsItem*> sliste = szene[aszene]->items();
/*if(uhr){
QList <QGraphicsItem*> sliste = szene->items();

for(QList <QGraphicsItem*>::iterator it = sliste.begin(); it < sliste.end(); ++it)
{
QGraphicsItem *handler = *it;
if(handler->toolTip() == "grosser Zeiger")
{
// 	static int minute; minute ++;
	handler->resetTransform();
	QTransform t;
	const int w = ((handler->boundingRect().width()/2));
	const int h = int(handler->boundingRect().height()-1.8);

	t.translate( w, h );
	t.rotateRadians(minute * M_PI / 30);
	t.translate( -w, -h );
	handler->setTransform( t );
	*it = handler;
}
if(handler->toolTip() == "kleiner Zeiger")
{
// 	static int minute;

	handler->resetTransform();
	QTransform t;
	const int w = int((handler->boundingRect().width()/2));
	const int h = int(handler->boundingRect().height()-1.8);

	t.translate( w, h );
	t.rotateRadians((minute/60 + stunde)* M_PI /6);
// 	t.rotateRadians(minute * M_PI / 150);
	t.translate( -w, -h );
	handler->setTransform( t );
	*it = handler;
}
}
}}
*/
}


void zeit::setClockHands(QGraphicsPixmapItem *sch, QGraphicsPixmapItem *bch)
{
	smallclockhand = sch;
	bigclockhand = bch;
}

