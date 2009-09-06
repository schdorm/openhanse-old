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
#ifndef _zeit_h
#define _zeit_h

#include <QtGui/QGraphicsPixmapItem>

class zeit
{

int m_day_length;
double m_minute;
int m_hour;
int m_day;
int m_month;
int m_year;

bool m_existingClock;
QGraphicsPixmapItem *smallclockhand;
QGraphicsPixmapItem *bigclockhand;
public:
 zeit();
void init();

void setClockHands(QGraphicsPixmapItem*, QGraphicsPixmapItem*);

void refreshClock();
bool refreshTime();

void setMinute(const double &);
void setHour(int);
void setDay(int);
void setMonth(int);
void setYear(int);

double minute() const;
int hour() const;
int day() const;
int month() const;
int year() const;

void setDayLength(int);
int dayLength() const;
};

#endif
