/***************************************************************************
 *   Copyright (C) 2009 by Christian Doerffel                              *
 *   schdorm@googlemail.com                                     *
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

#include "gesamtbild.h"
#include "zeit.h"

#include <QtCore/QFile>
#include <QtCore/QDir>


#include <QtGui/QLineEdit>
#include <QtGui/QGridLayout>

#include <QtDebug>


void gesamtbild::speicherndialog()
{
	aktiv=false;
	hf->startPause();
	hf->setEnabled(false);
	menupanel->setEnabled(false);

	QDir dir = QDir().current();
	if(!dir.cd("save"))
	{
		dir.mkdir("save");
		dir.cd("save");
	}

	rahmen = new QFrame(this);
	rahmen->setBackgroundRole(QPalette::Midlight);
	rahmen->setAutoFillBackground(true);
	rahmen->setGeometry(200,200,600,500);
	rahmen->setFrameShape(QFrame::Panel);
	rahmen->setFrameShadow(QFrame::Sunken);
	rahmen->setLineWidth(5);

	okbutton = new QPushButton(tr("Ok"),rahmen);
	connect(okbutton, SIGNAL(clicked()), this, SLOT(speichern()));
	connect(okbutton, SIGNAL(clicked()), rahmen, SLOT(deleteLater()));

	QPushButton *back = new QPushButton(QIcon(":img/icons/rotkreuz_alpha01.png"),QString(), rahmen);
// 	back->move(600,400);
	connect(back,SIGNAL(clicked()),this,SLOT(aktivieren()));
	connect(back,SIGNAL(clicked()),rahmen,SLOT(deleteLater()));

	QLineEdit *name = new QLineEdit(rahmen);

	connect(name,SIGNAL(textChanged(QString)),this,SLOT(speichername(QString)));
	connect(name,SIGNAL(returnPressed()),rahmen,SLOT(close()));
	connect(name,SIGNAL(returnPressed()),rahmen,SLOT(deleteLater()));
	connect(name,SIGNAL(returnPressed()),this,SLOT(speichern()));

	QListWidget *liste = new QListWidget(rahmen);
	liste->setSelectionMode(QAbstractItemView::SingleSelection);
	liste->addItems(dir.entryList( QStringList("*.ohs"), QDir::Files | QDir::NoDotAndDotDot));
	liste->resize(400, 450);

	connect(liste,SIGNAL(itemDoubleClicked(QListWidgetItem *)),rahmen,SLOT(close()));
	connect(liste,SIGNAL(itemDoubleClicked(QListWidgetItem *)),rahmen,SLOT(deleteLater()));
	connect(liste,SIGNAL(itemDoubleClicked(QListWidgetItem*)), this,SLOT(speichern(QListWidgetItem*)));
	connect(liste, SIGNAL(currentTextChanged(QString)), name,SLOT(setText(QString)));


// filename = QString();
	QGridLayout layout(rahmen);
	layout.addWidget(name,0,0,1,1);
	layout.addWidget(liste,1,0,1,1);
	layout.addWidget(okbutton, 0, 1, 1, 1);
	layout.addWidget(back, 1, 1, 1, 1);
	layout.setColumnStretch(0,6);
	layout.setColumnStretch(1,1);


	rahmen->setLayout(&layout);
	speichername(QString());
	rahmen->show();
	rahmen->raise();
}

void gesamtbild::speichername(QString fn)
{
filename = fn;
if(!filename.isEmpty() && !okbutton->isEnabled())
{
okbutton->setEnabled(true);
}
if(filename.isEmpty() && okbutton->isEnabled())
{
okbutton->setEnabled(false);
}
}

void gesamtbild::speichern(QListWidgetItem *item)
{
filename = item->text();
speichern();
}

void gesamtbild::speichern()
{

	QDir dir = QDir().current();
	
// 	qWarning() << dir;
	if(!dir.cd("save"))
	{
		qWarning() << "Verzeichnis erstellen ...";
		dir.mkdir("save");
// 		dir.mkdir();
	}
	if(!filename.endsWith(".ohs"))
	{
	filename.append(".ohs");
	}
	QFile savefile(filename.prepend("save/"));
	savefile.open(QIODevice::WriteOnly);
	QTextStream savestream(&savefile);

	savestream << _oh_version << "\n";
	savestream << hf->durchlauf << "\n";
	savestream << hf->schwierigkeit << "\n";
	savestream << gamedata->gametime.retMinute() << "\n";
	savestream << gamedata->gametime.retHour() << "\n";
	savestream << gamedata->gametime.retDay() << "\n";		//5. Zeile
	savestream << gamedata->gametime.retMonth() << "\n";
	savestream << gamedata->gametime.retYear() << "\n";
	savestream << gamedata->gametime.retDayLength() << "\n";

	savestream << gamedata->wind.retV() << "\n";
	savestream << gamedata->wind.retDir() << "\n";
// 	savestream << gamedata->active_ship->id << "\n";

	savestream << gamedata->anbord << "\n";	// 10. Zeile + 1
	savestream << gamedata->currentMap.cityname << "\n";
	savestream << gamedata->currentMap.filename << "\n";
// 	savestream << gamedata->currentMap.hintergrund << "\n";
// 	savestream << gamedata->currentMap.handlingimg << "\n";
// 	savestream << gamedata->currentMap.hoehe << "\n";
// 	savestream << gamedata->currentMap.breite << "\n";
// 	savestream << gamedata->currentMap.mapnord << "\n";
// 	savestream << gamedata->currentMap.mapost << "\n";
// 	savestream << gamedata->currentMap.mapsued << "\n";
// 	savestream << gamedata->currentMap.mapwest << "\n";


	CityClass *savecity;
	QList <CityClass> citylist = gamedata->ret_CityList();
	foreach(*savecity, citylist)
	{
		savestream << "<stadt>" << "\n";
		savestream << savecity->cityname << "\n";
		savestream << savecity->inhabitants << "\n";
		for(int i = 0; i < const_warenanzahl; i++)
		{
			savestream << savecity->goods.ware[i] << "\n";
			if(i<5)
			{
			savestream << savecity->hproduction[i] << "\n";
			savestream << savecity->mproduction[i] << "\n";
			savestream << savecity->lproduction[i] << "\n";
			}
		}
		savestream << savecity->goods.taler << "\n";
		savestream << savecity->goods.kapazitaet << "\n";
		savestream << "</stadt>" << "\n";
	}

	ShipClass *saveship;
	QList <ShipClass> shiplist = gamedata->ret_ShipList();
	shiplist << *gamedata->active_ship;
	foreach(*saveship, shiplist)
	{
		savestream << "<schiff>" << "\n";
		savestream << saveship->id << "\n";
		savestream << saveship->schiffsname << "\n";/*
		savestream << saveship->attribute.xpos << "\n";
		savestream << saveship->attribute.ypos << "\n";
		savestream << saveship->attribute.map << "\n";
		savestream << saveship->attribute.geschwindigkeit << "\n";
		savestream << saveship->attribute.ausrichtung << "\n";
		savestream << saveship->attribute.prozentgesetzteSegel << "\n";
		savestream << saveship->attribute.sollprozentgesetzteSegel << "\n";
		savestream << saveship->attribute.steuergeschwindigkeit << "\n";
		savestream << saveship->attribute.steuerruderausrichtung << "\n";
		savestream << saveship->attribute.sollsteuerruderausrichtung << "\n";
		savestream << saveship->attribute.segelausrichtung << "\n";*/
		for(int i = 0; i < const_warenanzahl; i++)
		{
		savestream << saveship->cargo.ware[i] << "\n";
		}
		savestream << saveship->cargo.taler << "\n";
		savestream << saveship->cargo.fuellung << "\n";
		savestream << saveship->cargo.kapazitaet << "\n";
		savestream << "</schiff>" << "\n";
	}
	shiplist.removeLast();
	KontorClass *savekontor;
	QList<KontorClass> kontorlist = gamedata->ret_KontorList();
	foreach(*savekontor, kontorlist)
	{
		savestream << "<kontor>" << "\n";
		savestream << savekontor->ret_ID() << "\n";
		savestream << savekontor->ret_CityID() << "\n";
			for(int i = 0; i < const_warenanzahl; i++)
			{
				savestream << savekontor->storage.ware[i] << "\n";
				savestream << savekontor->production.ware[i];
			}
		savestream << savekontor->storage.taler << "\n";
		savestream << savekontor->storage.fuellung << "\n";
		savestream << savekontor->storage.kapazitaet << "\n";
		savestream << "</kontor>" << "\n";
	}


// 	savestream << gamedata->active_ship->id;

	savefile.close();
qWarning() << "Nach " << filename << "gespeichert(" << dir.path() << ")" ;

							//muesste man mal mit der const-var belegen ...
hf->endePause();
aktiv=true;
}


void gesamtbild::laden(QListWidgetItem *spielstand)
{
// aktiv=false;
// load = true;

// QWidget *ladefenster = new QWidget(this);
// ladefenster->resize(width(), height());
// ladefenster->setBackgroundRole(QPalette::Window);
// ladefenster->setAutoFillBackground(true);
// ladefenster->show();
// spielfensteraufbau();
gamedata = new DataClass();
hf = new hauptfenster(gamedata);
// ladefenster->raise();
filename = spielstand->text();
qWarning() << "Lade Spielstand:" <<filename;
if(filename.endsWith(".ohs"))
{
filename.prepend("save/");
// enum lesetyp{null, stadt, gebaude, schiff, eof}typ = null;
QString typindikator, stringbuffer;
QFile loadfile(filename);
loadfile.open(QIODevice::ReadOnly);
QTextStream loadstream(&loadfile);

	stringbuffer = loadstream.readLine();
	if(stringbuffer.toInt() == _oh_version)
	{
	hf->durchlauf = loadstream.readLine().toInt();	/*qWarning()<< "Durchlauf"<<hf->durchlauf;*/
	hf->schwierigkeit = loadstream.readLine().toInt();
	gamedata->gametime.setMinute(loadstream.readLine().toFloat());
	gamedata->gametime.setHour(loadstream.readLine().toInt());
	gamedata->gametime.setDay(loadstream.readLine().toInt());	//5. Zeile
	gamedata->gametime.setMonth(loadstream.readLine().toInt());
	gamedata->gametime.setYear(loadstream.readLine().toInt());
	gamedata->gametime.setDayLength(loadstream.readLine().toInt());
	gamedata->wind.setV( loadstream.readLine().toInt());
// qWarning() << "WV"<<gamedata->windgeschwindigkeit;

// 	loadstream >> gamedata->windrichtung ;
	gamedata->wind.setDir(loadstream.readLine().toFloat());
// 	= loadstream.readLine();
// 	gamedata->active_ship->id = loadstream.readLine().toInt();

	QString anbord = loadstream.readLine();		// 10. Zeile + 1
	if(anbord == "0")
	{
		gamedata->anbord = false;
	}
	else
	{
		gamedata->anbord = true;
	}
	qWarning() << "Anbord: " << anbord << gamedata->anbord;
	gamedata->currentMap.cityname = loadstream.readLine();
// 	gamedata->currentMap.mapname = loadstream.readLine();
// 	gamedata->currentMap.hintergrund = loadstream.readLine();
// 	gamedata->currentMap.handlingimg = loadstream.readLine();
// 	gamedata->currentMap.hoehe = loadstream.readLine().toInt();
// 	gamedata->currentMap.breite = loadstream.readLine().toInt();
// 	gamedata->currentMap.mapnord = loadstream.readLine();
// 	gamedata->currentMap.mapost = loadstream.readLine();
// 	gamedata->currentMap.mapsued = loadstream.readLine();
// 	gamedata->currentMap.mapwest = loadstream.readLine();

	hf->karteladen(gamedata->currentMap.filename);


	CityClass loadcity;
// 	foreach(savecity, stadtliste)
// 	loadstream >> typindikator;
	typindikator = loadstream.readLine();
// 	qWarning() << "Typindikator" << typindikator;
	while(typindikator == "<stadt>")
	{
// 		loadstream >> "<stadt>" ;
		loadcity.init();
		loadcity.cityname = loadstream.readLine();
		loadcity.inhabitants = loadstream.readLine().toInt();
		for(int i = 0; i < const_warenanzahl; i++)
		{
			loadcity.goods.ware[i] = loadstream.readLine().toInt();
			if(i<5)
			{
				loadcity.hproduction[i] = loadstream.readLine().toInt();
				loadcity.mproduction[i] = loadstream.readLine().toInt();
				loadcity.lproduction[i] = loadstream.readLine().toInt();
			}
		}
		loadcity.goods.taler = loadstream.readLine().toInt();
// 		loadcity..kapazitaet = loadstream.readLine().toInt();
		stringbuffer = loadstream.readLine();
// 						 	qWarning() << "\n\tStringbuffer:" << stringbuffer;
		gamedata->addCity(&loadcity);
		typindikator = loadstream.readLine();
// 		qWarning() << "Typindikator" << typindikator << stadtliste.size();

	}

	ShipClass loadship;
	while(typindikator == "<schiff>")
	{
		loadship.id = loadstream.readLine().toInt();	/*qWarning() << "ID"<<loadship.id;*/
		loadship.schiffsname = loadstream.readLine();
// 		loadship.attribute.xpos = loadstream.readLine().toInt();
// 		loadship.attribute.ypos = loadstream.readLine().toInt();
// 		loadship.attribute.map = loadstream.readLine();	
// 		loadship.attribute.geschwindigkeit = loadstream.readLine().toInt();
// 		loadship.attribute.ausrichtung = loadstream.readLine().toFloat();
// 		loadship.attribute.prozentgesetzteSegel = loadstream.readLine().toFloat();
// 		loadship.attribute.sollprozentgesetzteSegel = loadstream.readLine().toFloat();
// 		loadship.attribute.steuergeschwindigkeit = loadstream.readLine().toInt();
// 		loadship.attribute.steuerruderausrichtung = loadstream.readLine().toFloat();
// 		loadship.attribute.sollsteuerruderausrichtung = loadstream.readLine().toFloat();
// 		loadship.attribute.segelausrichtung = loadstream.readLine().toFloat();
		for(int i = 0; i < const_warenanzahl; i++)
		{
			loadship.cargo.ware[i] = loadstream.readLine().toUShort();
// 			qWarning() << "Ware"<<i <<loadship.cargo.ware[i];
		}
		loadship.cargo.taler = loadstream.readLine().toInt();
		loadship.cargo.fuellung = loadstream.readLine().toInt();
		loadship.cargo.kapazitaet = loadstream.readLine().toInt();
		stringbuffer = loadstream.readLine();
		gamedata->addShip(&loadship);
		typindikator = loadstream.readLine();
	}
/*	gamedata->active_ship->id = loadstream.readLine().toInt();*/
// 	qWarning() << "Schiff belegt" << gamedata->active_ship->id << loadship.id ;
	gamedata->active_ship = &loadship;
	KontorClass loadkontor;
	while(typindikator == "<kontor>")
	{
// 		loadkontor.id = loadstream.readLine().toInt();
// 		loadkontor.cityID = loadstream.readLine().toInt();

		for(int i = 0; i < const_warenanzahl; i++)
		{
			loadkontor.storage.ware[i] = loadstream.readLine().toInt();
		}
		loadkontor.storage.taler = loadstream.readLine().toInt();
		loadkontor.storage.fuellung = loadstream.readLine().toInt();
		loadkontor.storage.kapazitaet = loadstream.readLine().toInt();
		stringbuffer = loadstream.readLine();
		gamedata->addKontor(&loadkontor);
		typindikator = loadstream.readLine();

	}
	spielfensteraufbau();
// 	qWarning() << "Map" << loadship.attribute.map;
// 	qWarning() << "SV:"<< loadship.attribute.geschwindigkeit;
/// 	gamedata->active_ship->graphicsitem->setPos();
// 	hf->testschiff->setPos(gamedata->active_ship->attribute.xpos, gamedata->active_ship->attribute.ypos);
// 	hf->testschiff->setPos(300,300);
// 	qWarning() << "Ausrichtung:"<< gamedata->active_ship->attribute.ausrichtung << "XPos" << gamedata->active_ship->attribute.xpos << "YPos" << gamedata->active_ship->attribute.ypos;
/// Wichtig: ....
/*	if(hf->anbord)
	{
	QTransform t;
	const int w = hf->testschiff->boundingRect().width()/2;
	const int h = hf->testschiff->boundingRect().height()/2;

	gamedata->active_ship->schiffbreite = 2 * w;
	gamedata->active_ship->schifflange = 2 * h;

	t.translate( w, h );
	t.rotateRadians(- gamedata->active_ship->attribute.ausrichtung);
	t.translate( -w, -h );
	hf->testschiff->setTransform( t );

	hf->show();
	hf->centerOn(hf->testschiff);
	hf->starttimer();
	}*/
// 	}
	hf->starttimer();

// ladefenster->close();
aktiv=true;
}
loadfile.close();


}
}


void gesamtbild::lademenu()
{
	for(int i = 0; i<10; i++)
	{
	qWarning() << "\n";
	}
	filename=QString();

	qWarning() << "Lademenu";
// 	QWidget *lademenu = new QWidget(this);
// 	lademenu->resize(1024,768);

	QDir dir = QDir().current();
	if(!dir.cd("save"))
	{
		dir.mkdir("save");
		dir.cd("save");
// 		rahmen = new QFrame(this);
// 		qWarning() << "kein gespeichertes Spiel!";
// 		QLabel *info = new QLabel(tr("Keine gespeicherten Spielstaende vorhanden!"),rahmen);
// 		info->move(300,300);
// 		QPushButton *back = new QPushButton(tr("Zurueck"),rahmen);
// 		rahmen->show();
// 		connect(back,SIGNAL(clicked()),this,SLOT(hauptmenu()));
// 		connect(back,SIGNAL(clicked()),rahmen,SLOT(deleteLater()));

	}
	
	{
		rahmen = new QFrame(this);

		QPushButton *back = new QPushButton(tr("Zurueck"),rahmen);

		back->move(600,400);
		connect(back,SIGNAL(clicked()),this,SLOT(hauptmenu()));
		connect(back,SIGNAL(clicked()),rahmen,SLOT(deleteLater()));

		QListWidget *liste = new QListWidget(rahmen);
		liste->setSelectionMode(QAbstractItemView::SingleSelection);
		liste->addItems(dir.entryList( QStringList("*.ohs"), QDir::Files | QDir::NoDotAndDotDot));
		liste->setGeometry(width()/8, 50, 400, 650);
// 		liste->show();
		connect(liste,SIGNAL(itemDoubleClicked(QListWidgetItem *)),rahmen,SLOT(close()));
		connect(liste,SIGNAL(itemDoubleClicked(QListWidgetItem *)),rahmen,SLOT(deleteLater()));
		connect(liste,SIGNAL(itemDoubleClicked(QListWidgetItem*)), this,SLOT(laden(QListWidgetItem*)));
		rahmen->show();
	}
// 	liste->move(width()/5, 50);
// 	liste->resize();


// 	lademenu->show();
}