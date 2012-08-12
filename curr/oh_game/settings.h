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

#ifndef _SETTINGS_H
#define _SETTINGS_H
#include <QtCore/QSize>

class Settings
{
  public:
    Settings(const QString &);
    ~Settings();
    void readConfigFile			();
    void writeConfigFile		();
    void applySettings			(const QSize &, bool, bool, int, int, int, bool);
    // bool openGL			() const {	return m_opengl;	}
    bool opengl				() const {	return m_opengl;	}
    bool fullscreen			() const {	return m_fullscreen;	}
    const QSize &resolution		() const {	return m_resolution;	}
    int fps				() const {	return m_fps;		}
    
    const QString &mapdirectory	() const {	return m_mapdirectory;	}
    const QString &debugFilePath	() const {	return m_debugfilepath;	}
    
    int miscVolume			() const {	return m_miscVolume;	}
    int musicVolume			() const {	return m_musicVolume;	}
    
    bool cacheMaps			() const {	return m_cacheMaps;	}
    
    
    private:
      QString m_configfile;
      
      QSize m_resolution;
      bool m_fullscreen;
      bool m_opengl;
      int m_fps;
      
      QString m_mapdirectory;		//member - mapdirectory
      QString m_debugfilepath;
      
      int m_musicVolume;
      int m_miscVolume;		//miscellaneous
      
      bool m_cacheMaps;
};

#endif
