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

#include "shipdata.h"
#include "datamanager.h"

#include <math.h>

// #define _debug_
#ifdef _debug_
#include <QtDebug>
#endif

void ShipData::calcMovement(int windv, double winddir)
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
	#ifdef _debug_
	qWarning() << settedSails << toSettedSails << " sS << tSS";
	#endif
// 	if(settedSails > 0 && windv > 0)
	{
		if(control_difficulty == 0)
		{
			double accelerationv = windv * (0.9 + cos(dir - winddir))/2 ;
// 			if(accelerationv > v)
			{
// 				v += (ceil((accelerationv - v)/4));
 				v += (settedSails + 0.1) * (accelerationv - v)/25;
			}
			if( v > 0)
			{
 			v -= (v+5)/100;
			}
/*			else if(accelerationv < v)
			{
// 				v += (floor((accelerationv - v)/4));
				v += (accelerationv - v)/20;
			}*/
			#ifdef _debug_
			qWarning() << accelerationv << v << v/20 << (settedSails + 0.1) * (accelerationv - v)/25;
			#endif
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
			#ifdef _debug_
			qWarning() << acceleration;
			#endif
		}
		#ifdef _debug_
		qWarning() << v << " v";
		#endif
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
		if(rudderDir != 0 || toRudderDir != 0)
		{
			static int delayvar;		// control-delaying-variable
			delayvar ++;
			if(delayvar % 10 == 0)
			{
				delayvar = 1;
				if(rudderDir != toRudderDir)
				{
					
					if(toRudderDir < 0 && rudderDir > toRudderDir)
					{
						rudderDir += (toRudderDir + rudderDir)/5;
					}
					else if(toRudderDir >= 0 && rudderDir < toRudderDir)
					{
						rudderDir += (toRudderDir - rudderDir)/5;
					}
					if(rudderDir < 0.0001 && rudderDir > -0.0001 && toRudderDir == 0)
					{
						rudderDir = 0;
					}
					else if(rudderDir > 0.1 || rudderDir < -0.1)
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

void ShipData::brake(double param_brakefactor)
{
	v = v * (1 - param_brakefactor);

}

double ShipData::ret_V()
{
return v;
}

double ShipData::ret_SettedSails()
{
return settedSails;
}

double ShipData::ret_ToSettedSails()
{
return toSettedSails;
}

double ShipData::ret_SailDir()
{
return sailDir;
}

// double ShipData::ret_ToSailDir()
// {
// return toSailDir;
// }

double ShipData::ret_Dir()
{
return dir;
}

double ShipData::ret_ToDir()
{
return toDir;
}

double ShipData::ret_RudderDir()
{
return rudderDir;
}

double ShipData::ret_ToRudderDir()
{
return toRudderDir;
}

PositioningStruct ShipData::ret_CurrentPosition()
{
return currentPosition;
}

int ShipData::ret_MPos_X()
{
return currentPosition.m_position.x();
}


int ShipData::ret_MPos_Y()
{
return currentPosition.m_position.y();
}


void ShipData::set_ToSettedSails(double param_amount)
{

	if(param_amount >= 0 && param_amount <= 1)
	{
		if(param_amount < 0.01)
		{
		toSettedSails = 0;
// 		return;
		}
		else
			toSettedSails = param_amount;
		
		#ifdef _debug_
		qWarning() << "void ShipData::set_ToSettedSails(double param_amount)" << param_amount;
		#endif
	}
}


void ShipData::set_SailDir(double param_dir)
{
	if(param_dir <= 0.3 && param_dir >= -0.3)
	{
	sailDir = param_dir;
	}
}

void ShipData::set_ToRudderDir(double param_dir)
{
	if(param_dir <= const_max_rudder_deflection && param_dir >= - const_max_rudder_deflection)
	{
	toRudderDir = param_dir;
	}
}

void ShipData::set_ToDir(double param_dir)
{
	if(param_dir <= 2 * M_PI && param_dir >= 0)
	{
	toDir = param_dir;
	}
}

int ShipData::ret_Condition()
{
	return condition;
}

void ShipData::calcPos()
{
	currentPosition.generic_position.setX(currentPosition.generic_position.x() - (v * sin(dir))/10);
	currentPosition.generic_position.setY(currentPosition.generic_position.y()  - (v * cos(dir))/10);
	currentPosition.m_position.setX(currentPosition.generic_position.x() + g_width2);
	currentPosition.m_position.setY(currentPosition.generic_position.y() + g_height2);
	
	
}


void ShipData::setPos(PositioningStruct param_destinationposition)
{
if(m_setPosAllowed || ((param_destinationposition.mapcoords.x() + 1 == currentPosition.mapcoords.x() || param_destinationposition.mapcoords.x() == currentPosition.mapcoords.x() || param_destinationposition.mapcoords.x() - 1 == currentPosition.mapcoords.x()) && (param_destinationposition.mapcoords.y() + 1 == currentPosition.mapcoords.y() || param_destinationposition.mapcoords.y() == currentPosition.mapcoords.y() || param_destinationposition.mapcoords.y() - 1 == currentPosition.mapcoords.y())))
currentPosition = param_destinationposition;
m_setPosAllowed = false;
}
