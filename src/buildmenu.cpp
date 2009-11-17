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

#include "buildmenu.h"
#include "buildingdata.h"
#include <QtGui/QWidget>
#include <QtCore/QSignalMapper>

BuildMenu::BuildMenu()
{
QWidget *basictab = new QWidget(this);
tabwidget->addTab(basictab, tr("Basicbuildings"));

QWidget *citytab = new QWidget(this);
tabwidget->addTab(citytab, tr("Factories"));

QWidget *factorytab = new QWidget(this);
tabwidget->addTab(factorytab, tr("Factories"));

QWidget *misctab = new QWidget(this);
tabwidget->addTab(misctab, tr("Misc"));

QPushButton *buildKontor = new QPushButton(tr("Kontor"), basictab);
QSignalMapper *kontormap = new QSignalMapper(buildkontor);
kontormap->setMaping(buildKontor, BuildingData::Kontor);
connect(buildKontor, SIGNAL(clicked()), kontormap, SLOT(map());
connect(kontormap, SIGNAL(mapped(int)), this, SIGNAL(build(int))); 

buttonlist << buildKontor;
}
