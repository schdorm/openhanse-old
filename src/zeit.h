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

int day_length;
float minute;
int hour;
int day;
int month;
int year;

bool existingClock;
QGraphicsPixmapItem *smallclockhand;
QGraphicsPixmapItem *bigclockhand;
public:
zeit();

void setClockHands(QGraphicsPixmapItem*, QGraphicsPixmapItem*);

void refreshClock();
void refreshTime();

void setMinute(float);
void setHour(int);
void setDay(int);
void setMonth(int);
void setYear(int);

float retMinute();
int retHour();
int retDay();
int retMonth();
int retYear();

void setDayLength(int);
int retDayLength();
};

#endif
