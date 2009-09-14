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

#include "dataclass.h"
// #include "gesamtbild.h"
#include "waren.h"
#include "stadtklasse.h"
#include "kontordata.h"
#include <QtDebug>

void DataClass::produktion(int durchlauf)
{
// 	QList <CityClass> cityList = GAMEDATA->ret_CityList();
// 	CityClass *cityit = 0;
// 	foreach(*cityit, CityList)
// 	{
// 	cityit->production(durchlauf);
// 	}
	
	for(QList<CityClass>::iterator it = m_CityList.begin(); it != m_CityList.end(); ++it)
	{
		it->production(durchlauf);
	}
}

void CityClass::production(int param_durchlauf)
{
		qWarning() << "Stadtproduktion:" << m_cityname;

		for(QList<int>::iterator it = m_hproductionlist.begin(); it != m_hproductionlist.end(); ++it)
		{
// 			switch(m_hproduction[j])
			switch(*it)
			{
			case W_Baumstamme:			//Baumstaemme
				{
				m_goods.ware[W_Baumstamme]++;		//Grundproduktion um Festfahren und komplette Stockung der Wirtschaft zu verhindern
				
// 			m_goods.ware[i] += ((rand() % 12) + m_inhabitants/100);
				if(m_goods.ware[W_Werkzeuge] - m_inhabitants/500 > 0)
				{
				m_goods.ware[W_Baumstamme] = m_goods.ware[W_Baumstamme] + m_inhabitants/100;
				m_goods.ware[W_Werkzeuge] = m_goods.ware[W_Werkzeuge] - m_inhabitants/500;
				}

				break;
				}
			case W_Holzbretter:			//Holzbretter
				{
				if(m_goods.ware[W_Baumstamme] - m_inhabitants/200 > 0 &&
				m_goods.ware[W_Werkzeuge] - m_inhabitants/400 > 0)
				{
				m_goods.ware[W_Holzbretter] += m_inhabitants/100;
				m_goods.ware[W_Baumstamme] -= m_inhabitants/200;
				m_goods.ware[W_Werkzeuge] -= m_inhabitants/400;
				}
				break;
				}
			case W_Holzkohle:			//Holzkohle ... (2 HK aus 3 BS und 1 HB)
				{
				if(m_goods.ware[W_Baumstamme] - m_inhabitants/500 > 0 && m_goods.ware[W_Holzbretter] - 1 > 0 )
				{
				m_goods.ware[W_Holzkohle] += m_inhabitants/400;
				m_goods.ware[W_Baumstamme] -= m_inhabitants/500;
// 				m_goods.ware[W_Holzbretter] -= m_inhabitants/1000;
				m_goods.ware[W_Holzbretter] --;
				}
				break;
				}
			case W_Pech:				//Pech (5 Pech aus 3 BS und 1 HB)
				{
				if(m_goods.ware[W_Baumstamme] - m_inhabitants/500 > 0 &&
 				m_goods.ware[W_Holzbretter] - 1 > 0)
				{
				m_goods.ware[W_Pech] += m_inhabitants/100;
				m_goods.ware[W_Baumstamme] -= m_inhabitants/500;
				m_goods.ware[W_Holzbretter] --;
				}
				break;
				}
			case W_Steine:				//Steine / Ziegel
				{
				if(m_goods.ware[W_Holzbretter] - m_inhabitants/500 > 0 && m_goods.ware[W_Werkzeuge] - m_inhabitants/1000 > 0)
				m_goods.ware[W_Steine] += m_inhabitants/400;
				m_goods.ware[W_Holzbretter] -= m_inhabitants/1000;
				m_goods.ware[W_Werkzeuge] -= m_inhabitants/500;
				break;
				}
			case W_Eisenerz:			//Eisenerz
				{
				if(m_goods.ware[W_Werkzeuge] - m_inhabitants/400 >0)
				{
				m_goods.ware[W_Eisenerz] += m_inhabitants/200;
				m_goods.ware[W_Werkzeuge] -= m_inhabitants/400;
				}
				m_goods.ware[W_Eisenerz]++;	// Grundproduktion
				break;
				}
			case W_Schmiedeeisen:			//Schmiedeeisen
				{
				if(m_goods.ware[W_Eisenerz] - m_inhabitants/200 > 0 && m_goods.ware[W_Holzkohle] - m_inhabitants/400 > 0 && m_goods.ware[W_Werkzeuge] - m_inhabitants/500 > 0)
				{
				m_goods.ware[W_Schmiedeeisen] += m_inhabitants/250;
				m_goods.ware[W_Eisenerz] -= m_inhabitants/200;	
				m_goods.ware[W_Holzkohle] -= m_inhabitants/400;
				m_goods.ware[W_Werkzeuge] -= m_inhabitants/500;
				}
				break;
				}
			case W_Werkzeuge:			//Werkzeuge
				{
				if(m_goods.ware[W_Schmiedeeisen] - m_inhabitants/200 > 0 && m_goods.ware[W_Holzkohle] - m_inhabitants/500 > 0 && m_goods.ware[W_Holzbretter] - m_inhabitants/400 > 0)
				{
					m_goods.ware[W_Werkzeuge] += m_inhabitants/25;
					m_goods.ware[W_Schmiedeeisen] -= m_inhabitants/200;
					m_goods.ware[W_Holzkohle] -= m_inhabitants/500;
					m_goods.ware[W_Holzbretter] -= m_inhabitants/400;
				}
				m_goods.ware[W_Werkzeuge]++;
				break;
				}
			case W_Leder:			//Leder
				{
				if(m_goods.ware[W_Salz] - m_inhabitants/1000 > 0 && m_goods.ware[W_Werkzeuge] - m_inhabitants/1000 > 0)
				{
					m_goods.ware[W_Leder] += m_inhabitants/500;
					m_goods.ware[W_Salz] -= m_inhabitants/1000;
					m_goods.ware[W_Werkzeuge] -= m_inhabitants/1000;
				}
				break;
				}
			case W_Wolle:			//Wolle
				{
				if(m_goods.ware[W_Werkzeuge] - m_inhabitants/1000 > 0)
				{
					m_goods.ware[W_Wolle] += m_inhabitants/500;
					m_goods.ware[W_Werkzeuge] -= m_inhabitants/1000;
				}
				break;
				}
			case W_Stoffe:		//Stoffe
				{
				if(m_goods.ware[W_Wolle] - m_inhabitants/500 > 0 && m_goods.ware[W_Werkzeuge] - m_inhabitants/1000 > 0)
				{
					m_goods.ware[W_Stoffe] += m_inhabitants/100;
					m_goods.ware[W_Wolle] -= m_inhabitants/1000;
					m_goods.ware[W_Werkzeuge] -= m_inhabitants/1000;
				}
				break;
				}
			case W_Salz:		//Salz
				{
				if(m_goods.ware[W_Holzbretter] - m_inhabitants/800 > 0 &&
				m_goods.ware[W_Werkzeuge] - m_inhabitants/1000 > 0)
				{
					m_goods.ware[W_Salz] += m_inhabitants/80;
					m_goods.ware[W_Holzbretter] -= m_inhabitants/800;
					m_goods.ware[W_Werkzeuge] -= m_inhabitants/2000;
				}
				break;
				}
			case W_Fisch:		//Fisch
				{
				if(m_goods.ware[W_Salz] - m_inhabitants/400 > 0 &&
				m_goods.ware[W_Werkzeuge] - m_inhabitants/1500 > 0 && m_goods.ware[W_Hanf] - m_inhabitants/1000 > 0)
				{
					m_goods.ware[W_Fisch] += m_inhabitants/200;
					m_goods.ware[W_Salz] -= m_inhabitants/400;
					m_goods.ware[W_Werkzeuge] -= m_inhabitants/1500;
					m_goods.ware[W_Hanf] -= m_inhabitants/1000;
				}
				break;
				}
			case W_Fleisch:		//Fleisch
				{
				if(m_goods.ware[W_Getreide] - m_inhabitants/200 > 0 && m_goods.ware[W_Werkzeuge] - m_inhabitants/1000 > 0 && m_goods.ware[W_Salz] - m_inhabitants/300 > 0)
				{
					m_goods.ware[W_Fleisch] += m_inhabitants/200;
					m_goods.ware[W_Werkzeuge] -= m_inhabitants/1000;
					m_goods.ware[W_Getreide] -= m_inhabitants/200;
					m_goods.ware[W_Salz] -= m_inhabitants/300;
				}
				break;
				}
			case W_Getreide:		//Getreide
				{
				if(m_goods.ware[W_Werkzeuge] - m_inhabitants/1000 > 0)
				{
					m_goods.ware[W_Getreide] += m_inhabitants/80;
					m_goods.ware[W_Werkzeuge] -= m_inhabitants/500;
				}
				m_goods.ware[W_Getreide]++;
				break;
				}
			case W_Bier:		//Bier
				{
				if(m_goods.ware[W_Getreide] - m_inhabitants/500 > 0 &&
				m_goods.ware[W_Holzbretter] - m_inhabitants/1000 > 0 &&
				m_goods.ware[W_Werkzeuge] - m_inhabitants/1000 > 0)
				{
					m_goods.ware[W_Bier] += m_inhabitants/80;
					m_goods.ware[W_Getreide] -= m_inhabitants/500;
					m_goods.ware[W_Holzbretter] -= m_inhabitants/1000;
					m_goods.ware[W_Werkzeuge] -= m_inhabitants/1000;
				}
				break;
				}
			case W_Wein:		//Wein
				{
				if(m_goods.ware[W_Werkzeuge] - m_inhabitants/2000 > 0)
				{
				m_goods.ware[W_Wein] += m_inhabitants/250;
				m_goods.ware[W_Werkzeuge] -= m_inhabitants/2000;
				}
				break;
				}
			case W_Hanf:		//Hanf
				{
				if(m_goods.ware[W_Werkzeuge] - m_inhabitants/1000 > 0)
				{
					m_goods.ware[W_Hanf] += m_inhabitants/250;
					m_goods.ware[W_Werkzeuge] -= m_inhabitants/1000;
				}
				break;
				}
			case W_Gold:		//Gold
				{
				break;
				}
			case W_Schmuck:		//Schmuck
				{
				break;
				}
			default:
				break;
			}
		}
		
		for(QList<int>::iterator it = m_mproductionlist.begin(); it != m_mproductionlist.end(); ++it)
		{
			switch(*it)
			{
			case W_Baumstamme:			//Baumstaemme
				{
// 			m_goods.ware[i] += ((rand() % 12) + m_inhabitants/100);
				if(m_goods.ware[W_Werkzeuge] - m_inhabitants/1000 > 0)
				{
				m_goods.ware[W_Baumstamme] = m_goods.ware[W_Baumstamme] + m_inhabitants/200;
				m_goods.ware[W_Werkzeuge] = m_goods.ware[W_Werkzeuge] - m_inhabitants/1000;
				}
				break;
				}
			case W_Holzbretter:			//Holzbretter
				{
				if(m_goods.ware[W_Baumstamme] - m_inhabitants/400 > 0 &&
				m_goods.ware[W_Werkzeuge] - m_inhabitants/800 > 0)
				{
				m_goods.ware[W_Holzbretter] += m_inhabitants/200;
				m_goods.ware[W_Baumstamme] -= m_inhabitants/400;
				m_goods.ware[W_Werkzeuge] -= m_inhabitants/800;
				}
				break;
				}
			case W_Holzkohle:			//Holzkohle ... (2 HK aus 3 BS und 1 HB)
				{
				if(m_goods.ware[W_Baumstamme] - m_inhabitants/1000 > 0 && m_goods.ware[W_Holzbretter] - 1 > 0 )
				{
				m_goods.ware[W_Holzkohle] += m_inhabitants/800;
				m_goods.ware[W_Baumstamme] -= m_inhabitants/1000;
// 				m_goods.ware[W_Holzbretter] -= m_inhabitants/1000;
				m_goods.ware[W_Holzbretter] --;
				}
				break;
				}
			case W_Pech:			//Pech (5 Pech aus 3 BS und 1 HB)
				{
				if(m_goods.ware[W_Baumstamme] - m_inhabitants/1000 > 0 &&
 				m_goods.ware[W_Holzbretter] - 1 > 0)
				{
				m_goods.ware[W_Holzkohle] += m_inhabitants/200;
				m_goods.ware[W_Baumstamme] -= m_inhabitants/1000;
				m_goods.ware[W_Holzbretter] --;
				}
				break;
				}
			case W_Steine:			//Steine / Ziegel
				{
				if(m_goods.ware[W_Holzbretter] - m_inhabitants/800 > 0 && m_goods.ware[W_Werkzeuge] - m_inhabitants/1500 > 0)
				m_goods.ware[W_Steine] += m_inhabitants/800;
				m_goods.ware[W_Holzbretter] -= m_inhabitants/1500;
				m_goods.ware[W_Werkzeuge] -= m_inhabitants/800;
				break;
				}
			case W_Eisenerz:
				{		//Eisenerz
				if(m_goods.ware[W_Werkzeuge] - m_inhabitants/800 >0)
				{
				m_goods.ware[W_Eisenerz] += m_inhabitants/400;
				m_goods.ware[W_Werkzeuge] -= m_inhabitants/800;
				}
				break;
				}
			case W_Schmiedeeisen:			//Schmiedeeisen
				{
				if(m_goods.ware[W_Eisenerz] - m_inhabitants/400 > 0 && m_goods.ware[W_Holzkohle] - m_inhabitants/800 > 0 && m_goods.ware[W_Werkzeuge] - m_inhabitants/1000 > 0)
				{
				m_goods.ware[W_Schmiedeeisen] += m_inhabitants/500;
				m_goods.ware[W_Eisenerz] -= m_inhabitants/400;	
				m_goods.ware[W_Holzkohle] -= m_inhabitants/800;
				m_goods.ware[W_Werkzeuge] -= m_inhabitants/1000;
				}
				break;
				}
			case W_Werkzeuge:			//Werkzeuge
				{
				if(m_goods.ware[W_Schmiedeeisen] - m_inhabitants/400 > 0 && m_goods.ware[W_Holzkohle] - m_inhabitants/1000 > 0 && m_goods.ware[W_Holzbretter] - m_inhabitants/800 > 0)
				{
					m_goods.ware[W_Werkzeuge] += m_inhabitants/40;
					m_goods.ware[W_Schmiedeeisen] -= m_inhabitants/400;
					m_goods.ware[W_Holzkohle] -= m_inhabitants/1000;
					m_goods.ware[W_Holzbretter] -= m_inhabitants/800;
				}
				m_goods.ware[W_Werkzeuge]++;
				break;
				}
			case W_Leder:			//Leder
				{
				if(m_goods.ware[W_Salz] - m_inhabitants/2000 > 0 && m_goods.ware[W_Werkzeuge] - m_inhabitants/2000 > 0)
				{
					m_goods.ware[W_Leder] += m_inhabitants/1000;
					m_goods.ware[W_Salz] -= m_inhabitants/2000;
					m_goods.ware[W_Werkzeuge] -= m_inhabitants/2000;
				}
				break;
				}
			case W_Wolle:			//Wolle
				{
				if(m_goods.ware[W_Werkzeuge] - m_inhabitants/1000 > 0)
				{
					m_goods.ware[W_Wolle] += m_inhabitants/1000;
					m_goods.ware[W_Werkzeuge] -= m_inhabitants/2000;
				}
				break;
				}
			case W_Stoffe:		//Stoffe
				{
				if(m_goods.ware[W_Wolle] - m_inhabitants/1000 > 0 && m_goods.ware[W_Werkzeuge] - m_inhabitants/2000 > 0)
				{
					m_goods.ware[W_Stoffe] += m_inhabitants/200;
					m_goods.ware[W_Wolle] -= m_inhabitants/1000;
					m_goods.ware[W_Werkzeuge] -= m_inhabitants/2000;
				}
				break;
				}
			case W_Salz:		//Salz
				{
				if(m_goods.ware[W_Holzbretter] - m_inhabitants/1600 > 0 &&
				m_goods.ware[W_Werkzeuge] - m_inhabitants/2000 > 0)
				{
					m_goods.ware[W_Salz] += m_inhabitants/100;
					m_goods.ware[W_Holzbretter] -= m_inhabitants/1600;
					m_goods.ware[W_Werkzeuge] -= m_inhabitants/2000;
				}
				break;
				}
			case W_Fisch:		//Fisch
				{
				if(m_goods.ware[W_Salz] - m_inhabitants/400 > 0 &&
				m_goods.ware[W_Werkzeuge] - m_inhabitants/2000 > 0)
				{
					m_goods.ware[W_Fisch] += m_inhabitants/400;
					m_goods.ware[W_Salz] -= m_inhabitants/400;
					m_goods.ware[W_Werkzeuge] -= m_inhabitants/2000;
				}
				break;
				}
			case W_Fleisch:		//Fleisch
				{
				if(m_goods.ware[W_Getreide] - m_inhabitants/400 > 0 && m_goods.ware[W_Werkzeuge] - m_inhabitants/2000 > 0 && m_goods.ware[W_Salz] - m_inhabitants/500 > 0)
				{
					m_goods.ware[W_Fleisch] += m_inhabitants/400;
					m_goods.ware[W_Werkzeuge] -= m_inhabitants/2000;
					m_goods.ware[W_Getreide] -= m_inhabitants/400;
					m_goods.ware[W_Salz] -= m_inhabitants/500 ;
				}
				break;
				}
			case W_Getreide:		//Getreide
				{
				if(m_goods.ware[W_Werkzeuge] - m_inhabitants/2000 > 0)
				{
					m_goods.ware[W_Getreide] += m_inhabitants/120;
					m_goods.ware[W_Werkzeuge] -= m_inhabitants/2000;
				}
				m_goods.ware[W_Getreide] ++;
				break;
				}
			case W_Bier:		//Bier
				{
				if(m_goods.ware[W_Getreide] - m_inhabitants/1000 > 0 &&
				m_goods.ware[W_Holzbretter] - m_inhabitants/2000 > 0 &&
				m_goods.ware[W_Werkzeuge] - m_inhabitants/2000 > 0)
				{
					m_goods.ware[W_Bier] += m_inhabitants/200;
					m_goods.ware[W_Getreide] -= m_inhabitants/1000;
					m_goods.ware[W_Holzbretter] -= m_inhabitants/2000;
					m_goods.ware[W_Werkzeuge] -= m_inhabitants/2000;
				}
				break;
				}
			case W_Wein:		//Wein
				{
				if(m_goods.ware[W_Werkzeuge] - m_inhabitants/2000 > 0)
				{
				m_goods.ware[W_Wein] += m_inhabitants/500;
				m_goods.ware[W_Werkzeuge] -= m_inhabitants/2000;
				}
				break;
				}
			case W_Gold:		//Gold
				{
				break;
				}
			case W_Schmuck:		//Schmuck
				{
				break;
				}
			case W_Hanf:		//Hanf?
				{
				break;
				}

			default:
				break;
			}
		}
		for(QList<int>::iterator it = m_lproductionlist.begin(); it != m_lproductionlist.end(); ++it)
		{
			switch(*it)
			{
			case W_Baumstamme:			//Baumstaemme
				{
// 			m_goods.ware[i] += ((rand() % 12) + m_inhabitants/100);
				if(m_goods.ware[W_Werkzeuge] - m_inhabitants/1500 > 0)
				{
				m_goods.ware[W_Baumstamme] = m_goods.ware[W_Baumstamme] + m_inhabitants/250;
				m_goods.ware[W_Werkzeuge] = m_goods.ware[W_Werkzeuge] - m_inhabitants/1500;
				}
				break;
				}
			case W_Holzbretter:			//Holzbretter
				{
				if(m_goods.ware[W_Baumstamme] - m_inhabitants/500 > 0 &&
				m_goods.ware[W_Werkzeuge] - m_inhabitants/1000 > 0)
				{
				m_goods.ware[W_Holzbretter] += m_inhabitants/250;
				m_goods.ware[W_Baumstamme] -= m_inhabitants/500;
				m_goods.ware[W_Werkzeuge] -= m_inhabitants/1000;
				}
				break;
				}
			case W_Holzkohle:			//Holzkohle ... (2 HK aus 3 BS und 1 HB)
				{
				if(m_goods.ware[W_Baumstamme] - m_inhabitants/1500 > 0 && m_goods.ware[W_Holzbretter] - 1 > 0 )
				{
				m_goods.ware[W_Holzkohle] += m_inhabitants/1000;
				m_goods.ware[W_Baumstamme] -= m_inhabitants/1500;
// 				m_goods.ware[W_Holzbretter] -= m_inhabitants/1000;
				m_goods.ware[W_Holzbretter] --;
				}
				break;
				}
			case W_Pech:			//Pech (5 Pech aus 3 BS und 1 HB)
				{
				if(m_goods.ware[W_Baumstamme] - m_inhabitants/1500 > 0 &&
 				m_goods.ware[W_Holzbretter] - 1 > 0)
				{
				m_goods.ware[W_Holzkohle] += m_inhabitants/250;
				m_goods.ware[W_Baumstamme] -= m_inhabitants/1500;
				m_goods.ware[W_Holzbretter] --;
				}
				break;
				}
			case W_Steine:			//Steine / Ziegel
				{
				if(m_goods.ware[W_Holzbretter] - m_inhabitants/1500 > 0 )
				{
				m_goods.ware[W_Steine] += m_inhabitants/800;
				m_goods.ware[W_Holzbretter] -= m_inhabitants/1500;
// 				m_goods.ware[W_Holzbretter] --;
				}
				break;
				}
			case W_Eisenerz:
				{		//Eisenerz
				if(m_goods.ware[W_Werkzeuge] - m_inhabitants/2000 >0)
				{
				m_goods.ware[W_Eisenerz] += m_inhabitants/1000;
				m_goods.ware[W_Werkzeuge] -= m_inhabitants/2000;
				}
				break;
				}
			case W_Schmiedeeisen:			//Schmiedeeisen
				{
				if(m_goods.ware[W_Eisenerz] - m_inhabitants/800 > 0 && m_goods.ware[W_Holzkohle] - m_inhabitants/1200 > 0 && m_goods.ware[W_Werkzeuge] - m_inhabitants/1500 > 0)
				{
				m_goods.ware[W_Schmiedeeisen] += m_inhabitants/1000;
				m_goods.ware[W_Eisenerz] -= m_inhabitants/800;	
				m_goods.ware[W_Holzkohle] -= m_inhabitants/1200;
				m_goods.ware[W_Werkzeuge] -= m_inhabitants/1500;
				}
				break;
				}
			case W_Werkzeuge:			//Werkzeuge
				{
				if(m_goods.ware[W_Schmiedeeisen] - m_inhabitants/500 > 0 && m_goods.ware[W_Holzkohle] - m_inhabitants/1500 > 0 && m_goods.ware[W_Holzbretter] - m_inhabitants/1200 > 0)
				{
					m_goods.ware[W_Werkzeuge] += m_inhabitants/100;
					m_goods.ware[W_Schmiedeeisen] -= m_inhabitants/500;
					m_goods.ware[W_Holzkohle] -= m_inhabitants/1500;
					m_goods.ware[W_Holzbretter] -= m_inhabitants/1200;
				}
				break;
				}
			case W_Leder:			//Leder
				{
				if(m_goods.ware[W_Salz] - m_inhabitants/2000 > 0 && m_goods.ware[W_Werkzeuge] - m_inhabitants/2000 > 0)
				{
					m_goods.ware[W_Leder] += m_inhabitants/1000;
					m_goods.ware[W_Salz] -= m_inhabitants/2000;
					m_goods.ware[W_Werkzeuge] -= m_inhabitants/2000;
				}
				break;
				}
			case W_Wolle:			//Wolle
				{
				if(m_goods.ware[W_Werkzeuge] - m_inhabitants/2000 > 0)
				{
					m_goods.ware[W_Wolle] += m_inhabitants/1500;
					m_goods.ware[W_Werkzeuge] -= m_inhabitants/2000;
				}
				break;
				}
			case W_Stoffe:		//Stoffe
				{
				if(m_goods.ware[W_Stoffe] - m_inhabitants/1500 > 0 && m_goods.ware[W_Werkzeuge] - m_inhabitants/2000 > 0)
				{
					m_goods.ware[W_Stoffe] += m_inhabitants/250;
					m_goods.ware[W_Wolle] -= m_inhabitants/1500;
					m_goods.ware[W_Werkzeuge] -= m_inhabitants/2000;
				}
				break;
				}
			case W_Salz:		//Salz
				{
				if(m_goods.ware[W_Holzbretter] - m_inhabitants/2000 > 0 &&
				m_goods.ware[W_Werkzeuge] - m_inhabitants/2000 > 0)
				{
					m_goods.ware[W_Salz] += m_inhabitants/400;
					m_goods.ware[W_Holzbretter] -= m_inhabitants/2000;
					m_goods.ware[W_Werkzeuge] -= m_inhabitants/2000;
				}
				break;
				}
			case W_Fisch:		//Fisch
				{
				if(m_goods.ware[W_Salz] - m_inhabitants/500 > 0 &&
				m_goods.ware[W_Werkzeuge] - m_inhabitants/2000 > 0)
				{
					m_goods.ware[W_Fisch] += m_inhabitants/500;
					m_goods.ware[W_Salz] -= m_inhabitants/500;
					m_goods.ware[W_Werkzeuge] -= m_inhabitants/2000;
				}
				break;
				}
			case W_Fleisch:		//Fleisch
				{
				if(m_goods.ware[W_Getreide] - m_inhabitants/1000 > 0 && m_goods.ware[W_Werkzeuge] - m_inhabitants/2000 > 0 && m_goods.ware[W_Salz] - m_inhabitants/500)
				{
					m_goods.ware[W_Fleisch] += m_inhabitants/500;
					m_goods.ware[W_Werkzeuge] -= m_inhabitants/2000;
					m_goods.ware[W_Getreide] -= m_inhabitants/1000;
					m_goods.ware[W_Salz] -= m_inhabitants/500;
				}
				break;
				}
			case W_Getreide:		//Getreide
				{
				if(m_goods.ware[W_Werkzeuge] - m_inhabitants/2000 > 0)
				{
					m_goods.ware[W_Getreide] += m_inhabitants/250;
					m_goods.ware[W_Werkzeuge] -= m_inhabitants/2000;
				}
				break;
				}
			case W_Bier:		//Bier
				{
				if(m_goods.ware[W_Getreide] - m_inhabitants/1500 > 0 &&
				m_goods.ware[W_Holzbretter] - m_inhabitants/2000 > 0 &&
				m_goods.ware[W_Werkzeuge] - m_inhabitants/2000 > 0)
				{
					m_goods.ware[W_Bier] += m_inhabitants/250;
					m_goods.ware[W_Getreide] -= m_inhabitants/1500;
					m_goods.ware[W_Holzbretter] -= m_inhabitants/2000;
					m_goods.ware[W_Werkzeuge] -= m_inhabitants/2000;
				}
				break;
				}
			case W_Wein:		//Wein
				{
				if(m_goods.ware[W_Werkzeuge] - m_inhabitants/2000 > 0)
				{
				m_goods.ware[W_Wein] += m_inhabitants/1000;
				m_goods.ware[W_Werkzeuge] -= m_inhabitants/2000;
				}
				break;
				}
			case W_Gold:		//Gold
				{
				break;
				}
			case W_Schmuck:		//Schmuck
				{
				break;
				}
			case W_Hanf:		//Hanf?
				{
				break;
				}

			default:
				break;
			}
		}
// 			if(hproduction[j] == i)
// 			{
// 			qWarning() << "Hproduktion vorher: "<< m_goods.ware[i];
// 			m_goods.ware[i] += ((rand() % 12) + m_inhabitants/100);
// 			qWarning() << "Hproduktion nachher" << m_goods.ware[i];
// 			}
// 			if(mproduction[j] == i)
// 			{
// 			qWarning() << "MProduktion vorher" << m_goods.ware[i];
// 			m_goods.ware[i] += ((rand() % 9) + m_inhabitants/200);
// 			qWarning() << "MProduktion nachher" << m_goods.ware[i];
// 			}
// 			if(lproduction[j] == i)
// 			{
// 			qWarning() << "NProduktion vorher" << m_goods.ware[i];
// 			m_goods.ware[i] += ((rand()% 4) + m_inhabitants/350);
// 			qWarning() << "NProduktion nachher" << m_goods.ware[i];
// 			}
///////////////////Stadtverbrauch durch Essen ^^


		if(param_durchlauf%3==0)				//Alle 3 "Tage"
		{
			// stadtware[W_Baumstamme];
			m_goods.ware[W_Holzbretter] -= m_inhabitants/1000;
// stadtware[W_Holzkohle] -= m_inhabitants/1000;		//Als Heizzeug .. evtl. anpassen
// stadtware[W_Pech];
			m_goods.ware[W_Steine] -= m_inhabitants/2000;
// stadtware[W_Eisenerz];
			m_goods.ware[W_Schmiedeeisen] -= m_inhabitants/2000;
			m_goods.ware[W_Werkzeuge] -= m_inhabitants/500;
			m_goods.ware[W_Leder] -= m_inhabitants/500;		//Leder
			m_goods.ware[W_Wolle] -= m_inhabitants/1000;
			m_goods.ware[W_Stoffe] -= m_inhabitants/300;
			m_goods.ware[W_Salz] -= m_inhabitants/500;
			m_goods.ware[W_Fisch] -= m_inhabitants/100;
					//Fisch hauefig gegessen
			m_goods.ware[W_Fleisch] -= m_inhabitants/800;
					//Fleisch fuer wohlhabendere Schichten
			m_goods.ware[W_Getreide] -= m_inhabitants/50;
					//Getreide fuer alle
			m_goods.ware[W_Bier] -= m_inhabitants/50;
					//Bier auch sehr wichtig - billiges Getraenk fuer jedermann
			m_goods.ware[W_Wein] -= m_inhabitants/100;
					//Wein wieder fuer wohlhabendere Schichten
// stadtware[17];
// stadtware[18];
// stadtware[19];
			int currentLifeQuality = 0;

			for(int i = 0; i < const_warenanzahl ;i++)
			{
				if(m_goods.ware[i] < 0)
				{
					currentLifeQuality -= (rand()%3 - m_goods.ware[i]);
					
					// m_goods.ware[i] is negative -> adds a positive value to the rand-value -> -= value
					
					m_goods.ware[i] = 0;
					
				
				}
				else
				{
					currentLifeQuality ++;
				}
			}
			currentLifeQuality = m_lifequality + 4*currentLifeQuality;
			currentLifeQuality = currentLifeQuality / 5;
			m_lifequality = currentLifeQuality;
			m_inhabitants += currentLifeQuality;
			qWarning() << "current Inhabitants:" << m_inhabitants << "(" << currentLifeQuality << ")";
		}

// 		for (QList<stadtklasse>::iterator it = stadtliste.begin(); it != stadtliste.end(); ++it)
// 		{
// // 			qWarning() << it->stadtname << hf->mapprops.stadtname ;
// 			if(it->stadtname == stadtname)
// 			{
// 				*it = stadt;
// 				break;
// 			}
// 		}

}

// qWarning() << "Ende Produktion";

// }
// }
// }

void KontorData::productGoods()
{
double production_param[const_warenanzahl];

	for(int i = 0; i<const_warenanzahl; i++)
	{
		production_param[i] = -1;
	}
	
	for(int i = 0; i < const_warenanzahl; i++)
	{
		if(m_production.ware[i] < 0)
		{
		    if(m_storage.ware[i] > m_production.ware[i])
		    {
			m_storage.ware[i] += m_production.ware[i];
		    }
		    else
		    {
			switch(i)
			{
			case W_Baumstamme:			//Baumstaemme
				{
				production_param[W_Pech] = m_storage.ware[i] / m_production.ware[i];
				production_param[W_Holzkohle] = m_storage.ware[i] / m_production.ware[i];
				production_param[W_Salz] = m_storage.ware[i] / m_production.ware[i];
				break;
				}
			case W_Holzbretter:			//Holzbretter
				{
				if(m_storage.ware[i] / m_production.ware[i] < production_param[W_Salz])
				{
					production_param[W_Salz] = m_storage.ware[i] / m_production.ware[i];
				}
				if(m_storage.ware[i] / m_production.ware[i] < production_param[W_Steine])
				{
					production_param[W_Steine] = m_storage.ware[i] / m_production.ware[i];
				}
				
				if(m_storage.ware[i] / m_production.ware[i] < production_param[W_Holzkohle])
				{
					production_param[W_Holzkohle] = m_storage.ware[i] / m_production.ware[i];
				}
				
				if(m_storage.ware[i] / m_production.ware[i] < production_param[W_Pech])
				{
					production_param[W_Pech] = m_storage.ware[i] / m_production.ware[i];
				}
				if(m_storage.ware[i] / m_production.ware[i] < production_param[W_Werkzeuge])
				{
					production_param[W_Werkzeuge] = m_storage.ware[i] / m_production.ware[i];
				}
				if(m_storage.ware[i] / m_production.ware[i] < production_param[W_Bier])
				{
					production_param[W_Bier] = m_storage.ware[i] / m_production.ware[i];
				}
				break;
				}
			case W_Holzkohle:			//Holzkohle ... (2 HK aus 3 BS und 1 HB)
				{
				if(m_storage.ware[i] / m_production.ware[i] < production_param[W_Werkzeuge])
				{
					production_param[W_Werkzeuge] = m_storage.ware[i] / m_production.ware[i];
				}
				if(m_storage.ware[i] / m_production.ware[i] < production_param[W_Schmiedeeisen])
				{
					production_param[W_Schmiedeeisen] = m_storage.ware[i] / m_production.ware[i];
				}
				
				break;
				}
			case W_Pech:				//Pech (5 Pech aus 3 BS und 1 HB)
				{
				
				break;
				}
			case W_Steine:				//Steine / Ziegel
				{
				
				break;
				}
			case W_Eisenerz:			//Eisenerz
				{
				if(m_storage.ware[i] / m_production.ware[i] < production_param[W_Schmiedeeisen])
				{
					production_param[W_Schmiedeeisen] = m_storage.ware[i] / m_production.ware[i];
				}
				break;
				}
			case W_Schmiedeeisen:			//Schmiedeeisen
				{
				if(m_storage.ware[i] / m_production.ware[i] < production_param[W_Werkzeuge])
				{
					production_param[W_Werkzeuge] = m_storage.ware[i] / m_production.ware[i];
				}
				break;
				}
			case W_Werkzeuge:			//Werkzeuge
				{
				if(m_storage.ware[i] / m_production.ware[i] < production_param[W_Baumstamme])
				{
					production_param[W_Baumstamme] = m_storage.ware[i] / m_production.ware[i];
				}
				if(m_storage.ware[i] / m_production.ware[i] < production_param[W_Holzbretter])
				{
					production_param[W_Holzbretter] = m_storage.ware[i] / m_production.ware[i];
				}
				if(m_storage.ware[i] / m_production.ware[i] < production_param[W_Eisenerz])
				{
					production_param[W_Eisenerz] = m_storage.ware[i] / m_production.ware[i];
				}
				if(m_storage.ware[i] / m_production.ware[i] < production_param[W_Stoffe])
				{
					production_param[W_Stoffe] = m_storage.ware[i] / m_production.ware[i];
				}
				if(m_storage.ware[i] / m_production.ware[i] < production_param[W_Wein])
				{
					production_param[W_Wein] = m_storage.ware[i] / m_production.ware[i];
				}
				if(m_storage.ware[i] / m_production.ware[i] < production_param[W_Fisch])
				{
					production_param[W_Fisch] = m_storage.ware[i] / m_production.ware[i];
				}
				if(m_storage.ware[i] / m_production.ware[i] < production_param[W_Bier])
				{
					production_param[W_Bier] = m_storage.ware[i] / m_production.ware[i];
				}
				if(m_storage.ware[i] / m_production.ware[i] < production_param[W_Fleisch])
				{
					production_param[W_Fleisch] = m_storage.ware[i] / m_production.ware[i];
				}
				if(m_storage.ware[i] / m_production.ware[i] < production_param[W_Leder])
				{
					production_param[W_Leder] = m_storage.ware[i] / m_production.ware[i];
				}
				if(m_storage.ware[i] / m_production.ware[i] < production_param[W_Getreide])
				{
					production_param[W_Getreide] = m_storage.ware[i] / m_production.ware[i];
				}
				if(m_storage.ware[i] / m_production.ware[i] < production_param[W_Schmiedeeisen])
				{
					production_param[W_Schmiedeeisen] = m_storage.ware[i] / m_production.ware[i];
				}
				
				break;
				}
			case W_Leder:			//Leder
				{
				
				break;
				}
			case W_Wolle:			//Wolle
				{
				if(m_storage.ware[i] / m_production.ware[i] < production_param[W_Stoffe])
				{
					production_param[W_Stoffe] = m_storage.ware[i] / m_production.ware[i];
				}
				break;
				}
			case W_Stoffe:		//Stoffe
				{
				break;
				}
			case W_Salz:		//Salz
				{
				if(m_storage.ware[i] / m_production.ware[i] < production_param[W_Leder])
				{
					production_param[W_Leder] = m_storage.ware[i] / m_production.ware[i];
				}
				if(m_storage.ware[i] / m_production.ware[i] < production_param[W_Fleisch])
				{
					production_param[W_Fleisch] = m_storage.ware[i] / m_production.ware[i];
				}
				if(m_storage.ware[i] / m_production.ware[i] < production_param[W_Fisch])
				{
					production_param[W_Fisch] = m_storage.ware[i] / m_production.ware[i];
				}
				break;
				}
			case W_Fisch:		//Fisch
				{
				break;
				}
			case W_Fleisch:		//Fleisch
				{
				break;
				}
			case W_Getreide:		//Getreide
				{
				if(m_storage.ware[i] / m_production.ware[i] < production_param[W_Leder])
				{
					production_param[W_Leder] = m_storage.ware[i] / m_production.ware[i];
				}
				if(m_storage.ware[i] / m_production.ware[i] < production_param[W_Fleisch])
				{
					production_param[W_Fleisch] = m_storage.ware[i] / m_production.ware[i];
				}
				if(m_storage.ware[i] / m_production.ware[i] < production_param[W_Bier])
				{
					production_param[W_Bier] = m_storage.ware[i] / m_production.ware[i];
				}
				if(m_storage.ware[i] / m_production.ware[i] < production_param[W_Wolle])
				{
					production_param[W_Wolle] = m_storage.ware[i] / m_production.ware[i];
				}
				break;
				}
			case W_Bier:		//Bier
				{
				break;
				}
			case W_Wein:		//Wein
				{
				break;
				}
			case W_Hanf:		//Hanf
				{
				break;
				}
			case W_Gold:		//Gold
				{
				break;
				}
			case W_Schmuck:		//Schmuck
				{
				break;
				}
			default:
				break;
			}
			}
		    }
		
		    
	}
for(int i = 0; i < const_warenanzahl; i++)
{
m_storage.ware[i] -= m_production.ware[i] * production_param[i];		// neg. production_param * neg prod = pos nettoprod. --> -nettoprod = neg. ; neg prod_param * pos prod = neg. nettoproduction --> -nettoprod = pos 
}
}
