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

#include "hauptfenster.h"
#include "dataclass.h"
#include "settings.h"

#include "shipdata.h"

#include <QtGui/QGraphicsScene>

#include <QtCore/QFile>
#include <QtCore/QXmlStreamReader>


#include <QtDebug>
#include <QtCore/QDir>
#include <QtCore/QVariant>

void hauptfenster::karteladen(Map::Orientations orientation)
{
	if(orientation != Map::null)
	{
		GAMEDATA->manageMapReading(orientation);
	/*
	Map *tempmappointer = GAMEDATA->currentMap();
	if(!SETTINGS->cacheMaps())
	{
	delete tempmappointer;
	}

	tempmappointer = new Map();
	
	tempmappointer->loadMap(orientation);
	
	if(SETTINGS->cacheMaps())
	{
		GAMEDATA->addMap(*tempmappointer);
	}*/
	}

	
	QGraphicsScene tempscene;
	setScene(&tempscene);
	
	scene()->clear();
// 	delete szene;
 	QGraphicsScene *szene = new QGraphicsScene();
//  	scene->clear();
// 	scene = QGraphicsScene();

	
	QFile mapimgfile(GAMEDATA->currentMap()->background());
	if(mapimgfile.exists())
	{
		szene->setBackgroundBrush(QBrush(QImage(GAMEDATA->currentMap()->background())));
	}
	else
	{
	      qWarning() << "Maphintergrund:" << GAMEDATA->currentMap()->background() << "nicht gefunden!";
	}
	
	if(!GAMEDATA->currentMap()->cityname().isEmpty())
	{
		GAMEDATA->setCurrentCity();
	}
	
	MapObject *MapObjectIterator = 0;
	QString filename;
	int role;
	foreach(MapObjectIterator, GAMEDATA->currentMap()->objectList())
	{
		filename = MapObjectIterator->fileName();
		role = MapObjectIterator->role();
		QFile pic(filename);
		if(pic.exists())
		{
			QGraphicsPixmapItem *gpi = szene->addPixmap((QPixmap(filename)));
			gpi->setPos(MapObjectIterator->position());
			gpi->setData(0, QVariant(role));
			gpi->setZValue(MapObjectIterator->zValue());
			if(!MapObjectIterator->toolTip().isEmpty())
			{
				gpi->setToolTip(MapObjectIterator->toolTip());
			}
			if(role >= 100 && role < 1000 )
			{ 
				landobjektliste << gpi;
			}
			qWarning() << filename << role << MapObjectIterator->position() << MapObjectIterator->toolTip();
		}
		else
			qWarning() << "pic.exists() == false!" << filename;
	}
	setScene(szene);
	setSceneRect(QRectF(QPoint(0,0), GAMEDATA->currentMap()->size()));

/*
	qWarning() << "Karteladen: " << mname;
	QDir dir;
	dir = QDir().current();
	QString wdir;
	if(dir.cd("maps"))
{
	wdir = dir.absolutePath();
// 	wdir.append("/maps");
	wdir.append("/");
	qWarning()  << "Working Direktory:" <<wdir;

	mname.prepend(wdir);



	qWarning() << "Wdir:" << wdir << "MName:" << mname;
}
else
{
qWarning() << "Mapdir does not exist. Exiting.";
}

	QGraphicsScene *tempsc = new QGraphicsScene;

	QFile file(mname);		//Map-XML-Lesen
	if(file.exists())
	{
	GAMEDATA->currentMap.filename = mname;

// 	QGraphicsScene *tempsc = new QGraphicsScene;
	setScene(tempsc);


	qWarning() << "Szene geloescht";


	szene = new QGraphicsScene();




		qWarning() << "Datei existiert" ;
		enum stati	{
				null,
				objekt,
				o_fkt,
				o_tooltip,
				o_datei,
				o_posx,
				o_posy,
				o_hoehe,
				m_prop,			// Allgemein: Mapeigenschaften
				m_stadtname,
				m_img,
				m_nord,			//noerdliche angrenzende Map
				m_west,			//westliche a M
				m_sued,			//suedliche a M
				m_ost,			//oestliche a M
				m_grx,			//breite
				m_gry,			//hoehe
				m_typ,
				} status = null;	// status als dieses enum: zeigt an, was fuer ein Wert als naechstes ausgelesen wird

		GAMEDATA->currentMap.cityname = QString();
		int ofkt = -1;				//Funktion des Objektes
		QString otooltip = QString();				//name/tooltip des objekts
		QString odatei = QString();				//name des Bildes des Objekts
		
		uhr = false;
		int oposx = -1;				//x-Koordinate
		int oposy = -1;				//y-Koordinate
		double ohoehe = 0;
		bool reading = true;

		file.open(QIODevice::ReadOnly | QIODevice::Text);
		QXmlStreamReader reader(&file);
		GAMEDATA->currentMap.isCity = false;
		while (reading) 
		{
		
		switch(reader.readNext())
		{
			case QXmlStreamReader::StartElement:
			{
			qWarning() << "\nStart:\t" <<reader.qualifiedName().toString();
				if(reader.qualifiedName().toString() =="mapproperties")
				{
// 				qWarning() << "Start: GAMEDATA->currentMap";
				status=m_prop;
				break;
				}
				if(reader.qualifiedName().toString() =="cityname")
				{
				status=m_stadtname;
				break;
				}
				if(reader.qualifiedName().toString() =="mapbackground")
				{
// 				qWarning() << "Start: GAMEDATA->currentMap";
				status=m_img;
				break;
				}
				if(reader.qualifiedName().toString() =="mapnorth")
				{
// 				qWarning() << "Start: GAMEDATA->currentMap";
				status=m_nord;
				break;
				}
				if(reader.qualifiedName().toString() =="mapeast")
				{
// 				qWarning() << "Start: GAMEDATA->currentMap";
				status=m_ost;
				break;
				}
				if(reader.qualifiedName().toString() =="mapsouth")
				{
// 				qWarning() << "Start: GAMEDATA->currentMap";
				status=m_sued;
				break;
				}
				if(reader.qualifiedName().toString() =="mapwest")
				{
// 				qWarning() << "Start: GAMEDATA->currentMap";
				status=m_west;
				break;
				}
				if(reader.qualifiedName().toString() =="mapwidth")
				{
// 				qWarning() << "Start: GAMEDATA->currentMap";
				status=m_grx;
				break;
				}
				if(reader.qualifiedName().toString() =="mapheight")
				{
// 				qWarning() << "Start: GAMEDATA->currentMap";
				status=m_gry;
				break;
				}

				if(reader.qualifiedName().toString() =="maptype")
				{
// 				qWarning() << "Start: GAMEDATA->currentMap";
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
// 				qWarning() << "o_fkt";
				status = o_fkt;
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
// 				qWarning() << "o_datei";
				status = o_datei;
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
				status = o_hoehe;
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
				case m_prop:
					break;
				case m_stadtname:
				{
// 					GAMEDATA->currentMap.cityname = reader.text().toString();
// 					GAMEDATA->currentMap.isCity = true;
					GAMEDATA->setCurrentCity(reader.text().toString());
				break;
				}
				case m_img:
				{
				GAMEDATA->currentMap.background = reader.text().toString();
				GAMEDATA->currentMap.background.prepend(wdir);
//  				GAMEDATA->currentMap.background.prepend(":");
 				QFile mapimgfile(GAMEDATA->currentMap.background);
 					if(mapimgfile.exists())
 					{
					szene->setBackgroundBrush(QBrush(QImage(GAMEDATA->currentMap.background)));
					}
					else
						qWarning() << "Maphintergrund:" << GAMEDATA->currentMap.background << "nicht gefunden!" << wdir;
				break;
				}

				case m_nord:
				{
				GAMEDATA->currentMap.mapnorth = reader.text().toString();

				qWarning() << "Nord-Map:" << GAMEDATA->currentMap.mapnorth;
				if(!QFile(GAMEDATA->currentMap.mapnorth).exists())
					{
					qWarning() << GAMEDATA->currentMap.mapnorth << "Existiert nicht";
					GAMEDATA->currentMap.mapnorth = QString();
					}
				break;
				}

				case m_ost:
				{
				GAMEDATA->currentMap.mapeast = reader.text().toString();
				qWarning() << "Ost-Map:" << GAMEDATA->currentMap.mapeast;
				if(!QFile(GAMEDATA->currentMap.mapeast).exists())
					{
					qWarning() << GAMEDATA->currentMap.mapeast << "Existiert nicht";
					GAMEDATA->currentMap.mapeast = QString();
					}
				break;
				}

				case m_sued:
				{
				GAMEDATA->currentMap.mapsouth = reader.text().toString();
				qWarning() << "Sued-Map:" << GAMEDATA->currentMap.mapsouth;
				if(!QFile(GAMEDATA->currentMap.mapsouth).exists())
					{
					qWarning() << GAMEDATA->currentMap.mapsouth << "Existiert nicht";
					GAMEDATA->currentMap.mapsouth = QString();
					}
				break;
				}

				case m_west:
				{
				GAMEDATA->currentMap.mapwest = reader.text().toString();
				qWarning() << "West-Map:" << GAMEDATA->currentMap.mapwest;
				if(!QFile(GAMEDATA->currentMap.mapwest).exists())
					{
					qWarning() << GAMEDATA->currentMap.mapwest << "Existiert nicht";
					GAMEDATA->currentMap.mapwest = QString();
					}
				break;
				}

				case m_grx:
				{
					GAMEDATA->currentMap.size.setWidth(reader.text().toString().toInt());
					break;
				}
				case m_gry:
				{
					GAMEDATA->currentMap.size.setHeight(reader.text().toString().toInt());
					break;
				}
				case m_typ:
				{
					GAMEDATA->currentMap.maptyp =
					  static_cast<MapType::mtyp>( reader.text().toString().toInt() );
					break;
	*//*				if(reader.text().toString().toInt() == 0)
					{
						GAMEDATA->currentMap.maptyp = MapType::sea;
					}
					if(reader.text().toString().toInt() == 1)
					{
						GAMEDATA->currentMap.maptyp = MapType::coast;
					}
					if(reader.text().toString().toInt() == 2)
					{
						GAMEDATA->currentMap.maptyp = MapType::land;
					}
					if(reader.text().toString().toInt() == 3)
					{
						GAMEDATA->currentMap.maptyp = MapType::coast_city;
					}
					if(reader.text().toString().toInt() == 4)
					{
						GAMEDATA->currentMap.maptyp = MapType::land_city;
					}*/
// 					if(reader.text().toString() == "sea")
// 					{
// 						GAMEDATA->currentMap.maptyp = sea;
// 					}
// 					if(reader.text().toString() == "coast")
// 					{
// 						GAMEDATA->currentMap.maptyp = coast;
// 					}
// 					if(reader.text().toString() == "land")
// 					{
// 						GAMEDATA->currentMap.maptyp = land;
// 					}
// 					GAMEDATA->currentMap.maptyp = reader.text().toString().toInt();
/*
				}

				case objekt:
					break;
				case o_fkt:
				{
					ofkt = reader.text().toString().toInt();
					qWarning() << "\tObjektfkt" << ofkt;
					break;
				}
				case o_tooltip:
				{
					otooltip = reader.text().toString();
					qWarning() << "\tObjekttooltip" << otooltip;
					break;
				}
				case o_datei:
				{
					odatei = reader.text().toString();
					qWarning() << "\tBild:" << odatei;
					break;
				}
				case o_posx:
				{
					oposx = reader.text().toString().toInt();
					qWarning() << "\tPosX:" << oposx;
					break;
				}
				case o_posy:
				{
					oposy = reader.text().toString().toInt();
					qWarning() << "\tPosY" << oposy;
					break;
				}
				case o_hoehe:
				{
					ohoehe = reader.text().toString().toDouble();
					qWarning() << "\tPosY" << oposy;
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
				if(reader.qualifiedName().toString() == "objekt" && ofkt != - 1 && !odatei.isEmpty())
	//jetzt zeichnen: habe alle Eigenschaften des Objektes erhalten?
				{
// 						if(!odatei.contains("img"))
// 						{ odatei.prepend(wdir);
// 						}
// 						else
// 							odatei.prepend(":");

					qWarning() << odatei << ofkt;
					odatei = odatei.prepend(wdir);
					QFile bild(odatei);
					if(bild.exists())
					{
// 						int static i;
						qWarning() << "Malen ....";
// #ifdef _RELEASE_
*//*						bool gemalt = false;
						if(ofkt == "Uhr")
						{
						uhr = true;
						QGraphicsItem *zb = szene->addPixmap((QPixmap(odatei)));
						zb->setPos(oposx,oposy);
						zb->setToolTip(otooltip);
						zb->setZValue(0.5);
						zb->setData(0,QVariant(QString("Ziffernblatt")));
						QGraphicsItem *gz = szene-> addPixmap((QPixmap(":/img/objekte/zeiger1.png")));
						gz->setPos(oposx+21,oposy+4);
						gz->setToolTip(tr("grosser Zeiger"));
						gz->setZValue(2);
						gz->setData(0,QVariant(QString("grosser Zeiger")));

						QGraphicsItem *kz = szene-> addPixmap( (QPixmap(":/img/objekte/zeiger2.png")));
						kz->setPos(oposx+23,oposy+9);
						kz->setToolTip(tr("kleiner Zeiger"));
						kz->setZValue(1);
						kz->setData(0,QVariant(QString("kleiner Zeiger")));
						gemalt = true;
						}


						if(!gemalt)
						{*/
						///*******************************************************////
						/*
						QGraphicsPixmapItem *geb = szene->addPixmap((QPixmap(odatei)));
						geb->setPos(oposx,oposy);
						geb->setData(0,QVariant(ofkt));
						geb->setZValue(ohoehe);

						

						if(!otooltip.isEmpty())
						{
							geb->setToolTip(otooltip);
						}

                                                if(ofkt >= 100 && ofkt < 1000 )
                                                { 
							landobjektliste << geb;
                                                }


						ofkt = -1;
						otooltip = QString();
						odatei = QString();
// 						}
					}
					else
					{
					qWarning() << "Bild" << odatei << "nicht gefunden. (Objekt: "<< ofkt << otooltip << " ).";

					odatei = QString();
					ofkt = -1;
					otooltip = QString();
					}
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
	
		if (reader.hasError()) {
		qWarning() << reader.errorString();
	}
}
// 	else
// {
// qWarning() << file.fileName() << "not found!";
// #ifndef _RELEASE_
// 	close();
// 	return;
// #endif
// }
// 	if(GAMEDATA->currentMap.maptyp == sea)
// 	{

// 	}
// 	if(GAMEDATA->currentMap.maptyp == coast)
// 	{
// 	QString mhfname = QString("kollisionskarte.png").prepend(wdir);
// 	QFile mhifile (mhfname);
// 	if(mhifile.exists())
// 	{
// 	qWarning() << mhfname << "vorhanden";
// 	maphandlingimg = QImage(mhfname);
// // 	qWarning() << QString("kollissionskarte.png").prepend(wdir);
// 	GAMEDATA->currentMap.breite =  maphandlingimg.width() * 5;
// 	GAMEDATA->currentMap.hoehe = maphandlingimg.height() * 5;
// // 	setSceneRect(0, 0, maphandlingimg.width() * 5, maphandlingimg.height() * 5);
// 	setSceneRect(0,0,GAMEDATA->currentMap.breite,GAMEDATA->currentMap.hoehe);
// 	qWarning() << "Breite:" << GAMEDATA->currentMap.breite << "Hoehe:" << GAMEDATA->currentMap.hoehe;
// 	}
// 	else
// 	qWarning() << mhfname << "not found";
// 	}
							///	GAMEDATA->currentMap.mapname = mname;
*/


	if(GAMEDATA->anbord())
{
QGraphicsPixmapItem *testschiff;
// 	qWarning() << GAMEDATA->active_ship->filename;
	testschiff = szene->addPixmap(QPixmap(":img/schiffe/schiff_gerade_skaliert2.png"));
	testschiff->setZValue(0.1);
	
	activeship_model = new ObjectGraphicsItem(GAMEDATA->activeShip());
	activeship_model->addMemberItem(testschiff,QPointF(0,0));
	activeship_model->rotateItem();
	szene->addItem(activeship_model);
	
	PositioningStruct destination_pos;
	destination_pos.mapcoords = GAMEDATA->currentMap()->coordinates();
	switch(orientation)
	{
		case Map::North:
		{
			destination_pos.generic_position = QPoint(GAMEDATA->activeShip()->currentPosition().generic_position.x(), GAMEDATA->currentMap()->size().height() - 50);
			break;
		}
		case Map::East:
		{
			destination_pos.generic_position = QPoint(30, GAMEDATA->activeShip()->currentPosition().generic_position.y());
			break;
		}
		case Map::South:
		{
			destination_pos.generic_position = QPoint(GAMEDATA->activeShip()->currentPosition().generic_position.x(), 0);
			break;
		}
		case Map::West:
		{
			destination_pos.generic_position = QPoint(GAMEDATA->currentMap()->size().width() -30, GAMEDATA->activeShip()->currentPosition().generic_position.y());
			break;
		}
		default:
		{
			destination_pos = GAMEDATA->activeShip()->currentPosition();
			break;
		}
	}
	GAMEDATA->activeShip()->setPos(destination_pos);
	centerOn(activeship_model);

// 	ShipData blah2;
// 	ObjectGraphicsItem blah = new QGraphicsItem();
// 	ObjectGraphicsItem;
	
// 	testschiff->setPos(1500,700);
// 	QTransform t;
// 	const int w = active_ship;
// 	const int h = testschiff->boundingRect().height()/2;
// 
// 	t.translate( w, h );
// 	t.rotateRadians(-GAMEDATA->active_ship.ret_Dir());
// 	t.translate( -w, -h );
// 	testschiff->setTransform( t );
// 	active_ship.schiffbreite = testschiff->boundingRect().width();
// 	active_ship.schifflange = testschiff->boundingRect().height();

// 	active_ship.attribute.map = GAMEDATA->currentMap.mapname;
// 	active_ship.attribute.stadt = GAMEDATA->currentMap.stadtname;
	
	qWarning() << GAMEDATA->currentMap()->type();
	if(GAMEDATA->currentMap()->type() == Map::coast || GAMEDATA->currentMap()->type() == Map::coast_city)
	{
	emit sig_anlegbar(true);
// 	qWarning() << "anlegbar";
	}
	else if(GAMEDATA->currentMap()->type() == Map::sea)
	{
	emit sig_anlegbar(false);
// 	qWarning() << "nicht anlegbar";
	}
}



	wolkenliste.clear();
// 	QImage img = QImage(":img/maps/coast02.gif");

// 	for(int j = 0; j< 240; j++)
// {
// 	for(int i = 0; i < 200; i++)
// 	{
// 	wolke = szene->addPixmap(QPixmap(":img/maps/blau_25.png"));
// 	wolke->setPos(j*25, i*25);
// 	wolke->setZValue(-1);
// 	}
// 
// }
// qWarning()<< "MLoad: WL: Eintraege" << wolkenliste.size();
///qWarning() << "Wolken malen";
	int wolkenzahl = rand()%25;
// 	int wolkenzahl=10;
	for(int i=0;i<wolkenzahl;i++)
	{
	int a = rand()%2;
	if(a==1)
	{
	wolke = szene->addPixmap(QPixmap(":img/objekte/wolke01.png"));
	}
	else
	{
	wolke = szene->addPixmap(QPixmap(":img/objekte/wolke04.png"));
	}
	wolke->setPos(rand()%3300+500,rand()%2300+400);
	wolke->setZValue(10);
	wolkenliste << wolke;

// 	wolken[i] = szene->addPixmap(QPixmap(":img/objekte/wolke01.png"));
// 	wolken[i]->setPos(rand()%3300+500,rand()%2300+400);
	}
	qWarning()<< "MloadEnde: WL: Eintraege" << wolkenliste.size();
	
	/*
	setScene(szene);
	qWarning() << GAMEDATA->currentMap.size;
	setSceneRect(0,0,GAMEDATA->currentMap.size.width(), GAMEDATA->currentMap.size.height() );
// if(GAMEDATA->anbord)
// {
// 	centerOn(GAMEDATA->active_ship->graphicsitem);
// }
	tempsc->deleteLater();*/

// maphandlingimg= QImage(":img/testimg/gros.gif");
}
