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
#ifndef _DATA_MANAGER_H
#define _DATA_MANAGER_H

#define DMP dataManager::instance()			// Data-Manager-Pointer
#define GAMEDATA dataManager::instance()->gamedata()	// Game-Data-Pointer
#define SETTINGS dataManager::instance()->settings()	// Settings-Pointer

#include "dataclass.h"
#include "settings.h"

class dataManager
{
public:
	dataManager()		// Konstruktor: erzeugt neue Instanzen fuer private Pointer 
	{
		m_gamedata = new DataClass();
		m_globalSettings = new Settings();
	}

	static dataManager *instance()
		// statische Funktion: erzeugt neue Instanz dieser Klasse, falls keine besteht und gibt diese zurück
	{
		if( m_instance == NULL )
		{
			m_instance = new dataManager();
		}
		return m_instance;
	}
	
	void recreateGamedata()		// loescht alte Spieldaten und erzeugt neue Instanz der Spieldaten
	{
		delete m_gamedata;
		m_gamedata = new DataClass();
	}
	
	Settings *settings()		// gibt die Settings zurueck
	{
		return m_globalSettings;
	}

	DataClass *gamedata()		// gibt die Spieldaten zurueck
	{
		return m_gamedata;
	};

private:

	DataClass *m_gamedata;
	Settings *m_globalSettings;
	static dataManager * m_instance;

};


#endif