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

#ifndef _SETTINGS_H
#define _SETTINGS_H
#include <QtCore/QSize>
class Settings
{
public:
Settings();
void readConfigs (const QString&);
bool openGL()			const	{	return m_opengl;	}
bool fullscreen()		const	{	return m_fullscreen;	}
const QSize &resolution()	const	{	return m_resolution;	}
int fps()			const	{	return m_fps;		}

const QString &mapdirectory()	const	{	return m_mapdirectory;	}

float miscVolume()		const	{	return m_misc_volume;	}
float musicVolume()		const	{	return m_music_volume;	}

bool cacheMaps()		const	{	return m_cacheMaps;	}

private:
QSize m_resolution;
bool m_fullscreen;
bool m_opengl;
int m_fps;

QString m_mapdirectory;		//member - mapdirectory

float m_misc_volume;		//miscellaneous
float m_music_volume;

bool m_cacheMaps;
};

#endif
