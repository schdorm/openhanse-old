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

#ifndef _quest_h
#define _quest_h


#include "zeit.h"

namespace Quest
{
	enum questtasks
	{
	talk,
	obtainGoods,
	delivery,
	
	};
	enum questtypes
	{
	startofquest,
	step,
	endofquest,
	
	};
}


class quest
{
public:
zeit *hfgametime;
void readQuest(QString);


private:

Quest::questtypes questtype;
int destinationTownID;
bool questfollowing;


};

#endif
