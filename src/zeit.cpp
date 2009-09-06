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

zeit::zeit()
{
 m_existingClock = false;
 m_day_length = 2000;
 m_year = 1350;
 m_month = 4;
 m_day = 1;
 m_hour = 12;
 m_minute = 0;
}

void zeit::init()
{
m_existingClock = false;
m_day_length = 2000;
m_year = 1350;
m_month = 4;
m_day = 1;
m_hour = 12;
m_minute = 0;
}

double zeit::minute() const
{
	return m_minute;
}

int zeit::hour() const
{
	return m_hour;
}

int zeit::day() const
{
	return m_day;
}

int zeit::month() const
{
	return m_month;
}

int zeit::year() const
{
	return m_year;
}

int zeit::dayLength() const
{
	return m_day_length;
}


void zeit::setDayLength(int dlparam)
{
	m_day_length = dlparam;
}

void zeit::setMinute(const double &min)
{
	m_minute = min;
}

void zeit::setHour(int hr_param)
{
	m_hour = hr_param;
}

void zeit::setDay(int dayparam)
{
	m_day = dayparam;
}

void zeit::setMonth(int monthparam)
{
	m_month = monthparam;
}

void zeit::setYear(int yearparam)
{
	m_year = yearparam;
}

bool zeit::refreshTime()		//bool -> new Day ?
{

if(m_existingClock)
{
	refreshClock();
}

m_minute += m_day_length/1440;
if(m_minute>=60)
{
	m_minute = 0;
	m_hour ++;
	if(m_hour >=24)
	{
		m_day++;
		m_hour = 0;
		
		if((m_day > 31 && (m_month == 1 || m_month == 3 || m_month == 5 || m_month == 7 || m_month == 8 || m_month == 10 || m_month == 12)) ||
		(m_day > 30 && ( m_month == 4 || m_month == 6 || m_month == 9 || m_month == 11)) ||
		(m_month == 2 && ((m_day > 28 && (m_year%4 != 0 || m_year%100 == 0)) || (m_day > 29 && m_year%4 == 0))))
		{
			m_day = 1;
			m_month++;
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


void zeit::setClockHands(QGraphicsPixmapItem *sch, QGraphicsPixmapItem *bch)	// Small / Big ClockHand
{
	smallclockhand = sch;
	bigclockhand = bch;
}

