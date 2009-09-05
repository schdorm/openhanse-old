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

#include "gesamtbild.h"
#include "settings.h"

int main(int argc, char *argv[])
{
		QStringList application_parameters;		//list of command-line-arguments
		for(int i = 0; i < argc; i++)
		{
			application_parameters << QString(argv[i]);
				// qWarning() << QString(argv[i]) << i;
		}
		
		Settings mainsettings;
		mainsettings.readConfigs(QDir().home().absolutePath().append("/.OpenHanse/cfg.ohc"));	//reads the configuration file in ~/.OpenHanse/cfg.ohc
		
		if( (!application_parameters.contains(QString("noopengl"))) && mainsettings.ret_OpenGL())
		{
			QApplication::setGraphicsSystem("opengl");		// graphics-things for the graphiccard, if there's no other order
		}

    QApplication app(argc, argv);		// start of the main-event-loop
	QDir dir;

	dir.setCurrent(QFileInfo(QString(argv[0])).absolutePath());

	gesamtbild gb;
	gb.currentSettings = mainsettings;
	if(gb.currentSettings.ret_Fullscreen())
	{
	gb.showFullScreen();
	}
	else
	{
	gb.show();
	gb.resize(gb.currentSettings.ret_Resolution());
	}
    return app.exec();
}

