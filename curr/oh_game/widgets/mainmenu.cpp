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

#include "mainmenu.h"
#include <QtGui/QPushButton>

#include <QtGui/QApplication>

MainMenu::MainMenu(QWidget *parent) : QFrame(parent)
{
  setFrameShape(Panel);
  setFrameShadow(Sunken);
  spButton = new QPushButton(tr("Single-Player-Game"), this);
  mpButton = new QPushButton(tr("Multi-Player-Game"), this);
  optButton = new QPushButton(tr("Options"), this);
  quitButton = new QPushButton(tr("Quit"), this);
  
  layout.addWidget(spButton);
  layout.addWidget(mpButton);
  layout.addWidget(optButton);
  layout.addWidget(quitButton);
  setLayout(&layout);
  setFixedSize(240,320);
  
  connect(spButton, SIGNAL(clicked()), this, SIGNAL(spGame()));
  connect(mpButton, SIGNAL(clicked()), this, SIGNAL(mpGame()));
  connect(optButton, SIGNAL(clicked()), this, SIGNAL(Options()));
  //   connect(quitButton, SIGNAL(clicked()), this, SIGNAL(Quit()));
  connect(quitButton, SIGNAL(clicked()), qApp, SLOT(quit()));
  
  connect(spButton, SIGNAL(clicked()), this, SIGNAL(buttonClicked()));
  connect(mpButton, SIGNAL(clicked()), this, SIGNAL(buttonClicked()));
  connect(optButton, SIGNAL(clicked()), this, SIGNAL(buttonClicked()));
//   connect(quitButton, SIGNAL(clicked()), this, SIGNAL(buttonClicked()));
  connect(this, SIGNAL(buttonClicked()), this, SLOT(deleteLater()));
}

MainMenu::~MainMenu()
{
  delete spButton;
  delete mpButton;
  delete optButton;
  delete quitButton;
}
