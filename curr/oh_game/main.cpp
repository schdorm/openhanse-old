/***************************************************************************
 *   Copyright (C) 2009 - 2012 by Christian Doerffel                       *
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

#include <QtGui/QApplication>

#include <QtCore/QtDebug>
#include <QtCore/QDir>

#include <QtCore/QResource>

///#include <QtGui/QLabel>

#include "datamanager.h"
#include "settings.h"

#include "widgets/mainwindow.h"

#include <OHSettingsDir>
#include <ShipType>

#include <stdlib.h>

DataManager *DataManager::m_instance;


int main(int argc, char *argv[])
{
  qsrand(time(NULL));
  // set Current Directory = Path of binary file		-- linux-specific only?
  QDir::setCurrent(QFileInfo(QString(argv[0])).absolutePath());
  
  //list of command-line-arguments
  QStringList application_parameters;
  for(int i = 0; i < argc; i++)
  {
    application_parameters << QString(argv[i]);
    // qWarning() << QString(argv[i]) << i;
  }
  
  SETTINGS->readConfigFile();
  
  QResource::registerResource("images.rcc");
  QResource::registerResource("music.rcc");
  QResource::registerResource("sounds.rcc");
  
  // graphics-things for the graphiccard, if there's no other order
  if( (!application_parameters.contains(QString("noopengl"))) && SETTINGS->opengl())
  {
    QApplication::setGraphicsSystem("opengl");
  }
  
  QApplication::setApplicationName("OpenHanse");
  QApplication::setApplicationVersion("0.2.1");
  
    QApplication app(argc, argv);		// start of the main-event-loop
    
      MainWindow MW;
      MW.applySettings();
      MW.show();
    
      QObject::connect(&MW, SIGNAL(appQuit()), qApp, SLOT(quit()));
      
    return app.exec();				// end of main-event-loop
}

