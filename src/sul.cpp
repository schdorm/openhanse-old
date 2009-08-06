/***************************************************************************
 *   Copyright (C) 2009 by Christian Doerffel   *
 *   christian.doerffel@googlemail.com   *
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
	savestream << hf->minute << "\n";
	savestream << hf->stunde << "\n";
	savestream << hf->tag << "\n";		//5. Zeile
	savestream << hf->jahr << "\n";
	savestream << hf->tageslaenge << "\n";

	savestream << hf->windgeschwindigkeit << "\n";
	savestream << hf->windrichtung << "\n";
// 	savestream << hf->activeship.id << "\n";

	savestream << hf->anbord << "\n";	// 10. Zeile
	savestream << hf->mapprops.stadtname << "\n";
	savestream << hf->mapprops.mapname << "\n";
// 	savestream << hf->mapprops.hintergrund << "\n";
// 	savestream << hf->mapprops.handlingimg << "\n";
// 	savestream << hf->mapprops.hoehe << "\n";
// 	savestream << hf->mapprops.breite << "\n";
// 	savestream << hf->mapprops.mapnord << "\n";
// 	savestream << hf->mapprops.mapost << "\n";
// 	savestream << hf->mapprops.mapsued << "\n";
// 	savestream << hf->mapprops.mapwest << "\n";


	stadtklasse savestadt;
	foreach(savestadt, stadtliste)
	{
		savestream << "<stadt>" << "\n";
		savestream << savestadt.stadtname << "\n";
		savestream << savestadt.stadtbewohner << "\n";
		for(int i = 0; i < const_warenanzahl; i++)
		{
			savestream << savestadt.stadtwaren.ware[i] << "\n";
			if(i<5)
			{
			savestream << stadt.hproduktion[i] << "\n";
			savestream << stadt.mproduktion[i] << "\n";
			savestream << stadt.nproduktion[i] << "\n";
			}
		}
		savestream << savestadt.stadtwaren.taler << "\n";
		savestream << savestadt.stadtwaren.kapazitaet << "\n";
		savestream << "</stadt>" << "\n";
	}
	schiffsliste << hf->activeship;
	schiffsklasse saveship;
	foreach(saveship, schiffsliste)
	{
		savestream << "<schiff>" << "\n";
		savestream << saveship.id << "\n";
		savestream << saveship.schiffsname << "\n";
		savestream << saveship.attribute.xpos << "\n";
		savestream << saveship.attribute.ypos << "\n";
		savestream << saveship.attribute.map << "\n";
		savestream << saveship.attribute.geschwindigkeit << "\n";
		savestream << saveship.attribute.ausrichtung << "\n";
		savestream << saveship.attribute.prozentgesetzteSegel << "\n";
		savestream << saveship.attribute.sollprozentgesetzteSegel << "\n";
		savestream << saveship.attribute.steuergeschwindigkeit << "\n";
		savestream << saveship.attribute.steuerruderausrichtung << "\n";
		savestream << saveship.attribute.sollsteuerruderausrichtung << "\n";
		savestream << saveship.attribute.segelausrichtung << "\n";
		for(int i = 0; i < const_warenanzahl; i++)
		{
		savestream << saveship.Ladung.ware[i] << "\n";
		}
		savestream << saveship.Ladung.taler << "\n";
		savestream << saveship.Ladung.fuellung << "\n";
		savestream << saveship.Ladung.kapazitaet << "\n";
		savestream << "</schiff>" << "\n";
	}
	schiffsliste.removeLast();
	kontorklasse savekontor;
	foreach(savekontor, kontorliste)
	{
		savestream << "<kontor>" << "\n";
		savestream << savekontor.id << "\n";
		savestream << savekontor.stadt << "\n";
			for(int i = 0; i < const_warenanzahl; i++)
			{
				savestream << savekontor.Lager.ware[i] << "\n";
			}
		savestream << savekontor.Lager.taler << "\n";
		savestream << savekontor.Lager.fuellung << "\n";
		savestream << savekontor.Lager.kapazitaet << "\n";
		savestream << "</kontor>" << "\n";
	}


// 	savestream << hf->activeship.id;

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
hf = new hauptfenster();
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
	hf->minute = loadstream.readLine().toFloat();
	hf->stunde = loadstream.readLine().toInt();
	hf->tag = loadstream.readLine().toInt();	//5. Zeile
	hf->jahr = loadstream.readLine().toInt();
	hf->tageslaenge = loadstream.readLine().toInt();
	hf->windgeschwindigkeit = loadstream.readLine().toInt();
// qWarning() << "WV"<<hf->windgeschwindigkeit;

// 	loadstream >> hf->windrichtung ;
	hf->windrichtung = loadstream.readLine().toFloat();
// 	= loadstream.readLine();
// 	hf->activeship.id = loadstream.readLine().toInt();

	QString anbord = loadstream.readLine();		// 10. Zeile
	if(anbord == "0")
	{
		hf->anbord = false;
	}
	else
	{
		hf->anbord = true;
	}
	qWarning() << hf->anbord;
	hf->mapprops.stadtname = loadstream.readLine();
	hf->mapprops.mapname = loadstream.readLine();
// 	hf->mapprops.hintergrund = loadstream.readLine();
// 	hf->mapprops.handlingimg = loadstream.readLine();
// 	hf->mapprops.hoehe = loadstream.readLine().toInt();
// 	hf->mapprops.breite = loadstream.readLine().toInt();
// 	hf->mapprops.mapnord = loadstream.readLine();
// 	hf->mapprops.mapost = loadstream.readLine();
// 	hf->mapprops.mapsued = loadstream.readLine();
// 	hf->mapprops.mapwest = loadstream.readLine();

	hf->karteladen(hf->mapprops.mapname);


	stadtklasse loadstadt;
// 	foreach(savestadt, stadtliste)
// 	loadstream >> typindikator;
	typindikator = loadstream.readLine();
// 	qWarning() << "Typindikator" << typindikator;
	while(typindikator == "<stadt>")
	{
// 		loadstream >> "<stadt>" ;
		loadstadt.stadtname = loadstream.readLine();
		loadstadt.stadtbewohner = loadstream.readLine().toInt();
		for(int i = 0; i < const_warenanzahl; i++)
		{
			loadstadt.stadtwaren.ware[i] = loadstream.readLine().toInt();
			if(i<5)
			{
				loadstadt.hproduktion[i] = loadstream.readLine().toInt();
				loadstadt.mproduktion[i] = loadstream.readLine().toInt();
				loadstadt.nproduktion[i] = loadstream.readLine().toInt();
			}
		}
		loadstadt.stadtwaren.taler = loadstream.readLine().toInt();
		loadstadt.stadtwaren.kapazitaet = loadstream.readLine().toInt();
		stringbuffer = loadstream.readLine();
// 						 	qWarning() << "\n\tStringbuffer:" << stringbuffer;
		stadtliste << loadstadt ;
		typindikator = loadstream.readLine();
// 		qWarning() << "Typindikator" << typindikator << stadtliste.size();

	}

	schiffsklasse loadship;
	while(typindikator == "<schiff>")
	{
		loadship.id = loadstream.readLine().toInt();	/*qWarning() << "ID"<<loadship.id;*/
		loadship.schiffsname = loadstream.readLine();
		loadship.attribute.xpos = loadstream.readLine().toInt();
		loadship.attribute.ypos = loadstream.readLine().toInt();
		loadship.attribute.map = loadstream.readLine();	
		loadship.attribute.geschwindigkeit = loadstream.readLine().toInt();
		loadship.attribute.ausrichtung = loadstream.readLine().toFloat();
		loadship.attribute.prozentgesetzteSegel = loadstream.readLine().toFloat();
		loadship.attribute.sollprozentgesetzteSegel = loadstream.readLine().toFloat();
		loadship.attribute.steuergeschwindigkeit = loadstream.readLine().toInt();
		loadship.attribute.steuerruderausrichtung = loadstream.readLine().toFloat();
		loadship.attribute.sollsteuerruderausrichtung = loadstream.readLine().toFloat();
		loadship.attribute.segelausrichtung = loadstream.readLine().toFloat();
		for(int i = 0; i < const_warenanzahl; i++)
		{
			loadship.Ladung.ware[i] = loadstream.readLine().toUShort();
// 			qWarning() << "Ware"<<i <<loadship.Ladung.ware[i];
		}
		loadship.Ladung.taler = loadstream.readLine().toInt();
		loadship.Ladung.fuellung = loadstream.readLine().toInt();
		loadship.Ladung.kapazitaet = loadstream.readLine().toInt();
		stringbuffer = loadstream.readLine();
		schiffsliste << loadship;
		typindikator = loadstream.readLine();
	}
/*	hf->activeship.id = loadstream.readLine().toInt();*/
// 	qWarning() << "Schiff belegt" << hf->activeship.id << loadship.id ;
	hf->activeship = loadship;
	kontorklasse loadkontor;
	while(typindikator == "<kontor>")
	{
		loadkontor.id = loadstream.readLine().toInt();
		loadkontor.stadt = loadstream.readLine();

		for(int i = 0; i < const_warenanzahl; i++)
		{
			loadkontor.Lager.ware[i] = loadstream.readLine().toInt();
		}
		loadkontor.Lager.taler = loadstream.readLine().toInt();
		loadkontor.Lager.fuellung = loadstream.readLine().toInt();
		loadkontor.Lager.kapazitaet = loadstream.readLine().toInt();
		stringbuffer = loadstream.readLine();
		kontorliste << loadkontor;
		typindikator = loadstream.readLine();

	}
	spielfensteraufbau();
// 	qWarning() << "Map" << loadship.attribute.map;
// 	qWarning() << "SV:"<< loadship.attribute.geschwindigkeit;

	hf->testschiff->setPos(hf->activeship.attribute.xpos, hf->activeship.attribute.ypos);
// 	hf->testschiff->setPos(300,300);
// 	qWarning() << "Ausrichtung:"<< hf->activeship.attribute.ausrichtung << "XPos" << hf->activeship.attribute.xpos << "YPos" << hf->activeship.attribute.ypos;
	if(hf->anbord)
	{
	QTransform t;
	const int w = hf->testschiff->boundingRect().width()/2;
	const int h = hf->testschiff->boundingRect().height()/2;

	hf->activeship.schiffbreite = 2 * w;
	hf->activeship.schifflange = 2 * h;

	t.translate( w, h );
	t.rotateRadians(- hf->activeship.attribute.ausrichtung);
	t.translate( -w, -h );
	hf->testschiff->setTransform( t );

	hf->show();
	hf->centerOn(hf->testschiff);
	hf->starttimer();
	}
// 	}

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