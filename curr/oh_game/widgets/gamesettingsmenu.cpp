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

#include "gamesettingsmenu.h"

// #include <QtGui/QComboBox>
// #include <QtGui/QPushButton>

#include "datamanager.h"
#include "clientgamedata.h"

GameSettingsMenu::GameSettingsMenu(QWidget *parent) : QWidget(parent)
{
  ui.setupUi(this);
  ui.ReadyButton->setCheckable(!GAMEDATA->localGame());		//if multiplayer --> ready-Button checkable
  connect(ui.AbortButton, SIGNAL(clicked()), this, SIGNAL(abort()));
  connect(ui.ReadyButton, SIGNAL(clicked()), this, SIGNAL(ready()));
}


// void GameSettingsMenu::accept()
// {
//   
//   emit start();
// }

// GameSettings GameSettingsMenu::gameSettings()
// {
//   GameSettings f_sett;
//   f_sett.difficulty = m_DiffSelect -> itemData( m_DiffSelect->currentIndex()).toInt();
//   return f_sett;
// }
// 
// GameSettingsMenu::~GameSettingsMenu()
// {
//   delete m_DiffSelect;
//   delete m_AbortButton;
//   delete m_StartButton;
//   
// }
