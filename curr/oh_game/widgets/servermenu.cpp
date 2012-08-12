/***************************************************************************
 *   Copyright (C) 2009 - 2010 by Christian Doerffel                       *
 *   oh.devs@googlemail.com                                                *
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

#include "servermenu.h"
#include "ipdialog.h"
#include "datamanager.h"
#include "clientgamedata.h"

#include <QtGui/QLabel>

ServerMenu::ServerMenu(QWidget *parent) : QWidget (parent)
{
  ui.setupUi(this);
  //   ui.ServerList->setSelection
  
  connect(ui.BackButton, SIGNAL(clicked()), this, SIGNAL(mainMenu()));
  connect(ui.BackButton, SIGNAL(clicked()), this, SLOT(deleteLater()));
  connect(ui.IPConnectButton, SIGNAL(clicked()),this, SLOT(ipdialog()));
  connect(GAMEDATA, SIGNAL(connected()), this, SIGNAL(mpConnected()));
  connect(GAMEDATA, SIGNAL(connected()), this, SLOT(deleteLater()));
}

void ServerMenu::ipdialog()
{
  IPDialog *f_ipdialog = new IPDialog(&m_hostName, &m_portNumber, this);
  f_ipdialog->show();
  connect(f_ipdialog, SIGNAL(accepted()), this, SLOT(connectBySettings()));
  connect(f_ipdialog, SIGNAL(finished(int)), f_ipdialog, SLOT(deleteLater()));
}

void ServerMenu::connectBySettings()
{
  GAMEDATA->connectToServer(m_hostName, m_portNumber);
  QDialog *d = new QDialog(this);
  d->setModal(true);
  //   deleteLater();
  QLabel *label = new QLabel("Connecting to Server ...", d);
  QHBoxLayout *layout = new QHBoxLayout(d);
  layout->addWidget(label);
//   QLabel *label = new QLabel("Connecting to Server ...");
//   label->setGeometry( width()/2 - label->width(), height()/2 - label->height(), 200, 32);
//   label->show();
//   label->raise();
//   label->setFocus();
//   label->raise();
//   label->show();
//   setEnabled(false);
  connect(GAMEDATA, SIGNAL(connectionFailed()), d, SLOT(deleteLater()));
  d->show();
}