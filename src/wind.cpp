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
#include <stdlib.h>
#include <math.h>
#include "wind.h"


Wind::Wind()
{
	m_dir = double (rand()%7);
	m_v = rand() %30 +5;
}

void Wind::refresh()
{
	int aenderung = ((rand()%3)-1);
	double faenderung = (rand()%23);
	if((aenderung*M_PI)/ (1+faenderung*10) < 0.2 && (aenderung*M_PI)/ (1+faenderung*10) > -0.2)
	{
		m_dir = m_dir + (aenderung*M_PI)/(1+faenderung*10);
	}
	if(m_dir > 2 * M_PI)
	{
		m_dir =0;
	}

	else if(m_dir < 0)
	{
		m_dir =2 * M_PI;
	}

	m_v = m_v + ((rand()%3)-1);

	if(m_v > 90)
	{
		m_v=90;
	}

	else if(m_v < 0)
	{
	m_v=1;
	}
}

void Wind::setDir(double param_dir)
{
m_dir = param_dir;
}

double Wind::dir()
{
return m_dir;
}

void Wind::setV(int param_v)
{
m_v = param_v;
}

int Wind::v()
{
return m_v;
}

