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
#ifndef _gameparameter_h
#define _gameparameter_h

#include <QtCore/QHash>

class GameParameter : public QObject
{

public:
GameParameter();
const QHash <int, QString> &GoodLabelHash  () const {	return m_GoodLabelHash;		}
const QHash <int, int> &GoodBasicPriceHash () const {	return m_GoodBasicPriceHash;	}

QString GoodName 	(int key) const {	return m_GoodLabelHash[key];		}
int BasicPrice 		(int key) const {	return m_GoodBasicPriceHash[key];	}

const QString &firstName () const	{	return m_FirstName;	}
const QString &lastName  () const	{	return m_LastName;	}

private:
QString m_FirstName;
QString m_LastName;

QHash<int, QString> m_GoodLabelHash;
QHash<int, int> m_GoodBasicPriceHash;


};

#endif
