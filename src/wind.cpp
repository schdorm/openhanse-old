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


void windclass::init()
{
	dir = double (rand()%7);
	v = rand() %30 +5;
}

void windclass::refresh()
{
	int aenderung = ((rand()%3)-1);
	double faenderung = (rand()%23);
	if((aenderung*M_PI)/ (1+faenderung*10) < 0.2 && (aenderung*M_PI)/ (1+faenderung*10) > -0.2)
	{
		dir = dir + (aenderung*M_PI)/(1+faenderung*10);
	}
	if(dir > 2 * M_PI)
	{
		dir =0;
	}

	else if(dir < 0)
	{
		dir =2 * M_PI;
	}

	v = v + ((rand()%3)-1);

	if(v > 90)
	{
		v=90;
	}

	else if(v < 0)
	{
	v=1;
	}
}

void windclass::setDir(double param_dir)
{
dir = param_dir;
}

double windclass::retDir()
{
return dir;
}

void windclass::setV(int param_v)
{
v = param_v;
}

int windclass::retV()
{
return v;
}

