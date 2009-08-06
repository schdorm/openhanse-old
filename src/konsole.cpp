/***************************************************************************
 *   Copyright (C) 2009 by Christian Doerffel   *
 *   schdorm@googlemail.com   *
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


#include "konsole.h"
#include "gesamtbild.h"
#include <QtGui/QVBoxLayout>
#include <QtCore/QFile>

#include <QDebug>

konsole::konsole()
{
	output = new QPlainTextEdit(this);
	output->setReadOnly(true);
	input = new QLineEdit(this);
	
	QVBoxLayout *clayout = new QVBoxLayout(this);
	clayout->addWidget(output);
	clayout->addWidget(input);
	connect(input, SIGNAL(returnPressed()), this, SLOT(execCommand()));
	connect(input, SIGNAL(returnPressed()), input, SLOT(clear()));

}


// void konsole::setConsoleBuffer(QString bufferstring)
// {
// consolebuffer = bufferstring;
// }

void konsole::execCommand()
{
bool executed = false;
QString inputstring = input->text();
output->appendPlainText(QString(inputstring).prepend("> "));
if(inputstring.startsWith("load "))
{executed = true;
QString filestring = QString(inputstring).remove("load ");
if(QFile(filestring).exists())
{
// karteladen(QString(inputstring).remove("load "));
qWarning() << "Load: " << filestring;
output->appendPlainText(QString("Load: ").append(filestring));
if(filestring.endsWith(".ohm"))
{
emit sig_command(inputstring);
return;
}
if(filestring.endsWith(".ohs"))		//Savegame
{
return;
}
if(filestring.endsWith(".oht"))		//Script
{
return;
}
else
{
QFile rfile(filestring);
rfile.open(QIODevice::ReadOnly|QIODevice::Text);
output->appendPlainText(rfile.readAll());
rfile.close();
}
}
else
{
output->appendPlainText(tr("Fehler: Datei nicht gefunden: \"").append(filestring).append("\" !"));

}
}

if(inputstring.startsWith("echo "))
{
output->appendPlainText(inputstring.remove("echo "));
return;
}

if(QString(inputstring).simplified().contains(" sidemenu"))
{
emit sig_command(inputstring);
return;
}

if(inputstring.isEmpty() || QString(inputstring).remove(" ").isEmpty())
{
return;
}

if(inputstring == "test a")
{
emit sig_command(inputstring);
return;
}

if(!executed)
{
output->appendPlainText(tr("Fehler: unbekannter Befehl: \"").append(inputstring).append("\" !"));

}
}


void gesamtbild::execCommand(QString cmd)
{
QString bu = cmd;
cmd = cmd.simplified();
if(cmd == "hide sidemenu")
{
// menupanel->hide();
menupanel->setMaximumWidth(0);
}
if(cmd == "show sidemenu")
{
menupanel->setMaximumWidth(width());

// menupanel->show();
}
if(cmd.startsWith("load "))
{
QString map = cmd;
if(map.remove("load maps/") != cmd)
{
hf->karteladen(map);
}

}

if(cmd == "test a")
{
QFile rfile("test.txt");
rfile.open(QIODevice::Append);
hf->mapprops.maptyp = MapType::coast;
rfile.write(QByteArray().append(QString(hf->mapprops.maptyp)));
// hf->mapprops.maptyp = MapType::coast | MapType::city;
rfile.write(QByteArray().append(QString(" ")));
qWarning() <<hf->mapprops.maptyp; 

rfile.write(QByteArray().append(QString(MapType::coast | MapType::city)));
rfile.write(QByteArray().append(QString(" ")));
qWarning() << (MapType::coast | MapType::city); 

rfile.write(QByteArray().append(QString(MapType::land | MapType::city)));
rfile.write(QByteArray().append(QString(" ")));
 qWarning() << (MapType::land | MapType::city);

rfile.write(QByteArray().append(QString(MapType::land)));
rfile.write(QByteArray().append(QString(" ")));
 qWarning() <<MapType::land; 

rfile.write(QByteArray().append(QString(MapType::coast)));
rfile.write(QByteArray().append(QString(" ")));
 qWarning() <<MapType::coast; 

rfile.write(QByteArray().append(QString(MapType::sea)));
 qWarning() <<MapType::sea; 


rfile.close();
}

}