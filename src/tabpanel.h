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


#ifndef _tabpanel_h
#define _tabpanel_h

// #define test

#include <QtGui/QTabWidget>
#include <QtGui/QLabel>
#include <QtGui/QSlider>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>

#include "waren.h"
// #include "datamanager.h"

class SeaTabPanel : public QTabWidget
{
Q_OBJECT
// public slots:

public:
SeaTabPanel();
~SeaTabPanel();
// void create();
void landmenu();

#ifdef __test_
bool sub;

int tempint;
int tempint2;
#endif

QLabel *ware[const_warenanzahl];
QLabel *fuellung;
QLabel *taler;
// QTabWidget *menutabs;
QWidget *tab[3];

QWidget *ladung;
QWidget *steuerung;
// QWidget *;

QPushButton *anlegen;
// QPushButton *ablegen;
QPushButton *schuss;
QSlider *geschwindigkeitsregler;
QProgressBar *geschwindigkeitsanzeige;

QLabel *stat_color;
QLabel *stat_icon;

// void setGameData(DataClass*);
private:
// DataClass *gamedata;

public slots:
void update();
};

#endif
