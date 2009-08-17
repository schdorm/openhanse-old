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

#include "schiff.h"
#include <math.h>

void schiffsklasse::calcMovement(int windv, double winddir)
{
	if(settedSails > toSettedSails)
	{
		settedSails -= 0.1;
		if(settedSails < 0.05)
		{
			settedSails = 0;
		}
	}
	
	else if(settedSails < toSettedSails)
	{
		settedSails += 0.1;
	}
	
	if(control_difficulty == 0)
	{
		double accelerationv = settedSails * windv * (1 + cos(dir - winddir))/2 ;
		if(accelerationv > v)
		{
			v += int(ceil((accelerationv - v)/4));
		}
		else if(accelerationv < v)
		{
			v += int(floor((accelerationv - v)/4));
		}
	}
	
	else if(control_difficulty == 1)
	{
		double acceleration = settedSails * windv * cos(dir + sailDir - winddir) - v;
		if(acceleration > 0)
		{
			v += int (ceil(acceleration/2));
		}
		else if(acceleration < 0 )
		{
			v += int (floor(acceleration/2));
		}
	}
	
	
	if(mouse_control)
	{
		if(dir != toDir)
		{
			if(toDir > dir - 0.01 && toDir < dir + 0.01)
			{
				dir = toDir;
				return;
			}
	
			if((dir < toDir && dir + M_PI > toDir) || (dir > toDir && dir - M_PI > toDir))
			{
				dir = dir + 0.0006 * ((v/4) + 2) * control_velocity;
			}
			else
			{
				dir = dir - 0.0006 * ((v/4) + 2) * control_velocity;
			}
			
			if(dir < 0)
			{
				dir = 2*M_PI-0.0000001;
			}
			else if(dir > 2*M_PI)
			{
				dir = 0;
			}
		}
	}
	else
	{
		if(rudderDir != 0 && toRudderDir != 0)
		{
			static int delayvar;		// control-delaying-variable
			delayvar ++;
			if(delayvar % 10 == 0)
			{
				delayvar = 1;
				if(rudderDir != toRudderDir)
				{
					rudderDir += (toRudderDir - rudderDir)/5;
					if(rudderDir < 0.0001 && rudderDir > -0.0001 && toRudderDir == 0)
					{
						rudderDir = 0;
					}
				}
			}
			dir += rudderDir;
			
			if(dir < 0)
			{
				dir = 2*M_PI-0.0000001;
			}
			else if(dir > 2*M_PI)
			{
				dir = 0;
			}
		}
	}
}

int schiffsklasse::ret_V()
{
return v;
}

double schiffsklasse::ret_SettedSails()
{
return settedSails;
}

double schiffsklasse::ret_ToSettedSails()
{
return toSettedSails;
}

double schiffsklasse::ret_SailDir()
{
return sailDir;
}

// double schiffsklasse::ret_ToSailDir()
// {
// return toSailDir;
// }

double schiffsklasse::ret_Dir()
{
return dir;
}

double schiffsklasse::ret_ToDir()
{
return toDir;
}

double schiffsklasse::ret_RudderDir()
{
return rudderDir;
}

double schiffsklasse::ret_ToRudderDir()
{
return toRudderDir;
}



void schiffsklasse::set_ToSettedSails(double param_amount)
{
	if(param_amount >= 0 && param_amount <= 1)
	{
		if(param_amount < 0.1)
		{
		toSettedSails = 0;
		return;
		}
		toSettedSails = param_amount;
		
	}
}


void schiffsklasse::set_SailDir(double param_dir)
{
	if(param_dir <= 2 * M_PI && param_dir >= 0)
	{
	sailDir = param_dir;
	}
}

void schiffsklasse::set_ToRudderDir(double param_dir)
{
	if(param_dir <= 2 * M_PI && param_dir >= 0)
	{
	toRudderDir = param_dir;
	}
}

void schiffsklasse::set_ToDir(double param_dir)
{
	if(param_dir <= 2 * M_PI && param_dir >= 0)
	{
	toDir = param_dir;
	}
}

void schiffsklasse::moveGraphics()
{
}