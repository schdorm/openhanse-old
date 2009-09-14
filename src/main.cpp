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


#include <QApplication>

// 	#include <QtDebug>
 #include <QDir>
 
#include "datamanager.h"
#include "settings.h"

#include "gesamtbild.h"

dataManager *dataManager::m_instance;


int main(int argc, char *argv[])
{
		QDir dir;
		dir.setCurrent(QFileInfo(QString(argv[0])).absolutePath());
	
		QStringList application_parameters;		//list of command-line-arguments
		for(int i = 0; i < argc; i++)
		{
			application_parameters << QString(argv[i]);
				// qWarning() << QString(argv[i]) << i;
		}
		
		SETTINGS->readConfigs(QDir().home().absolutePath().append("/.OpenHanse/cfg.ohc"));
				//reads the configuration file in ~/.OpenHanse/cfg.ohc
		
		if( (!application_parameters.contains(QString("noopengl"))) && SETTINGS->openGL())
		{
			QApplication::setGraphicsSystem("opengl");
				// graphics-things for the graphiccard, if there's no other order
		}

    QApplication app(argc, argv);		// start of the main-event-loop


	gesamtbild gb;
	if(SETTINGS->fullscreen())
	{
	gb.showFullScreen();
	}
	else
	{
	gb.show();
	gb.resize(SETTINGS->resolution());
	}
    return app.exec();
}

