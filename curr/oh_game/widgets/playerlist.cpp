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

#include "widgets/playerlist.h"

#include "datamanager.h"
#include "clientgamedata.h"

#include <QtDebug>

Playerlist::Playerlist(QWidget *parent): QWidget(parent)
{
  ui.setupUi(this);
  
  m_updateTimer.setSingleShot(true);
  m_updateTimer.setInterval(1500);
  connect(&m_updateTimer, SIGNAL(timeout()), this, SLOT(refreshData()));
  
}

void Playerlist::refreshData()
{
  if(isVisible())
    m_updateTimer.start();
  
//   qWarning() << "-------------- void Playerlist::refreshData()";
  
  ui.CurrentPlayers->setText(QString::number(GAMEDATA->currentPlayers()));
  ui.MaxPlayers->setText(QString::number(GAMEDATA->maxPlayers()));
  const QList<Player*> pl = GAMEDATA->playerList();
  const QList<Player*>::const_iterator endit = pl.end();
  int row = ui.Playerlist_table->rowCount();
  QTableWidgetItem *twi;
  qWarning() << "Function: void Playerlist::refreshData()" << row << pl.size();
  GAMEDATA->requestPlayerlist();
  
  while(row > pl.size())
  {
    row--;
    ui.Playerlist_table->removeCellWidget(row, 0);
    ui.Playerlist_table->removeCellWidget(row, 1);
    ui.Playerlist_table->removeCellWidget(row, 2);
    ui.Playerlist_table->removeCellWidget(row, 3);
    ui.Playerlist_table->setRowCount(row);
//      = ui.Playerlist_table->rowCount();
    qWarning() << "Case 1"<< row << pl.size();
  }
  
  while(row < pl.size())
  {
    ui.Playerlist_table->setRowCount(row + 1);
    twi = new QTableWidgetItem();
    ui.Playerlist_table->setItem(row, 0, twi);
    twi = new QTableWidgetItem();
    ui.Playerlist_table->setItem(row, 1, twi);
    twi = new QTableWidgetItem();
    ui.Playerlist_table->setItem(row, 2, twi);
    twi = new QTableWidgetItem();
    ui.Playerlist_table->setItem(row, 3, twi);
    row ++;
//     row = ui.Playerlist_table->rowCount();
      qWarning() << "Case 2" << row << pl.size();
  }
  
  row = 0;
  for(QList<Player*>::const_iterator it = pl.begin(); it != endit; ++it)
  {
    ui.Playerlist_table->item(row, 0)->setText(QString::number((*it)->ping()));
    ui.Playerlist_table->item(row, 1)->setText(QString::number((*it)->id()));
    ui.Playerlist_table->item(row, 2)->setText((*it)->name());
//     ui.Playerlist_table->item(row, 3)->setText((*it)->lastName());
    qWarning() << (*it)->id() << (*it)->ping();
//     ui.Playerlist_table->item(0, 0) = new QTableWidgetItem;
//     ui.Playerlist_table->item(1, 1)->setText("......");
//     ui.Playerlist_table->item(row, 0)->setText(QString::number((*it)->ping()));
//     ui.Playerlist_table->item(row, 1)->setText(QString::number((*it)->id()));
//     ui.Playerlist_table->item(row, 2)->setText((*it)->firstName());
//     ui.Playerlist_table->item(row, 3)->setText((*it)->lastName());
//     printf("#");
    row++;
  }
  setEnabled(false);
  qWarning()<< "End of Function: void Playerlist::refreshData()";
  
    
}