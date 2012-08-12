/***************************************************************************
 *   Copyright (C) 2009 - 2010 by Christian Doerffel                       *
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

#include "serverprocess.h"
#include <QtDebug>
#include <QtCore/QDir>

ServerProcess::ServerProcess(QObject *parent) : QProcess(parent)
{
//   setProcessChannelMode(QProcess::ForwardedChannels);
  setProcessChannelMode(QProcess::SeparateChannels);
  connect(this, SIGNAL(readyReadStandardOutput()), this, SLOT(handleData()));
  connect(this, SIGNAL(readyReadStandardError()), this, SLOT(handleData()));
  connect(this, SIGNAL(error(QProcess::ProcessError)), this, SLOT(printError(QProcess::ProcessError)));
}

void ServerProcess::startServer()
{
  m_serverPW = QByteArray::fromHex(QByteArray::number( (qlonglong) time(NULL) & qrand(),10) + QByteArray::number( qrand(),8) + QByteArray::number( qrand(),16));
  m_serverPW.replace(" ", "");
  
  qWarning() << "void ServerProcess::startServer()" << m_serverPW;
  /*QProcess::*/start(QDir::currentPath() + "/oh_server" + " --pw=" + m_serverPW);
}


void ServerProcess::handleData()
{
  QByteArray data = readAllStandardOutput();
  data.append(readAllStandardError());
  if(data.contains("ready"))
  {
    emit serverReady();
    qWarning() << "Server is Ready!!";
  }
  qWarning() << "void ServerProcess::handleData()" << data /*<< readAllStandardError()*/;
}

void ServerProcess::printError(QProcess::ProcessError error)
{
  qWarning() << error << errorString();
}
