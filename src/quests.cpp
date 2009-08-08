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


#include "questclass.h"
//  #include "hauptfenster.h"
#include "questhandler.h"
 
 #include <QtDebug>
 #include <QtCore/QFile>
 #include <QtCore/QXmlStreamReader>

 
void QuestHandler::indexQuestFile(QString questfile_name)
{

  if(!questIndexList.contains(questfile_name))
  {
  int count = 0;
    QFile indexingfile(questfile_name);
    if(indexingfile.open(QIODevice::ReadOnly))
    {

	

	QXmlStreamReader indexer(&indexingfile);
	while(!indexer.atEnd())
	{
		indexer.readNext();
		if(/*indexer.tokenType() == QXmlStreamReader::StartElement*/indexer.isStartElement())
		{
			qWarning() << indexer.name().toString();
			if(indexer.name().toString() == "quest")
			{
				if(indexer.attributes().value("questtype").toString() == "startquest" )
				{
					count++;
				}
			  
			}
		}
	}
	questIndexList[questfile_name] = count;
    }
    
  }
}

void quest::readQuest(QString questfile_name)
{
if(!questfile_name.isEmpty() && questfile_name.endsWith(".ohq"))
{
QFile questfile(questfile_name);
if(questfile.open(QIODevice::ReadOnly))
{


	QXmlStreamReader reader(&questfile);

}
}
}