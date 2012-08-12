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
#ifndef _DATA_MANAGER_H
#define _DATA_MANAGER_H

#define DAMAPOR DataManager::instance()			// Data-Manager-Pointer
#define GAMEDATA DataManager::instance()->gameData()	// Game-Data-Pointer
#define SETTINGS DataManager::instance()->settings()	// Settings-Pointer
// #define GAMEPARAMETER DataManager::instance()->gameParameter()	//Game-Parameter-Pointer

// #define OHSOCKET DataManager::instance()->socket()

#define OHDEBUG(x) DataManager::instance()->debugQueue()->debug(x)
#define DEBUGQUEUE DataManager::instance()->debugQueue()


// #include <QtCore/QObject>

// #include "dataclass.h"
// #include "settings.h"
//  #include "gameparameter.h"

// class OHSocket;
class ClientGameData;
class Settings;
class DebugQueue;
class ServerProcess;

class DataManager //: public QObject
{
  //  Q_OBJECT
public:
  ~DataManager();
  static DataManager *instance()
  // statische Funktion: erzeugt neue Instanz dieser Klasse, falls keine besteht und gibt diese zurück
  {
    if( m_instance == 0 )
    {
      m_instance = new DataManager();
    }
    return m_instance;
  }
  
  void recreateGamedata();
  // loescht alte Spieldaten und erzeugt neue Instanz der Spieldaten
  
  
  Settings *settings()		// gibt die Settings zurueck // returns a pointer to the settings-class
  {
    return m_globalSettings;
  }
  
  ClientGameData *gameData()		// gibt die Spieldaten zurueck - returns a pointer to the game-data-class
  {
    return m_gamedata;
  }
  
  DebugQueue *debugQueue()
  {
    return m_debugQueue;
  }
  ServerProcess *serverProcess();
  
  private:
    DataManager();		// Konstruktor: erzeugt neue Instanzen fuer private Pointer 
    
    
    ClientGameData *m_gamedata;
    Settings *m_globalSettings;
    DebugQueue *m_debugQueue;
    ServerProcess *m_serverProcess;
    
    static DataManager * m_instance;
    
};


#endif