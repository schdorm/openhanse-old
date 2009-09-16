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

#include "gesamtbild.h"
#include "dataclass.h"
#include "settings.h"
#include "shipdata.h"

#include "stadtklasse.h"

#include <QtCore/QFile>
#include <QtCore/QXmlStreamReader>
// #include <QtCore/QDir>

#include <QtCore/QtDebug>

#include <QtGui/QDialog>
// #include <QtCore/QSignalMapper>
#include <QtGui/QGroupBox>
#include <QtGui/QPushButton>
// #include <QtGui/QProgressBar>
// #include <QtGui/QSlider>
#include <QtGui/QGridLayout>

// #include <QtGui/QScrollArea>
/*
void gesamtbild::initGameData()
{
// GAMEDATA = new DataClass();

}*/

#include "konsole.h"


void gesamtbild::startNewGame()
{
// 	GAMEDATA = new DataClass();
// 	CityClass *activeCity = new CityClass();
	spielbool=true;
//  	QFile file("");		//Map-XML-Lesen
//  	if(file.exists())
	{
	QList<int> hproductionlist;
	QList<int> mproductionlist;
	QList<int> lproductionlist;

// 	int hproduction[const_warenanzahl];
// 	int mproduction[const_warenanzahl];
// 	int lproduction[const_warenanzahl];
	QString cityname;
// 		qWarning() << "Datei existiert" ;
// 		for(int i = 0; i<5 ; i++)
// 		{
// 			hproduction[i]=-1;
// 			mproduction[i]=-1;
// 			lproduction[i]=-1;
// 		}


		enum stati	{
				null,
				stadttoken,
				city_name,
				city_mproduction,
				city_hproduction,
				city_lproduction,
				} status = null;	// status als dieses enum: zeigt an, was fuer ein Wert als naechstes ausgelesen wird

// 		int hz = 0;		//Zaehlvariablen fuer die jeweiligen Produktionsarrays
// 		int mz = 0;
// 		int nz = 0;

		QFile file(":maps/stadtliste.ohc");
		file.open(QIODevice::ReadOnly | QIODevice::Text);
		QXmlStreamReader reader(&file);
		while (!reader.atEnd()) 
		{
		reader.readNext();
		switch(reader.tokenType())
		{
			case QXmlStreamReader::StartElement:
			{
			qWarning() << "Start:\t" <<reader.qualifiedName().toString();
				if(reader.qualifiedName().toString() == "list")
				{
				break;
				}
				if(reader.qualifiedName().toString() == "city")
				{
				status=stadttoken;
				break;
				}
				if(reader.qualifiedName().toString() == "cityname")
				{
				status=city_name;
				break;
				}

				if(reader.qualifiedName().toString() =="hproduction")
				{
				status=city_hproduction;
				break;
				}
				if(reader.qualifiedName().toString() =="mproduction")
				{
				status=city_mproduction;
				break;
				}
				if(reader.qualifiedName().toString() =="lproduction")
				{
				status=city_lproduction;
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
				qWarning() << "\n\tChars:" <<reader.text().toString() << "\n";
				//Tags ohne Inhalt - nur mit Unterkategorien
				if(reader.text().toString().simplified().isEmpty()){break;};
				switch(status)
				{
				case stadttoken:
					break;
				case city_name:
				{
				cityname = reader.text().toString();
				qWarning() << "\tStadt: " << cityname;
				break;
				}

				case city_hproduction:
				{
				hproductionlist << reader.text().toString().toInt();
				qWarning() << "\tHohe Produktion: " << hproductionlist.last() << "(wird viel produziert)";
				break;
				}

				case city_mproduction:
				{
				mproductionlist << reader.text().toString().toInt();
				qWarning() << "\tMittlere Produktion: " << mproductionlist.last() << "(wird maessig viel produziert)";
				break;
				}

				case city_lproduction:
				{
				lproductionlist << reader.text().toString().toInt();
				qWarning() << "\tNiedrige Produktion: " << lproductionlist.last() << "(wird wenig produziert)";
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
				if(reader.qualifiedName().toString() == "stadt" && !cityname.isEmpty())
				{
 				CityClass activeCity(cityname, hproductionlist, mproductionlist, lproductionlist);
				activeCity.init();
				GAMEDATA->addCity(activeCity);
				OHDebug(activeCity.cityname().append(" zur Liste hinzugefuegt"));
// 				activeCity->reset();
				}
				status=null;
				break;

			}
			default:
				break;

		}
		}
	
		if (reader.hasError()) {
		OHDebug(reader.errorString());
	}
}

	OHDebug("Stadtliste erzeugt");
// 	if(!load)
// 	{
	schwierigkeitsgrad = schwierigkeitsauswahl->currentIndex();
	OHDebug(QString("Schwierigkeitsgrad %1").arg(schwierigkeitsgrad));
	delete schwierigkeitsauswahl;
	schwierigkeitsauswahl = 0;
// 	}


	OHDebug("vor Spielfenster aufgebaut");

 	gameview = new hauptfenster(/*GAMEDATA, currentSettings*/);

	spielfensteraufbau();
	qWarning() << "Spielfenster aufgebaut";
// 	gameview->setDataClass(GAMEDATA);
	qWarning() << "Data set";
// 	TERMINAL->gameviewgametime = gameviewgametime;
// 	TERMINAL->debug("Timepointer set");
	gameview->schwierigkeit = schwierigkeitsgrad;
	qWarning() << "Schwierigkeitsgrad:" << schwierigkeitsgrad;
/// 	GAMEDATA->active_ship->filename = ":img/schiffe/schiff_gerade_skaliert2.png";
	GAMEDATA->activeShip()->setControlDifficulty(schwierigkeitsgrad);
	
//  	GAMEDATA->currentMap() = new Map();

	OHDebug("GAMEDATA->currentMap()->loadStartMap(\"testmap001.ohm\");");
	
	GAMEDATA->currentMap()->loadStartMap("testmap001.ohm");
	gameview->karteladen(Map::null);
// 	gameview->karteladen("testmap001.ohm");
// 	gameview->testschiff->setPos(1500,900);
/// 	GAMEDATA->active_ship->graphicsitem->setPos(1500, 900);
/// 	gameview->centerOn(GAMEDATA->active_ship->graphicsitem);
//  	qWarning() << "StartTimer";
	PositioningStruct destination_pos;
	destination_pos.mapcoords = GAMEDATA->currentMap()->coordinates();
	destination_pos.generic_position = QPoint(1500, 800);
	GAMEDATA->activeShip()->setPos(destination_pos);
	
	gameview->starttimer(1000/SETTINGS->fps());
	
	qWarning() << "Timer gestartet";
// 	gameview->show();
	aktiv=true;
	GAMEDATA->startTimer();
}

void gesamtbild::spielfensteraufbau()
{
	qWarning() << "spielfensteraufbau";
	QGridLayout *gridlayout = new QGridLayout(this);		//Fuer Hauptfenster

	gameview->setParent(this);
// 	gameview->resize(700,700);
	gameview->move(0,0);
	gameview->setFocus();
	gridlayout->addWidget(gameview,0,0,1,1);

// 	{
// 	QImage *img = new QImage(":img/sonstige/mapfarbdef.png");
// 	gameview->schiffbar = img->pixel(0,0);
// 	gameview->anlegestelle = img->pixel(0,1);
// 	gameview->strand_weich = img->pixel(0,2);
// 	gameview->strand_hart = img->pixel(0,3);
// 	gameview->nschiffbar = img->pixel(0,4);
// 	delete img;
// 	}
// 	QImage testimg = QImage(":img/testimg/gros.gif");


	qWarning() << "SFA1";
	menupanel = new SeaTabPanel();
// 	menupanel->create();
	qWarning() << "created";
// 	menupanel->setParent(this);
	gridlayout->addWidget(menupanel,0,1,1,1);

	qWarning()<< "gameview->setFocus(); (gb->spiel)";


// // 	qWarning() << "Vor Ladungszeugs";

	for(int i = 0; i < const_warenanzahl; i++)
 	{
		menupanel->ware[i]->setText(QString("%1").arg(GAMEDATA->activeShip()->cargo().ware[i]));
 	}

// // 	fuellung->setText(QString("Belegt: %1 von %2").arg(GAMEDATA->active_ship->cargo.gesamtladung, GAMEDATA->active_ship->ladekapazitaet));
	{
 	menupanel->taler->setText(QString("%1").arg(GAMEDATA->activeShip()->cargo().taler).prepend(tr("Money: ")));
	QString flstring = QString("%1").arg(GAMEDATA->activeShip()->cargo().fuellung);
	flstring.append(QString("/%1 belegt").arg(GAMEDATA->activeShip()->cargo().kapazitaet));
	menupanel->fuellung->setText(flstring);
	}
// 	menupanel->setGameData(GAMEDATA);
	menupanel->show();

	gridlayout->setColumnStretch(0,7);
	gridlayout->setColumnStretch(1,2);

	connect(gameview,SIGNAL(destroyed()),this,SLOT(close()));

	connect(gameview,SIGNAL(handel()),this,SLOT(handel()));
// 	connect(gameview,SIGNAL(handel()),gameview,SLOT(hide()));

	connect(gameview, SIGNAL(sig_anlegbar(bool)), menupanel->anlegen,SLOT(setEnabled(bool)));

// 	connect(GAMEDATA, SIGNAL(sig_newDay(int)), this, SLOT(produktion(int)));

	connect(gameview, SIGNAL(SIGgeschwindigkeit(int)), menupanel->geschwindigkeitsanzeige,SLOT(setValue(int)));

	connect(gameview, SIGNAL(zeitsig()),this,SLOT(zeitanzeige()));

	connect(gameview, SIGNAL(savesig()),this,SLOT(speicherndialog()));

	connect(gameview, SIGNAL(menusig()), this, SLOT(spielmenu()));

	connect(menupanel->anlegen, SIGNAL(clicked()), this, SLOT(landmenu()));
	connect(menupanel->schuss, SIGNAL(clicked()), gameview, SLOT(schuss()));
	connect(menupanel->anlegen, SIGNAL(clicked()), gameview, SLOT(landgang()));
// 	connect(anlegen, SIGNAL(clicked()), anlegen, SLOT(hide()));
// 	connect(menupanel->anlegen, SIGNAL(clicked()), menupanel->ablegen, SLOT(show()));

// 	connect(menupanel->ablegen, SIGNAL(clicked()), this, SLOT(seemenu()));
// 	connect(menupanel->ablegen, SIGNAL(clicked()), gameview, SLOT(ablegen()));
// 	connect(ablegen, SIGNAL(clicked()), anlegen, SLOT(show()));
// 	connect(ablegen, SIGNAL(clicked()), ablegen, SLOT(hide()));

	connect(menupanel->geschwindigkeitsregler,SIGNAL(valueChanged(int)), gameview, SLOT(segelsetzen(int)));
	
	TERMINAL->resize(width(), height()/2);
	TERMINAL->setParent(this);
	TERMINAL->setWindowFlags(Qt::Popup);
	TERMINAL->hide();
	connect(gameview, SIGNAL(sig_konsole()), TERMINAL, SLOT(show()));
// 	connect(TERMINAL, SIGNAL(sig_loadMap(QString)), gameview, SLOT(karteladen(QString)));
	connect(TERMINAL, SIGNAL(sig_command(QString)), this, SLOT(execCommand(QString)));
}



void gesamtbild::zeitanzeige(/*int dora, int hin, int may*/)
{
			qWarning() << "Zeit";


			QDialog *zeitw = new QDialog(this);
			QVBoxLayout layout(zeitw);
			QLabel *anzeige = new QLabel(tr("Time: Day %1,").arg(GAMEDATA->gametime().day()).append(QString("%1 hours").arg(GAMEDATA->gametime().hour())), zeitw);

// 			anzeige->setText(anzeige->text().append(QString(", %2 Uhr %3").arg( gameview->stunde, gameview->minute)));gameview->stunde
// 			qWarning() << anzeige->text().append(QString(", %2 Uhr %3").arg( gameview->stunde, gameview->minute));

			QPushButton *ok = new QPushButton("Ok",zeitw);
			ok->move(50, 50);
			layout.addWidget(anzeige);
			layout.addWidget(ok);
// 			zeitw->setGeometry(width()/2,height()/2,200,100);
			zeitw->setLayout(&layout);
			zeitw->setAutoFillBackground(true);
			zeitw->move(gameview->width()/2,gameview->height()/2);
  			zeitw->raise();
			zeitw->show();

			connect(ok, SIGNAL(clicked()), gameview, SLOT(endePause()));
			connect(ok, SIGNAL(clicked()), zeitw, SLOT(close()));
			connect(ok, SIGNAL(clicked()), zeitw, SLOT(deleteLater()));
}


void gesamtbild::spielmenu()
{
gameview->startPause();
gameview->setEnabled(false);
menupanel->setEnabled(false);
aktiv = false;

OHDebug("Spielmenu");
// gameview->hide();

QWidget *menuw = new QWidget(this);
QVBoxLayout layout;
QGroupBox *gb = new QGroupBox(menuw);
QPushButton *fortfahren = new QPushButton(tr("Resume"),menuw);
QPushButton *speichern = new QPushButton(tr("Save"),menuw);
QPushButton *laden = new QPushButton(tr("Load"),menuw);
QPushButton *verlassen = new QPushButton(tr("Quit"),menuw);

layout.addWidget(fortfahren);
layout.addWidget(speichern);
layout.addWidget(laden);
layout.addWidget(verlassen);

connect(fortfahren, SIGNAL(clicked()), menuw, SLOT(close()));
// connect(fortfahren, SIGNAL(clicked()), gameview, SLOT(endePause()));
connect(fortfahren, SIGNAL(clicked()), this, SLOT(aktivieren()));

connect(speichern, SIGNAL(clicked()), menuw, SLOT(close()));
connect(speichern, SIGNAL(clicked()), this, SLOT(aktivieren()));
connect(speichern, SIGNAL(clicked()), this, SLOT(speicherndialog()));

connect(verlassen, SIGNAL(clicked()), this, SLOT(close()));

// QSignalMapper *sigm = new QSignalMapper(this);
// sigm->setMapping(fortfahren, true);
// connect(fortfahren, SIGNAL(clicked()), this, SLOT(setEnabled(bool)));
// connect(sigm, SIGNAL(mapped(int)), gameview, SLOT(setEnabled(int)));
// connect(sigm, SIGNAL(mapped(int)), menupanel, SLOT(setEnabled(int)));


gb->setLayout(&layout);
menuw->setGeometry(width()/2-200,height()/2-200,200,400);
menuw->show();
menuw->raise();
}


void gesamtbild::aktivieren()
{
aktiv=true;
gameview->setEnabled(true);
menupanel->setEnabled(true);
gameview->endePause();
}


void gesamtbild::seemenu()
{
// 	tab[3]->hide();
// 	tab[4]->hide();
// 	tab[5]->hide();
// menupanel->clear();
// menupanel->removeTab(0);
// menupanel->removeTab(1);
// menupanel->removeTab(2);

	// int index;
	// 	index = menupanel->addTab(tab[0],QIcon(":img/icons/kiste_icon_alpha_hell.png") , tr("L"));
	// 	menupanel->setTabToolTip(index, tr("Warenladung des Schiffes"));
	// 
	// 	index = menupanel->addTab(tab[1],QIcon(":img/icons/steuerrad01.png"), tr("S"));
	// 	menupanel->setTabToolTip(index, tr("Steuerung des Schiffes"));
	// 
	// 	index = menupanel->addTab(tab[2], "B");
	// 	menupanel->setTabToolTip(index, tr("Besatzung des Schiffes"));

// menupanel->setTabText(0,tr("L"));
// menupanel->setTabIcon(0, QIcon(":img/icons/kiste_icon_alpha_hell.png"));
// menupanel->setTabToolTip(0, tr("Warenladung des Schiffes"));
// 
// 
// menupanel->setTabText(1, tr("S"));
// menupanel->setTabIcon(1, QIcon(":img/icons/steuerrad01.png"));
// menupanel->setTabToolTip(1, tr("Steuerung des Schiffes"));
// 
// menupanel->setTabText(2, tr("B"));
// 	menupanel->setTabToolTip(index, tr("Besatzung des Schiffes"));


}

void gesamtbild::landmenu()
{
// menupanel->landmenu();
execCommand(QString("hide sidemenu"));		//lets the sidebar disappear, isn't needed for a landwalk.

gameview->landing();
// 	tab[0]->hide();
// 	tab[1]->hide();
// 	tab[2]->hide();
// menupanel->clear();
// menupanel->removeTab(0);
// menupanel->removeTab(1);
// menupanel->removeTab(2);

// int index;
// 	index = menupanel->addTab(tab[3],QIcon(":img/icons/steuerrad01.png") , tr("Schiffsmenu"));
// 	menupanel->setTabToolTip(index, tr("Schiffsaktionen und -befehle verwalten"));

// 	index = menupanel->addTab(tab[4], tr("Baumenu"));
// 	menupanel->setTabToolTip(index, tr("Gebaude bauen"));

//  	index = menupanel->addTab(tab[5],QIcon(""), tr("blah"));
//  	menupanel->setTabToolTip(index, tr("irgendwas"));
// 

// tab[3]->show();
// tab[4]->show();
// tab[5]->show();
}
