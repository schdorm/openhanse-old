/***************************************************************************
 *   Copyright (C) 2009 by Christian Doerffel                              *
 *   christian.doerffel@googlemail.com                                     *
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

#include "stadtklasse.h"
#include "konsole.h"
// #include <QtDebug>
#include "datamanager.h"
#include "dataclass.h"

	void CityClass::init()
	{
	m_hasKontor = false;
		srand(time(NULL));
		for(int i=0; i<const_warenanzahl; i++)
		{
		// int p;
		// if(stadtwaren.ware[i]==0)
			{
			int r=rand()%20;
			int s=rand()%20;
			int p = rand()%10;
			m_goods.ware[i] = s + r + p;

		}
		// else
		// stadtwaren.ware[i] = int(sqrt(stadtwaren.ware[i] * stadtwaren.ware[i])) % 100;

		}
	m_inhabitants = 1300 + rand()%1000;				//das kommt mal noch ins XML-Zeugs rein


	}

// CityClass::CityClass(const QString &param_cityname, int param_hproduction[const_warenanzahl], int param_mproduction[const_warenanzahl], int param_lproduction[const_warenanzahl]) : m_hproduction (param_hproduction), m_mproduction (param_mproduction), m_lproduction ( param_lproduction)
CityClass::CityClass(const QString &param_cityname, const QList <int> &param_hproductionlist, const QList <int> &param_mproductionlist, const QList <int> &param_lproductionlist) : m_cityname (param_cityname), m_hproductionlist(param_hproductionlist), m_mproductionlist(param_mproductionlist), m_lproductionlist(param_lproductionlist)
{
	static int id_counter;
	m_id = id_counter;
	id_counter++;
}

void CityClass::setGoods(const Warenstruct &param_storage)
{
m_goods = param_storage;
}


void CityClass::printGoods()
{
// 	QString dbg;
	for(int i = 0; i<const_warenanzahl; i++)
	{
// 		dbg = ;
		OHDebug(QString("%1 ").arg(m_goods.ware[i]).append(GAMEDATA->GoodLabelHash().value(i)));
	}
}

void CityClass::reset()
{
// for(int i = 0; i<5; i++)
// {
// m_hproduction[i]=-1;
// m_mproduction[i]=-1;
// m_lproduction[i]=-1;
// }
m_cityname = QString();
m_inhabitants = 0;
// stadtwaren.kapazitaet = 0;
}