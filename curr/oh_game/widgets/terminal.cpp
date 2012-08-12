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

#include "terminal.h"
#include "mainwindow.h"
// #include "mainview.h"

#include "datamanager.h"
#include "debugqueue.h"
#include "clientgamedata.h"

#include "settings.h"

// #include "ship.h"

// #include "city.h"

#include <QtGui/QPlainTextEdit>
#include <QtGui/QLineEdit>
#include <QtGui/QVBoxLayout>
#include <QtCore/QFile>

#include <QtDebug>
#include <QtCore/QDateTime>

#include <OQString>

Terminal::Terminal(QWidget *parent) : QWidget(parent)
{
	output = new QPlainTextEdit(this);
	output->setReadOnly(true);
	input = new QLineEdit(this);
	
	QVBoxLayout *clayout = new QVBoxLayout(this);
	clayout->addWidget(output);
	clayout->addWidget(input);
	connect(input, SIGNAL(returnPressed()), this, SLOT(execCommand()));
	connect(input, SIGNAL(returnPressed()), input, SLOT(clear()));
	
	{
	QDateTime dt = QDateTime().currentDateTime();
	QFile(SETTINGS->debugFilePath()).rename(SETTINGS->debugFilePath() + "~");
	QFile dbf(SETTINGS->debugFilePath());
	dbf.open(QIODevice::Append);
	QTextStream errorstream(&dbf);
	errorstream << "\nStarting Log on ";
	errorstream << dt.toString(QString("ddd. MMM dd. yyyy hh:mm:ss ")) << "\n";
	dbf.close();
	}
	connect(DEBUGQUEUE, SIGNAL(dataAvailabled()), this, SLOT(debug()));

}

Terminal::~Terminal()
{
// 	lc_iterator = (lastcommands);
#ifdef _DEBUG_DESTRUCTORS
qWarning() << "Destructing Konsole";
#endif
	delete output;
#ifdef _DEBUG_DESTRUCTORS
qWarning() << "Output deleted";
#endif
	delete input;
#ifdef _DEBUG_DESTRUCTORS
qWarning() << "Input deleted. End of Destructing Konsole.";
#endif
}


// Terminal &Terminal::operator<<(int a)
// {
// debug(QString(a));
// return this;
// 
// }

Terminal &operator<<(Terminal &term, const char *characters)
{
  term.printMessage(QString(characters));
  return term;
}

Terminal &operator<<(Terminal &term, int integer)
{
  term.printMessage(QString::number(integer));
  return term;
}

Terminal &operator<<(Terminal &term, const QString &string)
{
  term.printMessage(string);
  return term;
}

// void Terminal::operator<<(const QString &param_debugmsg)
// {
// debug(param_debugmsg);
// return this;
// }

void Terminal::keyPressEvent(QKeyEvent *event)
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
  else if(event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_Q)
  {
//     deleteLater();
    emit sig_command("quit");
  }
}

void Terminal::debug()
{
  while(DEBUGQUEUE->dataAvailable())
  {
    printMessage(DEBUGQUEUE->dequeue());
  }
}



void Terminal::printMessage(const QString &msg) const
{
  qWarning() << msg;
  output->appendPlainText(msg);
  QFile dbg(SETTINGS->debugFilePath());
  dbg.open(QIODevice::Append|QIODevice::Text);
  dbg.write(msg.toAscii());
  dbg.write("\n");
  dbg.close();
}

// void Terminal::setConsoleBuffer(QString bufferstring)
// {
// consolebuffer = bufferstring;
// }

void Terminal::execCommand()
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
  {
    executed = true;
    QString filestring = QString(inputstring).remove("load ");
    if(QFile(filestring).exists())
    {
      qWarning() << "Load: " << filestring;
      output->appendPlainText(QString("Load: ").append(filestring));
      if(filestring.endsWith(".ohm"))
      {
	emit sig_command(inputstring.simplified());
	return;
      }
      else if(filestring.endsWith(".ohs"))		//Savegame
      {
	return;
      }
      else if(filestring.endsWith(".oht"))		//Script
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
  
  else if(inputstring.startsWith("echo "))
  {
    output->appendPlainText(inputstring.remove("echo "));
    return;
  }
  
  else if(QString(inputstring).simplified().contains(" sidemenu"))
  {
    emit sig_command(inputstring);
    return;
  }
  
  else if(inputstring.isEmpty() || QString(inputstring).remove(" ").isEmpty() ||  QString(inputstring).simplified().isEmpty())
  {
    return;
  }
  
  else if(inputstring == "test a")
  {
    emit sig_command(inputstring);
    return;
  }
  
  else if(inputstring == "print Shipposition")
  {
    // GAMEDATA->activeShip()->printPosition();
    return;
  }
  
  else if(inputstring.startsWith("print Citygoods"))
  {
    #ifdef OH_EVOLUTION_DEVELOPED
    bool printed = false;
    QString cityname = QString(inputstring).remove("print Citygoods ");
    qWarning() << "Cityname:" << cityname << "Inputstring:" << inputstring ;
    
    if(!cityname.isEmpty())
    {
      const QList<City*> &citylist = GAMEDATA->cityList();
      City *it = 0;
      // 	for(QList<CityClass*>::iterator it = citylist->begin();
      // 	it != citylist->end();
      // 	++it)
      foreach(it, citylist)
      {
	qWarning() << "It->cityname():" << it->name();
	if(it->name() == cityname)
	{
	  it->printGoods();
	  printed = true;
	}
      }
    }
    if(!printed)
    {
      OHDEBUG(QString(cityname).prepend("City \"").append("\" not found!"));
    }
    #endif
    return;
  }
  
  else if(inputstring == QString("gametime"))
  {
    #ifdef OH_EVOLUTION_DEVELOPED
    
    // output->appendPlainText(QString("%1.%2.%3, %4:%5").arg(QChar(GAMEDATA->gametime().retDay()), QChar(GAMEDATA->gametime().retMonth()), QChar(GAMEDATA->gametime().retYear()), QChar(GAMEDATA->gametime().retHour()), QChar(int(GAMEDATA->gametime().retMinute()))));
    output->appendPlainText(QString("%1.%2.%3, %4:%5").arg(QString("%1").arg(GAMEDATA->gametime().day()), QString("%1").arg(GAMEDATA->gametime().month()), QString("%1").arg(GAMEDATA->gametime().year()), QString("%1").arg(GAMEDATA->gametime().hour()), QString("%1").arg(GAMEDATA->gametime().minute())));
    
    qWarning() << QString("%1.%2.%3, %4:%5").arg(QString("%1").arg(GAMEDATA->gametime().day()), QString("%1").arg(GAMEDATA->gametime().month()), QString("%1").arg(GAMEDATA->gametime().year()), QString("%1").arg(GAMEDATA->gametime().hour()), QString("%1").arg(GAMEDATA->gametime().minute()));
    return;
    #endif
  }
  
  if(!executed)
  {
    output->appendPlainText(tr("Error: unknown Command \"").append(inputstring).append("\" !"));
  }
}

///##########################################################################################################

void MainWindow::execCommand(const QString &cmd)
{
/*QString bu = cmd;
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
GAMEDATA->currentMap()->loadStartMap("false");
GAMEDATA->currentMap()->loadStartMap(map);
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
/*}
if(cmd.startsWith("start game"))
{
  if(cmd.contains("empty"))
  {
    
  }
  
}*/

if(cmd == "quit" || cmd == "exit")
{
  emit appQuit();
}

}
