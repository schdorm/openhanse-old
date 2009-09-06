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

#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtCore/QXmlStreamReader>
#include "settings.h"

#include <QtDebug>

Settings::Settings()
{
	QDir dir = QDir().current();
	if(dir.cd("maps"))
	{
		m_mapdirectory = dir.absolutePath().append("/");
	}
}

void Settings::readConfigs(const QString &param_filename)
{
m_resolution = QSize(800,600); m_fullscreen = false; m_fps = 25; m_opengl = true;
m_music_volume = 1; m_misc_volume = 1;
m_cacheMaps = false;

		QFile cfg(param_filename);
		if(!cfg.exists())
		{
			cfg.open(QIODevice::WriteOnly);
			QTextStream cfgstream(&cfg);
			cfgstream << "<conf> \n\t<resolution> \n\t\t<height>600</height> \n\t\t<width>800</width> \n\t</resolution> \n\t<fullscreen>false</fullscreen> \n\t<fps>25</fps> \n\t<opengl>true</opengl> \n\t<music-volume>1</music-volume> \n\t<misc-volume>1</misc-volume> \n\t<cache-maps>true</cache-maps>\n</conf> ";
			cfg.close();

// 			return;
		}
		else
		{
			cfg.open(QIODevice::ReadOnly);
			QXmlStreamReader cfg_reader(&cfg);
			while(!cfg_reader.atEnd())
			{
			if(cfg_reader.readNext() == QXmlStreamReader::StartElement)
			{
			qWarning() << cfg_reader.name();
				if(cfg_reader.name() == "height")
				{
					cfg_reader.readNext();
					m_resolution.setHeight(cfg_reader.text().toString().toInt());
				}
				else if(cfg_reader.name() == "width")
				{
					cfg_reader.readNext();
					m_resolution.setWidth(cfg_reader.text().toString().toInt());
				}
				else if(cfg_reader.name() == "fullscreen")
				{
					cfg_reader.readNext();
					if(cfg_reader.text().toString() == "false")
					{
						m_fullscreen = false;
					}
					else
					{
						m_fullscreen = true;
					}
				}
				else if(cfg_reader.name() == "opengl")
				{
					cfg_reader.readNext();
					qWarning() << cfg_reader.text().toString();
					if(cfg_reader.text().toString() == "false")
					{
						m_opengl = false;
					}
					else
					{
						m_opengl = true;
					}
				}
				else if(cfg_reader.name() == "fps")
				{
					cfg_reader.readNext();
					m_fps = cfg_reader.text().toString().toInt();
				}
				else if(cfg_reader.name() == "misc-volume")
				{
					cfg_reader.readNext();
					m_misc_volume = cfg_reader.text().toString().toFloat();
				}
				else if(cfg_reader.name() == "music-volume")
				{
					cfg_reader.readNext();
					m_music_volume = cfg_reader.text().toString().toFloat();
				}
				else if(cfg_reader.name() == "cache-maps")
				{
					cfg_reader.readNext();
					qWarning() << cfg_reader.text().toString();
					if(cfg_reader.text().toString() == "true")
					{
						m_cacheMaps = true;
					}
					else
					{
						m_opengl = false;
					}
				}
				
			
			}
			
			}
			cfg.close();
		}

// qWarning() << m_opengl;
}
