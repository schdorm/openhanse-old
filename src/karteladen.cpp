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

#include <QtGui/QGraphicsScene>

#include <QtCore/QFile>
#include <QtCore/QXmlStreamReader>


#include <QtDebug>
#include <QtCore/QDir>
#include <QtCore/QVariant>

void hauptfenster::karteladen(QString mname)
{
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
	gamedata->currentMap.filename = mname;

// 	QGraphicsScene *tempsc = new QGraphicsScene;
	setScene(tempsc);

	szene->clear();
	delete szene;
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

		gamedata->currentMap.cityname = QString();
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
		gamedata->currentMap.isCity = false;
		while (reading) 
		{
		
		switch(reader.readNext())
		{
			case QXmlStreamReader::StartElement:
			{
			qWarning() << "\nStart:\t" <<reader.qualifiedName().toString();
				if(reader.qualifiedName().toString() =="mapproperties")
				{
// 				qWarning() << "Start: gamedata->currentMap";
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
				status=m_grx;
				break;
				}
				if(reader.qualifiedName().toString() =="mapheight")
				{
// 				qWarning() << "Start: gamedata->currentMap";
				status=m_gry;
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
// 					gamedata->currentMap.cityname = reader.text().toString();
// 					gamedata->currentMap.isCity = true;
					gamedata->setCurrentCity(reader.text().toString());
				break;
				}
				case m_img:
				{
				gamedata->currentMap.background = reader.text().toString();
				gamedata->currentMap.background.prepend(wdir);
//  				gamedata->currentMap.background.prepend(":");
 				QFile mapimgfile(gamedata->currentMap.background);
 					if(mapimgfile.exists())
 					{
					szene->setBackgroundBrush(QBrush(QImage(gamedata->currentMap.background)));
					}
					else
						qWarning() << "Maphintergrund:" << gamedata->currentMap.background << "nicht gefunden!" << wdir;
				break;
				}

				case m_nord:
				{
				gamedata->currentMap.mapnorth = reader.text().toString();

				qWarning() << "Nord-Map:" << gamedata->currentMap.mapnorth;
				if(!QFile(gamedata->currentMap.mapnorth).exists())
					{
					qWarning() << gamedata->currentMap.mapnorth << "Existiert nicht";
					gamedata->currentMap.mapnorth = QString();
					}
				break;
				}

				case m_ost:
				{
				gamedata->currentMap.mapeast = reader.text().toString();
				qWarning() << "Ost-Map:" << gamedata->currentMap.mapeast;
				if(!QFile(gamedata->currentMap.mapeast).exists())
					{
					qWarning() << gamedata->currentMap.mapeast << "Existiert nicht";
					gamedata->currentMap.mapeast = QString();
					}
				break;
				}

				case m_sued:
				{
				gamedata->currentMap.mapsouth = reader.text().toString();
				qWarning() << "Sued-Map:" << gamedata->currentMap.mapsouth;
				if(!QFile(gamedata->currentMap.mapsouth).exists())
					{
					qWarning() << gamedata->currentMap.mapsouth << "Existiert nicht";
					gamedata->currentMap.mapsouth = QString();
					}
				break;
				}

				case m_west:
				{
				gamedata->currentMap.mapwest = reader.text().toString();
				qWarning() << "West-Map:" << gamedata->currentMap.mapwest;
				if(!QFile(gamedata->currentMap.mapwest).exists())
					{
					qWarning() << gamedata->currentMap.mapwest << "Existiert nicht";
					gamedata->currentMap.mapwest = QString();
					}
				break;
				}

				case m_grx:
				{
					gamedata->currentMap.size.setWidth(reader.text().toString().toInt());
					break;
				}
				case m_gry:
				{
					gamedata->currentMap.size.setHeight(reader.text().toString().toInt());
					break;
				}
				case m_typ:
				{
					gamedata->currentMap.maptyp =
					  static_cast<MapType::mtyp>( reader.text().toString().toInt() );
					break;
	/*				if(reader.text().toString().toInt() == 0)
					{
						gamedata->currentMap.maptyp = MapType::sea;
					}
					if(reader.text().toString().toInt() == 1)
					{
						gamedata->currentMap.maptyp = MapType::coast;
					}
					if(reader.text().toString().toInt() == 2)
					{
						gamedata->currentMap.maptyp = MapType::land;
					}
					if(reader.text().toString().toInt() == 3)
					{
						gamedata->currentMap.maptyp = MapType::coast_city;
					}
					if(reader.text().toString().toInt() == 4)
					{
						gamedata->currentMap.maptyp = MapType::land_city;
					}*/
// 					if(reader.text().toString() == "sea")
// 					{
// 						gamedata->currentMap.maptyp = sea;
// 					}
// 					if(reader.text().toString() == "coast")
// 					{
// 						gamedata->currentMap.maptyp = coast;
// 					}
// 					if(reader.text().toString() == "land")
// 					{
// 						gamedata->currentMap.maptyp = land;
// 					}
// 					gamedata->currentMap.maptyp = reader.text().toString().toInt();

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
/*						bool gemalt = false;
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
// 	setSceneRect(0,0,2000,3000);
// 	if(gamedata->currentMap.maptyp == sea)
// 	{
	qWarning() << gamedata->currentMap.size;
	setSceneRect(0,0,gamedata->currentMap.size.width(), gamedata->currentMap.size.height() );
// 	}
// 	if(gamedata->currentMap.maptyp == coast)
// 	{
// 	QString mhfname = QString("kollisionskarte.png").prepend(wdir);
// 	QFile mhifile (mhfname);
// 	if(mhifile.exists())
// 	{
// 	qWarning() << mhfname << "vorhanden";
// 	maphandlingimg = QImage(mhfname);
// // 	qWarning() << QString("kollissionskarte.png").prepend(wdir);
// 	gamedata->currentMap.breite =  maphandlingimg.width() * 5;
// 	gamedata->currentMap.hoehe = maphandlingimg.height() * 5;
// // 	setSceneRect(0, 0, maphandlingimg.width() * 5, maphandlingimg.height() * 5);
// 	setSceneRect(0,0,gamedata->currentMap.breite,gamedata->currentMap.hoehe);
// 	qWarning() << "Breite:" << gamedata->currentMap.breite << "Hoehe:" << gamedata->currentMap.hoehe;
// 	}
// 	else
// 	qWarning() << mhfname << "not found";
// 	}
// 	gamedata->currentMap.hoehe = maphandlingimg.height();
// 	gamedata->currentMap.breite = maphandlingimg.width();
							///	gamedata->currentMap.mapname = mname;
// 	setSceneRect(20,20,gamedata->currentMap.breite-40, gamedata->currentMap.hoehe-40);



	if(gamedata->anbord)
{
QGraphicsPixmapItem *testschiff;
	qWarning() << gamedata->active_ship->filename;
	testschiff = szene->addPixmap(QPixmap(gamedata->active_ship->filename));
	testschiff->setZValue(0.1);
	gamedata->active_ship->setGraphicsItem(testschiff);
	gamedata->active_ship->rotateGraphics();
// 	testschiff->setPos(1500,700);
// 	QTransform t;
// 	const int w = active_ship;
// 	const int h = testschiff->boundingRect().height()/2;
// 
// 	t.translate( w, h );
// 	t.rotateRadians(-gamedata->active_ship.ret_Dir());
// 	t.translate( -w, -h );
// 	testschiff->setTransform( t );
// 	active_ship.schiffbreite = testschiff->boundingRect().width();
// 	active_ship.schifflange = testschiff->boundingRect().height();

// 	active_ship.attribute.map = gamedata->currentMap.mapname;
// 	active_ship.attribute.stadt = gamedata->currentMap.stadtname;
	
	qWarning() << gamedata->currentMap.maptyp;
	if(gamedata->currentMap.maptyp == MapType::coast || gamedata->currentMap.maptyp == MapType::coast_city)
	{
	emit sig_anlegbar(true);
// 	qWarning() << "anlegbar";
	}
	else if(gamedata->currentMap.maptyp == MapType::sea)
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
	
	
	setScene(szene);
if(gamedata->anbord)
{
	centerOn(gamedata->active_ship->graphicsitem);
}
	tempsc->deleteLater();

// maphandlingimg= QImage(":img/testimg/gros.gif");
}
