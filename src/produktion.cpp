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

#include "gesamtbild.h"
#include "waren.h"
#include "stadtklasse.h"
#include "kontorklasse.h"
#include <QtDebug>

void gesamtbild::produktion(int durchlauf)
{
	CityClass *cityit;
	QList <CityClass> cityList = gamedata->ret_CityList();
	foreach(*cityit, cityList)
	{
	cityit->production(durchlauf);
	}
}

void CityClass::production(int durchlauf)
{
		qWarning() << "Stadtproduktion:" << cityname;
// 		for(int i=0;i<20;i++)
// 		{
		for(int j=0;j<5;j++)		//kann man mal noch schoen mit switch und case machen
		{
			switch(hproduction[j])
			{
			case W_Baumstamme:			//Baumstaemme
				{
// 			goods.ware[i] += ((rand() % 12) + inhabitants/100);
				if(goods.ware[W_Werkzeuge] - inhabitants/500 > 0)
				{
				goods.ware[W_Baumstamme] = goods.ware[W_Baumstamme] + inhabitants/100;
				goods.ware[W_Werkzeuge] = goods.ware[W_Werkzeuge] - inhabitants/500;
				}
				goods.ware[W_Baumstamme]++;		//Grundproduktion um Festfahren und komplette Stockung der Wirtschaft zu verhindern
				break;
				}
			case W_Holzbretter:			//Holzbretter
				{
				if(goods.ware[W_Baumstamme] - inhabitants/200 > 0 &&
				goods.ware[W_Werkzeuge] - inhabitants/400 > 0)
				{
				goods.ware[W_Holzbretter] += inhabitants/100;
				goods.ware[W_Baumstamme] -= inhabitants/200;
				goods.ware[W_Werkzeuge] -= inhabitants/400;
				}
				break;
				}
			case W_Holzkohle:			//Holzkohle ... (2 HK aus 3 BS und 1 HB)
				{
				if(goods.ware[W_Baumstamme] - inhabitants/500 > 0 && goods.ware[W_Holzbretter] - 1 > 0 )
				{
				goods.ware[W_Holzkohle] += inhabitants/400;
				goods.ware[W_Baumstamme] -= inhabitants/500;
// 				goods.ware[W_Holzbretter] -= inhabitants/1000;
				goods.ware[W_Holzbretter] --;
				}
				break;
				}
			case W_Pech:				//Pech (5 Pech aus 3 BS und 1 HB)
				{
				if(goods.ware[W_Baumstamme] - inhabitants/500 > 0 &&
 				goods.ware[W_Holzbretter] - 1 > 0)
				{
				goods.ware[W_Pech] += inhabitants/100;
				goods.ware[W_Baumstamme] -= inhabitants/500;
				goods.ware[W_Holzbretter] --;
				}
				break;
				}
			case W_Steine:				//Steine / Ziegel
				{
				if(goods.ware[W_Holzbretter] - inhabitants/500 > 0 && goods.ware[W_Werkzeuge] - inhabitants/1000 > 0)
				goods.ware[W_Steine] += inhabitants/400;
				goods.ware[W_Holzbretter] -= inhabitants/1000;
				goods.ware[W_Werkzeuge] -= inhabitants/500;
				break;
				}
			case W_Eisenerz:			//Eisenerz
				{
				if(goods.ware[W_Werkzeuge] - inhabitants/400 >0)
				{
				goods.ware[W_Eisenerz] += inhabitants/200;
				goods.ware[W_Werkzeuge] -= inhabitants/400;
				}
				goods.ware[W_Eisenerz]++;
				break;
				}
			case W_Schmiedeeisen:			//Schmiedeeisen
				{
				if(goods.ware[W_Eisenerz] - inhabitants/200 > 0 && goods.ware[W_Holzkohle] - inhabitants/400 > 0 && goods.ware[W_Werkzeuge] - inhabitants/500 > 0)
				{
				goods.ware[W_Schmiedeeisen] += inhabitants/250;
				goods.ware[W_Eisenerz] -= inhabitants/200;	
				goods.ware[W_Holzkohle] -= inhabitants/400;
				goods.ware[W_Werkzeuge] -= inhabitants/500;
				}
				break;
				}
			case W_Werkzeuge:			//Werkzeuge
				{
				if(goods.ware[W_Schmiedeeisen] - inhabitants/200 > 0 && goods.ware[W_Holzkohle] - inhabitants/500 > 0 && goods.ware[W_Holzbretter] - inhabitants/400 > 0)
				{
					goods.ware[W_Werkzeuge] += inhabitants/25;
					goods.ware[W_Schmiedeeisen] -= inhabitants/200;
					goods.ware[W_Holzkohle] -= inhabitants/500;
					goods.ware[W_Holzbretter] -= inhabitants/400;
				}
				goods.ware[W_Werkzeuge]++;
				break;
				}
			case W_Leder:			//Leder
				{
				if(goods.ware[W_Salz] - inhabitants/1000 > 0 && goods.ware[W_Werkzeuge] - inhabitants/1000 > 0)
				{
					goods.ware[W_Leder] += inhabitants/500;
					goods.ware[W_Salz] -= inhabitants/1000;
					goods.ware[W_Werkzeuge] -= inhabitants/1000;
				}
				break;
				}
			case W_Wolle:			//Wolle
				{
				if(goods.ware[W_Werkzeuge] - inhabitants/1000 > 0)
				{
					goods.ware[W_Wolle] += inhabitants/500;
					goods.ware[W_Werkzeuge] -= inhabitants/1000;
				}
				break;
				}
			case W_Stoffe:		//Stoffe
				{
				if(goods.ware[W_Wolle] - inhabitants/500 > 0 && goods.ware[W_Werkzeuge] - inhabitants/1000 > 0)
				{
					goods.ware[W_Stoffe] += inhabitants/100;
					goods.ware[W_Wolle] -= inhabitants/1000;
					goods.ware[W_Werkzeuge] -= inhabitants/1000;
				}
				break;
				}
			case W_Salz:		//Salz
				{
				if(goods.ware[W_Holzbretter] - inhabitants/800 > 0 &&
				goods.ware[W_Werkzeuge] - inhabitants/1000 > 0)
				{
					goods.ware[W_Salz] += inhabitants/80;
					goods.ware[W_Holzbretter] -= inhabitants/800;
					goods.ware[W_Werkzeuge] -= inhabitants/2000;
				}
				break;
				}
			case W_Fisch:		//Fisch
				{
				if(goods.ware[W_Salz] - inhabitants/400 > 0 &&
				goods.ware[W_Werkzeuge] - inhabitants/1500 > 0 && goods.ware[W_Hanf] - inhabitants/1000 > 0)
				{
					goods.ware[W_Fisch] += inhabitants/200;
					goods.ware[W_Salz] -= inhabitants/400;
					goods.ware[W_Werkzeuge] -= inhabitants/1500;
					goods.ware[W_Hanf] -= inhabitants/1000;
				}
				break;
				}
			case W_Fleisch:		//Fleisch
				{
				if(goods.ware[W_Getreide] - inhabitants/200 > 0 && goods.ware[W_Werkzeuge] - inhabitants/1000 > 0)
				{
					goods.ware[W_Fleisch] += inhabitants/200;
					goods.ware[W_Werkzeuge] -= inhabitants/1000;
					goods.ware[W_Getreide] -= inhabitants/200;
				}
				break;
				}
			case W_Getreide:		//Getreide
				{
				if(goods.ware[W_Werkzeuge] - inhabitants/1000 > 0)
				{
					goods.ware[W_Getreide] += inhabitants/80;
					goods.ware[W_Werkzeuge] -= inhabitants/500;
				}
				goods.ware[W_Getreide]++;
				break;
				}
			case W_Bier:		//Bier
				{
				if(goods.ware[W_Getreide] - inhabitants/500 > 0 &&
				goods.ware[W_Holzbretter] - inhabitants/1000 > 0 &&
				goods.ware[W_Werkzeuge] - inhabitants/1000 > 0)
				{
					goods.ware[W_Bier] += inhabitants/80;
					goods.ware[W_Getreide] -= inhabitants/500;
					goods.ware[W_Holzbretter] -= inhabitants/1000;
					goods.ware[W_Werkzeuge] -= inhabitants/1000;
				}
				break;
				}
			case W_Wein:		//Wein
				{
				if(goods.ware[W_Werkzeuge] - inhabitants/2000 > 0)
				{
				goods.ware[W_Wein] += inhabitants/250;
				goods.ware[W_Werkzeuge] -= inhabitants/2000;
				}
				break;
				}
			case W_Hanf:		//Hanf
				{
				if(goods.ware[W_Werkzeuge] - inhabitants/1000 > 0)
				{
					goods.ware[W_Hanf] += inhabitants/250;
					goods.ware[W_Werkzeuge] -= inhabitants/1000;
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

			switch(mproduction[j])
			{
			case W_Baumstamme:			//Baumstaemme
				{
// 			goods.ware[i] += ((rand() % 12) + inhabitants/100);
				if(goods.ware[W_Werkzeuge] - inhabitants/1000 > 0)
				{
				goods.ware[W_Baumstamme] = goods.ware[W_Baumstamme] + inhabitants/200;
				goods.ware[W_Werkzeuge] = goods.ware[W_Werkzeuge] - inhabitants/1000;
				}
				break;
				}
			case W_Holzbretter:			//Holzbretter
				{
				if(goods.ware[W_Baumstamme] - inhabitants/400 > 0 &&
				goods.ware[W_Werkzeuge] - inhabitants/800 > 0)
				{
				goods.ware[W_Holzbretter] += inhabitants/200;
				goods.ware[W_Baumstamme] -= inhabitants/400;
				goods.ware[W_Werkzeuge] -= inhabitants/800;
				}
				break;
				}
			case W_Holzkohle:			//Holzkohle ... (2 HK aus 3 BS und 1 HB)
				{
				if(goods.ware[W_Baumstamme] - inhabitants/1000 > 0 && goods.ware[W_Holzbretter] - 1 > 0 )
				{
				goods.ware[W_Holzkohle] += inhabitants/800;
				goods.ware[W_Baumstamme] -= inhabitants/1000;
// 				goods.ware[W_Holzbretter] -= inhabitants/1000;
				goods.ware[W_Holzbretter] --;
				}
				break;
				}
			case W_Pech:			//Pech (5 Pech aus 3 BS und 1 HB)
				{
				if(goods.ware[W_Baumstamme] - inhabitants/1000 > 0 &&
 				goods.ware[W_Holzbretter] - 1 > 0)
				{
				goods.ware[W_Holzkohle] += inhabitants/200;
				goods.ware[W_Baumstamme] -= inhabitants/1000;
				goods.ware[W_Holzbretter] --;
				}
				break;
				}
			case W_Steine:			//Steine / Ziegel
				{
				break;
				}
			case W_Eisenerz:
				{		//Eisenerz
				if(goods.ware[W_Werkzeuge] - inhabitants/800 >0)
				{
				goods.ware[W_Eisenerz] += inhabitants/400;
				goods.ware[W_Werkzeuge] -= inhabitants/800;
				}
				break;
				}
			case W_Schmiedeeisen:			//Schmiedeeisen
				{
				if(goods.ware[W_Eisenerz] - inhabitants/400 > 0 && goods.ware[W_Holzkohle] - inhabitants/800 > 0 && goods.ware[W_Werkzeuge] - inhabitants/1000 > 0)
				{
				goods.ware[W_Schmiedeeisen] += inhabitants/500;
				goods.ware[W_Eisenerz] -= inhabitants/400;	
				goods.ware[W_Holzkohle] -= inhabitants/800;
				goods.ware[W_Werkzeuge] -= inhabitants/1000;
				}
				break;
				}
			case W_Werkzeuge:			//Werkzeuge
				{
				if(goods.ware[W_Schmiedeeisen] - inhabitants/400 > 0 && goods.ware[W_Holzkohle] - inhabitants/1000 > 0 && goods.ware[W_Holzbretter] - inhabitants/800 > 0)
				{
					goods.ware[W_Werkzeuge] += inhabitants/40;
					goods.ware[W_Schmiedeeisen] -= inhabitants/400;
					goods.ware[W_Holzkohle] -= inhabitants/1000;
					goods.ware[W_Holzbretter] -= inhabitants/800;
				}
				goods.ware[W_Werkzeuge]++;
				break;
				}
			case W_Leder:			//Leder
				{
				if(goods.ware[W_Salz] - inhabitants/2000 > 0 && goods.ware[W_Werkzeuge] - inhabitants/2000 > 0)
				{
					goods.ware[W_Leder] += inhabitants/1000;
					goods.ware[W_Salz] -= inhabitants/2000;
					goods.ware[W_Werkzeuge] -= inhabitants/2000;
				}
				break;
				}
			case W_Wolle:			//Wolle
				{
				if(goods.ware[W_Werkzeuge] - inhabitants/1000 > 0)
				{
					goods.ware[W_Wolle] += inhabitants/1000;
					goods.ware[W_Werkzeuge] -= inhabitants/2000;
				}
				break;
				}
			case W_Stoffe:		//Stoffe
				{
				if(goods.ware[W_Wolle] - inhabitants/1000 > 0 && goods.ware[W_Werkzeuge] - inhabitants/2000 > 0)
				{
					goods.ware[W_Stoffe] += inhabitants/200;
					goods.ware[W_Wolle] -= inhabitants/1000;
					goods.ware[W_Werkzeuge] -= inhabitants/2000;
				}
				break;
				}
			case W_Salz:		//Salz
				{
				if(goods.ware[W_Holzbretter] - inhabitants/1600 > 0 &&
				goods.ware[W_Werkzeuge] - inhabitants/2000 > 0)
				{
					goods.ware[W_Salz] += inhabitants/100;
					goods.ware[W_Holzbretter] -= inhabitants/1600;
					goods.ware[W_Werkzeuge] -= inhabitants/2000;
				}
				break;
				}
			case W_Fisch:		//Fisch
				{
				if(goods.ware[W_Salz] - inhabitants/400 > 0 &&
				goods.ware[W_Werkzeuge] - inhabitants/2000 > 0)
				{
					goods.ware[W_Fisch] += inhabitants/400;
					goods.ware[W_Salz] -= inhabitants/400;
					goods.ware[W_Werkzeuge] -= inhabitants/2000;
				}
				break;
				}
			case W_Fleisch:		//Fleisch
				{
				if(goods.ware[W_Getreide] - inhabitants/400 > 0 && goods.ware[W_Werkzeuge] - inhabitants/2000 > 0)
				{
					goods.ware[W_Fleisch] += inhabitants/400;
					goods.ware[W_Werkzeuge] -= inhabitants/2000;
					goods.ware[W_Getreide] -= inhabitants/400;
				}
				break;
				}
			case W_Getreide:		//Getreide
				{
				if(goods.ware[W_Werkzeuge] - inhabitants/2000 > 0)
				{
					goods.ware[W_Getreide] += inhabitants/120;
					goods.ware[W_Werkzeuge] -= inhabitants/2000;
				}
				goods.ware[W_Getreide] ++;
				break;
				}
			case W_Bier:		//Bier
				{
				if(goods.ware[W_Getreide] - inhabitants/1000 > 0 &&
				goods.ware[W_Holzbretter] - inhabitants/2000 > 0 &&
				goods.ware[W_Werkzeuge] - inhabitants/2000 > 0)
				{
					goods.ware[W_Bier] += inhabitants/200;
					goods.ware[W_Getreide] -= inhabitants/1000;
					goods.ware[W_Holzbretter] -= inhabitants/2000;
					goods.ware[W_Werkzeuge] -= inhabitants/2000;
				}
				break;
				}
			case W_Wein:		//Wein
				{
				if(goods.ware[W_Werkzeuge] - inhabitants/2000 > 0)
				{
				goods.ware[W_Wein] += inhabitants/500;
				goods.ware[W_Werkzeuge] -= inhabitants/2000;
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
			switch(lproduction[j])
			{
			case W_Baumstamme:			//Baumstaemme
				{
// 			goods.ware[i] += ((rand() % 12) + inhabitants/100);
				if(goods.ware[W_Werkzeuge] - inhabitants/1500 > 0)
				{
				goods.ware[W_Baumstamme] = goods.ware[W_Baumstamme] + inhabitants/250;
				goods.ware[W_Werkzeuge] = goods.ware[W_Werkzeuge] - inhabitants/1500;
				}
				break;
				}
			case W_Holzbretter:			//Holzbretter
				{
				if(goods.ware[W_Baumstamme] - inhabitants/500 > 0 &&
				goods.ware[W_Werkzeuge] - inhabitants/1000 > 0)
				{
				goods.ware[W_Holzbretter] += inhabitants/250;
				goods.ware[W_Baumstamme] -= inhabitants/500;
				goods.ware[W_Werkzeuge] -= inhabitants/1000;
				}
				break;
				}
			case W_Holzkohle:			//Holzkohle ... (2 HK aus 3 BS und 1 HB)
				{
				if(goods.ware[W_Baumstamme] - inhabitants/1500 > 0 && goods.ware[W_Holzbretter] - 1 > 0 )
				{
				goods.ware[W_Holzkohle] += inhabitants/1000;
				goods.ware[W_Baumstamme] -= inhabitants/1500;
// 				goods.ware[W_Holzbretter] -= inhabitants/1000;
				goods.ware[W_Holzbretter] --;
				}
				break;
				}
			case W_Pech:			//Pech (5 Pech aus 3 BS und 1 HB)
				{
				if(goods.ware[W_Baumstamme] - inhabitants/1500 > 0 &&
 				goods.ware[W_Holzbretter] - 1 > 0)
				{
				goods.ware[W_Holzkohle] += inhabitants/250;
				goods.ware[W_Baumstamme] -= inhabitants/1500;
				goods.ware[W_Holzbretter] --;
				}
				break;
				}
			case W_Steine:			//Steine / Ziegel
				{
				break;
				}
			case W_Eisenerz:
				{		//Eisenerz
				if(goods.ware[W_Werkzeuge] - inhabitants/2000 >0)
				{
				goods.ware[W_Eisenerz] += inhabitants/1000;
				goods.ware[W_Werkzeuge] -= inhabitants/2000;
				}
				break;
				}
			case W_Schmiedeeisen:			//Schmiedeeisen
				{
				if(goods.ware[W_Eisenerz] - inhabitants/800 > 0 && goods.ware[W_Holzkohle] - inhabitants/1200 > 0 && goods.ware[W_Werkzeuge] - inhabitants/1500 > 0)
				{
				goods.ware[W_Schmiedeeisen] += inhabitants/1000;
				goods.ware[W_Eisenerz] -= inhabitants/800;	
				goods.ware[W_Holzkohle] -= inhabitants/1200;
				goods.ware[W_Werkzeuge] -= inhabitants/1500;
				}
				break;
				}
			case W_Werkzeuge:			//Werkzeuge
				{
				if(goods.ware[W_Schmiedeeisen] - inhabitants/500 > 0 && goods.ware[W_Holzkohle] - inhabitants/1500 > 0 && goods.ware[W_Holzbretter] - inhabitants/1200 > 0)
				{
					goods.ware[W_Werkzeuge] += inhabitants/100;
					goods.ware[W_Schmiedeeisen] -= inhabitants/500;
					goods.ware[W_Holzkohle] -= inhabitants/1500;
					goods.ware[W_Holzbretter] -= inhabitants/1200;
				}
				break;
				}
			case W_Leder:			//Leder
				{
				if(goods.ware[W_Salz] - inhabitants/2000 > 0 && goods.ware[W_Werkzeuge] - inhabitants/2000 > 0)
				{
					goods.ware[W_Leder] += inhabitants/1000;
					goods.ware[W_Salz] -= inhabitants/2000;
					goods.ware[W_Werkzeuge] -= inhabitants/2000;
				}
				break;
				}
			case W_Wolle:			//Wolle
				{
				if(goods.ware[W_Werkzeuge] - inhabitants/2000 > 0)
				{
					goods.ware[W_Wolle] += inhabitants/1500;
					goods.ware[W_Werkzeuge] -= inhabitants/2000;
				}
				break;
				}
			case W_Stoffe:		//Stoffe
				{
				if(goods.ware[W_Stoffe] - inhabitants/1500 > 0 && goods.ware[W_Werkzeuge] - inhabitants/2000 > 0)
				{
					goods.ware[W_Stoffe] += inhabitants/250;
					goods.ware[W_Wolle] -= inhabitants/1500;
					goods.ware[W_Werkzeuge] -= inhabitants/2000;
				}
				break;
				}
			case W_Salz:		//Salz
				{
				if(goods.ware[W_Holzbretter] - inhabitants/2000 > 0 &&
				goods.ware[W_Werkzeuge] - inhabitants/2000 > 0)
				{
					goods.ware[W_Salz] += inhabitants/400;
					goods.ware[W_Holzbretter] -= inhabitants/2000;
					goods.ware[W_Werkzeuge] -= inhabitants/2000;
				}
				break;
				}
			case W_Fisch:		//Fisch
				{
				if(goods.ware[W_Salz] - inhabitants/500 > 0 &&
				goods.ware[W_Werkzeuge] - inhabitants/2000 > 0)
				{
					goods.ware[W_Fisch] += inhabitants/500;
					goods.ware[W_Salz] -= inhabitants/500;
					goods.ware[W_Werkzeuge] -= inhabitants/2000;
				}
				break;
				}
			case W_Fleisch:		//Fleisch
				{
				if(goods.ware[W_Getreide] - inhabitants/500 > 0 && goods.ware[W_Werkzeuge] - inhabitants/2000 > 0)
				{
					goods.ware[W_Fleisch] += inhabitants/500;
					goods.ware[W_Werkzeuge] -= inhabitants/2000;
					goods.ware[W_Getreide] -= inhabitants/500;
				}
				break;
				}
			case W_Getreide:		//Getreide
				{
				if(goods.ware[W_Werkzeuge] - inhabitants/2000 > 0)
				{
					goods.ware[W_Getreide] += inhabitants/250;
					goods.ware[W_Werkzeuge] -= inhabitants/2000;
				}
				break;
				}
			case W_Bier:		//Bier
				{
				if(goods.ware[W_Getreide] - inhabitants/1500 > 0 &&
				goods.ware[W_Holzbretter] - inhabitants/2000 > 0 &&
				goods.ware[W_Werkzeuge] - inhabitants/2000 > 0)
				{
					goods.ware[W_Bier] += inhabitants/250;
					goods.ware[W_Getreide] -= inhabitants/1500;
					goods.ware[W_Holzbretter] -= inhabitants/2000;
					goods.ware[W_Werkzeuge] -= inhabitants/2000;
				}
				break;
				}
			case W_Wein:		//Wein
				{
				if(goods.ware[W_Werkzeuge] - inhabitants/2000 > 0)
				{
				goods.ware[W_Wein] += inhabitants/1000;
				goods.ware[W_Werkzeuge] -= inhabitants/2000;
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
// 			if(hproduction[j] == i)
// 			{
// 			qWarning() << "Hproduktion vorher: "<< goods.ware[i];
// 			goods.ware[i] += ((rand() % 12) + inhabitants/100);
// 			qWarning() << "Hproduktion nachher" << goods.ware[i];
// 			}
// 			if(mproduction[j] == i)
// 			{
// 			qWarning() << "MProduktion vorher" << goods.ware[i];
// 			goods.ware[i] += ((rand() % 9) + inhabitants/200);
// 			qWarning() << "MProduktion nachher" << goods.ware[i];
// 			}
// 			if(lproduction[j] == i)
// 			{
// 			qWarning() << "NProduktion vorher" << goods.ware[i];
// 			goods.ware[i] += ((rand()% 4) + inhabitants/350);
// 			qWarning() << "NProduktion nachher" << goods.ware[i];
// 			}
		}
// 		}
///////////////////Stadtverbrauch durch Essen ^^


		if(durchlauf%3==0)				//Alle 3 "Tage"
		{
			int lqualitaet=0;
			// stadtware[W_Baumstamme];
			goods.ware[W_Holzbretter] -= inhabitants/1000;
// stadtware[W_Holzkohle] -= inhabitants/1000;		//Als Heizzeug .. evtl. anpassen
// stadtware[W_Pech];
			goods.ware[W_Steine] -= inhabitants/2000;
// stadtware[W_Eisenerz];
			goods.ware[W_Schmiedeeisen] -= inhabitants/2000;
			goods.ware[W_Werkzeuge] -= inhabitants/500;
			goods.ware[W_Leder] -= inhabitants/500;		//Leder
			goods.ware[W_Wolle] -= inhabitants/1000;
			goods.ware[W_Stoffe] -= inhabitants/300;
			goods.ware[W_Salz] -= inhabitants/500;
			goods.ware[W_Fisch] -= inhabitants/100;
					//Fisch hauefig gegessen
			goods.ware[W_Fleisch] -= inhabitants/800;
					//Fleisch fuer wohlhabendere Schichten
			goods.ware[W_Getreide] -= inhabitants/50;
					//Getreide fuer alle
			goods.ware[W_Bier] -= inhabitants/50;
					//Bier auch sehr wichtig - billiges Getraenk fuer jedermann
			goods.ware[W_Wein] -= inhabitants/100;
					//Wein wieder fuer wohlhabendere Schichten
// stadtware[17];
// stadtware[18];
// stadtware[19];

			for(int i = 0; i<const_warenanzahl ;i++)
			{
				if(goods.ware[i]<0)
				{
					goods.ware[i]=0;
					lqualitaet -= (1+rand()%7);
				}
				else
				{
				lqualitaet ++;
				}
			}
			inhabitants +=lqualitaet;
			qWarning() << inhabitants;
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
