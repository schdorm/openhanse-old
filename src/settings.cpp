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

#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtCore/QXmlStreamReader>
#include "settings.h"

#include <QtDebug>

void Settings::readConfigs(QString param_filename)
{
resolution = QSize(800,600); fullscreen = false; fps = 25; opengl = true; music_volume = 1; misc_volume = 1;

		QFile cfg(param_filename);
		if(!cfg.exists())
		{
			cfg.open(QIODevice::WriteOnly);
			QTextStream cfgstream(&cfg);
			cfgstream << "<conf> \n\t<resolution> \n\t\t<height>600</height> \n\t\t<width>800</width> \n\t</resolution> \n\t<fullscreen>false</fullscreen> \n\t<fps>25</fps> \n\t<opengl>true</opengl> \n\t<music-volume>1</music-volume> \n\t<misc-volume>1</misc-volume> \n</conf> ";
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
					resolution.setHeight(cfg_reader.text().toString().toInt());
				}
				else if(cfg_reader.name() == "width")
				{
					cfg_reader.readNext();
					resolution.setWidth(cfg_reader.text().toString().toInt());
				}
				else if(cfg_reader.name() == "fullscreen")
				{
					cfg_reader.readNext();
					if(cfg_reader.text().toString() == "false")
					{
						fullscreen = false;
					}
					else
					{
						fullscreen = true;
					}
				}
				else if(cfg_reader.name() == "opengl")
				{
					cfg_reader.readNext();
					qWarning() << cfg_reader.text().toString();
					if(cfg_reader.text().toString() == "false")
					{
						opengl = false;
					}
					else
					{
						opengl = true;
					}
				}
				else if(cfg_reader.name() == "fps")
				{
					cfg_reader.readNext();
					fps = cfg_reader.text().toString().toInt();
				}
				else if(cfg_reader.name() == "misc-volume")
				{
					cfg_reader.readNext();
					misc_volume = cfg_reader.text().toString().toFloat();
				}
				else if(cfg_reader.name() == "music-volume")
				{
					cfg_reader.readNext();
					music_volume = cfg_reader.text().toString().toFloat();
				}
			
			}
			
			}
			cfg.close();
		}

// qWarning() << opengl;
}
