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

#include "waren.h"

void Goods::setGood(int key, int value)
{
	m_GoodHash[key] = value;
}

void Goods::addGood(int key, int value)
{
	m_GoodHash[key] += value;
}
void Goods::setWeapon(int key, int value)
{
	m_WeaponHash[key] = value;
}

void Goods::setFilling(int param_filling)
{
	m_filling = param_filling;
}

void Goods::setCapacity(int param_capacity)
{
	m_capacity = param_capacity;
}

void Goods::setTaler(int param_taler)
{
	m_taler = param_taler;
}

void Goods::setExchangeVolume(int param_volume)
{
	m_exchange_volume = param_volume;
}

