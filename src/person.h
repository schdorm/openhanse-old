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

#ifndef _Person_H
#define _Person_H

#include <QtGui/QGraphicsItem>
#include "definitions.h"
class Person
{
// Q_OBJECT
public:
void setPixmapItem(QGraphicsPixmapItem*);

// public slots:
// 
// signals:
void fillSidePixmapList(QImage *, QRect, int, bool);		//adds n pixmaps to the Left and the section-images mirrored to the Right - Pixmap List
void fillUpPixmapList(QImage *,QRect, int);
void fillDownPixmapList(QImage *, QRect, int);

void move(int);

private:
QGraphicsPixmapItem *graphicsitem;
QList<QPixmap> LeftPixmapList;
QList<QPixmap> UpPixmapList;
QList<QPixmap> RightPixmapList;
QList<QPixmap> DownPixmapList;
int step;
int currentDirection;


protected:

};

#endif
