/***************************************************************************
 *   Copyright (C) 2009 by Christian Doerffel                              *
 *   schdorm@googlemail.com                                                *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; eitherm_version 2 of the License, or     *
 *   (at your option) any laterm_version.                                   *
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
#include "konsole.h"

#include <math.h>

// #define _debug_
#ifdef _debug_
#include <QtDebug>
#endif

#ifdef _DEBUG_DESTRUCTORS
#include <QtDebug>
#endif


ShipData::ShipData(const QString &param_name) : m_name (param_name)				///== RESET
{
	static int idzuweisung;
	m_id = idzuweisung;
	idzuweisung++;

	m_setPosAllowed = true;
	
	m_cargo.setTaler(5000);

	for(int i = 0; i<const_warenanzahl; i++)
	{
		m_cargo.setGood(i, 5);
	}
	m_cargo.setFilling(0);

	m_condition = 100;		// ehemals: "zustand"
	m_type = Kogge;
	m_v = 0;
	m_dir = 0;
	m_toDir = 0;
	m_sailDir = 0;
	m_rudderDir = 0;
	m_toRudderDir = 0;
	m_settedSails = 0;
	m_toSettedSails = 0;
	m_controlVelocity = 1;
	
	m_ControlDifficulty = 0;
// 	filename = ":img/schiffe/schiff_gerade_skaliert2.png";
	m_cargo.setCapacity(rand()%2001);
}

ShipData::~ShipData()
{
#ifdef _DEBUG_DESTRUCTORS
qWarning() << "Destructing Ship" <<m_name;
#endif
}

void ShipData::printPosition() const
{
OHDebug(QString("Generic Position: \tX: %1 \tY: %2")
.arg(m_currentPosition.generic_position.x())
.arg(m_currentPosition.generic_position.y())); 
OHDebug(QString("M Position: \tX: %1 \tY: %2")
.arg(m_currentPosition.m_position.x())
.arg(m_currentPosition.m_position.y())); 
}

void ShipData::setName(const QString &param_name)
{
m_name = param_name;
}

void ShipData::setMouseControl (bool param_mousecontrol)
{
m_MouseControl = param_mousecontrol;
}
void ShipData::setControlDifficulty (int param_difficulty)
{
m_ControlDifficulty = param_difficulty;
}

void ShipData::calcMovement(int windv, const double &winddir)
{
	if(m_settedSails > m_toSettedSails)
	{
		m_settedSails -= 0.1;
		if(m_settedSails < 0.05)
		{
			m_settedSails = 0;
		}
	}
	
	else if(m_settedSails < m_toSettedSails)
	{
		m_settedSails += 0.1;
	}
	#ifdef _debug_
	qWarning() << m_settedSails << m_toSettedSails << " sS << tSS";
	#endif
// 	if(m_settedSails > 0 && windv > 0)
	{
		if(m_ControlDifficulty == 0)
		{
			double accelerationv = windv * (0.9 + cos(m_dir - winddir))/2 ;
// 			if(accelerationv >m_v)
			{
// 				v += (ceil((accelerationv -m_v)/4));
 				m_v += (m_settedSails + 0.1) * (accelerationv - m_v)/25;
			}
			if(m_v> 0)
			{
 			m_v -= (m_v + 5)/100;
			}
/*			else if(accelerationv <m_v)
			{
// 				v += (floor((accelerationv -m_v)/4));
				v += (accelerationv -m_v)/20;
			}*/
			#ifdef _debug_
			qWarning() << accelerationv <<m_v<<m_v/20 << (m_settedSails + 0.1) * (accelerationv -m_v)/25;
			#endif
		}
	
		else if(m_ControlDifficulty == 1)
		{
			double acceleration = m_settedSails * windv * cos(m_dir + m_sailDir - winddir) -m_v;
			if(acceleration > 0)
			{
				m_v += int (ceil(acceleration/2));
			}
			else if(acceleration < 0 )
			{
				m_v += int (floor(acceleration/2));
			}
			#ifdef _debug_
			qWarning() << acceleration;
			#endif
		}
		#ifdef _debug_
		qWarning() << m_v << "m_v";
		#endif
	}
	
	if(m_MouseControl)
	{
		if(m_dir != m_toDir)
		{
			if(m_toDir > m_dir - 0.01 && m_toDir < m_dir + 0.01)
			{
				m_dir = m_toDir;
				return;
			}
	
			if((m_dir < m_toDir && m_dir + M_PI > m_toDir) || (m_dir > m_toDir && m_dir - M_PI > m_toDir))
			{
				m_dir = m_dir + 0.0006 * ((m_v/4) + 2) * m_controlVelocity;
			}
			else
			{
				m_dir = m_dir - 0.0006 * ((m_v/4) + 2) * m_controlVelocity;
			}
			
			if(m_dir < 0)
			{
				m_dir = 2*M_PI-0.0000001;
			}
			else if(m_dir > 2*M_PI)
			{
				m_dir = 0;
			}
		}
	}
	else		//keyboard-control
	{
		if(m_rudderDir != 0 || m_toRudderDir != 0)
		{
// 			static int delayvar;		// control-delaying-variable
			m_delayvar ++;
			if(m_delayvar % 10 == 0)
			{
				m_delayvar = 1;
				if(m_rudderDir != m_toRudderDir)
				{
					
					if(m_toRudderDir < 0 && m_rudderDir > m_toRudderDir)
					{
						m_rudderDir += (m_toRudderDir + m_rudderDir)/5;
					}
					else if(m_toRudderDir >= 0 && m_rudderDir < m_toRudderDir)
					{
						m_rudderDir += (m_toRudderDir - m_rudderDir)/5;
					}
					if(m_rudderDir < 0.0001 && m_rudderDir > -0.0001 && m_toRudderDir == 0)
					{
						m_rudderDir = 0;
					}
					else if(m_rudderDir > 0.1 || m_rudderDir < -0.1)
					{
						m_rudderDir = 0;
					}
				}
			}
			m_dir += m_rudderDir;
			
			if(m_dir < 0)
			{
				m_dir = 2*M_PI-0.0000001;
			}
			else if(m_dir > 2*M_PI)
			{
				m_dir = 0;
			}
		}
	}

}

void ShipData::brake(const double &param_brakefactor)
{
	m_v = m_v * (1 - param_brakefactor);

}



void ShipData::set_ToSettedSails(double param_amount)
{

	if(param_amount >= 0 && param_amount <= 1)
	{
		if(param_amount < 0.01)
		{
		m_toSettedSails = 0;
// 		return;
		}
		else
			m_toSettedSails = param_amount;
		
		#ifdef _debug_
		qWarning() << "void ShipData::set_ToSettedSails(double param_amount)" << param_amount;
		#endif
	}
}


void ShipData::set_SailDir(double param_dir)
{
	if(param_dir <= 0.3 && param_dir >= -0.3)
	{
	m_sailDir = param_dir;
	}
}

void ShipData::set_ToRudderDir(double param_dir)
{
	if(param_dir <= const_max_rudder_deflection && param_dir >= - const_max_rudder_deflection)
	{
	m_toRudderDir = param_dir;
	}
}

void ShipData::set_ToDir(double param_dir)
{
	if(param_dir <= 2 * M_PI && param_dir >= 0)
	{
	m_toDir = param_dir;
	}
}



void ShipData::calcPos()
{
	m_currentPosition.generic_position.setX(m_currentPosition.generic_position.x() - (m_v * sin(m_dir))/10);
	m_currentPosition.generic_position.setY(m_currentPosition.generic_position.y()  - (m_v * cos(m_dir))/10);
	m_currentPosition.m_position.setX(m_currentPosition.generic_position.x() + g_width2);
	m_currentPosition.m_position.setY(m_currentPosition.generic_position.y() + g_height2);
}


void ShipData::setPos(const PositioningStruct &param_destinationposition)
{
// if(m_setPosAllowed || ((param_destinationposition.mapcoords.x() + 1 == m_currentPosition.mapcoords.x() || param_destinationposition.mapcoords.x() == m_currentPosition.mapcoords.x() || param_destinationposition.mapcoords.x() - 1 == m_currentPosition.mapcoords.x()) && (param_destinationposition.mapcoords.y() + 1 == m_currentPosition.mapcoords.y() || param_destinationposition.mapcoords.y() == m_currentPosition.mapcoords.y() || param_destinationposition.mapcoords.y() - 1 == m_currentPosition.mapcoords.y())))
{
	m_currentPosition = param_destinationposition;
// 	m_setPosAllowed = false;
}
}


bool ShipData::setCargo(const Goods &param_newcargo)
{
m_cargo = param_newcargo;
return true;
}
