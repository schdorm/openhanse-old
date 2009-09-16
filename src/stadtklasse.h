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
#ifndef _stadtklasse_h
#define _stadtklasse_h

#include <QtCore/QList>
// #include <stdlib.h>

#include "waren.h"
#include "definitions.h"
// #include <math.h>
class CityClass /*: public QObject*/
{
// Q_OBJECT
public:

// struct Warenstruct{
// int taler;						//in Stadtkasse, fuer Handel erstmal unerheblich
// // int ware01,ware02,ware03,ware04,ware05,ware06,ware07,ware08,ware09,ware10,ware11,ware12, ware13, ware14, ware15, ware16, ware17, ware18, ware19, ware20;		//Waren der Haendler
// qint16 ware[30];
// };
// CityClass(const QString&, int *, int *, int *);
CityClass(const QString &, const QList<int> &,  const QList<int> &, const QList<int> &);

// CityClass(const QString&, int [const_warenanzahl], int [const_warenanzahl], int [const_warenanzahl]);

// CityClass(const QString&, const int &param_hproduction[const_warenanzahl], const int &param_mproduction[const_warenanzahl], const int &param_lproduction[const_warenanzahl])

	void init();
// 	{
// 	hasKontor = false;
// 		srand(time(NULL));
// 		for(int i=0; i<const_warenanzahl; i++)
// 		{
// 		// int p;
// 		// if(stadtwaren.ware[i]==0)
// 			{
// 			int r=rand()%20;
// 			int s=rand()%20;
// 			int p = rand()%10;
// 			goods.ware[i] = s + r + p;
// 
// 		}
// 		// else
// 		// stadtwaren.ware[i] = int(sqrt(stadtwaren.ware[i] * stadtwaren.ware[i])) % 100;
// 
// 		}
// 	inhabitants = 1300 + rand()%1000;				//das kommt mal noch ins XML-Zeugs rein
// 
// 	static int id_counter;
// 	m_id = id_counter;
// 	id++;
// 	}

void reset();
// {
// for(int i = 0; i<5; i++)
// {
// hproduction[i]=-1;
// mproduction[i]=-1;
// lproduction[i]=-1;
// }
// cityname = QString();
// inhabitants = 0;
// // stadtwaren.kapazitaet = 0;
// }

void printGoods();

void production(int);
void setGoods(const Warenstruct &);


int id() const	{		return m_id;		}
int inhabitants()  const	{	return m_inhabitants;	}
QString cityname() const	{	return m_cityname;	}
Warenstruct goods() const	{	return m_goods;		}

bool hasKontor() const	{		return m_hasKontor;	}


private:
int m_id;
QString m_cityname;
int m_inhabitants;

int m_lifequality;
int m_luxuryrate;

Warenstruct m_goods;


bool m_hasKontor;		//Kontor built in this town.

// int m_hproduction[5];		// high production
// int m_mproduction[5];
// int m_lproduction[5];		// low production
// public slots:
//  void produktion(int);

// void produktion();
// void verbrauch();

QList<int> m_hproductionlist;
QList<int> m_mproductionlist;
QList<int> m_lproductionlist;

};


#endif
