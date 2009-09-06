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


#include "konsole.h"
#include "gesamtbild.h"
#include <QtGui/QVBoxLayout>
#include <QtCore/QFile>

#include <QDebug>

konsole::konsole()
{
// 	lc_iterator = (lastcommands);
	output = new QPlainTextEdit(this);
	output->setReadOnly(true);
	input = new QLineEdit(this);
	
	QVBoxLayout *clayout = new QVBoxLayout(this);
	clayout->addWidget(output);
	clayout->addWidget(input);
	connect(input, SIGNAL(returnPressed()), this, SLOT(execCommand()));
	connect(input, SIGNAL(returnPressed()), input, SLOT(clear()));

}

void konsole::keyPressEvent(QKeyEvent *event)
{
// qWarning() << event->key() << Qt::Key_Up << row << lastcommands.size();

if(event->key() == Qt::Key_Up && row - 1 >= 0 && row <= lastcommands.size())
{
row--;
input->setText(lastcommands.at(row));
// qWarning() << "" << row;
}
else if(event->key() == Qt::Key_Down )
{
if(row + 1< lastcommands.size())
{
row++;
input->setText(lastcommands.at(row));
}
else
{
row = lastcommands.size();
input->setText(QString());
}
}
else if(event->key() == Qt::Key_Escape)
{
hide();
}
}


void konsole::debug(QString msg)
{
qWarning() << msg;
output->appendPlainText(msg);
QFile dbg("debug.log");
dbg.open(QIODevice::Append|QIODevice::Text);
dbg.write(msg.toAscii());
dbg.write("\n");
dbg.close();
}

// void konsole::setConsoleBuffer(QString bufferstring)
// {
// consolebuffer = bufferstring;
// }

void konsole::execCommand()
{
bool executed = false;
QString inputstring = input->text();
if(!inputstring.isEmpty())
{
lastcommands << inputstring;
// lc_iterator.toBack();
row = lastcommands.size();
}
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
emit sig_command(inputstring.simplified());
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

if(inputstring == QString("gametime"))
{
// output->appendPlainText(QString("%1.%2.%3, %4:%5").arg(QChar(GAMEDATA->gametime.retDay()), QChar(GAMEDATA->gametime.retMonth()), QChar(GAMEDATA->gametime.retYear()), QChar(GAMEDATA->gametime.retHour()), QChar(int(GAMEDATA->gametime.retMinute()))));
output->appendPlainText(QString("%1.%2.%3, %4:%5").arg(QString("%1").arg(GAMEDATA->gametime.day()), QString("%1").arg(GAMEDATA->gametime.month()), QString("%1").arg(GAMEDATA->gametime.year()), QString("%1").arg(GAMEDATA->gametime.hour()), QString("%1").arg(GAMEDATA->gametime.minute())));

qWarning() << QString("%1.%2.%3, %4:%5").arg(QString("%1").arg(GAMEDATA->gametime.day()), QString("%1").arg(GAMEDATA->gametime.month()), QString("%1").arg(GAMEDATA->gametime.year()), QString("%1").arg(GAMEDATA->gametime.hour()), QString("%1").arg(GAMEDATA->gametime.minute()));
return;
}

if(!executed)
{
output->appendPlainText(tr("Error: unknown Command \"").append(inputstring).append("\" !"));

}
}


void gesamtbild::execCommand(const QString &cmd)
{
QString bu = cmd;
//cmd = cmd.simplified();
if(cmd == "hide sidemenu")
{
// menupanel->hide();
menupanel->setMaximumWidth(0);
}
else if(cmd == "show sidemenu")
{
menupanel->setMaximumWidth(width());

// menupanel->show();
}
else if(cmd.startsWith("load maps/"))
{
QString map = cmd;
if(map.remove("load maps/") != cmd)
{
GAMEDATA->currentMap->loadStartMap("false");
GAMEDATA->currentMap->loadStartMap(map);
gameview->karteladen(Map::null);
}

}

if(cmd == "test a")
{
///
/*
QFile rfile("test.txt");
rfile.open(QIODevice::Append);
hf->mapprops.maptyp = MapType::coast;
rfile.write(QByteArray().append(QString(hf->mapprops.maptyp)));
// hf->mapprops.maptyp = MapType::coast | MapType::city;
rfile.write(QByteArray().append(QString(" ")));
qWarning() <<hf->mapprops.maptyp; */ ///
/*
rfile.write(QByteArray().append(QString(MapType::coast | MapType::city)));
rfile.write(QByteArray().append(QString(" ")));
qWarning() << (MapType::coast | MapType::city); 

rfile.write(QByteArray().append(QString(MapType::land | MapType::city)));
rfile.write(QByteArray().append(QString(" ")));
 qWarning() << (MapType::land | MapType::city);*/
///
/*rfile.write(QByteArray().append(QString(MapType::land)));
rfile.write(QByteArray().append(QString(" ")));
 qWarning() <<MapType::land; 

rfile.write(QByteArray().append(QString(MapType::coast)));
rfile.write(QByteArray().append(QString(" ")));
 qWarning() <<MapType::coast; 

rfile.write(QByteArray().append(QString(MapType::sea)));
 qWarning() <<MapType::sea; 


rfile.close();*/ ///
}

}
