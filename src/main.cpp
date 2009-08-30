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

	#include <QtDebug>
 #include <QDir>

#include "gesamtbild.h"

int main(int argc, char *argv[])
{
QStringList application_parameters;
for(int i = 0; i < argc; i++)
{
application_parameters << QString(argv[i]);
qWarning() << QString(argv[i]) << i;
}

if(!application_parameters.contains(QString("noopengl")))
{
	QApplication::setGraphicsSystem("opengl");
}

	QApplication app(argc, argv);
 	QDir dir;

	dir.setCurrent(QFileInfo(QString(argv[0])).absolutePath());
	
//  	qWarning() << argv[0];


	gesamtbild gb;
	gb.showFullScreen();

      return app.exec();
}

