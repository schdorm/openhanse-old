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

#include "clientgamedata.h"

#include <ohsocket.h>
#include <networkcommands.h>
#include <OMath>
  
#include "datamanager.h"

#include <QFile>
#include "serverprocess.h"


ClientGameData::ClientGameData(QObject *parent) : GameData(parent), m_ThreadParentObject (0), m_localGame(false), m_uncompleteBinaryDataPending (false)
{
  connect(this, SIGNAL(connectionFailed()), this, SLOT(quit()));
}

ClientGameData::~ClientGameData()
{
  delete m_ThreadParentObject;
}


void ClientGameData::connectToServer(QString hostname, int port)
{
  qWarning() << "void ClientGameData::connectToServer(QString hostname, int port)";
  m_hostname = hostname; m_port = port;
  start(QThread::HighPriority);
}

// void ClientGameData::connected()
// {
//     qWarning() << "1";
//     qWarning() << "2";
//     qWarning() << "3";
//     connect(m_self, SIGNAL(pidChanged(int)), this, SLOT(newPID(int)));
// //     connect(m_self, SIGNAL(dataAvailable()), this, SLOT(getData()));
//     emit connected();
// }

/*
void ClientGameData::printPlayerList()
{
  qWarning() << "Playerlist:";
  for(QHash<int, Player*>::const_iterator it = m_Players.begin(); it != m_Players.end(); ++it)
  {
    qWarning() << it.key() << (*it)->id() << (*it)->ping();
  }
}
*/

void ClientGameData::run() // reimplemented from QThread - the base-class
{
  qWarning() << "void ClientGameData::run()";
  m_ThreadParentObject = new QObject();
  m_socket = new OHSocket(m_ThreadParentObject);
  m_socket->connectToHost(m_hostname, m_port);
  
  Player *m_self = new Player(m_ThreadParentObject);
  addPlayer(m_self);
  m_ownID = m_self->id();
  
//   connect(m_socket, SIGNAL(pidChanged(int)), this, SLOT(newPID(int)));
  connect(m_socket, SIGNAL(dataUnhandled()), this, SLOT(handleSocketData()));

  connect(m_socket, SIGNAL(connected()), this, SLOT(ident()));
//   connect(timer, SIGNAL(timeout()), m_socket, SLOT(disconnectFromHostSlot()));
  connect(m_socket, SIGNAL(destroyed(QObject*)), this, SIGNAL(connectionFailed()));
  connect(this, SIGNAL(connectionFailed()), m_ThreadParentObject, SLOT(deleteLater()));
  exec();
}

void ClientGameData::ident()
{
  m_socket->killSocketTimer();
  m_socket->write(Command::ohsocketIdent);
  if(m_localGame)
  {
    //ADM 
    m_socket->write(Command::claimAdmin);
    m_socket->write(DAMAPOR->serverProcess()->serverAdminPassword());
  }
  emit connected();
}


void ClientGameData::handleSocketData()
{
  QByteArray data = m_socket->bufferedData();
  if(data.size() <= 8)
  {
    if(data.startsWith("IX"))
    {
      	data.remove(0,2);
	newPID(hexToDec(data));
	return;
    }
  }
  else if(data.startsWith("worldmap"))
  {
    
    if(data == "worldmap.default")
    {
      QFile file(":worldmap.png");
      file.open(QIODevice::ReadOnly);
      m_worldmapdata = file.readAll();
      file.close();
      qWarning() << "Using default worldmap!";
      emit worldmapReceived();
    }
    //     QFile file("worldmap.png");
    //     file.open(QIODevice::WriteOnly);
    //     file.write(data);
    //     file.close();
    //     qWarning() << "Data-Size:" << data.size();
    //     data.remove("worldmap\n");
    else
    {
      data.remove(0,9);
      if(data.endsWith(Network::EndOfFile))
      {
	data.replace(Network::EndOfFile, "");
	emit worldmapReceived();
      }
      else
      {
	m_uncompleteBinaryDataPending = true;
	m_uncompleteBinaryDataArray = &m_worldmapdata;
      }
      m_worldmapdata = data;
    }
    
    return;
  }
  else if(m_uncompleteBinaryDataPending)
  {
    m_uncompleteBinaryDataArray->append(data);
    if(data.endsWith(Network::EndOfFile))
    {
      if(m_uncompleteBinaryDataArray == &m_worldmapdata)
      {
	m_worldmapdata.replace(Network::EndOfFile, "");
	m_uncompleteBinaryDataPending = false;
	emit worldmapReceived();
      }

    }
  }
  
  loadData(data);
}

void ClientGameData::newPID(int newID)
{
  if(newID != m_ownID)
  {
    qWarning() << "void ClientGameData::newPID(int newID): " << newID;
    m_Players[newID] = m_Players.take(m_ownID);
    m_Players[newID]->setPID(newID);
    m_ownID = newID;
  }
}

void ClientGameData::requestPlayerlist()
{
  if(m_socket->state() == QAbstractSocket::ConnectedState)
    m_socket->write(Command::playerlist);
}

void ClientGameData::playerReady()
{
  m_socket->write(Command::playerReady);
}

QByteArray ClientGameData::getWorldmapData()
{
  QByteArray arr = m_worldmapdata;
// qWarning() << m_worldmapdata.size();
  m_worldmapdata.clear();
  return arr;
// return m_worldmapdata;
}
