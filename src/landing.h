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

#ifndef _LANDING_H
#define _LANDING_H

#include <QtCore/QLine>

class QGraphicsPixmapItem;


class Landing
{
public:
	enum statuses
	{
		NotActive,
		WaitingForDestination,
		ActiveLanding,
		AtLand
	};
// 	struct landingstructure{

void setLandingLine(const QPointF&, const QPointF&);
// void setLineOrientation(double);

void setStatus	(statuses);

const QLineF &landingLine()	const 	{	return m_LandingLine;		}
double lineOrientation ()	const	{	return m_LineOrientation;	}
double orientation()		const 	{	return m_Orientation;		}
statuses status()		const	{	return m_status;		}

protected:

		statuses m_status;
		QLineF m_LandingLine;
		bool m_correctOrientation;
		double m_LineOrientation;		//Line-Orientation
		double m_Orientation;
		double m_vx, m_vy;
		QGraphicsPixmapItem *m_landingShip_gi;
// 	};
};

#endif