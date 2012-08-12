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

#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QBuffer>
#include <QtCore/QTextStream>
#include <QtCore/QXmlStreamReader>
#include "settings.h"

#include <QtDebug>
#include <OQString>


Settings::Settings(const QString &configfile) : m_configfile(configfile), m_resolution (QSize(800,600)), m_fullscreen (true), m_opengl (false), m_fps (25), m_musicVolume (80), m_miscVolume (80), m_cacheMaps (false)
{
	QDir dir = QDir::current();
	if(dir.cd("maps"))
	{
		m_mapdirectory = dir.absolutePath().append("/");
	}
	dir = QDir::current();
	if(!dir.cd("save"))
	{
		qWarning() << "Verzeichnis erstellen ...";
		dir.mkdir("save");
// 		dir.mkdir();
	}
}

Settings::~Settings()
{
  writeConfigFile();
}

void Settings::readConfigFile()
{
  // READ from File
  //   qWarning() << ("void Settings::processConfigFile(QByteArray *newConfig)");
  qWarning() << "void Settings::readConfigFile()";
  QFile configFile (m_configfile);
  if(configFile.open(QIODevice::ReadOnly))
  {
    QXmlStreamReader cfg_reader(&configFile);
    while(!cfg_reader.atEnd() && (!cfg_reader.hasError()))
    {
      if(cfg_reader.readNext() == QXmlStreamReader::StartElement)
      {
// 	qWarning() << cfg_reader.name() << cfg_reader.name().string()->toInt();
	if(cfg_reader.name() == "graphics")
	{
	  m_fullscreen = toBool(cfg_reader.attributes().value("fullscreen"));
	  m_opengl = toBool(cfg_reader.attributes().value("opengl"));
	  bool fpsbool;
	  int fpsint = cfg_reader.attributes().value("fps").toString().toInt(&fpsbool);
	  if(fpsbool)
	  {
	    m_fps = fpsint;
	  }
	}
	else if(cfg_reader.name() == "resolution")
	{
// 	  qWarning() << cfg_reader.attributes().value("size").toString();
	  m_resolution = StringToSize(cfg_reader.attributes().value("size").toString());
	  // m_resolution.setHeight(cfg_reader.attributes().value("height").toString().toInt());
	  // m_resolution.setWidth(cfg_reader.attributes().value("width").toString().toInt());
	}
	else if(cfg_reader.name() == "volume")
	{
	  m_miscVolume = cfg_reader.attributes().value("misc").toString().toInt();
	  m_musicVolume = cfg_reader.attributes().value("music").toString().toInt();
// 	  qWarning() << "Music-Volume:" << m_musicVolume << cfg_reader.attributes().value("music").string()->toInt();
	}
	else if(cfg_reader.name() == "cache")
	{
	  // 					cfg_reader.readNext();
	  // 					qWarning() << cfg_reader.text().toString();
	  m_cacheMaps = toBool(cfg_reader.attributes().value("maps").toString());
	  
	}
	else if(cfg_reader.name() == "debug")
	{
	  m_debugfilepath = cfg_reader.attributes().value("filepath").toString();
	}
      }
    }
    configFile.close();
  }
  // qWarning() << m_opengl;
  qWarning() << "\nRead Configuration:";
  qWarning() << "\nResolution: " << m_resolution.width() << " x " << m_resolution.height();
  qWarning() << "FPS: " << m_fps;
  qWarning() << "OpenGL: " << m_opengl << " \t Fullscreen: " << m_fullscreen;
  qWarning() << "Music-Volume: " << m_musicVolume << "\t Misc-Volume: " << m_miscVolume;
  qWarning() << "Chaching Maps: " << m_cacheMaps;
  qWarning() << "End of Reading Configs ...\n";
}

void Settings::writeConfigFile()
{
  
  QFile configfile(m_configfile);
  configfile.open(QIODevice::WriteOnly);
  
  QXmlStreamWriter writer(&configfile);
  writer.setAutoFormatting(true);
  writer.writeStartDocument();
  writer.writeStartElement("conf");
  writer.writeStartElement("graphics");
  writer.writeAttribute("fullscreen", fromBool(m_fullscreen));
  writer.writeAttribute("fps", QString::number(m_fps));
  writer.writeAttribute("opengl", fromBool(m_opengl));
  writer.writeEmptyElement("resolution");
  writer.writeAttribute("size", StringFromSize(m_resolution));
  writer.writeEndElement();
  //     writer.writeEndElement();
  
  writer.writeEmptyElement("cache");
  writer.writeAttribute("maps", fromBool(m_cacheMaps));
  
  writer.writeEmptyElement("volume");
  writer.writeAttribute("misc", QString::number(m_miscVolume));
  writer.writeAttribute("music", QString::number(m_musicVolume));
  
  writer.writeEmptyElement("debug");
  writer.writeAttribute("filepath", "game_debug.ohl");
  
  writer.writeEndDocument();
  configfile.close();
}


void Settings::applySettings(const QSize &size, bool fullscreen, bool opengl, int fps, int musicVolume, int miscVolume, bool cacheMaps)
{
  m_resolution = size;
  m_fullscreen = fullscreen;
  m_opengl = opengl;
  m_fps = fps;
  m_musicVolume = musicVolume;
  m_miscVolume = miscVolume;
  m_cacheMaps = cacheMaps;
}


