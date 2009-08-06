/***************************************************************************
 *   Copyright (C) 2009 by Christian Doerffel   *
 *   christian.doerffel@googlemail.com   *
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

#include <QtDebug>

void gesamtbild::produktion(int durchlauf)
{
	foreach(stadt,stadtliste)
	{
		qWarning() << "Stadtproduktion:" << stadt.stadtname;
// 		for(int i=0;i<20;i++)
// 		{
		for(int j=0;j<5;j++)		//kann man mal noch schoen mit switch und case machen
		{
			switch(stadt.hproduktion[j])
			{
			case W_Baumstamme:			//Baumstaemme
				{
// 			stadt.stadtwaren.ware[i] += ((rand() % 12) + stadt.stadtbewohner/100);
				if(stadt.stadtwaren.ware[W_Werkzeuge] - stadt.stadtbewohner/500 > 0)
				{
				stadt.stadtwaren.ware[W_Baumstamme] = stadt.stadtwaren.ware[W_Baumstamme] + stadt.stadtbewohner/100;
				stadt.stadtwaren.ware[W_Werkzeuge] = stadt.stadtwaren.ware[W_Werkzeuge] - stadt.stadtbewohner/500;
				}
				stadt.stadtwaren.ware[W_Baumstamme]++;		//Grundproduktion um Festfahren und komplette Stockung der Wirtschaft zu verhindern
				break;
				}
			case W_Holzbretter:			//Holzbretter
				{
				if(stadt.stadtwaren.ware[W_Baumstamme] - stadt.stadtbewohner/200 > 0 &&
				stadt.stadtwaren.ware[W_Werkzeuge] - stadt.stadtbewohner/400 > 0)
				{
				stadt.stadtwaren.ware[W_Holzbretter] += stadt.stadtbewohner/100;
				stadt.stadtwaren.ware[W_Baumstamme] -= stadt.stadtbewohner/200;
				stadt.stadtwaren.ware[W_Werkzeuge] -= stadt.stadtbewohner/400;
				}
				break;
				}
			case W_Holzkohle:			//Holzkohle ... (2 HK aus 3 BS und 1 HB)
				{
				if(stadt.stadtwaren.ware[W_Baumstamme] - stadt.stadtbewohner/500 > 0 && stadt.stadtwaren.ware[W_Holzbretter] - 1 > 0 )
				{
				stadt.stadtwaren.ware[W_Holzkohle] += stadt.stadtbewohner/400;
				stadt.stadtwaren.ware[W_Baumstamme] -= stadt.stadtbewohner/500;
// 				stadt.stadtwaren.ware[W_Holzbretter] -= stadt.stadtbewohner/1000;
				stadt.stadtwaren.ware[W_Holzbretter] --;
				}
				break;
				}
			case W_Pech:				//Pech (5 Pech aus 3 BS und 1 HB)
				{
				if(stadt.stadtwaren.ware[W_Baumstamme] - stadt.stadtbewohner/500 > 0 &&
 				stadt.stadtwaren.ware[W_Holzbretter] - 1 > 0)
				{
				stadt.stadtwaren.ware[W_Pech] += stadt.stadtbewohner/100;
				stadt.stadtwaren.ware[W_Baumstamme] -= stadt.stadtbewohner/500;
				stadt.stadtwaren.ware[W_Holzbretter] --;
				}
				break;
				}
			case W_Steine:				//Steine / Ziegel
				{
				if(stadt.stadtwaren.ware[W_Holzbretter] - stadt.stadtbewohner/500 > 0 && stadt.stadtwaren.ware[W_Werkzeuge] - stadt.stadtbewohner/1000 > 0)
				stadt.stadtwaren.ware[W_Steine] += stadt.stadtbewohner/400;
				stadt.stadtwaren.ware[W_Holzbretter] -= stadt.stadtbewohner/1000;
				stadt.stadtwaren.ware[W_Werkzeuge] -= stadt.stadtbewohner/500;
				break;
				}
			case W_Eisenerz:			//Eisenerz
				{
				if(stadt.stadtwaren.ware[W_Werkzeuge] - stadt.stadtbewohner/400 >0)
				{
				stadt.stadtwaren.ware[W_Eisenerz] += stadt.stadtbewohner/200;
				stadt.stadtwaren.ware[W_Werkzeuge] -= stadt.stadtbewohner/400;
				}
				stadt.stadtwaren.ware[W_Eisenerz]++;
				break;
				}
			case W_Schmiedeeisen:			//Schmiedeeisen
				{
				if(stadt.stadtwaren.ware[W_Eisenerz] - stadt.stadtbewohner/200 > 0 && stadt.stadtwaren.ware[W_Holzkohle] - stadt.stadtbewohner/400 > 0 && stadt.stadtwaren.ware[W_Werkzeuge] - stadt.stadtbewohner/500 > 0)
				{
				stadt.stadtwaren.ware[W_Schmiedeeisen] += stadt.stadtbewohner/250;
				stadt.stadtwaren.ware[W_Eisenerz] -= stadt.stadtbewohner/200;	
				stadt.stadtwaren.ware[W_Holzkohle] -= stadt.stadtbewohner/400;
				stadt.stadtwaren.ware[W_Werkzeuge] -= stadt.stadtbewohner/500;
				}
				break;
				}
			case W_Werkzeuge:			//Werkzeuge
				{
				if(stadt.stadtwaren.ware[W_Schmiedeeisen] - stadt.stadtbewohner/200 > 0 && stadt.stadtwaren.ware[W_Holzkohle] - stadt.stadtbewohner/500 > 0 && stadt.stadtwaren.ware[W_Holzbretter] - stadt.stadtbewohner/400 > 0)
				{
					stadt.stadtwaren.ware[W_Werkzeuge] += stadt.stadtbewohner/25;
					stadt.stadtwaren.ware[W_Schmiedeeisen] -= stadt.stadtbewohner/200;
					stadt.stadtwaren.ware[W_Holzkohle] -= stadt.stadtbewohner/500;
					stadt.stadtwaren.ware[W_Holzbretter] -= stadt.stadtbewohner/400;
				}
				stadt.stadtwaren.ware[W_Werkzeuge]++;
				break;
				}
			case W_Leder:			//Leder
				{
				if(stadt.stadtwaren.ware[W_Salz] - stadt.stadtbewohner/1000 > 0 && stadt.stadtwaren.ware[W_Werkzeuge] - stadt.stadtbewohner/1000 > 0)
				{
					stadt.stadtwaren.ware[W_Leder] += stadt.stadtbewohner/500;
					stadt.stadtwaren.ware[W_Salz] -= stadt.stadtbewohner/1000;
					stadt.stadtwaren.ware[W_Werkzeuge] -= stadt.stadtbewohner/1000;
				}
				break;
				}
			case W_Wolle:			//Wolle
				{
				if(stadt.stadtwaren.ware[W_Werkzeuge] - stadt.stadtbewohner/1000 > 0)
				{
					stadt.stadtwaren.ware[W_Wolle] += stadt.stadtbewohner/500;
					stadt.stadtwaren.ware[W_Werkzeuge] -= stadt.stadtbewohner/1000;
				}
				break;
				}
			case W_Stoffe:		//Stoffe
				{
				if(stadt.stadtwaren.ware[W_Wolle] - stadt.stadtbewohner/500 > 0 && stadt.stadtwaren.ware[W_Werkzeuge] - stadt.stadtbewohner/1000 > 0)
				{
					stadt.stadtwaren.ware[W_Stoffe] += stadt.stadtbewohner/100;
					stadt.stadtwaren.ware[W_Wolle] -= stadt.stadtbewohner/1000;
					stadt.stadtwaren.ware[W_Werkzeuge] -= stadt.stadtbewohner/1000;
				}
				break;
				}
			case W_Salz:		//Salz
				{
				if(stadt.stadtwaren.ware[W_Holzbretter] - stadt.stadtbewohner/800 > 0 &&
				stadt.stadtwaren.ware[W_Werkzeuge] - stadt.stadtbewohner/1000 > 0)
				{
					stadt.stadtwaren.ware[W_Salz] += stadt.stadtbewohner/80;
					stadt.stadtwaren.ware[W_Holzbretter] -= stadt.stadtbewohner/800;
					stadt.stadtwaren.ware[W_Werkzeuge] -= stadt.stadtbewohner/2000;
				}
				break;
				}
			case W_Fisch:		//Fisch
				{
				if(stadt.stadtwaren.ware[W_Salz] - stadt.stadtbewohner/400 > 0 &&
				stadt.stadtwaren.ware[W_Werkzeuge] - stadt.stadtbewohner/1500 > 0 && stadt.stadtwaren.ware[W_Hanf] - stadt.stadtbewohner/1000 > 0)
				{
					stadt.stadtwaren.ware[W_Fisch] += stadt.stadtbewohner/200;
					stadt.stadtwaren.ware[W_Salz] -= stadt.stadtbewohner/400;
					stadt.stadtwaren.ware[W_Werkzeuge] -= stadt.stadtbewohner/1500;
					stadt.stadtwaren.ware[W_Hanf] -= stadt.stadtbewohner/1000;
				}
				break;
				}
			case W_Fleisch:		//Fleisch
				{
				if(stadt.stadtwaren.ware[W_Getreide] - stadt.stadtbewohner/200 > 0 && stadt.stadtwaren.ware[W_Werkzeuge] - stadt.stadtbewohner/1000 > 0)
				{
					stadt.stadtwaren.ware[W_Fleisch] += stadt.stadtbewohner/200;
					stadt.stadtwaren.ware[W_Werkzeuge] -= stadt.stadtbewohner/1000;
					stadt.stadtwaren.ware[W_Getreide] -= stadt.stadtbewohner/200;
				}
				break;
				}
			case W_Getreide:		//Getreide
				{
				if(stadt.stadtwaren.ware[W_Werkzeuge] - stadt.stadtbewohner/1000 > 0)
				{
					stadt.stadtwaren.ware[W_Getreide] += stadt.stadtbewohner/80;
					stadt.stadtwaren.ware[W_Werkzeuge] -= stadt.stadtbewohner/500;
				}
				stadt.stadtwaren.ware[W_Getreide]++;
				break;
				}
			case W_Bier:		//Bier
				{
				if(stadt.stadtwaren.ware[W_Getreide] - stadt.stadtbewohner/500 > 0 &&
				stadt.stadtwaren.ware[W_Holzbretter] - stadt.stadtbewohner/1000 > 0 &&
				stadt.stadtwaren.ware[W_Werkzeuge] - stadt.stadtbewohner/1000 > 0)
				{
					stadt.stadtwaren.ware[W_Bier] += stadt.stadtbewohner/80;
					stadt.stadtwaren.ware[W_Getreide] -= stadt.stadtbewohner/500;
					stadt.stadtwaren.ware[W_Holzbretter] -= stadt.stadtbewohner/1000;
					stadt.stadtwaren.ware[W_Werkzeuge] -= stadt.stadtbewohner/1000;
				}
				break;
				}
			case W_Wein:		//Wein
				{
				if(stadt.stadtwaren.ware[W_Werkzeuge] - stadt.stadtbewohner/2000 > 0)
				{
				stadt.stadtwaren.ware[W_Wein] += stadt.stadtbewohner/250;
				stadt.stadtwaren.ware[W_Werkzeuge] -= stadt.stadtbewohner/2000;
				}
				break;
				}
			case W_Hanf:		//Hanf
				{
				if(stadt.stadtwaren.ware[W_Werkzeuge] - stadt.stadtbewohner/1000 > 0)
				{
					stadt.stadtwaren.ware[W_Hanf] += stadt.stadtbewohner/250;
					stadt.stadtwaren.ware[W_Werkzeuge] -= stadt.stadtbewohner/1000;
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

			switch(stadt.mproduktion[j])
			{
			case W_Baumstamme:			//Baumstaemme
				{
// 			stadt.stadtwaren.ware[i] += ((rand() % 12) + stadt.stadtbewohner/100);
				if(stadt.stadtwaren.ware[W_Werkzeuge] - stadt.stadtbewohner/1000 > 0)
				{
				stadt.stadtwaren.ware[W_Baumstamme] = stadt.stadtwaren.ware[W_Baumstamme] + stadt.stadtbewohner/200;
				stadt.stadtwaren.ware[W_Werkzeuge] = stadt.stadtwaren.ware[W_Werkzeuge] - stadt.stadtbewohner/1000;
				}
				break;
				}
			case W_Holzbretter:			//Holzbretter
				{
				if(stadt.stadtwaren.ware[W_Baumstamme] - stadt.stadtbewohner/400 > 0 &&
				stadt.stadtwaren.ware[W_Werkzeuge] - stadt.stadtbewohner/800 > 0)
				{
				stadt.stadtwaren.ware[W_Holzbretter] += stadt.stadtbewohner/200;
				stadt.stadtwaren.ware[W_Baumstamme] -= stadt.stadtbewohner/400;
				stadt.stadtwaren.ware[W_Werkzeuge] -= stadt.stadtbewohner/800;
				}
				break;
				}
			case W_Holzkohle:			//Holzkohle ... (2 HK aus 3 BS und 1 HB)
				{
				if(stadt.stadtwaren.ware[W_Baumstamme] - stadt.stadtbewohner/1000 > 0 && stadt.stadtwaren.ware[W_Holzbretter] - 1 > 0 )
				{
				stadt.stadtwaren.ware[W_Holzkohle] += stadt.stadtbewohner/800;
				stadt.stadtwaren.ware[W_Baumstamme] -= stadt.stadtbewohner/1000;
// 				stadt.stadtwaren.ware[W_Holzbretter] -= stadt.stadtbewohner/1000;
				stadt.stadtwaren.ware[W_Holzbretter] --;
				}
				break;
				}
			case W_Pech:			//Pech (5 Pech aus 3 BS und 1 HB)
				{
				if(stadt.stadtwaren.ware[W_Baumstamme] - stadt.stadtbewohner/1000 > 0 &&
 				stadt.stadtwaren.ware[W_Holzbretter] - 1 > 0)
				{
				stadt.stadtwaren.ware[W_Holzkohle] += stadt.stadtbewohner/200;
				stadt.stadtwaren.ware[W_Baumstamme] -= stadt.stadtbewohner/1000;
				stadt.stadtwaren.ware[W_Holzbretter] --;
				}
				break;
				}
			case W_Steine:			//Steine / Ziegel
				{
				break;
				}
			case W_Eisenerz:
				{		//Eisenerz
				if(stadt.stadtwaren.ware[W_Werkzeuge] - stadt.stadtbewohner/800 >0)
				{
				stadt.stadtwaren.ware[W_Eisenerz] += stadt.stadtbewohner/400;
				stadt.stadtwaren.ware[W_Werkzeuge] -= stadt.stadtbewohner/800;
				}
				break;
				}
			case W_Schmiedeeisen:			//Schmiedeeisen
				{
				if(stadt.stadtwaren.ware[W_Eisenerz] - stadt.stadtbewohner/400 > 0 && stadt.stadtwaren.ware[W_Holzkohle] - stadt.stadtbewohner/800 > 0 && stadt.stadtwaren.ware[W_Werkzeuge] - stadt.stadtbewohner/1000 > 0)
				{
				stadt.stadtwaren.ware[W_Schmiedeeisen] += stadt.stadtbewohner/500;
				stadt.stadtwaren.ware[W_Eisenerz] -= stadt.stadtbewohner/400;	
				stadt.stadtwaren.ware[W_Holzkohle] -= stadt.stadtbewohner/800;
				stadt.stadtwaren.ware[W_Werkzeuge] -= stadt.stadtbewohner/1000;
				}
				break;
				}
			case W_Werkzeuge:			//Werkzeuge
				{
				if(stadt.stadtwaren.ware[W_Schmiedeeisen] - stadt.stadtbewohner/400 > 0 && stadt.stadtwaren.ware[W_Holzkohle] - stadt.stadtbewohner/1000 > 0 && stadt.stadtwaren.ware[W_Holzbretter] - stadt.stadtbewohner/800 > 0)
				{
					stadt.stadtwaren.ware[W_Werkzeuge] += stadt.stadtbewohner/40;
					stadt.stadtwaren.ware[W_Schmiedeeisen] -= stadt.stadtbewohner/400;
					stadt.stadtwaren.ware[W_Holzkohle] -= stadt.stadtbewohner/1000;
					stadt.stadtwaren.ware[W_Holzbretter] -= stadt.stadtbewohner/800;
				}
				stadt.stadtwaren.ware[W_Werkzeuge]++;
				break;
				}
			case W_Leder:			//Leder
				{
				if(stadt.stadtwaren.ware[W_Salz] - stadt.stadtbewohner/2000 > 0 && stadt.stadtwaren.ware[W_Werkzeuge] - stadt.stadtbewohner/2000 > 0)
				{
					stadt.stadtwaren.ware[W_Leder] += stadt.stadtbewohner/1000;
					stadt.stadtwaren.ware[W_Salz] -= stadt.stadtbewohner/2000;
					stadt.stadtwaren.ware[W_Werkzeuge] -= stadt.stadtbewohner/2000;
				}
				break;
				}
			case W_Wolle:			//Wolle
				{
				if(stadt.stadtwaren.ware[W_Werkzeuge] - stadt.stadtbewohner/1000 > 0)
				{
					stadt.stadtwaren.ware[W_Wolle] += stadt.stadtbewohner/1000;
					stadt.stadtwaren.ware[W_Werkzeuge] -= stadt.stadtbewohner/2000;
				}
				break;
				}
			case W_Stoffe:		//Stoffe
				{
				if(stadt.stadtwaren.ware[W_Wolle] - stadt.stadtbewohner/1000 > 0 && stadt.stadtwaren.ware[W_Werkzeuge] - stadt.stadtbewohner/2000 > 0)
				{
					stadt.stadtwaren.ware[W_Stoffe] += stadt.stadtbewohner/200;
					stadt.stadtwaren.ware[W_Wolle] -= stadt.stadtbewohner/1000;
					stadt.stadtwaren.ware[W_Werkzeuge] -= stadt.stadtbewohner/2000;
				}
				break;
				}
			case W_Salz:		//Salz
				{
				if(stadt.stadtwaren.ware[W_Holzbretter] - stadt.stadtbewohner/1600 > 0 &&
				stadt.stadtwaren.ware[W_Werkzeuge] - stadt.stadtbewohner/2000 > 0)
				{
					stadt.stadtwaren.ware[W_Salz] += stadt.stadtbewohner/100;
					stadt.stadtwaren.ware[W_Holzbretter] -= stadt.stadtbewohner/1600;
					stadt.stadtwaren.ware[W_Werkzeuge] -= stadt.stadtbewohner/2000;
				}
				break;
				}
			case W_Fisch:		//Fisch
				{
				if(stadt.stadtwaren.ware[W_Salz] - stadt.stadtbewohner/400 > 0 &&
				stadt.stadtwaren.ware[W_Werkzeuge] - stadt.stadtbewohner/2000 > 0)
				{
					stadt.stadtwaren.ware[W_Fisch] += stadt.stadtbewohner/400;
					stadt.stadtwaren.ware[W_Salz] -= stadt.stadtbewohner/400;
					stadt.stadtwaren.ware[W_Werkzeuge] -= stadt.stadtbewohner/2000;
				}
				break;
				}
			case W_Fleisch:		//Fleisch
				{
				if(stadt.stadtwaren.ware[W_Getreide] - stadt.stadtbewohner/400 > 0 && stadt.stadtwaren.ware[W_Werkzeuge] - stadt.stadtbewohner/2000 > 0)
				{
					stadt.stadtwaren.ware[W_Fleisch] += stadt.stadtbewohner/400;
					stadt.stadtwaren.ware[W_Werkzeuge] -= stadt.stadtbewohner/2000;
					stadt.stadtwaren.ware[W_Getreide] -= stadt.stadtbewohner/400;
				}
				break;
				}
			case W_Getreide:		//Getreide
				{
				if(stadt.stadtwaren.ware[W_Werkzeuge] - stadt.stadtbewohner/2000 > 0)
				{
					stadt.stadtwaren.ware[W_Getreide] += stadt.stadtbewohner/120;
					stadt.stadtwaren.ware[W_Werkzeuge] -= stadt.stadtbewohner/2000;
				}
				stadt.stadtwaren.ware[W_Getreide] ++;
				break;
				}
			case W_Bier:		//Bier
				{
				if(stadt.stadtwaren.ware[W_Getreide] - stadt.stadtbewohner/1000 > 0 &&
				stadt.stadtwaren.ware[W_Holzbretter] - stadt.stadtbewohner/2000 > 0 &&
				stadt.stadtwaren.ware[W_Werkzeuge] - stadt.stadtbewohner/2000 > 0)
				{
					stadt.stadtwaren.ware[W_Bier] += stadt.stadtbewohner/200;
					stadt.stadtwaren.ware[W_Getreide] -= stadt.stadtbewohner/1000;
					stadt.stadtwaren.ware[W_Holzbretter] -= stadt.stadtbewohner/2000;
					stadt.stadtwaren.ware[W_Werkzeuge] -= stadt.stadtbewohner/2000;
				}
				break;
				}
			case W_Wein:		//Wein
				{
				if(stadt.stadtwaren.ware[W_Werkzeuge] - stadt.stadtbewohner/2000 > 0)
				{
				stadt.stadtwaren.ware[W_Wein] += stadt.stadtbewohner/500;
				stadt.stadtwaren.ware[W_Werkzeuge] -= stadt.stadtbewohner/2000;
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
			switch(stadt.nproduktion[j])
			{
			case W_Baumstamme:			//Baumstaemme
				{
// 			stadt.stadtwaren.ware[i] += ((rand() % 12) + stadt.stadtbewohner/100);
				if(stadt.stadtwaren.ware[W_Werkzeuge] - stadt.stadtbewohner/1500 > 0)
				{
				stadt.stadtwaren.ware[W_Baumstamme] = stadt.stadtwaren.ware[W_Baumstamme] + stadt.stadtbewohner/250;
				stadt.stadtwaren.ware[W_Werkzeuge] = stadt.stadtwaren.ware[W_Werkzeuge] - stadt.stadtbewohner/1500;
				}
				break;
				}
			case W_Holzbretter:			//Holzbretter
				{
				if(stadt.stadtwaren.ware[W_Baumstamme] - stadt.stadtbewohner/500 > 0 &&
				stadt.stadtwaren.ware[W_Werkzeuge] - stadt.stadtbewohner/1000 > 0)
				{
				stadt.stadtwaren.ware[W_Holzbretter] += stadt.stadtbewohner/250;
				stadt.stadtwaren.ware[W_Baumstamme] -= stadt.stadtbewohner/500;
				stadt.stadtwaren.ware[W_Werkzeuge] -= stadt.stadtbewohner/1000;
				}
				break;
				}
			case W_Holzkohle:			//Holzkohle ... (2 HK aus 3 BS und 1 HB)
				{
				if(stadt.stadtwaren.ware[W_Baumstamme] - stadt.stadtbewohner/1500 > 0 && stadt.stadtwaren.ware[W_Holzbretter] - 1 > 0 )
				{
				stadt.stadtwaren.ware[W_Holzkohle] += stadt.stadtbewohner/1000;
				stadt.stadtwaren.ware[W_Baumstamme] -= stadt.stadtbewohner/1500;
// 				stadt.stadtwaren.ware[W_Holzbretter] -= stadt.stadtbewohner/1000;
				stadt.stadtwaren.ware[W_Holzbretter] --;
				}
				break;
				}
			case W_Pech:			//Pech (5 Pech aus 3 BS und 1 HB)
				{
				if(stadt.stadtwaren.ware[W_Baumstamme] - stadt.stadtbewohner/1500 > 0 &&
 				stadt.stadtwaren.ware[W_Holzbretter] - 1 > 0)
				{
				stadt.stadtwaren.ware[W_Holzkohle] += stadt.stadtbewohner/250;
				stadt.stadtwaren.ware[W_Baumstamme] -= stadt.stadtbewohner/1500;
				stadt.stadtwaren.ware[W_Holzbretter] --;
				}
				break;
				}
			case W_Steine:			//Steine / Ziegel
				{
				break;
				}
			case W_Eisenerz:
				{		//Eisenerz
				if(stadt.stadtwaren.ware[W_Werkzeuge] - stadt.stadtbewohner/2000 >0)
				{
				stadt.stadtwaren.ware[W_Eisenerz] += stadt.stadtbewohner/1000;
				stadt.stadtwaren.ware[W_Werkzeuge] -= stadt.stadtbewohner/2000;
				}
				break;
				}
			case W_Schmiedeeisen:			//Schmiedeeisen
				{
				if(stadt.stadtwaren.ware[W_Eisenerz] - stadt.stadtbewohner/800 > 0 && stadt.stadtwaren.ware[W_Holzkohle] - stadt.stadtbewohner/1200 > 0 && stadt.stadtwaren.ware[W_Werkzeuge] - stadt.stadtbewohner/1500 > 0)
				{
				stadt.stadtwaren.ware[W_Schmiedeeisen] += stadt.stadtbewohner/1000;
				stadt.stadtwaren.ware[W_Eisenerz] -= stadt.stadtbewohner/800;	
				stadt.stadtwaren.ware[W_Holzkohle] -= stadt.stadtbewohner/1200;
				stadt.stadtwaren.ware[W_Werkzeuge] -= stadt.stadtbewohner/1500;
				}
				break;
				}
			case W_Werkzeuge:			//Werkzeuge
				{
				if(stadt.stadtwaren.ware[W_Schmiedeeisen] - stadt.stadtbewohner/500 > 0 && stadt.stadtwaren.ware[W_Holzkohle] - stadt.stadtbewohner/1500 > 0 && stadt.stadtwaren.ware[W_Holzbretter] - stadt.stadtbewohner/1200 > 0)
				{
					stadt.stadtwaren.ware[W_Werkzeuge] += stadt.stadtbewohner/100;
					stadt.stadtwaren.ware[W_Schmiedeeisen] -= stadt.stadtbewohner/500;
					stadt.stadtwaren.ware[W_Holzkohle] -= stadt.stadtbewohner/1500;
					stadt.stadtwaren.ware[W_Holzbretter] -= stadt.stadtbewohner/1200;
				}
				break;
				}
			case W_Leder:			//Leder
				{
				if(stadt.stadtwaren.ware[W_Salz] - stadt.stadtbewohner/2000 > 0 && stadt.stadtwaren.ware[W_Werkzeuge] - stadt.stadtbewohner/2000 > 0)
				{
					stadt.stadtwaren.ware[W_Leder] += stadt.stadtbewohner/1000;
					stadt.stadtwaren.ware[W_Salz] -= stadt.stadtbewohner/2000;
					stadt.stadtwaren.ware[W_Werkzeuge] -= stadt.stadtbewohner/2000;
				}
				break;
				}
			case W_Wolle:			//Wolle
				{
				if(stadt.stadtwaren.ware[W_Werkzeuge] - stadt.stadtbewohner/2000 > 0)
				{
					stadt.stadtwaren.ware[W_Wolle] += stadt.stadtbewohner/1500;
					stadt.stadtwaren.ware[W_Werkzeuge] -= stadt.stadtbewohner/2000;
				}
				break;
				}
			case W_Stoffe:		//Stoffe
				{
				if(stadt.stadtwaren.ware[W_Stoffe] - stadt.stadtbewohner/1500 > 0 && stadt.stadtwaren.ware[W_Werkzeuge] - stadt.stadtbewohner/2000 > 0)
				{
					stadt.stadtwaren.ware[W_Stoffe] += stadt.stadtbewohner/250;
					stadt.stadtwaren.ware[W_Wolle] -= stadt.stadtbewohner/1500;
					stadt.stadtwaren.ware[W_Werkzeuge] -= stadt.stadtbewohner/2000;
				}
				break;
				}
			case W_Salz:		//Salz
				{
				if(stadt.stadtwaren.ware[W_Holzbretter] - stadt.stadtbewohner/2000 > 0 &&
				stadt.stadtwaren.ware[W_Werkzeuge] - stadt.stadtbewohner/2000 > 0)
				{
					stadt.stadtwaren.ware[W_Salz] += stadt.stadtbewohner/400;
					stadt.stadtwaren.ware[W_Holzbretter] -= stadt.stadtbewohner/2000;
					stadt.stadtwaren.ware[W_Werkzeuge] -= stadt.stadtbewohner/2000;
				}
				break;
				}
			case W_Fisch:		//Fisch
				{
				if(stadt.stadtwaren.ware[W_Salz] - stadt.stadtbewohner/500 > 0 &&
				stadt.stadtwaren.ware[W_Werkzeuge] - stadt.stadtbewohner/2000 > 0)
				{
					stadt.stadtwaren.ware[W_Fisch] += stadt.stadtbewohner/500;
					stadt.stadtwaren.ware[W_Salz] -= stadt.stadtbewohner/500;
					stadt.stadtwaren.ware[W_Werkzeuge] -= stadt.stadtbewohner/2000;
				}
				break;
				}
			case W_Fleisch:		//Fleisch
				{
				if(stadt.stadtwaren.ware[W_Getreide] - stadt.stadtbewohner/500 > 0 && stadt.stadtwaren.ware[W_Werkzeuge] - stadt.stadtbewohner/2000 > 0)
				{
					stadt.stadtwaren.ware[W_Fleisch] += stadt.stadtbewohner/500;
					stadt.stadtwaren.ware[W_Werkzeuge] -= stadt.stadtbewohner/2000;
					stadt.stadtwaren.ware[W_Getreide] -= stadt.stadtbewohner/500;
				}
				break;
				}
			case W_Getreide:		//Getreide
				{
				if(stadt.stadtwaren.ware[W_Werkzeuge] - stadt.stadtbewohner/2000 > 0)
				{
					stadt.stadtwaren.ware[W_Getreide] += stadt.stadtbewohner/250;
					stadt.stadtwaren.ware[W_Werkzeuge] -= stadt.stadtbewohner/2000;
				}
				break;
				}
			case W_Bier:		//Bier
				{
				if(stadt.stadtwaren.ware[W_Getreide] - stadt.stadtbewohner/1500 > 0 &&
				stadt.stadtwaren.ware[W_Holzbretter] - stadt.stadtbewohner/2000 > 0 &&
				stadt.stadtwaren.ware[W_Werkzeuge] - stadt.stadtbewohner/2000 > 0)
				{
					stadt.stadtwaren.ware[W_Bier] += stadt.stadtbewohner/250;
					stadt.stadtwaren.ware[W_Getreide] -= stadt.stadtbewohner/1500;
					stadt.stadtwaren.ware[W_Holzbretter] -= stadt.stadtbewohner/2000;
					stadt.stadtwaren.ware[W_Werkzeuge] -= stadt.stadtbewohner/2000;
				}
				break;
				}
			case W_Wein:		//Wein
				{
				if(stadt.stadtwaren.ware[W_Werkzeuge] - stadt.stadtbewohner/2000 > 0)
				{
				stadt.stadtwaren.ware[W_Wein] += stadt.stadtbewohner/1000;
				stadt.stadtwaren.ware[W_Werkzeuge] -= stadt.stadtbewohner/2000;
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
// 			if(stadt.hproduktion[j] == i)
// 			{
// 			qWarning() << "Hproduktion vorher: "<< stadt.stadtwaren.ware[i];
// 			stadt.stadtwaren.ware[i] += ((rand() % 12) + stadt.stadtbewohner/100);
// 			qWarning() << "Hproduktion nachher" << stadt.stadtwaren.ware[i];
// 			}
// 			if(stadt.mproduktion[j] == i)
// 			{
// 			qWarning() << "MProduktion vorher" << stadt.stadtwaren.ware[i];
// 			stadt.stadtwaren.ware[i] += ((rand() % 9) + stadt.stadtbewohner/200);
// 			qWarning() << "MProduktion nachher" << stadt.stadtwaren.ware[i];
// 			}
// 			if(stadt.nproduktion[j] == i)
// 			{
// 			qWarning() << "NProduktion vorher" << stadt.stadtwaren.ware[i];
// 			stadt.stadtwaren.ware[i] += ((rand()% 4) + stadt.stadtbewohner/350);
// 			qWarning() << "NProduktion nachher" << stadt.stadtwaren.ware[i];
// 			}
		}
// 		}
///////////////////Stadtverbrauch durch Essen ^^


		if(durchlauf%3==0)				//Alle 3 "Tage"
		{
			int lqualitaet=0;
			// stadt.stadtware[W_Baumstamme];
			stadt.stadtwaren.ware[W_Holzbretter] -= stadt.stadtbewohner/1000;
// stadt.stadtware[W_Holzkohle] -= stadt.stadtbewohner/1000;		//Als Heizzeug .. evtl. anpassen
// stadt.stadtware[W_Pech];
			stadt.stadtwaren.ware[W_Steine] -= stadt.stadtbewohner/2000;
// stadt.stadtware[W_Eisenerz];
			stadt.stadtwaren.ware[W_Schmiedeeisen] -= stadt.stadtbewohner/2000;
			stadt.stadtwaren.ware[W_Werkzeuge] -= stadt.stadtbewohner/500;
			stadt.stadtwaren.ware[W_Leder] -= stadt.stadtbewohner/500;		//Leder
			stadt.stadtwaren.ware[W_Wolle] -= stadt.stadtbewohner/1000;
			stadt.stadtwaren.ware[W_Stoffe] -= stadt.stadtbewohner/300;
			stadt.stadtwaren.ware[W_Salz] -= stadt.stadtbewohner/500;
			stadt.stadtwaren.ware[W_Fisch] -= stadt.stadtbewohner/100;
					//Fisch hauefig gegessen
			stadt.stadtwaren.ware[W_Fleisch] -= stadt.stadtbewohner/800;
					//Fleisch fuer wohlhabendere Schichten
			stadt.stadtwaren.ware[W_Getreide] -= stadt.stadtbewohner/50;
					//Getreide fuer alle
			stadt.stadtwaren.ware[W_Bier] -= stadt.stadtbewohner/50;
					//Bier auch sehr wichtig - billiges Getraenk fuer jedermann
			stadt.stadtwaren.ware[W_Wein] -= stadt.stadtbewohner/100;
					//Wein wieder fuer wohlhabendere Schichten
// stadt.stadtware[17];
// stadt.stadtware[18];
// stadt.stadtware[19];

			for(int i = 0; i<const_warenanzahl ;i++)
			{
				if(stadt.stadtwaren.ware[i]<0)
				{
					stadt.stadtwaren.ware[i]=0;
					lqualitaet -= (1+rand()%7);
				}
				else
				{
				lqualitaet ++;
				}
			}
			stadt.stadtbewohner +=lqualitaet;
			qWarning() << stadt.stadtbewohner;
		}

		for (QList<stadtklasse>::iterator it = stadtliste.begin(); it != stadtliste.end(); ++it)
		{
// 			qWarning() << it->stadtname << hf->mapprops.stadtname ;
			if(it->stadtname == stadt.stadtname)
			{
				*it = stadt;
				break;
			}
		}

	}

// qWarning() << "Ende Produktion";

}
// }
// }
