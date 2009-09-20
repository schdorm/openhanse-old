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
			case Goods::Trunks:			//Baumstaemme
				{
				m_storage.addGood(Goods::Trunks, 1);		//Grundproduktion um Festfahren und komplette Stockung der Wirtschaft zu verhindern
				
// 			m_storage.good(i) += ((rand() % 12) + m_inhabitants/100);
				if(m_storage.good(Goods::Tools) - m_inhabitants/250 > 0)
				{
				m_storage.setGood(Goods::Trunks, m_storage.good(Goods::Trunks) + m_inhabitants/40);
				m_storage.setGood(Goods::Tools, m_storage.good(Goods::Tools) - m_inhabitants/250);
				}

				break;
				}
			case Goods::Shelves:			//Holzbretter
				{
				if(m_storage.good(Goods::Trunks) - m_inhabitants/100 > 0 &&
				m_storage.good(Goods::Tools) - m_inhabitants/200 > 0)
				{
				m_storage.addGood(Goods::Shelves, m_inhabitants/40);
				m_storage.addGood(Goods::Trunks, - m_inhabitants/100);
				m_storage.addGood(Goods::Tools, - m_inhabitants/200);
				}
				break;
				}
			case Goods::Charcoal:			//Holzkohle ... (2 HK aus 3 BS und 1 HB)
				{
				if(m_storage.good(Goods::Trunks) - m_inhabitants/300 > 0 && m_storage.good(Goods::Shelves) - 1 > 0 )
				{
				m_storage.addGood(Goods::Charcoal, m_inhabitants/150);
				m_storage.addGood(Goods::Trunks, - m_inhabitants/300);
// 				m_storage.addGood(Goods::Shelves, - m_inhabitants/1000);
				m_storage.addGood(Goods::Shelves, -1);
				}
				break;
				}
			case Goods::Pitch:				//Pech (5 Pech aus 3 BS und 1 HB)
				{
				if(m_storage.good(Goods::Trunks) - m_inhabitants/500 > 0 &&
 				m_storage.good(Goods::Shelves) - 1 > 0)
				{
					m_storage.addGood(Goods::Pitch,  m_inhabitants/80);
					m_storage.addGood(Goods::Trunks, - m_inhabitants/500);
					m_storage.addGood(Goods::Shelves, -1);
				}
				break;
				}
			case Goods::Bricks:				//Steine / Ziegel
				{
				if(m_storage.good(Goods::Shelves) - m_inhabitants/1000 > 0 && m_storage.good(Goods::Tools) - m_inhabitants/500 > 0)
				{
					m_storage.addGood(Goods::Bricks, m_inhabitants/100);
					m_storage.addGood(Goods::Shelves, - m_inhabitants/800);
					m_storage.addGood(Goods::Tools, - m_inhabitants/300);
				}
				break;
				}
			case Goods::IronOre:			//Eisenerz
				{
				if(m_storage.good(Goods::Tools) - m_inhabitants/400 >0)
				{
					m_storage.addGood(Goods::IronOre, m_inhabitants/100);
					m_storage.addGood(Goods::Tools, - m_inhabitants/400);
				}
				m_storage.addGood(Goods::IronOre, +1);	// Grundproduktion
				break;
				}
			case Goods::MalleableIron:			//Schmiedeeisen
				{
				if(m_storage.good(Goods::IronOre) - m_inhabitants/100 > 0 && m_storage.good(Goods::Charcoal) - m_inhabitants/300 > 0 && m_storage.good(Goods::Tools) - m_inhabitants/500 > 0)
				{
					m_storage.addGood(Goods::MalleableIron, m_inhabitants/150);
					m_storage.addGood(Goods::IronOre, - m_inhabitants/140);	
					m_storage.addGood(Goods::Charcoal, - m_inhabitants/300);
					m_storage.addGood(Goods::Tools, - m_inhabitants/500);
				}
				break;
				}
			case Goods::Tools:			//Werkzeuge
				{
				if(m_storage.good(Goods::MalleableIron) - m_inhabitants/200 > 0 && m_storage.good(Goods::Charcoal) - m_inhabitants/500 > 0 && m_storage.good(Goods::Shelves) - m_inhabitants/400 > 0)
				{
					m_storage.addGood(Goods::Tools, m_inhabitants/25);
					m_storage.addGood(Goods::MalleableIron, - m_inhabitants/200);
					m_storage.addGood(Goods::Charcoal, -- m_inhabitants/500);
					m_storage.addGood(Goods::Shelves, - m_inhabitants/400);
				}
				m_storage.addGood(Goods::Tools, 1);
				break;
				}
			case Goods::Leather:			//Leder
				{
				if(m_storage.good(Goods::Salt) - m_inhabitants/700 > 0 && m_storage.good(Goods::Tools) - m_inhabitants/700 > 0)
				{
					m_storage.addGood(Goods::Leather,  m_inhabitants/100);
					m_storage.addGood(Goods::Salt, - m_inhabitants/700);
					m_storage.addGood(Goods::Tools, - m_inhabitants/700);
				}
				break;
				}
			case Goods::Wool:			//Wolle
				{
				if(m_storage.good(Goods::Tools) - m_inhabitants/600 > 0 && m_storage.good(Goods::Cereal) - m_inhabitants/600 > 0)
				{
					m_storage.addGood(Goods::Wool,  m_inhabitants/200);
					m_storage.addGood(Goods::Tools, --m_inhabitants/600);
					m_storage.addGood(Goods::Cereal, - m_inhabitants/600);
				}
				break;
				}
			case Goods::Cloth:		//Stoffe
				{
				if(m_storage.good(Goods::Wool) - m_inhabitants/500 > 0 && m_storage.good(Goods::Tools) - m_inhabitants/1000 > 0)
				{
					m_storage.addGood(Goods::Cloth, m_inhabitants/80);
					m_storage.addGood(Goods::Wool, - m_inhabitants/500);
					m_storage.addGood(Goods::Tools, - m_inhabitants/1000);
				}
				break;
				}
			case Goods::Salt:		//Salz
				{
				if(m_storage.good(Goods::Shelves) - m_inhabitants/800 > 0 &&
				m_storage.good(Goods::Tools) - m_inhabitants/1000 > 0)
				{
					m_storage.addGood(Goods::Salt, m_inhabitants/80);
					m_storage.addGood(Goods::Shelves, - m_inhabitants/800);
					m_storage.addGood(Goods::Tools, - m_inhabitants/1000);
				}
				break;
				}
			case Goods::Fish:		//Fisch
				{
				if(m_storage.good(Goods::Salt) - m_inhabitants/100 > 0 &&
				m_storage.good(Goods::Tools) - m_inhabitants/400 > 0 && m_storage.good(Goods::Hemp) - m_inhabitants/250 > 0)
				{
					m_storage.addGood(Goods::Fish,  m_inhabitants/30);
					m_storage.addGood(Goods::Salt, - m_inhabitants/100);
					m_storage.addGood(Goods::Tools, - m_inhabitants/400);
					m_storage.addGood(Goods::Hemp, - m_inhabitants/250);
				}
				break;
				}
			case Goods::Meat:		//Fleisch
				{
				if(m_storage.good(Goods::Cereal) - m_inhabitants/200 > 0 && m_storage.good(Goods::Tools) - m_inhabitants/1000 > 0 && m_storage.good(Goods::Salt) - m_inhabitants/300 > 0)
				{
					m_storage.addGood(Goods::Meat,  m_inhabitants/45);
					m_storage.addGood(Goods::Tools, - m_inhabitants/250);
					m_storage.addGood(Goods::Cereal, - m_inhabitants/100);
					m_storage.addGood(Goods::Salt, - m_inhabitants/100);
				}
				break;
				}
			case Goods::Cereal:		//Getreide
				{
				if(m_storage.good(Goods::Tools) - m_inhabitants/1000 > 0)
				{
					m_storage.addGood(Goods::Cereal, m_inhabitants/10);
					m_storage.addGood(Goods::Tools, - m_inhabitants/100);
				}
				m_storage.addGood(Goods::Cereal, 1);
				break;
				}
			case Goods::Beer:		//Bier
				{
				if(m_storage.good(Goods::Cereal) - m_inhabitants/500 > 0 &&
				m_storage.good(Goods::Shelves) - m_inhabitants/1000 > 0 &&
				m_storage.good(Goods::Tools) - m_inhabitants/1000 > 0)
				{
					m_storage.addGood(Goods::Beer,  m_inhabitants/25);
					m_storage.addGood(Goods::Cereal, - m_inhabitants/100);
					m_storage.addGood(Goods::Shelves, - m_inhabitants/200);
					m_storage.addGood(Goods::Tools, - m_inhabitants/200);
				}
				break;
				}
			case Goods::Wine:		//Wein
				{
				if(m_storage.good(Goods::Tools) - m_inhabitants/2000 > 0)
				{
					m_storage.addGood(Goods::Wine, m_inhabitants/50);
					m_storage.addGood(Goods::Tools, - m_inhabitants/500);
				}
				break;
				}
			case Goods::Hemp:		//Hanf
				{
				if(m_storage.good(Goods::Tools) - m_inhabitants/1000 > 0)
				{
					m_storage.addGood(Goods::Hemp,  m_inhabitants/250);
					m_storage.addGood(Goods::Tools, - m_inhabitants/1000);
				}
				break;
				}
			case Goods::Gold:		//Gold
				{
				break;
				}
			case Goods::Jewellery:		//Schmuck
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
			case Goods::Trunks:			//Baumstaemme
				{
// 			m_storage.good(i) += ((rand() % 12) + m_inhabitants/100);
				if(m_storage.good(Goods::Tools) - m_inhabitants/1000 > 0)
				{
					m_storage.setGood(Goods::Trunks, m_storage.good(Goods::Trunks) + m_inhabitants/200);
					m_storage.setGood(Goods::Tools, m_storage.good(Goods::Tools) - m_inhabitants/1000);
				}
				break;
				}
			case Goods::Shelves:			//Holzbretter
				{
				if(m_storage.good(Goods::Trunks) - m_inhabitants/400 > 0 &&
				m_storage.good(Goods::Tools) - m_inhabitants/800 > 0)
				{
				m_storage.addGood(Goods::Shelves, m_inhabitants/200);
				m_storage.addGood(Goods::Trunks, -m_inhabitants/400);
				m_storage.addGood(Goods::Tools, - m_inhabitants/800);
				}
				break;
				}
			case Goods::Charcoal:			//Holzkohle ... (2 HK aus 3 BS und 1 HB)
				{
				if(m_storage.good(Goods::Trunks) - m_inhabitants/1000 > 0 && m_storage.good(Goods::Shelves) - 1 > 0 )
				{
				m_storage.addGood(Goods::Charcoal, m_inhabitants/800);
				m_storage.addGood(Goods::Trunks, -m_inhabitants/1000);
// 				m_storage.addGood(Goods::Shelves, - m_inhabitants/1000);
				m_storage.addGood(Goods::Shelves, -1);
				}
				break;
				}
			case Goods::Pitch:			//Pech (5 Pech aus 3 BS und 1 HB)
				{
				if(m_storage.good(Goods::Trunks) - m_inhabitants/1000 > 0 &&
 				m_storage.good(Goods::Shelves) - 1 > 0)
				{
				m_storage.addGood(Goods::Charcoal, m_inhabitants/200);
				m_storage.addGood(Goods::Trunks, -m_inhabitants/1000);
				m_storage.addGood(Goods::Shelves, -1);
				}
				break;
				}
			case Goods::Bricks:			//Steine / Ziegel
				{
				if(m_storage.good(Goods::Shelves) - m_inhabitants/800 > 0 && m_storage.good(Goods::Tools) - m_inhabitants/1500 > 0)
				m_storage.addGood(Goods::Bricks, m_inhabitants/800);
				m_storage.addGood(Goods::Shelves, - m_inhabitants/1500);
				m_storage.addGood(Goods::Tools, - m_inhabitants/800);
				break;
				}
			case Goods::IronOre:
				{		//Eisenerz
				if(m_storage.good(Goods::Tools) - m_inhabitants/800 >0)
				{
				m_storage.addGood(Goods::IronOre, m_inhabitants/400);
				m_storage.addGood(Goods::Tools, - m_inhabitants/800);
				}
				break;
				}
			case Goods::MalleableIron:			//Schmiedeeisen
				{
				if(m_storage.good(Goods::IronOre) - m_inhabitants/400 > 0 && m_storage.good(Goods::Charcoal) - m_inhabitants/800 > 0 && m_storage.good(Goods::Tools) - m_inhabitants/1000 > 0)
				{
				m_storage.addGood(Goods::MalleableIron, m_inhabitants/500);
				m_storage.addGood(Goods::IronOre, - m_inhabitants/400);	
				m_storage.addGood(Goods::Charcoal, - m_inhabitants/800);
				m_storage.addGood(Goods::Tools, - m_inhabitants/1000);
				}
				break;
				}
			case Goods::Tools:			//Werkzeuge
				{
				if(m_storage.good(Goods::MalleableIron) - m_inhabitants/400 > 0 && m_storage.good(Goods::Charcoal) - m_inhabitants/1000 > 0 && m_storage.good(Goods::Shelves) - m_inhabitants/800 > 0)
				{
					m_storage.addGood(Goods::Tools, m_inhabitants/40);
					m_storage.addGood(Goods::MalleableIron,  m_inhabitants/400);
					m_storage.addGood(Goods::Charcoal, - m_inhabitants/1000);
					m_storage.addGood(Goods::Shelves, - m_inhabitants/800);
				}
				m_storage.addGood(Goods::Tools, 1);
				break;
				}
			case Goods::Leather:			//Leder
				{
				if(m_storage.good(Goods::Salt) - m_inhabitants/2000 > 0 && m_storage.good(Goods::Tools) - m_inhabitants/2000 > 0)
				{
					m_storage.addGood(Goods::Leather,  m_inhabitants/1000);
					m_storage.addGood(Goods::Salt, - m_inhabitants/2000);
					m_storage.addGood(Goods::Tools, - m_inhabitants/2000);
				}
				break;
				}
			case Goods::Wool:			//Wolle
				{
				if(m_storage.good(Goods::Tools) - m_inhabitants/1000 > 0)
				{
					m_storage.addGood(Goods::Wool,  m_inhabitants/1000);
					m_storage.addGood(Goods::Tools, - m_inhabitants/2000);
				}
				break;
				}
			case Goods::Cloth:		//Stoffe
				{
				if(m_storage.good(Goods::Wool) - m_inhabitants/1000 > 0 && m_storage.good(Goods::Tools) - m_inhabitants/2000 > 0)
				{
					m_storage.addGood(Goods::Cloth, m_inhabitants/100);
					m_storage.addGood(Goods::Wool, - m_inhabitants/500);
					m_storage.addGood(Goods::Tools, - m_inhabitants/1000);
				}
				break;
				}
			case Goods::Salt:		//Salz
				{
				if(m_storage.good(Goods::Shelves) - m_inhabitants/1600 > 0 &&
				m_storage.good(Goods::Tools) - m_inhabitants/2000 > 0)
				{
					m_storage.addGood(Goods::Salt, m_inhabitants/100);
					m_storage.addGood(Goods::Shelves, - m_inhabitants/1600);
					m_storage.addGood(Goods::Tools, - m_inhabitants/2000);
				}
				break;
				}
			case Goods::Fish:		//Fisch
				{
				if(m_storage.good(Goods::Salt) - m_inhabitants/400 > 0 &&
				m_storage.good(Goods::Tools) - m_inhabitants/2000 > 0)
				{
					m_storage.addGood(Goods::Fish,  m_inhabitants/400);
					m_storage.addGood(Goods::Salt, - m_inhabitants/400);
					m_storage.addGood(Goods::Tools, - m_inhabitants/2000);
				}
				break;
				}
			case Goods::Meat:		//Fleisch
				{
				if(m_storage.good(Goods::Cereal) - m_inhabitants/400 > 0 && m_storage.good(Goods::Tools) - m_inhabitants/2000 > 0 && m_storage.good(Goods::Salt) - m_inhabitants/500 > 0)
				{
					m_storage.addGood(Goods::Meat,  m_inhabitants/400);
					m_storage.addGood(Goods::Tools, - m_inhabitants/2000);
					m_storage.addGood(Goods::Cereal, - m_inhabitants/400);
					m_storage.addGood(Goods::Salt, - m_inhabitants/500);
				}
				break;
				}
			case Goods::Cereal:		//Getreide
				{
				if(m_storage.good(Goods::Tools) - m_inhabitants/2000 > 0)
				{
					m_storage.addGood(Goods::Cereal, m_inhabitants/120);
					m_storage.addGood(Goods::Tools, - m_inhabitants/2000);
				}
				m_storage.addGood(Goods::Cereal, 1);
				break;
				}
			case Goods::Beer:		//Bier
				{
				if(m_storage.good(Goods::Cereal) - m_inhabitants/1000 > 0 &&
				m_storage.good(Goods::Shelves) - m_inhabitants/2000 > 0 &&
				m_storage.good(Goods::Tools) - m_inhabitants/2000 > 0)
				{
					m_storage.addGood(Goods::Beer,  m_inhabitants/200);
					m_storage.addGood(Goods::Cereal, - m_inhabitants/1000);
					m_storage.addGood(Goods::Shelves, - m_inhabitants/2000);
					m_storage.addGood(Goods::Tools, - m_inhabitants/2000);
				}
				break;
				}
			case Goods::Wine:		//Wein
				{
				if(m_storage.good(Goods::Tools) - m_inhabitants/2000 > 0)
				{
				m_storage.addGood(Goods::Wine, m_inhabitants/500);
				m_storage.addGood(Goods::Tools, - m_inhabitants/2000);
				}
				break;
				}
			case Goods::Gold:		//Gold
				{
				break;
				}
			case Goods::Jewellery:		//Schmuck
				{
				break;
				}
			case Goods::Hemp:		//Hanf?
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
			case Goods::Trunks:			//Baumstaemme
				{
// 			m_storage.good(i) += ((rand() % 12) + m_inhabitants/100);
				if(m_storage.good(Goods::Tools) - m_inhabitants/1500 > 0)
				{
				m_storage.setGood(Goods::Trunks, m_storage.good(Goods::Trunks) + m_inhabitants/250);
				m_storage.setGood(Goods::Tools, m_storage.good(Goods::Tools) - m_inhabitants/1500);
				}
				break;
				}
			case Goods::Shelves:			//Holzbretter
				{
				if(m_storage.good(Goods::Trunks) - m_inhabitants/500 > 0 &&
				m_storage.good(Goods::Tools) - m_inhabitants/1000 > 0)
				{
				m_storage.addGood(Goods::Shelves,m_inhabitants/250);
				m_storage.addGood(Goods::Trunks, -m_inhabitants/500);
				m_storage.addGood(Goods::Tools, - m_inhabitants/1000);
				}
				break;
				}
			case Goods::Charcoal:			//Holzkohle ... (2 HK aus 3 BS und 1 HB)
				{
				if(m_storage.good(Goods::Trunks) - m_inhabitants/1500 > 0 && m_storage.good(Goods::Shelves) - 1 > 0 )
				{
				m_storage.addGood(Goods::Charcoal, m_inhabitants/1000);
				m_storage.addGood(Goods::Trunks, -m_inhabitants/1500);
// 				m_storage.addGood(Goods::Shelves, - m_inhabitants/1000);
				m_storage.addGood(Goods::Shelves, 1);
				}
				break;
				}
			case Goods::Pitch:			//Pech (5 Pech aus 3 BS und 1 HB)
				{
				if(m_storage.good(Goods::Trunks) - m_inhabitants/1500 > 0 &&
 				m_storage.good(Goods::Shelves) - 1 > 0)
				{
				m_storage.addGood(Goods::Charcoal, m_inhabitants/250);
				m_storage.addGood(Goods::Trunks, -m_inhabitants/1500);
				m_storage.addGood(Goods::Shelves, 1);
				}
				break;
				}
			case Goods::Bricks:			//Steine / Ziegel
				{
				if(m_storage.good(Goods::Shelves) - m_inhabitants/1500 > 0 )
				{
				m_storage.addGood(Goods::Bricks, m_inhabitants/800);
				m_storage.addGood(Goods::Shelves, - m_inhabitants/1500);
// 				m_storage.good(Goods::Shelves) --;
				}
				break;
				}
			case Goods::IronOre:
				{		//Eisenerz
				if(m_storage.good(Goods::Tools) - m_inhabitants/2000 >0)
				{
				m_storage.addGood(Goods::IronOre, m_inhabitants/1000);
				m_storage.addGood(Goods::Tools, - m_inhabitants/2000);
				}
				break;
				}
			case Goods::MalleableIron:			//Schmiedeeisen
				{
				if(m_storage.good(Goods::IronOre) - m_inhabitants/800 > 0 && m_storage.good(Goods::Charcoal) - m_inhabitants/1200 > 0 && m_storage.good(Goods::Tools) - m_inhabitants/1500 > 0)
				{
				m_storage.addGood(Goods::MalleableIron, m_inhabitants/1000);
				m_storage.addGood(Goods::IronOre, - m_inhabitants/800);	
				m_storage.addGood(Goods::Charcoal, - m_inhabitants/1200);
				m_storage.addGood(Goods::Tools, - m_inhabitants/1500);
				}
				break;
				}
			case Goods::Tools:			//Werkzeuge
				{
				if(m_storage.good(Goods::MalleableIron) - m_inhabitants/500 > 0 && m_storage.good(Goods::Charcoal) - m_inhabitants/1500 > 0 && m_storage.good(Goods::Shelves) - m_inhabitants/1200 > 0)
				{
					m_storage.addGood(Goods::Tools, m_inhabitants/100);
					m_storage.addGood(Goods::MalleableIron,  m_inhabitants/500);
					m_storage.addGood(Goods::Charcoal, - m_inhabitants/1500);
					m_storage.addGood(Goods::Shelves, - m_inhabitants/1200);
				}
				break;
				}
			case Goods::Leather:			//Leder
				{
				if(m_storage.good(Goods::Salt) - m_inhabitants/2000 > 0 && m_storage.good(Goods::Tools) - m_inhabitants/2000 > 0)
				{
					m_storage.addGood(Goods::Leather,  m_inhabitants/1000);
					m_storage.addGood(Goods::Salt, - m_inhabitants/2000);
					m_storage.addGood(Goods::Tools, - m_inhabitants/2000);
				}
				break;
				}
			case Goods::Wool:			//Wolle
				{
				if(m_storage.good(Goods::Tools) - m_inhabitants/2000 > 0)
				{
					m_storage.addGood(Goods::Wool,  m_inhabitants/1500);
					m_storage.addGood(Goods::Tools, - m_inhabitants/2000);
				}
				break;
				}
			case Goods::Cloth:		//Stoffe
				{
				if(m_storage.good(Goods::Cloth) - m_inhabitants/1500 > 0 && m_storage.good(Goods::Tools) - m_inhabitants/2000 > 0)
				{
					m_storage.addGood(Goods::Cloth, m_inhabitants/250);
					m_storage.addGood(Goods::Wool, - m_inhabitants/1500);
					m_storage.addGood(Goods::Tools, - m_inhabitants/2000);
				}
				break;
				}
			case Goods::Salt:		//Salz
				{
				if(m_storage.good(Goods::Shelves) - m_inhabitants/2000 > 0 &&
				m_storage.good(Goods::Tools) - m_inhabitants/2000 > 0)
				{
					m_storage.addGood(Goods::Salt, m_inhabitants/400);
					m_storage.addGood(Goods::Shelves, - m_inhabitants/2000);
					m_storage.addGood(Goods::Tools, - m_inhabitants/2000);
				}
				break;
				}
			case Goods::Fish:		//Fisch
				{
				if(m_storage.good(Goods::Salt) - m_inhabitants/500 > 0 &&
				m_storage.good(Goods::Tools) - m_inhabitants/2000 > 0)
				{
					m_storage.addGood(Goods::Fish,  m_inhabitants/500);
					m_storage.addGood(Goods::Salt, - m_inhabitants/500);
					m_storage.addGood(Goods::Tools, - m_inhabitants/2000);
				}
				break;
				}
			case Goods::Meat:		//Fleisch
				{
				if(m_storage.good(Goods::Cereal) - m_inhabitants/1000 > 0 && m_storage.good(Goods::Tools) - m_inhabitants/2000 > 0 && m_storage.good(Goods::Salt) - m_inhabitants/500)
				{
					m_storage.addGood(Goods::Meat,  m_inhabitants/500);
					m_storage.addGood(Goods::Tools, - m_inhabitants/2000);
					m_storage.addGood(Goods::Cereal, - m_inhabitants/1000);
					m_storage.addGood(Goods::Salt, - m_inhabitants/500);
				}
				break;
				}
			case Goods::Cereal:		//Getreide
				{
				if(m_storage.good(Goods::Tools) - m_inhabitants/2000 > 0)
				{
					m_storage.addGood(Goods::Cereal, m_inhabitants/250);
					m_storage.addGood(Goods::Tools, - m_inhabitants/2000);
				}
				break;
				}
			case Goods::Beer:		//Bier
				{
				if(m_storage.good(Goods::Cereal) - m_inhabitants/1500 > 0 &&
				m_storage.good(Goods::Shelves) - m_inhabitants/2000 > 0 &&
				m_storage.good(Goods::Tools) - m_inhabitants/2000 > 0)
				{
					m_storage.addGood(Goods::Beer,  m_inhabitants/250);
					m_storage.addGood(Goods::Cereal, - m_inhabitants/1500);
					m_storage.addGood(Goods::Shelves, - m_inhabitants/2000);
					m_storage.addGood(Goods::Tools, - m_inhabitants/2000);
				}
				break;
				}
			case Goods::Wine:		//Wein
				{
				if(m_storage.good(Goods::Tools) - m_inhabitants/2000 > 0)
				{
				m_storage.addGood(Goods::Wine, m_inhabitants/1000);
				m_storage.addGood(Goods::Tools, - m_inhabitants/2000);
				}
				break;
				}
			case Goods::Gold:		//Gold
				{
				break;
				}
			case Goods::Jewellery:		//Schmuck
				{
				break;
				}
			case Goods::Hemp:		//Hanf?
				{
				break;
				}

			default:
				break;
			}
		}
// 			if(hproduction[j) == i)
// 			{
// 			qWarning() << "Hproduktion vorher: "<< m_storage.good(i);
// 			m_storage.good(i) += ((rand() % 12) + m_inhabitants/100);
// 			qWarning() << "Hproduktion nachher" << m_storage.good(i);
// 			}
// 			if(mproduction[j) == i)
// 			{
// 			qWarning() << "MProduktion vorher" << m_storage.good(i);
// 			m_storage.good(i) += ((rand() % 9) + m_inhabitants/200);
// 			qWarning() << "MProduktion nachher" << m_storage.good(i);
// 			}
// 			if(lproduction[j) == i)
// 			{
// 			qWarning() << "NProduktion vorher" << m_storage.good(i);
// 			m_storage.good(i) += ((rand()% 4) + m_inhabitants/350);
// 			qWarning() << "NProduktion nachher" << m_storage.good(i);
// 			}
///////////////////Stadtverbrauch durch Essen ^^


		if(param_durchlauf%3==0)				//Alle 3 "Tage"
		{
			// stadtware[Goods::Trunks);
			m_storage.addGood(Goods::Shelves, - m_inhabitants/1000);
// stadtware[Goods::Charcoal) -= m_inhabitants/1000);		//Als Heizzeug .. evtl. anpassen
// stadtware[Goods::Pitch);
			m_storage.addGood(Goods::Bricks, -m_inhabitants/2000);
// stadtware[Goods::IronOre);
			m_storage.addGood(Goods::MalleableIron,  m_inhabitants/2000);
			m_storage.addGood(Goods::Tools, - m_inhabitants/500);
			m_storage.addGood(Goods::Leather, - m_inhabitants/500);		//Leder
			m_storage.addGood(Goods::Wool, - m_inhabitants/1000);
			m_storage.addGood(Goods::Cloth, - m_inhabitants/300);
			m_storage.addGood(Goods::Salt, - m_inhabitants/500);
			m_storage.addGood(Goods::Fish, -m_inhabitants/100);
					//Fisch hauefig gegessen
			m_storage.addGood(Goods::Meat, - m_inhabitants/800);
					//Fleisch fuer wohlhabendere Schichten
			m_storage.addGood(Goods::Cereal, - m_inhabitants/100);
					//Getreide fuer alle
			m_storage.addGood(Goods::Bread, - m_inhabitants/60);
					//Brot als Grundnahrungsmittel überhaupt fuer alle	
			m_storage.addGood(Goods::Beer, - m_inhabitants/50);
					//Bier auch sehr wichtig - billiges Getraenk fuer jedermann
			m_storage.addGood(Goods::Wine, - m_inhabitants/100);
					//Wein wieder fuer wohlhabendere Schichten
// stadtware[17];
// stadtware[18];
// stadtware[19];
			int currentLifeQuality = 0;

			for(int i = 0; i < const_warenanzahl ;i++)
			{
				if(m_storage.good(i) < 0)
				{
					currentLifeQuality -= (rand()%3 - m_storage.good(i));
					
					// m_storage.good(i) is negative -> adds a positive value to the rand-value -> -= value
					
					m_storage.setGood(i, 0);
					
				
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
		if(m_production.good(i) < 0)
		{
		    if(m_storage.good(i) < m_production.good(i))
// 		    {
// 			m_storage.addGood(i, m_production.good(i));
// 		    }
// 		    else
		    {
			switch(i)
			{
			case Goods::Trunks:			//Baumstaemme
				{
				production_param[Goods::Pitch] = m_storage.good(i) / m_production.good(i);
				production_param[Goods::Charcoal] = m_storage.good(i) / m_production.good(i);
				production_param[Goods::Salt] = m_storage.good(i) / m_production.good(i);
				break;
				}
			case Goods::Shelves:			//Holzbretter
				{
				if(m_storage.good(i) / m_production.good(i) < production_param[Goods::Salt])
				{
					production_param[Goods::Salt] = m_storage.good(i) / m_production.good(i);
				}
				if(m_storage.good(i) / m_production.good(i) < production_param[Goods::Bricks])
				{
					production_param[Goods::Bricks] = m_storage.good(i) / m_production.good(i);
				}
				
				if(m_storage.good(i) / m_production.good(i) < production_param[Goods::Charcoal])
				{
					production_param[Goods::Charcoal] = m_storage.good(i) / m_production.good(i);
				}
				
				if(m_storage.good(i) / m_production.good(i) < production_param[Goods::Pitch])
				{
					production_param[Goods::Pitch] = m_storage.good(i) / m_production.good(i);
				}
				if(m_storage.good(i) / m_production.good(i) < production_param[Goods::Tools])
				{
					production_param[Goods::Tools] = m_storage.good(i) / m_production.good(i);
				}
				if(m_storage.good(i) / m_production.good(i) < production_param[Goods::Beer])
				{
					production_param[Goods::Beer] = m_storage.good(i) / m_production.good(i);
				}
				break;
				}
			case Goods::Charcoal:			//Holzkohle ... (2 HK aus 3 BS und 1 HB)
				{
				if(m_storage.good(i) / m_production.good(i) < production_param[Goods::Tools])
				{
					production_param[Goods::Tools] = m_storage.good(i) / m_production.good(i);
				}
				if(m_storage.good(i) / m_production.good(i) < production_param[Goods::MalleableIron])
				{
					production_param[Goods::MalleableIron] = m_storage.good(i) / m_production.good(i);
				}
				
				break;
				}
			case Goods::Pitch:				//Pech (5 Pech aus 3 BS und 1 HB)
				{
				
				break;
				}
			case Goods::Bricks:				//Steine / Ziegel
				{
				
				break;
				}
			case Goods::IronOre:			//Eisenerz
				{
				if(m_storage.good(i) / m_production.good(i) < production_param[Goods::MalleableIron])
				{
					production_param[Goods::MalleableIron] = m_storage.good(i) / m_production.good(i);
				}
				break;
				}
			case Goods::MalleableIron:			//Schmiedeeisen
				{
				if(m_storage.good(i) / m_production.good(i) < production_param[Goods::Tools])
				{
					production_param[Goods::Tools] = m_storage.good(i) / m_production.good(i);
				}
				break;
				}
			case Goods::Tools:			//Werkzeuge
				{
				if(m_storage.good(i) / m_production.good(i) < production_param[Goods::Trunks])
				{
					production_param[Goods::Trunks] = m_storage.good(i) / m_production.good(i);
				}
				if(m_storage.good(i) / m_production.good(i) < production_param[Goods::Shelves])
				{
					production_param[Goods::Shelves] = m_storage.good(i) / m_production.good(i);
				}
				if(m_storage.good(i) / m_production.good(i) < production_param[Goods::IronOre])
				{
					production_param[Goods::IronOre] = m_storage.good(i) / m_production.good(i);
				}
				if(m_storage.good(i) / m_production.good(i) < production_param[Goods::Cloth])
				{
					production_param[Goods::Cloth] = m_storage.good(i) / m_production.good(i);
				}
				if(m_storage.good(i) / m_production.good(i) < production_param[Goods::Wine])
				{
					production_param[Goods::Wine] = m_storage.good(i) / m_production.good(i);
				}
				if(m_storage.good(i) / m_production.good(i) < production_param[Goods::Fish])
				{
					production_param[Goods::Fish] = m_storage.good(i) / m_production.good(i);
				}
				if(m_storage.good(i) / m_production.good(i) < production_param[Goods::Beer])
				{
					production_param[Goods::Beer] = m_storage.good(i) / m_production.good(i);
				}
				if(m_storage.good(i) / m_production.good(i) < production_param[Goods::Meat])
				{
					production_param[Goods::Meat] = m_storage.good(i) / m_production.good(i);
				}
				if(m_storage.good(i) / m_production.good(i) < production_param[Goods::Leather])
				{
					production_param[Goods::Leather] = m_storage.good(i) / m_production.good(i);
				}
				if(m_storage.good(i) / m_production.good(i) < production_param[Goods::Cereal])
				{
					production_param[Goods::Cereal] = m_storage.good(i) / m_production.good(i);
				}
				if(m_storage.good(i) / m_production.good(i) < production_param[Goods::MalleableIron])
				{
					production_param[Goods::MalleableIron] = m_storage.good(i) / m_production.good(i);
				}
				
				break;
				}
			case Goods::Leather:			//Leder
				{
				
				break;
				}
			case Goods::Wool:			//Wolle
				{
				if(m_storage.good(i) / m_production.good(i) < production_param[Goods::Cloth])
				{
					production_param[Goods::Cloth] = m_storage.good(i) / m_production.good(i);
				}
				break;
				}
			case Goods::Cloth:		//Stoffe
				{
				break;
				}
			case Goods::Salt:		//Salz
				{
				if(m_storage.good(i) / m_production.good(i) < production_param[Goods::Leather])
				{
					production_param[Goods::Leather] = m_storage.good(i) / m_production.good(i);
				}
				if(m_storage.good(i) / m_production.good(i) < production_param[Goods::Meat])
				{
					production_param[Goods::Meat] = m_storage.good(i) / m_production.good(i);
				}
				if(m_storage.good(i) / m_production.good(i) < production_param[Goods::Fish])
				{
					production_param[Goods::Fish] = m_storage.good(i) / m_production.good(i);
				}
				break;
				}
			case Goods::Fish:		//Fisch
				{
				break;
				}
			case Goods::Meat:		//Fleisch
				{
				break;
				}
			case Goods::Cereal:		//Getreide
				{
				if(m_storage.good(i) / m_production.good(i) < production_param[Goods::Leather])
				{
					production_param[Goods::Leather] = m_storage.good(i) / m_production.good(i);
				}
				if(m_storage.good(i) / m_production.good(i) < production_param[Goods::Meat])
				{
					production_param[Goods::Meat] = m_storage.good(i) / m_production.good(i);
				}
				if(m_storage.good(i) / m_production.good(i) < production_param[Goods::Beer])
				{
					production_param[Goods::Beer] = m_storage.good(i) / m_production.good(i);
				}
				if(m_storage.good(i) / m_production.good(i) < production_param[Goods::Wool])
				{
					production_param[Goods::Wool] = m_storage.good(i) / m_production.good(i);
				}
				break;
				}
			case Goods::Beer:		//Bier
				{
				break;
				}
			case Goods::Wine:		//Wein
				{
				break;
				}
			case Goods::Hemp:		//Hanf
				{
				break;
				}
			case Goods::Gold:		//Gold
				{
				break;
				}
			case Goods::Jewellery:		//Schmuck
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
m_storage.addGood(i, - m_production.good(i) * production_param[i]);		// neg. production_param * neg prod = pos nettoprod. --> -nettoprod = neg. ; neg prod_param * pos prod = neg. nettoproduction --> -nettoprod = pos 
}
}
