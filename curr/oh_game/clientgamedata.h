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

class Player;
class OHSocket;

#include <GameData>

#ifndef _ClientGameData_H
#define _ClientGameData_H

class ClientGameData : public GameData
{
  Q_OBJECT
  public:
    ClientGameData(QObject *parent = 0);
    ~ClientGameData();
    
    
    int ownPID		() const{	return m_ownID;						}
    Player *ownPlayer	()	{	return m_Players.value(m_ownID, m_defaultPlayer);	}
    Player * self	()	{	return m_Players.value(m_ownID, m_defaultPlayer);	}
    
    QByteArray getWorldmapData();
    
    void setLocalGame	(bool local) {	m_localGame = local;					}
    bool localGame	() const{	return m_localGame;					}
    
  public slots:
    void connectToServer(QString hostname = "127.0.0.1", int port = 9967);
    void ident();
    void newPID(int);
    void requestPlayerlist();
    void playerReady();
    
    
    
  signals:
    void ready();
    void connected();
    void connectionFailed();
    void worldmapReceived();
    
  private:
    int m_ownID;
    QString m_hostname; int m_port;
    
    QObject *m_ThreadParentObject;
    OHSocket *m_socket;
    QByteArray m_worldmapdata;
    
    bool m_localGame;
    
    bool m_uncompleteBinaryDataPending;
    QByteArray *m_uncompleteBinaryDataArray;
    
    
  protected slots:
//     void getData();
    void handleSocketData();
  protected:
    void run();
};

#endif
