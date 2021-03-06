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
#ifndef _MAPOBJECT_H
#define _MAPOBJECT_H

class MapObject
{
public:

// MapObject(int param_role, QString param_filename, QString param_tooltip, QPoint param_position, double param_zvalue)
 MapObject(const int &, const QString &, const QString &, const QPoint &, const double &);


int	role ()	{	return m_role;		}
QString	fileName ()	{	return m_filename;	}
QString	toolTip  ()	{	return m_tooltip;		}
QPoint	position ()	{	return m_position;	}
double	zValue ()	{	return m_zValue;		}

private:
int m_role;
QString m_filename;
QString m_tooltip;
QPoint m_position;
double m_zValue;



};

#endif
