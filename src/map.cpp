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
#include "map.h"
#include "mapobject.h"
#include "datamanager.h"


#include <QtCore/QFile>
#include <QtCore/QXmlStreamReader>


#include <QtDebug>
#include <QtCore/QDir>
#include <QtCore/QVariant>

MapObject::MapObject(const int &param_role, const QString &param_filename, const QString &param_tooltip, const QPoint &param_position, const double &param_zvalue) : m_role( param_role), m_filename (param_filename), m_tooltip (param_tooltip), m_position (param_position), m_zValue (param_zvalue)
{
// 	m_role = param_role;
// 	m_filename = param_filename;
// 	m_tooltip = param_tooltip;
// 	m_position = param_position;
// 	m_zValue = param_zvalue;
}


// QString Map::mapdirectory;

Map::Map()
{
m_mapdirectory = SETTINGS->mapdirectory();
// 	if(mapdirectory.isEmpty())			// static QString in Map-Class
// 	{
// 		QDir dir= QDir().current();
// 		if(dir.cd("maps"))
// 		{
// 			mapdirectory = dir.absolutePath().append("/");
// 			qWarning()  << "Working Direktory:" << mapdirectory;
// 			
// 		}
// 		else
// 		{
// 			qWarning() << "Mapdir does not exist. Exiting.";
// 			mapdirectory = QString();
// 		}
// 	}
	filename = QString();
	mapnorth = QString();
	mapeast  = QString();
	mapsouth = QString();
	mapwest  = QString();
}

Map::~Map()
{
MapObject *mapobjectit = 0;	//Map-Object-Iterator
foreach(mapobjectit, objectlist)
{
delete mapobjectit;
}

}


void Map::loadStartMap(const QString &mapfilename)
{
static bool started;
if(!started)
{
started = loadMap(mapfilename);
coordinate = QPoint(400,400);
}
else if(mapfilename == "false")
{
started = false;
}

}

bool Map::loadMap(const Orientations &mapdirection)
{
	switch(mapdirection)
	{
		case North:
		{
			if(loadMap(mapnorth))
			{
				coordinate.setY(coordinate.y() + 1);
				return true;
			}
			break;
		}
		case East:
		{
			if(loadMap(mapeast))
			{
				coordinate.setX(coordinate.x() + 1);
				return true;
			}
			break;
		}
		case South:
		{
			if(loadMap(mapsouth))
			{
				  coordinate.setY(coordinate.y() - 1);
				return true;
			}
			break;
		}
		case West:
		{
			if(loadMap(mapwest))
			{
				coordinate.setX(coordinate.x() - 1);
				return true;
			}
			break;
		}
		default:
			break;
	}
	return false;
}


bool Map::loadMap(QString param_mapname)
{
	qWarning() << "bool Map::loadMap(QString param_mapname)" << "Karteladen: " << param_mapname;

	param_mapname.prepend(m_mapdirectory);

	qWarning() << "Mapdirectory:" << m_mapdirectory << "Mappath:" << param_mapname;


	QFile file(param_mapname);		//Map-XML-Lesen
	if(file.exists())
	{
		filename = param_mapname;
		qWarning() << "Mapfile is existing";
		
		enum stati	{
				null,			// nothing
				objekt,			// Objectproperties
				o_role,			// Object-role
				o_tooltip,		// Object-Tooltip
				o_file,			// Image-File
				o_posx,			// X-Position
				o_posy,			// Y-Position
				o_zvalue,		// Z-Value
				map,			// Allgemein: Mapeigenschaften ///Mapproperties
				m_cityname,		// cityname
				m_img,			// mapbackground
				m_nord,			//noerdliche angrenzende Map	mapnorth
				m_west,			//westliche a M			mapwest
				m_sued,			//suedliche a M			mapsouth
				m_ost,			//oestliche a M			mapeast
				m_width,		//breite			width
				m_height,		//hoehe				height
				m_typ,
				} status = null;	// status als dieses enum: zeigt an, was fuer ein Wert als naechstes ausgelesen wird

		cityname = QString();		isCity = false;
		int object_role = -1;				//Funktion des Objektes /// objectrole
		QString object_tooltip = QString();				//name/tooltip des objekts
		QString object_file = QString();				//name des Bildes des Objekts

		int object_posx = 0;				//x-Koordinate /// x-position
		int object_posy = 0;				//y-Koordinate /// y-position
		double object_zvalue = 0;			// z-Value = Hoehe /// Z-Value
		bool reading = true;

		
		file.open(QIODevice::ReadOnly);
		QXmlStreamReader reader(&file);
		while (reading) 
		{
		switch(reader.readNext())
		{
			case QXmlStreamReader::StartElement:
			{
			qWarning() << "\nStart:\t" << reader.qualifiedName().toString();
				if(reader.qualifiedName().toString() =="mapproperties")
				{
// 				qWarning() << "Start: gamedata->currentMap";
				status=map;
				break;
				}
				if(reader.qualifiedName().toString() =="cityname")
				{
				status=m_cityname;
				break;
				}
				if(reader.qualifiedName().toString() =="mapbackground")
				{
// 				qWarning() << "Start: gamedata->currentMap";
				status=m_img;
				break;
				}
				if(reader.qualifiedName().toString() =="mapnorth")
				{
// 				qWarning() << "Start: gamedata->currentMap";
				status=m_nord;
				break;
				}
				if(reader.qualifiedName().toString() =="mapeast")
				{
// 				qWarning() << "Start: gamedata->currentMap";
				status=m_ost;
				break;
				}
				if(reader.qualifiedName().toString() =="mapsouth")
				{
// 				qWarning() << "Start: gamedata->currentMap";
				status=m_sued;
				break;
				}
				if(reader.qualifiedName().toString() =="mapwest")
				{
// 				qWarning() << "Start: gamedata->currentMap";
				status=m_west;
				break;
				}
				if(reader.qualifiedName().toString() =="mapwidth")
				{
// 				qWarning() << "Start: gamedata->currentMap";
				status=m_width;
				break;
				}
				if(reader.qualifiedName().toString() =="mapheight")
				{
// 				qWarning() << "Start: gamedata->currentMap";
				status=m_height;
				break;
				}

				if(reader.qualifiedName().toString() =="maptype")
				{
// 				qWarning() << "Start: gamedata->currentMap";
				status=m_typ;
				break;
				}

				if(reader.qualifiedName().toString() =="objekt")
				{
// 				qWarning() << "objekt";
				status=objekt;
				break;
				}

				if(reader.qualifiedName().toString() == "objektfunktion")
				{
// 				qWarning() << "o_role";
				status = o_role;
				break;
				}

				if(reader.qualifiedName().toString() == "objekttooltip")
				{
// 				qWarning() << "o_tooltip";
				status = o_tooltip;
				break;
				}

				if(reader.qualifiedName().toString() == "objektdatei")
				{
// 				qWarning() << "o_file";
				status = o_file;
				break;
				}

				if(reader.qualifiedName().toString() == "objektpositionx")
				{
// 				qWarning() << "o_posx";
				status = o_posx;
				break;
				}

				if(reader.qualifiedName().toString() == "objektpositiony")
				{
// 				qWarning() << "o_posy";
				status = o_posy;
				break;
				}
				
				if(reader.qualifiedName().toString() == "objekthoehe")
				{
// 				qWarning() << "o_posy";
				status = o_zvalue;
				break;
				}
				break;
			}

			case QXmlStreamReader::Invalid:
			{
			qWarning() << "Error:" << reader.errorString() <<"\nEnde Error" ;
			break;
			}

			case QXmlStreamReader::Characters:
			{
 				qWarning() << "Chars:" <<reader.text().toString();
				//Tags ohne Inhalt - nur mit Unterkategorien
				switch(status)
				{
				case map:
					break;
				case m_cityname:
				{
					cityname = reader.text().toString();
					isCity = true;
// 					gamedata->setCurrentCity(reader.text().toString());
				break;
				}
				case m_img:
				{
				background = reader.text().toString();
				background.prepend(m_mapdirectory);
				break;
				}

				case m_nord:
				{
				mapnorth = reader.text().toString();

				qWarning() << "Nord-Map:" << mapnorth;
				if(!QFile(mapnorth).exists())
					{
					qWarning() << mapnorth << "Existiert nicht";
					mapnorth = QString();
					}
				break;
				}

				case m_ost:
				{
				mapeast = reader.text().toString();
				qWarning() << "Ost-Map:" << mapeast;
				if(!QFile(mapeast).exists())
					{
					qWarning() << mapeast << "Existiert nicht";
					mapeast = QString();
					}
				break;
				}

				case m_sued:
				{
				mapsouth = reader.text().toString();
				qWarning() << "Sued-Map:" << mapsouth;
				if(!QFile(mapsouth).exists())
					{
					qWarning() << mapsouth << "Existiert nicht";
					mapsouth = QString();
					}
				break;
				}

				case m_west:
				{
				mapwest = reader.text().toString();
				qWarning() << "West-Map:" << mapwest;
				if(!QFile(mapwest).exists())
					{
					qWarning() << mapwest << "Existiert nicht";
					mapwest = QString();
					}
				break;
				}

				case m_width:
				{
					size.setWidth(reader.text().toString().toInt());
					break;
				}
				case m_height:
				{
					size.setHeight(reader.text().toString().toInt());
					break;
				}
				case m_typ:
				{
					type =
					  static_cast<Map::MapType>( reader.text().toString().toInt() );
					break;
				}

				case objekt:
					break;
				case o_role:
				{
					object_role = reader.text().toString().toInt();
					qWarning() << "\tObjektfkt" << object_role;
					break;
				}
				case o_tooltip:
				{
					object_tooltip = reader.text().toString();
					qWarning() << "\tObjekttooltip" << object_tooltip;
					break;
				}
				case o_file:
				{
					object_file = reader.text().toString();
					object_file.prepend(m_mapdirectory);
					qWarning() << "\tBild:" << object_file;
					break;
				}
				case o_posx:
				{
					object_posx = reader.text().toString().toInt();
					qWarning() << "\tPosX:" << object_posx;
					break;
				}
				case o_posy:
				{
					object_posy = reader.text().toString().toInt();
					qWarning() << "\tPosY" << object_posy;
					break;
				}
				case o_zvalue:
				{
					object_zvalue = reader.text().toString().toDouble();
					qWarning() << "\tPosY" << object_zvalue;
					break;
				}
				
				default:
					break;
				}
				break;
			}
			case QXmlStreamReader::EndElement:
			{
				qWarning() << "Ende :"<< reader.qualifiedName().toString();
				if(reader.qualifiedName().toString() == "objekt" && object_role != - 1 && !object_file.isEmpty())
	//jetzt zeichnen: habe alle Eigenschaften des Objektes erhalten?
				{
					qWarning() << object_file << object_role;
					
					MapObject *currentMO = new MapObject(object_role, object_file, object_tooltip, QPoint(object_posx, object_posy), object_zvalue);
					
					objectlist << currentMO;
					
					object_role = -1;
					object_tooltip = QString();
					object_file = QString();
					object_posx = 0;
					object_posy = 0;
					object_zvalue = 0;
				}
				status=null;
				break;

			}
			default:
				break;

		}
		if(reader.atEnd() || (reader.tokenType() == QXmlStreamReader::EndElement && reader.qualifiedName().toString() =="map"))
		{
		reading = false;
		}

		}
	
		if (reader.hasError())
		{
			qWarning() << reader.errorString();
		}
		qWarning() << "Returning true: Map sucessfully read!";
		return true;
	}
	else
	{
	qWarning() << "Mapfile not found!";
	return false;
	}
}
