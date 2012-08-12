/***************************************************************************
 *   Copyright (C) 2009 by Christian Doerffel                              *
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

#include "datamanager.h"
#include "clientgamedata.h"
#include "settings.h"
#include "debugqueue.h"
#include "serverprocess.h"
#include <libs/ohsettingsdir.h>

// Konstruktor: erzeugt neue Instanzen fuer private Pointer 
DataManager::DataManager() : m_gamedata(new ClientGameData()), m_globalSettings(new Settings(settingsdir().append("config.ohc"))), m_debugQueue(new DebugQueue()), m_serverProcess (0)
{
	
	
// 	m_ohsocket = 0;
}

DataManager::~DataManager()
{
  	delete m_gamedata;
	delete m_globalSettings;
	delete m_debugQueue;
	delete m_serverProcess;
// 	delete m_ohsocket;
}

ServerProcess *DataManager::serverProcess()
{
  if(m_serverProcess)
    return m_serverProcess;
  else
  {
    m_serverProcess = new ServerProcess();
    return m_serverProcess;
  }
}
	
void DataManager::recreateGamedata()		// loescht alte Spieldaten und erzeugt neue Instanz der Spieldaten
{
	delete m_gamedata;
	m_gamedata = new ClientGameData();
}


