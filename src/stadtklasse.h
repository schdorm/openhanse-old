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
#ifndef _stadtklasse_h
#define _stadtklasse_h

// #include <QtCore/QObject>
#include <QtCore/QString>

#include "waren.h"
// #include <math.h>
class stadtklasse /*: public QObject*/
{
// Q_OBJECT
public:

// struct Warenstruct{
// int taler;						//in Stadtkasse, fuer Handel erstmal unerheblich
// // int ware01,ware02,ware03,ware04,ware05,ware06,ware07,ware08,ware09,ware10,ware11,ware12, ware13, ware14, ware15, ware16, ware17, ware18, ware19, ware20;		//Waren der Haendler
// qint16 ware[30];
// };
Warenstruct stadtwaren;
QString stadtname;
int stadtbewohner;
bool hasOffice;		//Kontor/Office built in this town.

int hproduktion[5];
int mproduktion[5];
int nproduktion[5];
// public slots:
//  void produktion(int);

	void init()
	{
		srand(time(NULL));
		for(int i=0; i<const_warenanzahl; i++)
		{
		// int p;
		// if(stadtwaren.ware[i]==0)
			{
			int r=rand()%20;
			int s=rand()%20;
			int p = rand()%10;
			stadtwaren.ware[i] = s + r + p;

		}
		// else
		// stadtwaren.ware[i] = int(sqrt(stadtwaren.ware[i] * stadtwaren.ware[i])) % 100;

		}
	stadtbewohner=2000;				//das kommt mal noch ins XML-Zeugs rein

	static int id;
	stadtwaren.kapazitaet = id + 10000000;	// i + 10 mio
	id++;
	}

void reset()
{
for(int i = 0; i<5; i++)
{
hproduktion[i]=-1;
mproduktion[i]=-1;
nproduktion[i]=-1;
}
stadtname=QString();
stadtbewohner = 0;
stadtwaren.kapazitaet = 0;
}

};


#endif
